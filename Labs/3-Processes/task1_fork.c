#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {


    int x = 100;
    pid_t pid = fork();

    if (pid == 0) { //son
        x += 50;
        printf("My PID is %d: x = %d\n", getpid(), x);
    } 
    else {
        if (pid > 0) { //parent
            wait(NULL);
            printf("My PID is %d: x = %d\n", getpid(), x);
        }
    }

    return 0;
}