
CC = gcc
OFLAGS = -lm
CFLAGS = -Wall -ansi
SRC = $(wildcard *.c)
OBJ = $(SRC: .c=.o)
EXEC = generator

all: $(EXEC)

generator: $(OBJ)
	$(CC) -o $@ $^ $(OFLAGS)

%.o:%.c PeriodicTask.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o $(EXEC) *.txt run Flag 



