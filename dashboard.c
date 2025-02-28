#include "matrix_keypad.h"
#include "external_EEPROM.h"
unsigned char gear_index = 0;

unsigned char collision_flag = 0, key_press = 0;

unsigned int event_count = 0;

unsigned char write_addr = 0x00;

void display_time(void)
{
    //HOUR
    clcd_putch(((hr / 10) + 48), LINE2(0));
    clcd_putch(((hr % 10) + 48), LINE2(1));
    clcd_putch(':', LINE2(2));
    
    //MINUTE
    clcd_putch(((min / 10) + 48), LINE2(3));
    clcd_putch(((min % 10) + 48), LINE2(4));
    clcd_putch(':', LINE2(5));
    
    //SECONDS
    clcd_putch(((sec / 10) + 48), LINE2(6));
    clcd_putch(((sec % 10) + 48), LINE2(7));
}

void view_dashboard(void) 
{
    if(key == MK_SW11)
    {
        CLEAR_DISP_SCREEN;
        state = e_main_menu;
        return;
    }
    clcd_print("  TIME   GEAR SP", LINE1(0));
    
    /*****************************************************/
    //TIME //Data from RTC
    display_time();
    /*******************************************************/
    
    if(key != ALL_RELEASED)
    {
        if(key == MK_SW1)  //SW1
        {
            key_press = 1;
            gear_index++;
            if(gear_index > 7)  
            {
                key_press = 0;
                gear_index = 7;
            }
            
            if(collision_flag)  gear_index = 1;

            clcd_print(gear[gear_index], LINE2(10));
            collision_flag = 0;
        }
        else if(key == MK_SW2) //SW2
        {
            key_press = 1;
            gear_index--;
            if(gear_index == 255)  
            {
                key_press = 0;
                gear_index = 0;
            }
            else if(gear_index < 1 || collision_flag)  gear_index = 1;
            
            clcd_print(gear[gear_index], LINE2(10));
            collision_flag = 0;
        }
        else if(key == MK_SW3 && !collision_flag)
        {
            key_press = 1;
            gear_index = 8;
            clcd_print(gear[gear_index], LINE2(10));
            collision_flag = 1;
        }
    }
    else
        clcd_print(gear[gear_index], LINE2(10));
    
    //SPEED //data from potentiometer
    if(speed > 99)  speed = 99;
    clcd_putch((speed / 10 + 48), LINE2(14));
    clcd_putch(speed % 10 + 48, LINE2(15));
    
    if(key_press)
    {
        event_store(hr, min, sec, gear[gear_index], speed);
        key_press = 0;
    }
    return;
}
unsigned char shift_10data(unsigned char addr)
{
    unsigned short i1 = 0;
    unsigned short i2 = 10;
    
    for( ;i2 < 100; i1++, i2++)
    {
        unsigned char ch = read_EEPROM(i2);
        write_EEPROM(i1, ch);
    }
    return 90;
}
void event_store(unsigned short int hr, unsigned short int min, unsigned short int sec, unsigned char *gear, unsigned short int speed)
{
    event_count++;
    if(event_count > 10) 
    {
        event_count = 10;
        write_addr = shift_10data(write_addr); 
    }
    write_EEPROM(write_addr, ((hr / 10) + 48));
    write_EEPROM(write_addr + 1, ((hr % 10) + 48));
    write_EEPROM(write_addr + 2, ((min / 10) + 48));
    write_EEPROM(write_addr + 3, ((min % 10)+ 48));
    write_EEPROM(write_addr + 4, ((sec / 10)+ 48));
    write_EEPROM(write_addr + 5, ((sec % 10)+ 48));
    write_EEPROM(write_addr + 6, gear[0]);
    write_EEPROM(write_addr + 7, gear[1]);
    write_EEPROM(write_addr + 8, ((speed / 10)+ 48));
    write_EEPROM(write_addr + 9, ((speed % 10)+ 48));
    
    if(event_count != 10)   write_addr += 10;
    
    return;
}
