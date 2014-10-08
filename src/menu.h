#ifndef _MENU_H
#define _MENU_H

#include "types.h"
#include <stdio.h>


typedef enum 
{
    MC_PRINT,
    MC_EDIT,
    MC_HALT,
    MC_PREV,
    MC_NEXT,
    MC_INVALID

} menu_choice_t;

menu_choice_t show_main_menu(void);
menu_choice_t prev_next(void);

#endif
