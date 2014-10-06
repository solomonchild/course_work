#ifndef _IO_H

#include "types.h"

#include <stdio.h>

FILE* open_file();
int write_rec(FILE *fp, const record_t *rec);
int read_rec(FILE *fp, record_t *rec);
int close_file(FILE *fp);

#endif