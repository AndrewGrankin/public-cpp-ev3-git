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
    int max_rsp, num_rsp;
    int dev_id, socket, len, flags;
    int i;
    char addr[19] = {0};
    char name[248] = {0};

    dev_id = hci_get_route(NULL);
    socket = hci_open_dev(dev_id);
    if (dev_id < 0 || socket < 0) 
    {
        perror("opening socket");
        exit(1);
    }

    len = 8;
    max_rsp = 255;
    flags = IREQ_CACHE_FLUSH;
    ii = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));

    num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, flags);
    if (num_rsp < 0)
    {
        perror("hci_inquiry");
    }

    for (i = 0; i < num_rsp; i++)
    {
        /*
            typedef struct {
                uint8_t b[6];
            } __attribute__((packed)) bdaddr_t;
            -----------------------------------------
            "bdaddr_t" - this structure used to specify a Bluetooth device address.
            -----------------------------------------
            Two functions to convert between strings and bdaddr_t structures:
            int str2ba(const char* str, bdaddr_t* ba);
            int ba2str(const bdaddr_t*, char* str);

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