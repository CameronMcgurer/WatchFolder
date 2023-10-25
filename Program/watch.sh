#!/bin/bash

# check the number of arguments
if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <watch_folder> <version> <output_folder>"
    exit 1
fi

# build all executables
gcc ./progV1.c -o progV1
gcc ./progV2.c -o progV2
gcc ./progV3.c -o progV3

watch_folder="$1"
version_index="$2"
output_path="$3"

# check if output file path end in a '/' and adds one if it doesnt
if [[ "$output_path" != */ ]]; then
  output_path="$output_path/"
fi

# create the watch folder if it doesnt already exist
mkdir -p "$watch_folder"

initial_contents=$(find "$watch_folder")

dat_files=()

while true; do
    # checks for file updates every 10 seconds  
    sleep 10
    
    current_contents=$(find "$watch_folder")
    if [ "$current_contents" != "$initial_contents" ]; then
        initial_contents="$current_contents"

        # check in folder and subfolders for .dat files and add them to array
        dat_files=($(find "$watch_folder" -type f -name "*.dat"))

        "./progV$version_index" "$output_path" "${dat_files[@]}"
    fi
done
