#include "matrix_keypad.h"
#include "external_EEPROM.h"
unsigned short sl_no = 0;

char event[15];

short init_print_flag = 1;

void read_event(unsigned char read_addr)
{
    int i=0;
    for(int j = 0; j < 14; j++)
    {
        if(j == 2 || j == 5)
           event[j] = ':';  
        
        else if(j == 8 || j == 11)
            event[j] = ' ';
        else
        event[j] = read_EEPROM(read_addr + i++);
    }
    event[14] = '\0';
    return;
}
void view_log(void)
{
    if(!event_count)
    {
        //no logs
        clcd_print("  !!NO LOGS!!",LINE1(0));
        clcd_print("RET-> MAIN MENU",LINE2(0));
        
        //blocking delay
        for(unsigned long int delay = 1000000; delay--; );
        
        state = e_main_menu;
        CLEAR_DISP_SCREEN;
        return;
    }
    else
    {
        //Data present
        clcd_print("#   TIME   EV SP", LINE1(0));

        if(key == ALL_RELEASED && init_print_flag)
        {
            clcd_putch((sl_no + 48), LINE2(0));
            read_event(0);
            clcd_print(event, LINE2(2));
            init_print_flag = 0;
        }
        
        if(key == MK_SW1)   //scroll up
        {
            if(sl_no > 0)  sl_no--;
            else    sl_no = 0;

            clcd_putch((sl_no + 48), LINE2(0));
            
            read_event(sl_no * 10);
            
            clcd_print(event, LINE2(2));
        }
        else if(key == MK_SW2)  //scroll down
        {
            if(sl_no < 9)  sl_no++;
            else    sl_no = 9;
            
            if(sl_no == event_count) sl_no = event_count - 1;
            
            clcd_putch((sl_no + 48), LINE2(0));
            
            read_event(sl_no * 10);
            
            clcd_print(event, LINE2(2));
        }
        else if(key == MK_SW12)  
        {
            state = e_main_menu;
            CLEAR_DISP_SCREEN;
            init_print_flag = 1;
            sl_no = 0;
        }
    }
    return;
}