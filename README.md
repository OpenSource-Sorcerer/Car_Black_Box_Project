# Car_Black_Box_Project

# Overview

The Car Black Box project is designed to record and store critical vehicle data, 
similar to an aircraft's black box. It captures and logs essential parameters such as 
speed, acceleration, brake status, and timestamped event data to help analyze driving patterns and accident causes.

# HARDWARE SPECIFICATIONS

   ## rhydolabs board(Development Kit)

       https://www.rhydolabz.com/pic16f877a-development-board-rhydolabz

   ## MicroController(PIC18F4580) datasheet
   
       https://www.bing.com/ck/a?!&&p=813487720545ea35109321f287d238e81729e638819447e9da7e724da6f825d6JmltdHM9MTc0MDg3MzYwMA&ptn=3&ver=2&hsh=4&fclid=07df9f89-0e04-62ed-3276-8c4a0ff363f1&psq=pic18f4580+datasheet&u=a1aHR0cHM6Ly93dzEubWljcm9jaGlwLmNvbS9kb3dubG9hZHMvZW4vRGV2aWNlRG9jLzM5NjM3ZC5wZGY&ntb=1

   ## External RTC(ds1307) datasheet

       https://www.bing.com/ck/a?!&&p=f05f19e5a3e6a841d894e2ecbda40ebcd708597689148f6e2b2d596b2618c557JmltdHM9MTc0MDg3MzYwMA&ptn=3&ver=2&hsh=4&fclid=07df9f89-0e04-62ed-3276-8c4a0ff363f1&psq=ds1307+datasheet&u=a1aHR0cHM6Ly93d3cuYW5hbG9nLmNvbS9tZWRpYS9lbi90ZWNobmljYWwtZG9jdW1lbnRhdGlvbi9kYXRhLXNoZWV0cy9EUzEzMDcucGRm&ntb=1

# Features

  📌 Real-time data logging: Records key vehicle parameters at regular intervals.

  🚗 Crash/Event Detection: Logs sudden changes in acceleration and braking.

  💾 Persistent Storage: Saves data in a structured format for post-event analysis.

  🔍 Data Retrieval & Analysis: Allows users to extract and review stored logs.

# Work Flow

Turn ON -----> DASHBOARD -----> MAIN MENU

               ├── TIME         ├── VIEW LOG  
               ├── GEAR             ├── Prints the (previous) Last 10 events on CLCD
               ├── SPEED        ├── DOWNLOAD LOG
                                    ├── Prints the (previous) Last 10 events on terminal emulation application(i.e. teraterm)
                                ├── CLEAR LOG
                                    ├── Clears all logs which are occured previously
                                ├── SET TIME
                                    ├── Set the time which will updated to dashboard (writing into RTC)
                                    
# File Structure

    ├── I2C.c             - Function Defintions for I2C Protocol (initialization, read, write)
    ├── I2C.h             - Function Declarations for I2C Protocol
    ├── adc.c             - Function Defintions for ADC(for calculating speed) (initialization, read, write)
    ├── adc.h             - Function Declarations for ADC(for calculating speed)
    ├── black_box.h       - Function and structure declarations for all functions in project
    ├── clcd.c            - Function Definitions for CLCD display (initialization, printing)
    ├── clcd.h            - Function Declarations for CLCD display 
    ├── clear_log.c       - Clears the stored logs
    ├── dashboard.c       - Prints the common paramters like Time, Speed, Gear on CLCD display
    ├── download_log.c    - Prints the Logs in teratrum(external software) using UART
    ├── ds1307.c          - Function Defintions for RTC(Real Time Clock)
    ├── ds1307.h          - Function Declarations for RTC
    ├── eeprom.c          - Function Defintions for internal EEPROM (read, write)
    ├── external_EEPROM.c - Function Defintions for external EEPROM (read, write)
    ├── external_EEPROM.h - Function Declarations for external EEPROM (read, write)
    ├── main.c            - All function Calls for the project
    ├── main_menu.c       - Prints the Options like (view log, download log, clear log, set time) for user 
    ├── matrix_keypad.h   - Function Declarations for keypad
    ├── read_matrix_keypad.c - Function Defintions for matrix keypad
    ├── set_time.c        - Editing time by user which shown on dashboard
    ├── uart.c            - Functions Defintions for UART
    ├── uart.h            - Function Declarations for UART
    ├── view_log.c        - Prints the last 10 events occured

# Learning Outcomes

   - Enhanced problem-solving skills in eading and writing in EEPROM, CLCD and RTC

   - Debugging and testing using Teraterm

   - Mastery of Embedded C with PIC Microcontrollers

   - Gained knowledge about Communication Protocols( UART, I2C )(i.e. peripharel programming) and files management
     
# Future Enhancements

  🛰 Integration with GPS to log location-based event data.

  📶 Remote Data Transmission for real-time monitoring.

  📊 Graphical Visualization of recorded vehicle parameters.
  
# Contributing

Feel free to fork the repository, raise issues, or submit pull requests for improvements!

# License

This project is licensed under the MIT License.


