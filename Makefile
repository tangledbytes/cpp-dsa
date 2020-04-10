main: main.o
	g++ main.o -o a.out

main.o: main.cpp
	g++ -c -Wall -pedantic main.cpp