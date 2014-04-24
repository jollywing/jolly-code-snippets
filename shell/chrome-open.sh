#! /bin/bash

chrome_command="google-chrome"

if [ $# -ne 1 ]; then
    echo "Usage: $0 <pdf-file>"
    exit 1
fi

# get the absolute path of the file
absolute_path=`readlink -e "$1"`

# if the file exist, open the file with chrome
if [ -z "$absolute_path" ]; then
    echo "$1 does not exist!"
    exit 1
else
    file_url="file://$absolute_path"
    $chrome_command "$file_url"
fi

