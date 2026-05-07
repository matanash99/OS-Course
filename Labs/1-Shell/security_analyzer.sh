#!/bin/bash

if [ $# -lt 1 ]; then 
    echo "Wrong amount of arguments."
    exit 1
fi

file_name=$1

if [ -f "$file_name" ]; then
    grep -E "ATTACK|ERROR" "$file_name" | cut -d":" -f2 | sort -r | uniq

else
    echo "File not found!"
    exit 1
fi

echo "Summary: $(sort "$file_name" | uniq | wc -l) unique incidents found."


