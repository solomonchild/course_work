#include "io.h"
#include "menu.h"
#include "errno.h"

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
        ret = show_main_menu();
        switch(ret)
        {
            case(MC_PRINT):
            {
                int ret = 0;
                do
                {
                    record_t rec;
                    ret = read_rec(fp, &rec);
                    print_rec(&rec);
                }
                while(ret > 0);
                break;
            }
            default:
                break;
        }
    }
    while(ret != MC_HALT);
}
