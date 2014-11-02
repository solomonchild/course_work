#include "menu.h"

#include "io.h"

menu_choice_t show_main_menu(void)
{

    printf("Menu:\n"
            "----\n"
            "View recs:%d\n"
            "Add a record:%d\n"
            "Exit :%d\n"
            "Enter your choice: ", MC_VIEW, MC_ADD_REC, MC_QUIT);
    int c = get_input();
    return c - '0';
}


menu_choice_t prev_next(int what)
{
    if(what & MO_NEXT)
        printf("N/n for next");
    if(what & MO_PREV)
        printf(", P/p for next");
    if(what & MO_EDIT)
        printf(", E/e to edit");
    if(what & MO_SEARCH)
        printf(", S/s to search");
    printf(", other char to quit: "); 

    int c = get_input();
    switch(c)
    {
        case 'N':
        case 'n':
            return MC_NEXT;
        case 'P':
        case 'p':
            return MC_PREV;
        case 'E':
        case 'e':
            return MC_EDIT;
        case 'S':
        case 's':
            return MC_SEARCH;
    }
    return MC_INVALID;
}

