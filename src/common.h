
/////////////////
// Global Vars
//


#pragma once
// Arduino libraries
#include <Arduino.h>
#include "config.h" //config vars, pin assignments



// // OLED Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//////////////////
// prototypes
//
void output_measurements_uart(void);
void process_cal_bit(void);
void calc_measurements(void);
void calc_alt_sizes(void);

void display_settings(void);
void oled_display_text(String, String);
void oled_display_measur(void);
void oled_display_text2(uint8_t, uint8_t, uint8_t, uint8_t,String); // (line, pos_x, pos_y, size, text)/
void oled_clear_text_zone(void);
void oled_clear_zone(uint8_t, uint8_t, uint8_t, uint8_t);
void oled_debug_text(String);
void oled_display_icon(void);

// void oled_
void calc_nut(uint8_t, uint8_t);
void calc_screw(uint8_t, uint8_t);
void calc_drill(uint8_t, uint8_t);
void calc_awg(uint8_t, uint8_t);
void calc_awg_solid(uint8_t, uint8_t);
void calc_awg_stranded(uint8_t, uint8_t);
void calc_fraction(uint8_t, uint8_t);
// void oled_clear_text_zone(void);
// String calc_alt_sizes_ave(const alt_measur_table*, String);

// void oled_display(String, String); //, const unsigned char (&icon)[288]);
void mode_button_detect(void); // mode buttons


extern uint32_t tic_cnt ;
extern uint32_t tic_cnt_change ;
extern uint8_t clk_prev_state ;
extern uint8_t  clk_cur_state ;
extern uint8_t packet_started ;

extern uint32_t data_cal ; //data packet, using the first(left most) 24bits of the 32
extern uint32_t data_cal_past ; //previous data packet 

extern uint16_t measurement ;
// extern uint8_t bitbit ;
extern uint8_t unit ;
extern int8_t sign ; // 1 or -1
extern float measurement_mm ;
extern float measurement_in ;
extern float measurement_in_old ;
// char[15] measurement_nut = ''; // text for nut size, ex(#4, 3/8)
// char[15] measurement_screw = ''; // text for screw size, ex(#8, 1/4)
// char[15] measurement_drill = ''; // text for drill size, ex(#56, #A, 3/8)
// char[15] measurement_awg = ''; // text for nut size ex(000, 14, 28)

extern uint8_t no_bit_detected_cnt ; // 
extern uint8_t data_bit_cnt ;

extern uint8_t mode ;
// modes: 0="mm,inch"; 1="64ths"; 2="nuts"; 3="screws"; 4="drill-bits"; 5="AWG"

// display output
// display_title
// display_icon
// display_line1
// display_line2


extern String awg_solid ;

/////////////////
// Global Vars
//
extern uint32_t tic_cnt ;
extern uint32_t tic_cnt_change ;
extern uint8_t clk_prev_state ;
extern uint8_t  clk_cur_state ;
extern uint8_t packet_started ;

extern uint32_t data_cal ; //data packet, using the first(left most) 24bits of the 32
extern uint32_t data_cal_past ; //previous data packet 

extern uint16_t measurement ;
// extern uint8_t bitbit ;
extern uint8_t unit ;
extern int8_t sign ; // 1 or -1
extern float measurement_mm ;
extern float measurement_in ;
extern float measurement_in_old ;
// char[15] measurement_nut = ''; // text for nut size, ex(#4, 3/8)
// char[15] measurement_screw = ''; // text for screw size, ex(#8, 1/4)
// char[15] measurement_drill = ''; // text for drill size, ex(#56, #A, 3/8)
// char[15] measurement_awg = ''; // text for nut size ex(000, 14, 28)

extern uint8_t no_bit_detected_cnt ; // 
extern uint8_t data_bit_cnt ;

extern uint8_t mode ;
// modes: 0="mm,inch"; 1="64ths"; 2="nuts"; 3="screws"; 4="drill-bits"; 5="AWG"

// display output
// display_title
// display_icon
// display_line1
// display_line2


extern String awg_solid ;

// oled output
extern String oled_line1;
extern String oled_line2;


// maybe dont use
 extern String nut_text_s ;
 extern  String screw_text_s;
 extern  String drill_text_s;
 extern  String fraction_text_s;
 extern  String awg_solid_text_s;
 extern  String awg_stranded_text_s;

