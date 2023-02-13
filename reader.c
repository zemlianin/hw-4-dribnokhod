#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

const int size = 32;
int main(int argc, char **argv)
{
    int fd;
    int fdout;
    char buffer[size + 1];
    ssize_t read_bytes;
    ssize_t written_bytes;
    if (argc < 3)
    {
        fprintf(stderr, "Too few arguments\n");
        exit(1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "Cannot open file\n");
        exit(1);
    }
    fdout = open(argv[2], O_WRONLY);
    while ((read_bytes = read(fd, buffer, size)) > 0)
    {
        written_bytes = write(fdout, buffer, read_bytes);
        if (written_bytes != read_bytes)
        {
            fprintf(stderr, "Cannot write\n");
            exit(1);
        }
    }
    if (read_bytes < 0)
    {
        fprintf(stderr, "myread: Cannot read file\n");
        exit(1);
    }
    close(fd);
    return 0
}