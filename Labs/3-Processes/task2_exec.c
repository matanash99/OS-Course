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

    pid_t pid = fork();

    if (pid == 0) { //child
        execlp(argv[1], argv[1], NULL);
        perror("execlp failed\n");
        exit(1);
    }

    else{
        printf("Parent: waiting for command to finish.\n");
        wait(NULL);
        printf("Parent: execution complete.\n");
    }
    return 0;

}