///////////////////////////////////////////////////////////////////
//
//             Enhanced Digital Calipers Display
//
//  Description: Added to display to show standardized sizes such
//    as nut, screw sizes and wire gauges
//
//  Author: 
//    Zef the Tinker
//
//  Date: 
//    2023
//
//  License: 
//    GPL-v3
//
//  Features:
//  Modes: 
//    * Normal: mm/in
//    * 64ths, fractions
//    * Nuts
//    * Screws
//    * Screws (including metric) 
//    * Drill-bits
//    * Drill-bits (including numbered bits)
//
//  Missing features:
//    * no shutdown button, easy to add it you want
//    * more modes, like AWG, ran out of progmem
//    * no integrated zero button, uses calipers zero button  
//
//  Modes to maybe add: 
//    * screw hole mode, sockets, screw-holes, AWG, other wire gauge, 128th
//
//  Libraries:
//    * https://github.com/adafruit/Adafruit_SSD1306
//        * https://adafruit.github.io/Adafruit_SSD1306/html/index.html
//    * https://github.com/adafruit/Adafruit-GFX-Library
//        * https://learn.adafruit.com/adafruit-gfx-graphics-library
//
//  Notes:
//    * avoid too much serial out, takes too much time between reading caliper bits
//    * Generic I2C OLED displays use SSD1306 chip
//    * I commented out Adafruit SSD1306 (scrolling, splash, inverting) functions to save 8.2%(~2.5KiB) flash
//    * Text: ASCII - chars 0x20 thru 0x7E (standard keyboard chars only) (https://www.ascii-code.com/)
//    * lighter alternative to Adafruit https://github.com/greiman/SSD1306Ascii, but does not support bitmaps
//    * Wire sizes(AWG) disabled, ran out of progmem
//
//  Bugs
//    * if Lithium battery gets below 3.2V screen acts bizarre, and needs recharge
//      this is because voltage drop across turn on transistor is larger than desirable
//    * when SERIAL_ENABLE=1 progmem overloads
//    * Power button need to be held down for a second or two, 
//       because Arduino boot loader takes a while load, so shutdown pin isnt enabled until then, so I need to add a larger cap.
//
//  Debug
//    * if the output bounces around by large numbers, usually from positive and negative
//      * voltage to caliper is too low. look are caliper screen
//    * if screen has odd output, cut off screen or text at wrong position
//      * lithium battery voltage is too low, making MCU voltage too low, making MCU reset constantly
//
/////////////////////////////////////////////////////////////////////////


// Arduino libraries
#include <Arduino.h>

// OLED libraries
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Local
#include "tables.h" // data for nut/screw/drill/etc sizes
#include "PROGMEM_readAnything.h" // some fuctions to open PROGMEM data
#include "alt_measure_sizes.h" // functions for sizing for nut, screw, drill-bit, etc
#include "common.h" //global vars
#include "config.h" //config vars, pin assignments
#include "bitmaps.h" // icons
#include "oled.h" // oled functions

// Pin Assignments in config.h




/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//// Code
////


// OLED Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);




/////////////////////////////////////////////////////////////////////////////////////
// Global Vars
//
uint32_t tic_cnt = 0;
uint32_t tic_cnt_change = 0;
uint8_t clk_prev_state = 0;
uint8_t  clk_cur_state = 0;
uint8_t packet_started = 0;

uint32_t data_cal = 0; //data packet, using the first(left most) 24bits of the 32
uint32_t data_cal_past = 0; //previous data packet 

uint16_t measurement = 0;
// uint8_t bitbit = 0;
uint8_t unit = 0;
int8_t sign = 0; // 1 or -1
float measurement_mm = 0;
float measurement_in = 0;
float measurement_in_old = 0;


uint8_t no_bit_detected_cnt = 0; // 
uint8_t data_bit_cnt = 0;

uint8_t mode = 0;
// modes: 0="mm,inch"; 1="64ths"; 2="nuts"; 3="screws"; 4="drill-bits"; 5="AWG(solid); 6=AWG(stranded)"

// display output
// display_title
// display_icon
// display_line1
// display_line2


// oled output vars
String oled_line1 = "";
String oled_line2 = "";

// oled_logo
String nut_text_s = "";
String screw_text_s = "";
String drill_text_s = "";
String fraction_text_s = "";
String awg_solid_text_s = "";
String awg_stranded_text_s = "";




////////////////////////////////////////////////////////////////////////////////////////////////
// Functions
//



// OLED display measurement text
void oled_display_measur(void){
  // these options should be equal to MAX MODES
  
  String text_s1 = "";
  String text_s2 = "";
  String text_s3 = "";
  
  // oled_debug_text(String("->" + String(mode)));
  if(SERIAL_ENABLED){
    Serial.print("Mode:");
  }

  if(mode == 0){ // mm-inch
    if(SERIAL_ENABLED){
      Serial.println("mm/inches");
    } 
		oled_clear_text_zone();
    text_s2 = String(String(measurement_in) + "\"");
    text_s1 = String(measurement_mm,1);
    text_s3 = "mm";
    oled_display_text2(0, OLED_X_POS_DEFAULT, 0, 2, text_s1); // (line,pos_x,pos_y,size,text)
    oled_display_text2(0, 100, 0, 1, text_s3); // (line,pos_x,pos_y,size,text)
    oled_display_text2(0, OLED_X_POS_DEFAULT, Y_POS_2ND_LINE_DEFAULT, 2, text_s2); // (line,pos_x,pos_y,size,text)
  }else if(mode == 1){ //fractions
    if(SERIAL_ENABLED){
      Serial.println("fractions");
    }    
    calc_fraction(0,1);

  }else if(mode == 2){ // nuts-socket
    if(SERIAL_ENABLED){
      Serial.println("nuts/socket");
    }    
    calc_nut(0,1);

  }else if(mode == 3){ // screw
    if(SERIAL_ENABLED){
      Serial.println("screw-size");
    }    
    calc_screw(0,1);
  }else if(mode == 4){ // screw-all
    if(SERIAL_ENABLED){
      Serial.println("screw-all-size");
    }    
    calc_screw_all(0,1);    
  }else if(mode == 5){ // drill-bit
    if(SERIAL_ENABLED){
      Serial.println("drill-bit size");
    }    
    calc_drill(0,1);
  }else if(mode == 6){ // drill-bit all
    if(SERIAL_ENABLED){
      Serial.println("drill-bit all size");
    }    
    calc_drill_all(0,1);
  }
  // DISABLED - Wire Sizing because ran out of progmem
  // else if(mode == 7){ // AWG solid
  //   if(SERIAL_ENABLED){
  //     Serial.println("AWG(solid)");
  //   }    
  //   calc_awg_solid(0,1);
  // }else if(mode == 8){ // AWG stranded
  //   if(SERIAL_ENABLED){
  //     Serial.println("AWG(stranded)");
  //   }    
  //   calc_awg_stranded(0,1);
  // }
  // Display: write the text to OLED
  // oled_display_text(oled_line1, oled_line2);


}







// Mode Button press
void mode_button_detect(void){

  if(!digitalRead(PIN_MODE_BUTTON)){ // button pulls low

    // short button press is about 500 clk cnts(25ms)
    // long button press is about 1700 clk cnts(85ms)
    // fastest normal pressing is 500 clk-counts(25ms) ON, 400 clk-counts(20ms) OFF for me
    // I want presses to change mode once no matter the length
    // so im going to loop until a button press stops

    mode++;
    // change mode
    if(mode == MAX_MODES + 1){
      mode = 0;
    }
    


    // Reset data packet read // FIXME why isnt this reseting need to process/
    data_bit_cnt = 0;
    data_cal = 0;
    no_bit_detected_cnt = 0;   


    if(DEBUG){
      Serial.println("-");  
      Serial.print("Click detected, ");
      Serial.print("Mode: ");
      Serial.println(mode);
      Serial.println("-");      
    }
    // mode++;

    // clear screen
    if(OLED_ENABLED){
    display.clearDisplay();
    display.display();

    // update oled icon
    oled_display_icon();
    // update oled text output
    oled_display_measur();
    }
    
    // loop until button press stops (single mode change per button press)
    delay(10);  // milli-seconds, sleep time much less that fastest button press
    while (!digitalRead(PIN_MODE_BUTTON)){
      delay(10); //mili-seconds
    }
  }

}



// process new bit from calipers
void process_cal_bit(void){

    // save new data bit
    data_cal = data_cal >> 1; //shift data
    // save data bit
    // pins data is inverted, adds 1 if false
    if(digitalRead(PIN_CAL_DATA) == LOW){
      data_cal |= 0x80000000; // shift in 1
      // Serial.print('#');
    }else{ // no need to write 0
      // Serial.print('@');
    }

    
    data_bit_cnt++; // inc bit cnt after read/stored (need to inc here because of reset)

    // if a time has passed with no new bits, reset count and data

    // if 24 bit read, data packet is done and ready to be proccessed
    if(data_bit_cnt == 24){

      // if data packet has changed, perform calculations, refresh output
      // tic_cnt check ensures inital reading, even when no change
      if(data_cal != data_cal_past || tic_cnt < 1000){

        // calculate the measurements from data packet
        calc_measurements();

        // find alternative measurments
        calc_alt_sizes();

        // get display details
        oled_display_measur();

        // output the calip measurements to uart
        if(SERIAL_ENABLED || DEBUG){
          output_measurements_uart();
        }

        data_cal_past = data_cal; // store data packet, for furture check for change
      }

      data_bit_cnt = 0; // reset cnt after 24 bits received
    }
}








// Calculate measurements from data
void calc_measurements(void){
       // check units
      unit = (data_cal >> 31) & 0x00000001;
      if(DEBUG){
        Serial.println("|"); // end of line
        Serial.print("units=");
        if( unit ){
          Serial.println("in");
        }else{
          Serial.println("mm");
        }
      }
      // Check sign +/-
      sign = (data_cal >> 28) & 0x00000001 ;
      if(DEBUG){
        Serial.print("sign=");
      }
      if( sign ){
        if (DEBUG){
          Serial.println("-");
        }
        sign = -1;
      }else{
        if(DEBUG){
          Serial.println("+");
        }
        sign = 1;
      }

      if(DEBUG){ //raw data
        Serial.println("data packet=");
        Serial.println(data_cal, BIN);
        Serial.print("####XXXX####XXXX");
        Serial.println("####XXXX####XXXX");
      }

     // calculate measurements (mm/in)
      measurement = 0;
      if ( unit ){ // inches
        // bitbit = 0;
        measurement = 0;
        for (int i = 24; i >= 8; i--){ 
          // ignoring the +0.0005 bit because back of calipers state 
          //  res=0.01in, acuracy= +/- 0.01in
          // bitbit = (data_cal >> (i + 1) ) & 0x00000001;
          // if(DEBUG){
          //   Serial.print(bitbit);
          // }
          measurement |= (data_cal >> (i + 1) ) & 0x00000001; //store bit
          measurement <<= 1; //shift
        }
        measurement >>= 1; //unshift
        // convert bin to inches
        measurement_in = (float)sign * (float)measurement / 1000;
        measurement_mm = measurement_in * 25.4;
      }else{ // mm
        // bitbit = 0;
        measurement = 0;
        for (int i = 23; i >= 7; i--){
          // bitbit = (data_cal >> (i + 1) ) & 0x00000001;
          // if(DEBUG){
          //   Serial.print(bitbit);
          // }
          measurement |= (data_cal >> (i + 1) ) & 0x00000001; // store bit
          measurement <<= 1; //shift
        }
        measurement >>= 1; //unshift
        // convert bin to mm
        measurement_mm = (float)sign * (float)measurement/100;
        measurement_in = measurement_mm / 25.4;
      }

}




void calc_alt_sizes(void){
  // Using caliper measurements in inches, 
  // estimate the closest standard values,
  // and display percentage off from that value
  // Standard values and their size in inches stored in "tables.hpp"
  //
  //  Examples:
  //    Nut: 3/8
  //    Drill: #56
  //    Screw: #8
  //

  
  
  
  if (SERIAL_ENABLED){
    calc_nut(1,0);
    calc_screw(1,0);
    calc_screw_all(1,0);
    calc_drill(1,0);
    calc_drill_all(1,0);
    calc_fraction(1,0);
    // calc_awg_solid(1,0);
    // calc_awg_stranded(1,0);
    // awg_solid = calc_alt_sizes_ave(*wire_solid, "AWG(solid)");
  }else if(OLED_ENABLED){
  
  // if(SERIAL_ENABLED){
    // Serial.print("Mode: ");
    // Serial.println(mode);
  // }

  // oled display measurements
    oled_display_measur();
  }
}










// print measurement data via uart
void output_measurements_uart(void){
      if(DEBUG){
        Serial.print("measurement(bin): ");
        Serial.println(measurement, BIN);
        Serial.print("measurement(dec): ");
        Serial.println(measurement);
      }
      Serial.print("(mm): ");
      Serial.println(measurement_mm);
      Serial.print("(in): ");
      Serial.println(measurement_in, 3);
      if(DEBUG){
        Serial.print("mode number: ");
        Serial.println(mode);
      }

      // Serial.println(measurement_nut);
      Serial.println("-");


}





/////////////////////////////
// Initial Setup
//
void setup(){

  // use pin to keep-on softswitch, and to later shutdown
  pinMode(PIN_SOFT_POWER_OFF, OUTPUT);
  digitalWrite(PIN_SOFT_POWER_OFF, HIGH);

  // pinMode(LED_BUILTIN, OUTPUT);
 
  // Caliper inputs clk and data, thru NPN transistor and internal pullup res
  pinMode(PIN_CAL_CLK, INPUT_PULLUP);       
  pinMode(PIN_CAL_DATA, INPUT_PULLUP);       
 

  // Mode button, initialize
  pinMode(PIN_MODE_BUTTON, INPUT_PULLUP);





  // Set pin close to NPN input, 
  //  to make wireing cleaner
  // pinMode(PIN_NPN_GND, OUTPUT);
  // digitalWrite(PIN_NPN_GND, LOW);

  // Setup serial
  if(SERIAL_ENABLED){
    Serial.begin(57600);
    Serial.println("Start up calipers...");
  }else if(OLED_ENABLED){
    // no serial
  
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
      Serial.println(F("SSD1306 allocation failed"));
      for(;;); // Don't proceed, loop forever
    }else if(SERIAL_ENABLED){
      Serial.println("OLED initilized");
    }

    display.setTextSize(2); // integers 
    display.setTextColor(SSD1306_WHITE); // Draw white(or blue) text, otherwise its black

    // Initial OLED display
    display.clearDisplay();
    display.display(); 
    oled_display_icon();
    // delay(1000);

    oled_clear_text_zone();
  }
  delay(4000);
}




///////////////////////////
// Looping function
//
void loop()
{
  // put your main code here, to run repeatedly:

  // get the caliper's clk state for edge detection
  clk_cur_state = digitalRead(PIN_CAL_CLK);

  
  // clk falling edge detected
  if( clk_cur_state == 0 && clk_prev_state == 1){
    if(DEBUG){ // display data bit detected
      Serial.print("o");
    }
    process_cal_bit(); //process the new bit
    no_bit_detected_cnt=0; //bit was detected
  }else{
    // No clk detected, no data bit, 
    // if there is no data for X intervals, it is between readings
    // to avoid using partial data, reset bit storage until we are
    // sure it is the begining of packet

    if(DEBUG){ // display no data bit detected
      Serial.print(".");
    }
    no_bit_detected_cnt++;
    if(no_bit_detected_cnt > 30){ // FIXME (this may change)
      // time is longer than the pause between nibs
      if(DEBUG){ // display a reset
        Serial.print("^");
      }
      //   // therefor it must be between packets
      //   // so reseting counts
      data_bit_cnt = 0;
      data_cal = 0;
      no_bit_detected_cnt = 0;
    }

  }



  // Autoshut down 
  //   MCU+Caliper (reset soft-power switch)
  //   shuts down after SHUTDOWN_TIME
  if(measurement_in != measurement_in_old){
    tic_cnt_change = tic_cnt;
  }
  // else{
  //   if(1){
  //     if(tic_cnt % 100 == 0){
  //       display.setCursor(90,18);
  //       display.setTextSize(1);
  //       display.print(tic_cnt % 100);
  //       display.display();
  //     }
  //   }
  // }
  if( tic_cnt > (long)SHUTDOWN_TIME * 1000 * 1000 / CLK_TIC_TIME + tic_cnt_change){
    // shut down does not work if UART/programmer is attached, even if Vcc is cut
    if(SERIAL_ENABLED){
      Serial.println("Shutting down.");
    }



    digitalWrite(PIN_SOFT_POWER_OFF, LOW);
    digitalWrite(LED_BUILTIN, HIGH);
    // delay(1000); // MCU should be shut off but this will halt when debuging
    // delay(1000);
    // delay(1000);
    // add a no change check
  }
  // else if(tic_cnt == 2000){
    // digitalWrite(PIN_SOFT_POWER_OFF, HIGH);
    // tic_cnt = 0;
  // }



  // Mode Button detection
  mode_button_detect();

  // save clocks previous state for edge detection
  clk_prev_state = clk_cur_state;
  // saved for measurement changes to adjust shutdown
  measurement_in_old = measurement_in;

  // inc clk cnt
  tic_cnt++;

  // sleep
  _delay_us(CLK_TIC_TIME); // less than the bits per second of data packet

// oled_debug_text(String(mode));
}































// void oled_display_text(String line1, String line2){ //, const unsigned char (&icon)[288]){


//   // delay(2000);
//   // display.clearDisplay();
//   // display.drawBitmap(0,0,epd_bitmap_drill_alt1,32,32,1);
//   // display.display();
//   // delay(100);

//   // Line 
//   display.clearDisplay();
//   display.setTextSize(2);
//   display.setCursor(30,0); // 1st line position
//   // Display static text
//   display.println(line1);
//   display.display(); 

//   // Line 2
//   display.setCursor(30,19); // Second line position
//   // Display static text
//   display.println(line2);
//   display.display(); 


// }



// oled clear a section of icon area and write 'ALL'
void oled_add_icon_all_text(void){
  if(OLED_ENABLED){
      for(uint8_t x=0; x < 20; x++){
        for(uint8_t y=18; y <31; y++){
          display.drawPixel(x,y,0);
        }
      }
      display.setCursor(3,20);
      display.print("ALL");
      display.display();
  }
}




/// OLED display icon for modes
void oled_display_icon(void){

    // Logo
    //  Set logo here so it only has to update icon once 
    //  bitmap takes some time to update

  if(OLED_ENABLED){ // disable logos to save mem, otherwise run out of mem with serial 

    if(mode == 0){ //normal mode
      // maybe a goblin
      display.clearDisplay();
      display.setCursor(0,0);
      display.setTextSize(4);
      display.print("*");
      // if(DEBUG){
        display.setCursor(0,30);
        display.setTextSize(1);
        display.print("ssss"); //mode);
      // }
     
      display.display();
    }else if(mode == 1){ // 1/64, fraction mode
      // display.clearDisplay();
      // display.display();
      // display.setTextSize(2);
      // display.setCursor(0,0);
      // display.print("1");
      // display.setCursor(5,10);
      // display.print("/");
      // display.setCursor(9,18);
      // display.print("64");
      if(DEBUG){
        display.setCursor(0,20);
        display.setTextSize(1);
        display.print(mode);
      }
      display.drawBitmap(0, 5, epd_bitmap_64th_20b, 20, 20, 1); //  1/64 icon
      display.display();
    }else if(mode == 2){ // nut mode
      display.clearDisplay();
      if(DEBUG){
        display.setCursor(0,20);
        display.setTextSize(1);
        display.print(mode);
      }
      display.drawBitmap(0, 5, epd_bitmap_wrench_20b, 20, 20, 1); // a wrench icon
      display.display();
    }else if(mode == 3){ // screw mode
      display.clearDisplay();
      if(DEBUG){
        display.setCursor(0,20);
        display.setTextSize(1);
        display.print(mode);
      }
      display.drawBitmap(0, 0, epd_bitmap_screw_alt1_20x32, 20, 32, 1); // screw icon
      display.display();
          }else if(mode == 4){ // screw-all mode
      display.clearDisplay();
      if(DEBUG){
        display.setCursor(0,20);
        display.setTextSize(1);
        display.print(mode);
      }
      display.drawBitmap(0, 0, epd_bitmap_screw_alt1_20x32, 20, 32, 1); // screw icon

      oled_add_icon_all_text();
      display.display();
    }else if(mode == 5){ // drill mode
      display.clearDisplay();
      if(DEBUG){
        display.setCursor(0,20);
        display.setTextSize(1);
        display.print(mode);
      }
      display.drawBitmap(0, 5, epd_bitmap_drill_alt1_20b, 20, 20, 1); // cordless drill icon
      display.display();
    }else if(mode == 6){ // drill-all mode
      display.clearDisplay();
      if(DEBUG){
        display.setCursor(0,20);
        display.setTextSize(1);
        display.print(mode);
      }
      display.drawBitmap(0, 5, epd_bitmap_drill_alt1_20b, 20, 20, 1); // cordless drill icon
      oled_add_icon_all_text();
      display.display();
    }
  }
    // DISABLED wire sizes, ran out of progmem
    // else if(mode == 7){ // wire(solid) mode
    //   display.clearDisplay();
    //   if(DEBUG){
    //     display.setCursor(0,20);
    //     display.setTextSize(1);
    //     display.print(mode);
    //   }
    //   display.drawBitmap(0, 5, epd_bitmap_wire_solid_20b, 20, 20, 1); // solid wire icon
    //   display.display();
    // }else if(mode == 8){ // wire(stranded) mode
    //   display.clearDisplay();
    //   if(DEBUG){
    //     display.setCursor(0,20);
    //     display.setTextSize(1);
    //     display.print(mode);
    //   }
    //   display.drawBitmap(0, 5, epd_bitmap_wire_stranded_20b, 20, 20, 1); // stranded wire icon
    //   display.display();
    // }

}


void oled_debug_text(String debugtext){
  if(OLED_ENABLED){
   oled_clear_zone(0,64,0,10); //clear area
        // display.display();
    display.setCursor(0,0);
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.print("->"); 
    display.print(debugtext);
    // display.print("test");
    display.drawPixel(0,0, SSD1306_WHITE);
    display.display();
  }
}


// OLED - writes a line of text with pos and size
void oled_display_text2(uint8_t line, uint8_t pos_x, uint8_t pos_y, uint8_t size, String text){
  // display.clearDisplay();
  if(OLED_ENABLED){
  display.setTextSize(size);
  display.setCursor(pos_x,pos_y); // 1st line position
  // Display static text
  display.println(text);
  display.display(); 
  }
}




// this blanks out the text area, not the icon area
void oled_clear_text_zone(void){
  // it ends up the drawRect -> fastDrawLine - > loop of drawPixel
  // so i just do it here, and commented out fastdrawlines
  if(OLED_ENABLED){
    uint8_t x_min = 30;
    uint8_t x_max = 128;
    uint8_t y_min = 0;
    uint8_t y_max = 32;
    oled_clear_zone(x_min,x_max,y_min,y_max);
    // for(uint8_t x=x_min; x < x_max; x++){
      // for(uint8_t y=y_min; y < y_max; y++){
        // display.drawPixel(x,y, BLACK);
      // }
    // }
    // display.display();
  }
// display.fillRect(70, 10, 30, 30);
}


// this blanks out the text area, not the icon area
void oled_clear_zone(uint8_t x_min, uint8_t x_max, uint8_t y_min, uint8_t y_max){
  // it ends up the drawRect -> fastDrawLine - > loop of drawPixel
  // so i just do it here, and commented out fastdrawlines
  if(OLED_ENABLED){
  for(uint8_t x=x_min; x < x_max; x++){
    for(uint8_t y=y_min; y < y_max; y++){
      display.drawPixel(x,y, BLACK);
    }
  }
  display.display();
  }
// display.fillRect(70, 10, 30, 30);
}














//  End