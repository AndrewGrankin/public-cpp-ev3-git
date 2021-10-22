#!/bin/bash

# variables definition 
file_name="ev3_cpp_robo_arm_help3r_client"
current_location=`pwd`

# removing the old binary file if it exists
echo "removing the old binary file if it exists..."
if [[ -e ${current_location}/${file_name} ]]
then
   rm ${current_location}/${file_name}
fi

# source code compilation
echo "compiling the ${file_name}.cpp and ev3dev.cpp files..."
arm-linux-gnueabi-g++ -static ../../ev3dev.cpp ${file_name}.cpp -o ${file_name}

# moving binary file to the brick
if [[ -e ${current_location}/${file_name} ]]
then 
   echo "compilation is ok"
   echo "moving compiled file to the brick..."
   scp ${file_name} robot@10.42.0.133:~/scripts/cpp
else
   echo "compilation is NOT OK"
fi
