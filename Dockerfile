FROM ubuntu:18.04

RUN apt update
RUN apt install build-essential -y
RUN apt install valgrind -y

COPY . .