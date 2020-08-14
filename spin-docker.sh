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

if [ $? -ne 0 ]; then
    echo "Error building the image"
    exit 1
fi

# Check if the container already exists
# if the container already exists then just start the container
# if not then create the container and then start it
if [ ! "$(docker ps -aq -f name=$tag)" ]; then
	printf "Creating a new container... "
	docker create -it -v $(pwd):/app --name "$tag" "$tag"
fi

printf "Starting the container... "
docker start "$tag"

# Enter the container with custom command
docker exec -it "$tag" ./$run_script "$@"

# Stop the container after using it
printf "Stopping... "
docker stop "$tag"