CC = gcc
OPT = -O3
CFLAGS = -Wall -Wpedantic -Wextra -g $(OPT)
BINARY=main
FLAGS= -lm
OBJECTS=main.o sound.o

$(BINARY): $(OBJECTS)
	$(CC) $(CFLAGS) $(FLAGS) -o $@ $^

%.o:%.c
	$(CC) $(CFLAGS) $(FLAGS) -c -o $@ $^

clean:
	rm -rf $(BINARY) $(OBJECTS)
