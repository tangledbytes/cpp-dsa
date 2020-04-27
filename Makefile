OBJS = main.o
CC = clang++
CFLAGS = -Wall -c -std=c++17
LFLAGS = -Wall -std=c++17
OUTFILE = a.out

all: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(OUTFILE)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	\rm *.o $(OUTFILE)