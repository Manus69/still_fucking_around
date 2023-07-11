#ifndef IO_H
#define IO_H

#include "../type/Str.h"
#include "../structure/Vec.h"

Str io_file_read(const char * name);
Vec io_txt_file_lines(const char * name);
STATUS io_write_to_file_fd(int fd, const void * data, U64 size);
STATUS io_write_to_file(const char * file_name, const void * data, U64 size);

#endif