#!/bin/sh

# TAG NAME (Change as per convinience)
tag="cppdsa"
# SCRIPT NAME
run_script="run.sh"

# Make sure docker exists
if test command -v docker > /dev/null 2>&1; then
    echo "Docker not found"
    exit 1
fi

# Build the image
docker build -t "$tag" .

echo "\n=================== [CPP RUNNER] ======================== \n"
# Run the image
docker run "$tag" ./$run_script "$@"

echo "\n[CPP RUNNER]: EXITTED WITH CODE $?"