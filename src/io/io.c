#include "io.h"

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define READ_SIZE (1 << 10)

Str io_file_read_fd(int fd)
{
    char *      buffer;
    Str         str;
    struct stat _stat;

    fstat(fd, & _stat);
    buffer = mem_zero(_stat.st_size + 1);
    read(fd, buffer, _stat.st_size);
    str = Str_own(buffer, _stat.st_size);

    return str;
}

Str io_file_read(const char * name)
{
    int fd;

    if ((fd = open(name, O_RDONLY)) < 0) return Str_init(1);

    return io_file_read_fd(fd);
}

Vec io_txt_file_lines(const char * name)
{
    Str content;
    Vec lines;

    content = io_file_read(name);
    lines = Str_split_c(& content, '\n');
    Str_del(& content);

    return lines;
}

STATUS io_write_to_file_fd(int fd, const void * data, U64 size)
{
    return write(fd, data, size) >= 0 ? STATUS_OK : STATUS_NOT_OK;
}

STATUS io_write_to_file(const char * file_name, const void * data, U64 size)
{
    int fd;

    if ((fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR)) < 0) return STATUS_NOT_OK;

    return io_write_to_file_fd(fd, data, size);
}