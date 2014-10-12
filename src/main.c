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
        "1",
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


void change_field(record_t *rec, int fieldnum)
{
    const char *field_name = record_field_names[fieldnum - 1]; 
    char buf[30] = { 0 };
    printf("Enter value for %s: ", field_name);
    scanf("%30s", buf);
    getchar();
    char *dest = NULL;
    size_t len = 0;
    switch(fieldnum)
    {
        
        case 1: 
		{
            dest = rec->name;                
            len = sizeof(rec->name);
            break;
		}

        case 2: 
		{
            dest = rec->surname;                
            len = sizeof(rec->surname);
            break;
		}

        case 3: 
		{
            dest = rec->id;                
            len = sizeof(rec->id);
            break;
		}

        case 4: 
		{
            dest = rec->subject;                
            len = sizeof(rec->subject);
            break;
		}

        case 5: 
		{
            dest = rec->mark;                
            len = sizeof(rec->mark);
            break;
		}

        case 6: 
		{
            dest = rec->t_name;                
            len = sizeof(rec->t_name);
            break;
		}

        case 7: 
		{
            dest = rec->t_surname;                
            len = sizeof(rec->t_surname);
            break;
        }

    }
    strncpy(dest, buf, len);

}

void edit_rec(record_t *rec)
{
    if(!rec)
        return;

    printf("Enter field number (1-7) to edit: ");
    char c = getchar();
    getchar();
    int choice = c - '0';
    if(choice >= 1 && choice <= 7)
        change_field(rec, choice);
    else
        printf("Error: no such field %d\n", choice);
}

void edit_records(FILE *fp)
{
    record_t *rec = NULL;
    size_t len = read_all_rec(fp, &rec);
    printf("RECS LEN : %d\n", len);
    int i = 0;

    if(len > 0)
    {
        while(1)
        {
            printf("%dth\n", i + 1);
            print_rec(rec + i);
            menu_choice_t mc = prev_next_edit();
            if(mc == MC_EDIT)
                edit_rec(rec + i);
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
    
    reset_cursor(fp);
    printf("RECS LEN B4 write: %d\n", len);
    for(int i =0; i < len; i++)
        write_rec(fp, rec + i);

    free(rec);
}

void view_records(FILE *fp)
{
    record_t *rec = NULL;
    size_t len = read_all_rec(fp, &rec);
    printf("read : %d\n", len);

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
        printf("Couldn't open the database");
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
            case(MC_EDIT_RECS):
            {
                edit_records(fp);
                break;
            }
            default:
                break;
        }
    }
    while(ret != MC_HALT);
}
