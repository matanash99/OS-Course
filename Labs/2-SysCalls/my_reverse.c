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

        char c;
        off_t pos = lseek(fd, -1, SEEK_END);
        while (pos >= 0){
                read(fd, &c, 1);
                write(1, &c, 1);
                if (pos == 0) {
                        break;
                }
                pos = lseek(fd, -2, SEEK_CUR);
        }

        close(fd);
        return 0;
}
