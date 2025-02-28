#include <xc.h>
#include <string.h>
#include "uart.h"
/* Enum for maintaining the app state */
typedef enum {
    e_dashboard, e_main_menu, e_view_log, e_set_time, e_download_log, e_clear_log
} State_t;

extern State_t state; // App state

//Function declarations

//Dashboard function declaration
void view_dashboard(void);

//Storing events function declaration
void event_store(unsigned short int hr, unsigned short int min, unsigned short int sec, unsigned char *gear, unsigned short int speed);

//Password function declaration
void password(void);

//main menu function declaration
void display_main_menu(void);

//View log function declaration
void view_log(void);

//Reading events function declaration
void event_reader(void);

//Change password function declaration
void change_password(void);

//Set time function declaration
void set_time(void);

//Download log function _declaration
void download_log(void);

//Clear log function declaration
void clear_log(void);

//String contains gear texts 
const char *gear[] = {"ON", "GN", "G1", "G2", "G3", "G4", "G5", "GR","C "};

//variables for Time and Speed
extern unsigned short int hr, min, sec, speed, adc_reg_val;

//variable to count the number of events
extern unsigned int event_count;

extern unsigned char write_addr;

extern char event[15];
//EEPROM read and write
void write_internal_eeprom(unsigned char address, unsigned char data); 
unsigned char read_internal_eeprom(unsigned char address);

void read_event(unsigned char read_addr);

extern unsigned short int set_hr, set_min, set_sec;

//void get_time(unsigned short int hr, unsigned short int min, unsigned short int sec);