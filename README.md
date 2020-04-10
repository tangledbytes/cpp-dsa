# CPP DSA (Data structures and algorithms)

The repository contains implementations of very basic data structures and algorithms.

This repository also contains several bash script which can be used if the user has docker installed. The advantage to use the script is that
it enables monitoring of the files inside the docker container along with memory leak checks without manually repeating the commands. Hit
save and it would simply re run the compile and execution process for you.

To see how to use the script:

If running it for the first time, give it execution permission
```
chmod +x run.sh
```

Pass in help flag to get the help message
```
./run.sh --help
```

### NOTE: The spin-docker.sh is a POSIX compliant script and hence should be able to run on most *nix evironments provided docker is installed and is added to sudo user group
