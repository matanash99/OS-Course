#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){

    if (argc < 2) {
        printf("Error: Missing argument N.\n");
        return 1;
    }

    int n = atoi(argv[1]);

    for (int i = 0; i < n; i++){
        pid_t pid = fork();
        if (pid == 0) {
            printf("Process %d, my parent is %d\n", getpid(), getppid());
        }
        else{
            wait(NULL);
            break;
        }
    }
    return 0;
}