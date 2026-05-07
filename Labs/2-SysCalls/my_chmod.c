#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        char *err_msg= "Error: not the right number of arguments.\n";
        write(2, err_msg, strlen(err_msg));
        return 1;
    }

    mode_t mode = (mode_t)strtol(argv[2], NULL, 8);

    if (chmod(argv[1], mode) < 0) {
        char *err_msg = "Chmod failed.\n";
        write(2, err_msg, strlen(err_msg));
        return 1;
    }

    return 0;
}