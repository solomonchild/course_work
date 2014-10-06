#include "menu.h"

menu_choice_t show_main_menu(void)
{

    printf("Menu:\n"
            "----\n"
            "Print records:%d\n"
            "Exit :%d\n"
            "Enter your choice: ", MC_PRINT, MC_HALT);
    int c;
    scanf("%d", &c);
    return c;
}
