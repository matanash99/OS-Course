#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    
    if (argc < 3) {
        printf("Error: Missing argument N.\n");
        return 1;
    }
    
    int num_1 = atoi(argv[1]);
    int num_2 = atoi(argv[2]);
    int status;

    pid_t pid_add = fork();
    if (pid_add == 0){
        int sum_nums = num_1+num_2;
        printf("Child1: (Sum): %d + %d = %d\n", num_1, num_2, sum_nums);
        exit(sum_nums);
    }
    waitpid(pid_add, &status, 0);
    printf("Parent: Child 1 result was %d\n", WEXITSTATUS(status));


    pid_t pid_mult = fork();
    if (pid_mult == 0){
        int prod_nums = num_1*num_2;
        printf("Child2: (Mul): %d * %d = %d\n", num_1, num_2, prod_nums);
        exit(prod_nums);
    }
    waitpid(pid_mult, &status, 0);
    printf("Parent: Child 2 result was %d\n", WEXITSTATUS(status));
    
    printf("All computations done\n");

    return 0;
}