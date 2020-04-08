#!/bin/bash

# ================= LOG FUNCTION ====================================================
log ()
{
    echo "[CPP RUNNER]: $@"
}

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
            --*) log "Invalid flag!"; close 1
            ;;
            *) in_file=$i
            ;;
        esac
    done
}

# ===================================================================================
close()
{
    log "EXITTED WITH CODE $1"
    exit $1
}

# ===================================================================================
# Default output filename
out_file="a.out"
# Default memory check
no_mem=0
# Default file name
in_file="main.cpp"
# ===================================================================================

echo ""
echo "=================== [CPP RUNNER] ========================"
echo ""

# Setup
check_argument "$@"

# Log compile process
log "Compiling $in_file..."

# Compile the file
g++ -Wall -pedantic -std=c++17 -o "$out_file" $in_file

# Exit if above process didn't suceeded properly
if [ $? -ne 0 ]; then close 1; fi

# Log running process
log "Running $in_file..."

if [ $no_mem -eq 1 ]; then
    log "Opted no memory leak checks"
    ./$out_file
    close 0
fi

# Check if valgrind exists
if command -v valgrind >/dev/null 2>&1; then
    valgrind --leak-check=full ./$out_file
else
    log "Failed to find valgrind... skipping memory checks"
    ./$out_file
fi

echo ""
close 0