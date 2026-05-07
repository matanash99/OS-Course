#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]){

        if (argc != 3) {
                char *err_msg= "Error: not the right number of arguments.\n";
                write(2, err_msg, strlen(err_msg));
                return 1;
        }

	char *source = argv[1];
	char *dest = argv[2];
	int fd_s = open(source, O_RDONLY);
	int fd_d = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);

	char buffer[1024];
	ssize_t bytes_read;

	while ((bytes_read = read(fd_s, buffer, sizeof(buffer))) > 0) {
                ssize_t bytes_written = write(fd_d, buffer, bytes_read);
                if (bytes_written != bytes_read) {
                        char *err_write = "Error writing to destination file\n";
                        write(2, err_write, strlen(err_write));
                        close(fd_s);
                        close(fd_d);
                        return 1;
                }
        }

	close(fd_d);
	close(fd_s);




}
