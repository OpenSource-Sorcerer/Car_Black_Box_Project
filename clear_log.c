#include "matrix_keypad.h"

void clear_log(void)
{
    if(!event_count)    clcd_print("  !!NO LOGS!!",LINE1(0));
    else    clcd_print("!!LOGS CLEARED!!",LINE1(0));
    
    clcd_print("RET-> MAIN MENU",LINE2(0));
        
    //blocking delay
    for(unsigned long int delay = 1000000; delay--; );
        
    state = e_main_menu;
    CLEAR_DISP_SCREEN;
    event_count = 0;
    write_addr = 0x00;
    return;
}

