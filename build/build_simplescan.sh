#!/bin/bash

# variables definition 
file_name="simplescan"
current_location=`pwd`

# removing the old binary file if it exists
echo "log: removing the old binary file if it exists..."
echo "checking file: ${current_location}/artifacts/${file_name}"
if [[ -e ${current_location}/artifacts/${file_name} ]]
then
   rm ${current_location}/artifacts/${file_name}
   echo "log: the file ${file_name} has been removed"
fi

# source code compilation
echo "log: compiling the ${file_name}.cpp ..."
g++ -g ../bluetooth/${file_name}.cpp -o artifacts/${file_name} -lbluetooth