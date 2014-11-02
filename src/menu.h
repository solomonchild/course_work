#ifndef _MENU_H
#define _MENU_H

#include "types.h"
#include <stdio.h>


typedef enum 
{
    MC_VIEW,
    MC_ADD_REC,
    MC_QUIT,
    MC_BACK,
    MC_PREV,
    MC_NEXT,
    MC_EDIT,
    MC_SEARCH,

    MC_INVALID

} menu_choice_t;

typedef enum
{
    MO_PREV = 0x1,
    MO_NEXT = 0x2,
    MO_EDIT = 0x4,
    MO_SEARCH = 0x8

} menu_option_t;

menu_choice_t show_main_menu(void);
menu_choice_t prev_next(int what);

#endif
