#!/bin/sh

# TAG NAME (Change as per convinience)
tag="cppdsa"
# SCRIPT NAME
run_script="run.sh"

# Build the image
docker build -t "$tag" .

# Run the image
docker run "$tag" ./$run_script "$@"