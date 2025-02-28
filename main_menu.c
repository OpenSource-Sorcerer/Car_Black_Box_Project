#include "matrix_keypad.h"
#include "ds1307.h"
unsigned char limit = 0;
char *logs[] = {"VIEW LOG", "DOWNLOAD LOG", "CLEAR LOG", "SET TIME"};
unsigned char clock_reg1[3];
void display_main_menu(void)
{
    //default
    if(!limit)
    {
        clcd_print("-> VIEW LOG", LINE1(0));
        clcd_print("   DOWNLOAD LOG", LINE2(0));
    }
    if(key == MK_SW1) //scroll up 
    {  
        CLEAR_DISP_SCREEN;
        if(limit > 0)  limit--;
        else    limit = 0;
        
        clcd_print("->", LINE1(0));
        clcd_print("  ", LINE2(0));
        
        if(limit > 0)
        {
            clcd_print(logs[limit],LINE1(3));
            clcd_print(logs[limit + 1],LINE2(3));
        }
    }
    else if(key == MK_SW2) //scroll down
    {
        CLEAR_DISP_SCREEN;
        if(limit < 3)  limit++;
        else    limit = 3;
        
        clcd_print("->", LINE2(0));
        clcd_print("  ", LINE1(0));
        
        if(limit > 0)
        {
            clcd_print(logs[limit - 1],LINE1(3));
            clcd_print(logs[limit],LINE2(3));
        }
    }
    else if(key == MK_SW11) //Enter the log
    {
        CLEAR_DISP_SCREEN;
        //based on limit, change the state
        switch(limit)
        {
            case 0:
                state = e_view_log;
                break;
                
            case 1:
                state = e_download_log;
                break;
                
            case 2:
                state = e_clear_log;
                break;
                
            case 3:
                 //read time from RTC
                clock_reg1[0] = read_ds1307(HOUR_ADDR);
                clock_reg1[1] = read_ds1307(MIN_ADDR);
                clock_reg1[2] = read_ds1307(SEC_ADDR);
    
                if (clock_reg1[0] & 0x40)
                {
                    set_hr =  ((clock_reg1[0] >> 4) & 0x01); set_hr *= 10;
                    set_hr +=  (clock_reg1[0] & 0x0F);
                }
                else
                {
                    set_hr = ((clock_reg1[0] >> 4) & 0x03);  set_hr *= 10;
                    set_hr += (clock_reg1[0] & 0x0F);
                }
                set_min = ((clock_reg1[1] >> 4) & 0x0F);     set_min *= 10;
                set_min += (clock_reg1[1] & 0x0F);
                set_sec = ((clock_reg1[2] >> 4) & 0x0F);     set_sec *= 10;
                set_sec += (clock_reg1[2] & 0x0F);
                state = e_set_time;
        }
        limit = 0;
    }
    //Exit from main menu    
    if(key == MK_SW12)  
    {
        limit = 0;
        state = e_dashboard;
        CLEAR_DISP_SCREEN;
    }
    return;
}
