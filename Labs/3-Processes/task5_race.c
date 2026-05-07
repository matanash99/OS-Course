#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>


int main(int argc, char *argv[]){


    if (argc < 2) {
        printf("Error: Missing argument N.\n");
        return 1;
    }
    srand(time(NULL));
    
    int k = atoi(argv[1]);

    for (int i = 0; i < k; i++){

        pid_t pid = fork();

        if (pid == 0){ // child
            sleep(rand() % 5);
            printf("Child pid: %d\n", getpid());
            exit(1);
        }
    }

    system("ps -l");
    printf("Parent: Reviewing process state (look for <defunc>)\n");
    for (int i = 0; i < k; i++){
        wait(NULL);
    }
    printf("Parent: all children reaped\n");

    return 0;
}