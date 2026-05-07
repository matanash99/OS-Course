#!/bin/bash

if [ $# -lt 1 ]; then 
    echo "Wrong amount of arguments."
    exit 1
fi

name=$1
num_lines=$(grep "$name" users.txt | wc -l)

if [ $num_lines -eq 0 ]; then
    echo "User not found"
    exit 1
fi

id=$(grep "$name" users.txt | head -n 1 | cut -d " " -f4)

error_count=$(grep "ID:$id" raw_data.txt | grep "ERROR" | wc -l)

echo "User: $name | ID: $id | Total Errors: $error_count"
