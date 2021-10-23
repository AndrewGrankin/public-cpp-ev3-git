#!/bin/bash

# variables definition 
file_name="simplescan"
current_location=`pwd`

# removing the old binary file if it exists
echo "removing the old binary file if it exists..."
if [[ -e ${current_location}/artifacts/${file_name} ]]
then
   rm ${current_location}/artifacts/${file_name}
fi

# source code compilation
echo "compiling the ${file_name}.cpp"
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
