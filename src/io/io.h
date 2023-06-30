#ifndef IO_H
#define IO_H

#include "../type/Str.h"
#include "../structure/Vec.h"

Str io_file_read(const char * name);
Vec io_txt_file_lines(const char * name);

#endif