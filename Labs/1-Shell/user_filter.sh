#!/bin/bash
file_name="users.txt"

if [ -f "$file_name" ]; then
    > admins_list.csv
    grep "Engineering" "$file_name" | grep "Admin" | while IFS= read -r line; do
        name=$(echo "$line" | cut -d" " -f1)
        id=$(echo "$line" | cut -d" " -f4)
        last_login=$(echo "$line" | cut -d" " -f5)
        echo "$name,$id,$last_login" >> admins_list.csv
    done

else
    echo "File not found!"
    exit 1
fi

chmod 600 admins_list.csv

echo "Filer complete. File permissions updated."