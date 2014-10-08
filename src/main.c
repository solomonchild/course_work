#include "io.h"
#include "menu.h"

#include <errno.h>
#include <string.h>
#include <stdlib.h>

void test(void)
{
    record_t rec =
    {
        "John",
        "Doe",
        "140891-14458",
        "Maths",
        1,
        "Teacher",
        "One"
    };
    FILE *fp = open_file();
    print_rec(&rec);
    write_rec(fp, &rec);
    close_file(fp);

    fp = open_file();
    record_t trec;
    read_rec(fp, &trec);
    print_rec(&trec);
    close_file(fp);
}


void edit_rec(record_t *rec)
{
    if(!rec)
        return;

    printf("Enter field to edit: ");
    char c = getchar();
    getchar();
    if(c == 0)
        printf("ZERO\n");
}

void edit_records(FILE *fp)
{
    record_t *rec = NULL;
    size_t len = read_all_rec(fp, &rec);
    int i = 0;

    if(len > 0)
    {
        while(1)
        {
            edit_rec(rec + i);
            menu_choice_t mc = prev_next();
            if(mc == MC_NEXT && i < len)
                i++;
            if(mc == MC_PREV && i > 0)
                i--;
            if(mc == MC_INVALID)
                break;
        }
    }
    else
    {
        printf("Error:No recs\nPress any key to continue...");
        getchar();
    }




    free(rec);
}

void view_records(FILE *fp)
{
    record_t *rec = NULL;
    size_t len = read_all_rec(fp, &rec);

    int i = 0;

    if(len > 0)
    {
        while(1)
        {
            printf("%dth\n", i + 1);
            print_rec(rec + i);
            menu_choice_t mc = prev_next();
            if(mc == MC_NEXT && i < len - 1)
                i++;
            if(mc == MC_PREV && i > 0)
                i--;
            if(mc == MC_INVALID)
                break;
        }
    }
    else
    {
        printf("Error:No recs\nPress any key to continue...");
        getchar();
    }
    free(rec);

}
int main(int argc, char **argv)
{
    if(argc > 1 && !strcmp(argv[1], "test"))
        test();
    FILE *fp = open_file();
    if(fp == NULL)
    {
        printf("Couldn't open database");
        return -EBADF;
    }

    menu_choice_t ret;
    do
    {
        reset_cursor(fp);
        ret = show_main_menu();
        switch(ret)
        {
            case(MC_PRINT):
            {
                view_records(fp);
                break;
            }
            case(MC_EDIT):
            {

                break;
            }
            default:
                break;
        }
    }
    while(ret != MC_HALT);
}
