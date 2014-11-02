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


void search_field(record_t const *rec, size_t rec_len, int fieldnum)
{
    const char *field_name = record_field_names[fieldnum - 1]; 
    char buf[30] = { 0 };
    printf("Enter value for %s: ", field_name);
    scanf("%30s", buf);
    getchar();
    const char *dest = NULL;
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

void search_rec(record_t const *rec, size_t len)
{
    if(!rec)
        return;

    printf("Enter field number (1-7) to search: ");
    char c = getchar();
    getchar();
    int choice = c - '0';
    if(choice >= 1 && choice <= 7)
        search_field(rec, len, choice);
    else
        printf("Error: no such field %d\n", choice);
}

void dump_recs(FILE *fp, record_t *recs, size_t len)
{
    reopen_wipe(fp);
    for(int i =0; i < len; i++)
        write_rec(fp, recs + i);
}

void view_records(FILE *fp, record_t *rec, size_t len)
{

    int i = 0;

    if(len > 0)
    {
        while(1)
        {
            printf("%dth\n", i + 1);
            print_rec(rec + i);
            menu_choice_t mc = prev_next(MO_NEXT | MO_PREV | MO_SEARCH | MO_EDIT);
            if(mc == MC_NEXT && i < len - 1)
            {
                i++;
            }
            else if(mc == MC_PREV && i > 0)
            {
                i--;
            }
            else if(mc == MC_EDIT)
            {
                edit_rec(rec + i);
                dump_recs(fp, rec, len);
            }
            else if(mc == MC_INVALID)
                break;
        }
    }
    else
    {
        printf("Error:No recs\nPress any key to continue...");
        getchar();
    }
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
    record_t *recs = NULL;
    do
    {
        reset_cursor(fp);
        size_t len = read_all_rec(fp, &recs);
        ret = show_main_menu();
        switch(ret)
        {
            case(MC_VIEW):
            {
                view_records(fp, recs, len);
                break;
            }
            case(MC_ADD_REC):
            {
                break;
            }
            default:
                break;
        }
    }
    while(ret != MC_QUIT);
}
