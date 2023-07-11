// #pragma once
// // Arduino libraries
// #include <Arduino.h>

// // OLED libraries
// #include <SPI.h>
// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>

// // Local
// #include "tables.h" // data for nut/screw/drill/etc sizes
// #include "PROGMEM_readAnything.h" // some fuctions to open PROGMEM data
// #include "alt_measure_sizes.h" // functions for sizing for nut, screw, drill-bit, etc
// #include "common.h" //global vars
// #include "config.h" //config vars, pin assignments
// #include "bitmaps.h" // icons
// #include "oled.h" // oled functions



// // void oled_display_text(String line1, String line2){ //, const unsigned char (&icon)[288]){


// //   // delay(2000);
// //   // display.clearDisplay();
// //   // display.drawBitmap(0,0,epd_bitmap_drill_alt1,32,32,1);
// //   // display.display();
// //   // delay(100);

// //   // Line 
// //   display.clearDisplay();
// //   display.setTextSize(2);
// //   display.setCursor(30,0); // 1st line position
// //   // Display static text
// //   display.println(line1);
// //   display.display(); 

// //   // Line 2
// //   display.setCursor(30,19); // Second line position
// //   // Display static text
// //   display.println(line2);
// //   display.display(); 


// // }



// // oled clear a section of icon area and write 'ALL'
// void oled_add_icon_all_text(void){
//   if(OLED_ENABLED){
//       for(uint8_t x=0; x < 20; x++){
//         for(uint8_t y=18; y <31; y++){
//           display.drawPixel(x,y,0);
//         }
//       }
//       display.setCursor(3,20);
//       display.print("ALL");
//       display.display();
//   }
// }




// /// OLED display icon for modes
// void oled_display_icon(void){

//     // Logo
//     //  Set logo here so it only has to update icon once 
//     //  bitmap takes some time to update

//   if(OLED_ENABLED){ // disable logos to save mem, otherwise run out of mem with serial 

//     if(mode == 0){ //normal mode
//       // maybe a goblin
//       display.clearDisplay();
//       display.setCursor(0,0);
//       display.setTextSize(4);
//       display.print("*");
//       // if(DEBUG){
//         display.setCursor(0,30);
//         display.setTextSize(1);
//         display.print("ssss"); //mode);
//       // }
     
//       display.display();
//     }else if(mode == 1){ // 1/64, fraction mode
//       // display.clearDisplay();
//       // display.display();
//       // display.setTextSize(2);
//       // display.setCursor(0,0);
//       // display.print("1");
//       // display.setCursor(5,10);
//       // display.print("/");
//       // display.setCursor(9,18);
//       // display.print("64");
//       if(DEBUG){
//         display.setCursor(0,20);
//         display.setTextSize(1);
//         display.print(mode);
//       }
//       display.drawBitmap(0, 5, epd_bitmap_64th_20b, 20, 20, 1); //  1/64 icon
//       display.display();
//     }else if(mode == 2){ // nut mode
//       display.clearDisplay();
//       if(DEBUG){
//         display.setCursor(0,20);
//         display.setTextSize(1);
//         display.print(mode);
//       }
//       display.drawBitmap(0, 5, epd_bitmap_wrench_20b, 20, 20, 1); // a wrench icon
//       display.display();
//     }else if(mode == 3){ // screw mode
//       display.clearDisplay();
//       if(DEBUG){
//         display.setCursor(0,20);
//         display.setTextSize(1);
//         display.print(mode);
//       }
//       display.drawBitmap(0, 0, epd_bitmap_screw_alt1_20x32, 20, 32, 1); // screw icon
//       display.display();
//           }else if(mode == 4){ // screw-all mode
//       display.clearDisplay();
//       if(DEBUG){
//         display.setCursor(0,20);
//         display.setTextSize(1);
//         display.print(mode);
//       }
//       display.drawBitmap(0, 0, epd_bitmap_screw_alt1_20x32, 20, 32, 1); // screw icon

//       oled_add_icon_all_text();
//       display.display();
//     }else if(mode == 5){ // drill mode
//       display.clearDisplay();
//       if(DEBUG){
//         display.setCursor(0,20);
//         display.setTextSize(1);
//         display.print(mode);
//       }
//       display.drawBitmap(0, 5, epd_bitmap_drill_alt1_20b, 20, 20, 1); // cordless drill icon
//       display.display();
//     }else if(mode == 6){ // drill-all mode
//       display.clearDisplay();
//       if(DEBUG){
//         display.setCursor(0,20);
//         display.setTextSize(1);
//         display.print(mode);
//       }
//       display.drawBitmap(0, 5, epd_bitmap_drill_alt1_20b, 20, 20, 1); // cordless drill icon
//       oled_add_icon_all_text();
//       display.display();
//     }
//   }
//     // DISABLED wire sizes, ran out of progmem
//     // else if(mode == 7){ // wire(solid) mode
//     //   display.clearDisplay();
//     //   if(DEBUG){
//     //     display.setCursor(0,20);
//     //     display.setTextSize(1);
//     //     display.print(mode);
//     //   }
//     //   display.drawBitmap(0, 5, epd_bitmap_wire_solid_20b, 20, 20, 1); // solid wire icon
//     //   display.display();
//     // }else if(mode == 8){ // wire(stranded) mode
//     //   display.clearDisplay();
//     //   if(DEBUG){
//     //     display.setCursor(0,20);
//     //     display.setTextSize(1);
//     //     display.print(mode);
//     //   }
//     //   display.drawBitmap(0, 5, epd_bitmap_wire_stranded_20b, 20, 20, 1); // stranded wire icon
//     //   display.display();
//     // }

// }


// void oled_debug_text(String debugtext){
//   if(OLED_ENABLED){
//    oled_clear_zone(0,64,0,10); //clear area
//         display.display();
//     display.setCursor(0,0);
//     display.setTextColor(SSD1306_WHITE);
//     display.setTextSize(1);
//        display.print("010"); 
//     display.print(debugtext);
//     // display.print("test");
//         display.display();
//           display.drawPixel(0,0, SSD1306_WHITE);
//     display.display();
//   }
// }


// // OLED - writes a line of text with pos and size
// void oled_display_text2(uint8_t line, uint8_t pos_x, uint8_t pos_y, uint8_t size, String text){
//   // display.clearDisplay();
//   if(OLED_ENABLED){
//   display.setTextSize(size);
//   display.setCursor(pos_x,pos_y); // 1st line position
//   // Display static text
//   display.println(text);
//   display.display(); 
//   }
// }




// // this blanks out the text area, not the icon area
// void oled_clear_text_zone(void){
//   // it ends up the drawRect -> fastDrawLine - > loop of drawPixel
//   // so i just do it here, and commented out fastdrawlines
//   if(OLED_ENABLED){
//     uint8_t x_min = 30;
//     uint8_t x_max = 128;
//     uint8_t y_min = 0;
//     uint8_t y_max = 32;
//     oled_clear_zone(x_min,x_max,y_min,y_max);
//     // for(uint8_t x=x_min; x < x_max; x++){
//       // for(uint8_t y=y_min; y < y_max; y++){
//         // display.drawPixel(x,y, BLACK);
//       // }
//     // }
//     // display.display();
//   }
// // display.fillRect(70, 10, 30, 30);
// }


// // this blanks out the text area, not the icon area
// void oled_clear_zone(uint8_t x_min, uint8_t x_max, uint8_t y_min, uint8_t y_max){
//   // it ends up the drawRect -> fastDrawLine - > loop of drawPixel
//   // so i just do it here, and commented out fastdrawlines
//   if(OLED_ENABLED){
//   for(uint8_t x=x_min; x < x_max; x++){
//     for(uint8_t y=y_min; y < y_max; y++){
//       display.drawPixel(x,y, BLACK);
//     }
//   }
//   display.display();
//   }
// // display.fillRect(70, 10, 30, 30);
// }

