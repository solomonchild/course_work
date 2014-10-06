#ifndef _MENU_H
#define _MENU_H

#include "types.h"
#include <stdio.h>


typedef enum 
{
    MC_PRINT,
    MC_HALT

} menu_choice_t;

menu_choice_t show_main_menu(void);

#endif
