/*
 * File:   main.c
 * Author: Balasubramaniyan N
 *
 * Created on 14 February, 2024, 5:40 PM
 */


#include "matrix_keypad.h"
#include "ds1307.h"
#include "I2C.h"
State_t state;

unsigned short int hr = 0, min = 0, sec = 0, speed = 0;

unsigned short adc_reg_val = 0;

unsigned char clock_reg[3];

static void get_time(void)
{
    clock_reg[0] = read_ds1307(HOUR_ADDR);
	clock_reg[1] = read_ds1307(MIN_ADDR);
	clock_reg[2] = read_ds1307(SEC_ADDR);
    
    if (clock_reg[0] & 0x40)
	{
		hr =  ((clock_reg[0] >> 4) & 0x01); hr *= 10;
		hr +=  (clock_reg[0] & 0x0F);
	}
	else
	{
		hr = ((clock_reg[0] >> 4) & 0x03);  hr *= 10;
		hr += (clock_reg[0] & 0x0F);
	}
    min = ((clock_reg[1] >> 4) & 0x0F);     min *= 10;
	min += (clock_reg[1] & 0x0F);
    sec = ((clock_reg[2] >> 4) & 0x0F);     sec *= 10;
	sec += (clock_reg[2] & 0x0F);
}
void init_config()
{
    /* Matrix initialization */
    init_matrix_keypad();
    
    /* LCD initialization */
	init_clcd();
    
    /* ADC initialization */
    init_adc();
    
    /* UART initialization */
    init_uart();
    
    /* I2C initialization */
    init_i2c();
    
    /* RTC initialization */
    init_ds1307();
    
    state = e_dashboard;
}

void main(void) 
{
    init_config();
    
    write_internal_eeprom(0x06, 'O');
    write_internal_eeprom(0x07, 'N');

    while(1)
    {
        // Detect key press
        key = read_switches(STATE_CHANGE);
        
        // Read ADC value
        adc_reg_val = read_adc(CHANNEL4);
        speed = (adc_reg_val) / 10.23;
        
        //DATA from RTC
        get_time();
        
        switch (state)
        {
            case e_dashboard:
                view_dashboard();
                break;
            
            case e_main_menu:
                display_main_menu();
                break;
            
            case e_view_log:
                view_log();
                break;
                 
            case e_download_log:
                download_log();
                break;
                
            case e_clear_log:
                clear_log();
                break;
                          
            case e_set_time:
                set_time();
                break;
        }
    }   
}
