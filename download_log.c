#include "matrix_keypad.h"

void download_log(void)
{ 
    if(!event_count)
    {
        puts("\nNO LOGS TO DOWNLOAD\n\n\r");
        clcd_print("  !!NO LOGS!!",LINE1(0));
    }
        
    else
    {
        clcd_print("LOGS  DOWNLOADED",LINE1(0));
        
        puts("\n#   TIME   EV SP\n\r");
        //print the events
        //read data from 0 to event_count * 10
        unsigned int read_enable = 0;
        while(read_enable != event_count)
        {
            putch(read_enable + 48);
            puts(" ");
            read_event(read_enable * 10);
            puts(event);
            puts("\n\r");
            read_enable++;
        }
        
    }
    clcd_print("RET-> MAIN MENU",LINE2(0));
    //blocking delay
    for(unsigned long int delay = 1000000; delay--; );
        
    state = e_main_menu;
    CLEAR_DISP_SCREEN;
    return;
}