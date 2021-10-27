#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

#include <iostream>

int main(int argc, char** argv)
{
    std::cout << "Hello Bluetooth!" << std::endl;
    
    inquiry_info* ii = NULL;
    int max_responses, num_responses;
    int device_id, socket, query_length, flags;
    int i;
    char addr[19] = {0};
    char name[248] = {0};

    /*
        Local Bluetooth adapters are assigned identifying numbers starting with 0, and a program
        must sepcify which adapter to use when allocating system resources. Usually, there is only
        one adapter or it doesn't matter which one is used. Passing NULL to hci_get_route will
        retreive the resource number of the first available Bluetooth adapter.
        -------------------------------------------
        int hci_get_route(bdaddr_t* bdaddr); // or int hci_devid(char* str);
        int hci_open_dev(int dev_id);
        -------------------------------------------
        Most Bluetooth operations require the use of an open socket. hci_open_dev is a function that
        opens a Bluetooth socket with the specified resource number. This socket represents a connection
        to the microcontroller on the spedified local Bluetooth adapter, and not a connection to a 
        remote Bluetooth device. Performing low level Bluetooth operations involves sending commands
        directly ot the microcontroller with this socket.
    */
    device_id = hci_get_route(NULL); // retrieves the resource number of the first available Bluetooth adapter.
    socket = hci_open_dev(device_id); // opens a socket with used device_id to the microcontroller of local adapter.
    if (device_id < 0 || socket < 0) 
    {
        perror("opening socket");
        exit(1);
    }

    query_length = 8;
    max_responses = 255;
    flags = IREQ_CACHE_FLUSH;
    /*
        void* malloc(size_t size);
        --------------------------------------------------
        The malloc function allocates a memory block of at least size bytes. The block may be larger than
        size bytes because of the space that's required for alignment and maintenance information.
    */
    ii = (inquiry_info*)malloc(max_responses * sizeof(inquiry_info));

    /*
        After choosing the local Bluetooth adapter to use and allocating system resources, the program
        is ready to scan for nearby Bluetooth devices. hci_inquiry performs a Bluetooth device discovery
        and returns a list of detected devices and some basic information about them in the variable ii.
        On error, it returns -1 and sets errno accordingly.
        --------------------------------------------------
        int hci_inquiry(int dev_id, int len, int max_rsp, const uint8_t* lap, inquiry_info** ii, long flags);
        --------------------------------------------------
        hci_inquiry is one of the few functions that requires the use of a resource number instead of an
        open socket, so we use the dev_id (device_id) returned by hci_get_route. The inquiry lasts for at 
        most 1.28 * len (query_length) seconds, and at most max_rsp (max_responses) devices will be returned
        in the output parameter ii, which must be large enough to accommodate max_rsp (max_responses)
        results. It suggested using a max_rsp (max_responses) of 255 for a standard 1.28*8=10.24 seconds
        inquiry. rsp stands for response.
    */
    num_responses = hci_inquiry(device_id, query_length, max_responses, NULL, &ii, flags);
    if (num_responses < 0)
    {
        perror("hci_inquiry");
    }

    for (i = 0; i < num_responses; i++)
    {
        /*
            typedef struct {
                uint8_t b[6];
            } __attribute__((packed)) bdaddr_t;
            -----------------------------------------
            "bdaddr_t" - this structure used to specify a Bluetooth device address.
            *****************************************
            Two functions to convert between strings and bdaddr_t structures:
            -----------------------------------------
            int str2ba(const char* str, bdaddr_t* ba);
            int ba2str(const bdaddr_t*, char* str);
            -----------------------------------------
            str2ba takes a string in form "XX:XX:XX:XX:XX:XX" where XX is a hex num in 48-bit address, and
            packs it into a 6-byte bdaddr_t. ba2str does exactly the opposite
        */
        ba2str(&(ii + i)->bdaddr, addr);
        memset(name, 0, sizeof(name));
        if (hci_read_remote_name(socket, &(ii + i)->bdaddr, sizeof(name), name, 0) < 0)
        {
            strcpy(name, "[unknown]");
        }
        printf("%s %s\n", addr, name);
    }

    free(ii);
    close(socket);
    return 0;
}