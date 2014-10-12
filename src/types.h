#ifndef _TYPES_H
#define _TYPES_H
typedef struct 
{
    char name[20];
    char surname[20];
    char id[15];
    char subject[20];
    char mark[2];
    char t_name[20];
    char t_surname[20];

} record_t;

#define RECORD_T_LEN 8
extern char const * const record_field_names[];
#endif
