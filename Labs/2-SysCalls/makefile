# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Default target: builds all four projects
all: my_cat my_reverse my_cp my_chmod

# Build targets
my_cat: my_cat.c
	$(CC) $(CFLAGS) my_cat.c -o my_cat

my_reverse: my_reverse.c
	$(CC) $(CFLAGS) my_reverse.c -o my_reverse

my_cp: my_cp.c
	$(CC) $(CFLAGS) my_cp.c -o my_cp

my_chmod: my_chmod.c
	$(CC) $(CFLAGS) my_chmod.c -o my_chmod

# Clean target to remove compiled binary files
clean:
	rm -f my_cat my_reverse my_cp my_chmod