#include "matrix_keypad.h"
#include "ds1307.h"

unsigned short int set_hr = 0, set_min = 0, set_sec = 0;
unsigned short int field_select = 1;
unsigned long int delay = 0;

void blink(unsigned short int field_select)
{
    clcd_putch(':',LINE2(6));
    clcd_putch(':',LINE2(9));
    if(delay++ > 300 && delay < 600)
    {
        switch(field_select)
        {
            case 1:            
                clcd_putch(' ', LINE2(4));
                clcd_putch(' ', LINE2(5));
                break;
            case 2:
                clcd_putch(' ', LINE2(7));
                clcd_putch(' ', LINE2(8));
                break;
            case 3:
                clcd_putch(' ', LINE2(10));
                clcd_putch(' ', LINE2(11));
        }
    }
    else if(delay > 600)  delay = 0;
    
    else
    {
        ///////////////////////////////////////////
        clcd_putch((set_hr / 10) + 48, LINE2(4));
        clcd_putch((set_hr % 10) + 48, LINE2(5));
        clcd_putch((set_min / 10) + 48, LINE2(7));
        clcd_putch((set_min % 10) + 48, LINE2(8));
        clcd_putch((set_sec / 10) + 48, LINE2(10));
        clcd_putch((set_sec % 10) + 48, LINE2(11));
        ////////////////////////////////////////////
    }
}

void set_time(void) 
{
    clcd_print("    HH:MM:SS",LINE1(0));
   
    blink(field_select);
    if(key == MK_SW2)
    {
        field_select++;
        if(field_select > 3)    field_select = 1;
    }
    else if(key == MK_SW1)
    {
        switch(field_select)
        {
            case 1:
                set_hr++;
                if(set_hr > 23)     set_hr = 0;
                break;
            case 2:
                set_min++;
                if(set_min > 59)    set_min = 0;
                break;
            case 3:
                set_sec++;
                if(set_sec > 59)    set_sec = 0;
        }
    }
    else if(key == MK_SW11)
    {
        write_ds1307(HOUR_ADDR, (((set_hr  / 10) << 4) | (set_hr  % 10)));
        write_ds1307(MIN_ADDR,  (((set_min / 10) << 4) | (set_min % 10)));
        write_ds1307(SEC_ADDR,  (((set_sec / 10) << 4) | (set_sec % 10)));
        clcd_print("TIME UPDATED",LINE1(0));
        clcd_print("    SUCCESSFULLY",LINE2(0));
        
        //blocking delay
        for(unsigned long int delay = 1000000; delay--; );
        
        state = e_dashboard;
        field_select = 1;
        CLEAR_DISP_SCREEN;
    }
    else if(key == MK_SW12)  
    {
        field_select = 1;
        state = e_main_menu;
        CLEAR_DISP_SCREEN;
    }
    return;
}
