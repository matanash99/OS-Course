#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]){

        if (argc != 2) {
                char *err_msg= "Error: not the right number of arguments.\n";
                write(2, err_msg, strlen(err_msg));
                return 1;
        }

        int fd = open(argv[1], O_RDONLY);
        if (fd == -1) {
                char *error = "Error opening file\n";
                write(2, error, strlen(error));
                return 1;
        }

        char buffer[1024];
        ssize_t bytes_read;

        while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
                write(1, buffer, bytes_read);
        }

        return 0;
}
