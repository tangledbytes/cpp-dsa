FROM ubuntu:18.04

WORKDIR /app

RUN apt update
RUN apt install build-essential valgrind inotify-tools -y
RUN apt install clang -y
RUN apt autoremove

ENTRYPOINT [ "/bin/bash" ]