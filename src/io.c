#include "io.h"

#include <stdlib.h>

#define DB_NAME "db.bin"

char const * const record_field_names[] =
{
    "Name",
    "Surname",
    "ID",
    "Subject",
    "Mark",
    "Teacher's name",
    "Teacher's surname"
};

FILE* open_file()
{
    return fopen(DB_NAME, "a+b");
}

int close_file(FILE *fp)
{
    return fclose(fp);
}

int write_rec(FILE *fp, const record_t *rec)
{
    if(fp == NULL)
        return -1;
    fseek(fp, 0, SEEK_END);
    return fwrite(rec, sizeof(*rec), 1, fp);
}

void reset_cursor(FILE *fp)
{
    fseek(fp, 0, SEEK_SET);
}

int read_rec(FILE *fp, record_t *rec)
{
    if(fp == NULL)
        return -1;
    int ret =  fread(rec, sizeof(record_t), 1, fp);
    return ret;
}

size_t read_all_rec(FILE *fp, record_t **rec)
{
    int arr_size = 5;
    size_t res_len = 0;
    int ret = 0;
    record_t *arr = malloc(sizeof(record_t) * arr_size); 

    while((ret = read_rec(fp, arr + res_len)) > 0)
    {
        if(res_len ++ == arr_size - 1)
        {
            arr_size *= 2;
            arr = realloc(arr, sizeof(record_t) * arr_size);
        }
    }
    
    *rec = arr;
    return res_len;

}

void print_rec(record_t *rec)
{
    printf( "----------------------\n"
            "1) Name:              |%s\n"
            "2) Surname:           |%s\n"
            "3) ID:                |%s\n"
            "4) Subject:           |%s\n"
            "5) Mark:              |%d\n"
            "6) Teacher's name:    |%s\n"
            "7) Teacher's surname: |%s\n"
            "----------------------\n",
            rec->name, rec->surname, rec->id, rec->subject, rec->mark, rec->t_name, rec->t_surname);
}

