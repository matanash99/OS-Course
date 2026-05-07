# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

all: my_fork my_exec my_chain my_calc my_race

# Build targets
my_fork: task1_fork.c
	$(CC) $(CFLAGS) task1_fork.c -o my_fork

my_exec: task2_exec.c
	$(CC) $(CFLAGS) task2_exec.c -o my_exec

my_chain: task3_chain.c
	$(CC) $(CFLAGS) task3_chain.c -o my_chain

my_calc: task4_calc.c
	$(CC) $(CFLAGS) task4_calc.c -o my_calc


my_race: task5_race.c
	$(CC) $(CFLAGS) task5_race.c -o my_race

	


# Clean target to remove compiled binary files
clean:
	rm -f my_fork my_exec my_chain my_calc my_race