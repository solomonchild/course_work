#include "menu.h"

menu_choice_t show_main_menu(void)
{

    printf("Menu:\n"
            "----\n"
            "Print records:%d\n"
            "Edit records:%d\n"
            "Exit :%d\n"
            "Enter your choice: ", MC_PRINT, MC_EDIT, MC_HALT);
    int c;
    c = getchar();
    getchar();
    return c - '0';
}


menu_choice_t prev_next(void)
{
    printf("N/n for next, P/p for previous, other char to quit: ");
    int c;
    c = getchar();
    getchar();

    switch(c)
    {
        case 'N':
        case 'n':
            return MC_NEXT;
        case 'P':
        case 'p':
            return MC_PREV;
    }
    return MC_INVALID;
}
