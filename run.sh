#!/bin/bash

# ================ Check if required argument was passed or not =====================
check_argument()
{
    for i in "$@"
    do
        VALUE=$(echo $i | awk -F= '{print $2}')
        case "$i" in
            --no-mem) no_mem=1
            ;;
            -o=*) out_file=$VALUE
            ;;
        esac
    done
}

# ===================================================================================
# Default output filename
out_file="a.out"
# Default memory check
no_mem=0
# ===================================================================================

# Setup
check_argument "$@"

# Log compile process
echo "[CPP RUNNER]: Compiling $1..."

# Compile the file
g++ -Wall -pedantic -std=c++17 -o "$out_file" $1

# Exit if above process didn't suceeded properly
if [ $? -ne 0 ]; then exit 1; fi

# Log running process
echo "[CPP RUNNER]: Running $1..."

if [ $no_mem -eq 1 ]; then
    echo "[CPP RUNNER]: Opted no memory leak checks"
    ./$out_file
    exit 0
fi

# Check if valgrind exists
if command -v valgrind >/dev/null 2>&1; then
    valgrind ./$out_file
else
    echo "[CPP RUNNER]: Failed to find valgrind... skipping memory checks"
    ./$out_file
fi
