# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Automatically grab all .c files in the directory
SRCS = $(wildcard *.c)

all: main_compare

# Build targets
main_compare: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o main_compare

# Clean target to remove compiled binary files
clean:
	rm -f main_compare main_compare.exe *.o