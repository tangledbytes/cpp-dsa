#!/bin/bash

# ===================================== FUNCTIONS ===========================================

# Import coloring script
. bash-colors.sh

# Logs the argument
log ()
{
    echo -e "$(c 0gB)[CPP RUNNER]:$(c) $(c 0gL)$@$(c)"
}

# Log warning
warn()
{
    echo -e "$(c 0yB)[CPP RUNNER]:$(c) $(c 0yL)$@$(c)"
}

# Log error
error()
{
    echo -e "$(c 0rB)[CPP RUNNER]:$(c) $(c 0rL)$@$(c)"
}

# Banner
banner()
{
    echo -e "$(c gB)$@$(c)"
}

# Parses the arguments passed
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
            --watch=*| -w=*)
                watch=$VALUE
            ;;
            --*) log "Invalid flag!"; close 1
            ;;
            *) in_file=$i
            ;;
        esac
    done
}

# Closes with a certain exit code
close()
{
    if [ $# -eq 0 ]; then
        log "EXITTING..."
        exit 0;
    else
        log "EXITTED WITH CODE $1"
        exit $1
    fi
}

# Runs the cpp code
cpp_runner()
{
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
        warn "Opted no memory leak checks"
        ./$out_file
    else
        # Check if valgrind exists
        if command -v valgrind >/dev/null 2>&1; then
            valgrind --leak-check=full ./$out_file
        else
            warn "Failed to find valgrind... skipping memory checks"
            ./$out_file
        fi
    fi
}

# =============================== GLOBAL VARIABLES ==================================
# Default output filename
out_file="a.out"

# Default memory check
no_mem=0

# Default file name
in_file="main.cpp"

# Default file/directory to watch
watch=$in_file
# ===================================================================================

# Parse arguments
check_argument "$@"

# Check if inotify exists on the system/container
if command -v inotifywait >/dev/null 2>&1; then
    echo ""
    banner "=================== [CPP RUNNER] ========================"
    echo ""
    
    log "Monitoring changes..."
    log "Watching $watch for changes..."
    while inotifywait -q -r -e modify $watch >/dev/null 2>&1; do
        cpp_runner "$@"
        echo ""
        log "Watching $watch for changes..."
    done
else
    warn "inotify not found"
    warn "Proceeding without monitoring"
    cpp_runner "$@"
fi