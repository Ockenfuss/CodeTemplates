#include <stdlib.h>


#ifndef MYCTOOLS_H
#define MYCTOOLS_H

int readstring_f(char* str, char* delim, float* val, const size_t n_val);
char* readline_file(const char *filename, int line_number);

#endif /* MYCTOOLS_H */