FROM ubuntu:18.04

WORKDIR /app

RUN apt update
RUN apt install build-essential -y
RUN apt install valgrind -y
RUN apt install inotify-tools -y

COPY . .