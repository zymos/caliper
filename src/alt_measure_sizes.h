///////////////////////////////////////////////////////////////////////////////////
// Alt sizing types
//
// nut, screw wire
//
// probable could do in a single fuction instead but im not smart enough
//


#pragma once
#include <Arduino.h>  // for type definitions

#include <Arduino.h>

// OLED libraries
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Local
#include "tables.h" // data for nut/screw/drill/etc sizes
#include "PROGMEM_readAnything.h" // some fuctions to open PROGMEM data
#include "common.h" //global vars
#include "config.h" //config vars, pin assignments
#include "bitmaps.h" // icons
#include "oled.h" // oled functions



void calc_screw_all(uint8_t output_serial, uint8_t output_oled){
//   // calc the closest standard value

  String text_s = "";
  String text_s1 = "";
  String text_s2 = "";
  String text_s3 = "";
  String sign = "";
 
  String text_s_m = "";
  String text_s1_m = "";
  String text_s2_m = "";
  String text_s3_m = ""; 
  // example text
  // '7/32"           +10%'
  // '#0, #1, 5/32    - 5%'

  float inches_std = 999;
  float inches_m = 999;
  uint8_t x=0;
  uint8_t set = 0;
  float percent = 0;

  alt_measur_table_6 thisItem; // 6 char length
  alt_measur_table_4 thisItem_m; // 6 char length
  // alt_measur_table nextItem;
  // get first element
  PROGMEM_readAnything(&screw [0], thisItem);
  // PROGMEM_readAnything(&screw_m [0], thisItem_m);
  
  
  // M1 < #1
  if(measurement_in < thisItem.inches){ // smaller than smallest nut
    text_s1 = String("< min");
    text_s2 = String("screw size");  
    text_s = String(text_s1 + text_s2);


    set = 1;
  }else{
    while(thisItem.inches != 0){ // loop unit
      
      PROGMEM_readAnything(&screw [x], thisItem);
      // Serial.print('.');
      if(measurement_in <= thisItem.inches){
          set = 1;
          inches_std = thisItem.inches;
          percent = 100 * (thisItem.inches - measurement_in) / measurement_in;

          // percent_s = String(String(percent, 1) + "%");
          text_s1 = String(thisItem.text);
          // void = modf(percent, %)
          if(percent > 0){
            sign = "+";
          }
          text_s2 = String(sign + String(percent, 0) + "%");
          text_s = String(text_s1 + text_s2);
          break;
      }
      x++; 
    }

  }
  if(set == 0){
    text_s1 = "> max";
    text_s2 = "screw size";
    text_s = String(text_s1 + text_s2);

  }
 
  //
  //  extra bits
  //
  PROGMEM_readAnything(&screw_m [0], thisItem_m);
  // set = 0;
  if(measurement_in < thisItem_m.inches){ // smaller than smallest screw
    text_s1_m = String("< min");
    text_s2_m = String("screw size");

    text_s_m = String("< min size");
    set = 1;
    if(DEBUG2){Serial.println("size < M(min)," + String(thisItem_m.inches));}
  }else{
    while(thisItem_m.inches != 0){ // loop unit
      
      PROGMEM_readAnything(&screw_m [x], thisItem_m);
      //  PROGMEM_readAnything(&screw [x+1], nextItem);
      // Serial.print('.');
      if(measurement_in <= thisItem_m.inches){
        set = 1;
        inches_m = thisItem_m.inches;
        percent = 100 * (thisItem_m.inches - measurement_in) / measurement_in;

        // percent_s = String("(" + String(percent, 1) + "%)");
        text_s_m = String(String(thisItem_m.text) + "," + String(percent, 0) + "%");
        text_s1_m = String(thisItem_m.text);          
        if(percent > 0){
          sign = "+";
        }
        text_s2_m = String(sign + String(percent, 0) + "%");

        if(DEBUG2){Serial.println("M(size)" + String(thisItem_m.inches));}
        break;
      }

      x++; 
    }
  }
  if(set == 0){
    text_s_m = "> max size";
    text_s1_m = String("> max");
    text_s2_m = String("screw size");
    if(DEBUG2){Serial.println("size > M(max)");}
  } 

        // if(DEBUG2){Serial.println("M(size)qq" + String(thisItem_m.inches));}
  // check which is closest
  if(inches_m != 999 && inches_std == 999){
    //  std bits out of spec, numb bit found
    text_s = text_s_m;
    text_s1 = text_s1_m;
    text_s2 = text_s2_m;
    if(SERIAL_ENABLED){Serial.println(String("screw-all(S/M): min M closest" +  String(inches_std,3) + "/" + String(inches_m,3)));}
  }else if( abs(measurement_in - inches_std) > abs(measurement_in - inches_m)){
    // closest bit is numbered bits
    text_s = text_s_m;
    text_s1 = text_s1_m;
    text_s2 = text_s2_m;
    if(SERIAL_ENABLED){Serial.println(String("screw-all(S/M): M closest" + String(inches_std,3) + "/" + String(inches_m,3)));}
  }else{ 
    // else closest bit is std, so keep the text the same
    if(SERIAL_ENABLED){Serial.println(String("screw-all(S/M): std closest" +  String(inches_std,3) + "/" + String(inches_m,3)));}
  }

 if(output_oled && OLED_ENABLED){
    oled_clear_text_zone();
    oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
    oled_display_text2(0,OLED_X_POS_DEFAULT,Y_POS_2ND_LINE_DEFAULT,1,text_s2); // (line,pos_x,pos_y,size,text)
  }
  if(output_serial){
    Serial.print("Screw-all: ");
    Serial.println(text_s);
  }


  
}





void calc_screw(uint8_t output_serial, uint8_t output_oled){
//   // calc the closest standard value

  String text_s = "";
  String text_s1 = "";
  String text_s2 = "";
  String text_s3 = "";
  String sign = "";
  
  // example text
  // '7/32"           +10%'
  // '#0, #1, 5/32    - 5%'

  // Nuts
  uint8_t x=0;
  uint8_t set = 0;
  float percent = 0;

  alt_measur_table_6 thisItem; // 6 char length
  // alt_measur_table nextItem;
  // get first element
  PROGMEM_readAnything(&screw [0], thisItem);

  if(measurement_in < thisItem.inches){ // smaller than smallest nut
    text_s1 = String("< min");
    text_s2 = String("screw size");  
    text_s = String(text_s1 + text_s2);
    set = 1;
  }else{
    while(thisItem.inches != 0){ // loop unit
      
      PROGMEM_readAnything(&screw [x], thisItem);
      // Serial.print('.');
      if(measurement_in <= thisItem.inches){
        set = 1;
          percent = 100 * (thisItem.inches - measurement_in) / measurement_in;

          // percent_s = String(String(percent, 1) + "%");
          text_s1 = String(thisItem.text);
          // void = modf(percent, %)
          if(percent > 0){
            sign = "+";
          }
          text_s2 = String(sign + String(percent, 0) + "%");
          text_s = String(text_s1 + text_s2);
          break;
      }
      x++; 
    }
  }
  if(set == 0){
    text_s1 = "> max";
    text_s2 = "screw size";
    text_s = String(text_s1 + text_s2);
  }
  
  if(output_oled && OLED_ENABLED){
    oled_clear_text_zone();
    oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
    oled_display_text2(0,OLED_X_POS_DEFAULT,Y_POS_2ND_LINE_DEFAULT,1,text_s2); // (line,pos_x,pos_y,size,text)
  }
  if(output_serial){
    Serial.print("Screw: ");
    Serial.println(text_s);
  }


  
}




// String calc_alt_sizes_ave(alt_measur_table* size_type, String type_s){

//   String text_s = "";
//   // example text
//   // '7/32"           +10%'
//   // '#0, #1, 5/32    - 5%'

//   // Nuts
//   uint8_t x=0;
//   uint8_t set = 0;
//   float percent = 0;

//   alt_measur_table thisItem;
//   // alt_measur_table nextItem;
//   // get first element
//   PROGMEM_readAnything(&size_type[0], thisItem);

//   if(measurement_in < thisItem.inches){ // smaller than smallest nut
//     text_s = String("< min" + type_s + " size");
//     set = 1;
//   }else{
//     while(thisItem.inches != 0){ // loop unit
      
//       PROGMEM_readAnything(&size_type [x], thisItem);
//       // Serial.print('.');
//       if(measurement_in <= thisItem.inches){
//         set = 1;
//           percent = 100 * (thisItem.inches - measurement_in) / measurement_in;

//           // percent_s = String("(" + String(percent, 1) + "%)");
//           text_s = String(String(thisItem.text) + "(" + String(percent, 0) + "%)");
//           break;
//       }
//       // if(measurement_in >= nut_table_inch[x] && measurement_in < nut_table_max[x]){
//       //   // found the correct size
//       //   set = 1;
//       //   if(measurement_in < nut_table_inches[x]){
//       //     percent = 100 * (nut_table_inches[x] - measurement_in) / measurement_in;
//       //     nut_text_s = String(String(nut_table_text[x]) + " -" + String(percent, 0) + "%");
//       //   }else{
//       //     percent = 100 * ( measurement_in - nut_table_inches[x])  / measurement_in;
//       //     nut_text_s = String(String(nut_table_text[x]) + " +" + String(percent, 0) + "%");
//       //   }
//       // }
//       x++; 
//     }
//   }
//   if(set == 0){
//     text_s = "> max " + type_s + "drill size";
//   }

//   if(output_serial){
//     Serial.print(String(type_s + "-bit: "));
//     Serial.println(text_s);
//   }

//   
// }




void calc_drill(uint8_t output_serial, uint8_t output_oled){

  String text_s = "";
  String text_s1 = "";
  String text_s2 = "";
  String text_s3 = "";
  String sign = "";
  // example text
  // '7/32"           +10%'
  // '#0, #1, 5/32    - 5%'

  // Nuts
  uint8_t x=0;
  uint8_t set = 0;
  float percent = 0;

  alt_measur_table_8 thisItem; // 8 char length
  // alt_measur_table prevItem;
  // alt_measur_table prev2Item;
  // alt_measur_table nextItem;


  // alt_measur_table nextItem;
  // get first element
  PROGMEM_readAnything(&drill [0], thisItem);

  if(measurement_in < thisItem.inches){ // smaller than smallest nut
    text_s1 = String("< min");
    text_s2 = String("drill size");

    text_s = String("< min size");
    set = 1;
  }else{
    while(thisItem.inches != 0){ // loop unit
      
      PROGMEM_readAnything(&drill [x], thisItem);
      //  PROGMEM_readAnything(&drill [x+1], nextItem);
      // Serial.print('.');
      if(measurement_in <= thisItem.inches){
        set = 1;
          percent = 100 * (thisItem.inches - measurement_in) / measurement_in;

          // percent_s = String("(" + String(percent, 1) + "%)");
          text_s = String(String(thisItem.text) + "," + String(percent, 0) + "%");
          text_s1 = String(thisItem.text);          
          if(percent > 0){
            sign = "+";
          }
          text_s2 = String(sign + String(percent, 0) + "%");

          break;
      }

      x++; 
    }


  }
  if(set == 0){
    text_s = "> max size";
    text_s1 = String("> max");
    text_s2 = String("drill size");

  }
  if(output_oled && OLED_ENABLED){
    oled_clear_text_zone();
    oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
    oled_display_text2(0,OLED_X_POS_DEFAULT,Y_POS_2ND_LINE_DEFAULT,1,text_s2); // (line,pos_x,pos_y,size,text)
  }
  if(output_serial){
    Serial.print("Drill: ");
    Serial.println(text_s);
  }

  
}


void calc_drill_all(uint8_t output_serial, uint8_t output_oled){

  String text_s = "";
  String text_s1 = "";
  String text_s2 = "";
  String text_s3 = "";
  String sign = "";
  String text_s_num = "";
  String text_s1_num = "";
  String text_s2_num = "";
  String text_s3_num = "";

  float inches_std = 999;
  float inches_num = 999;
  // example text
  // '7/32"           +10%'
  // '#0, #1, 5/32    - 5%'

  // Nuts
  uint8_t x=0;
  uint8_t set = 0;
  float percent = 0;

  alt_measur_table_8 thisItem;
  alt_measur_table_4 thisItem_num;
  // alt_measur_table prevItem;
  // alt_measur_table prev2Item;
  // alt_measur_table nextItem;


  // alt_measur_table nextItem;
  // get first element

  //
  //  standard bits
  // 
  PROGMEM_readAnything(&drill [0], thisItem);

  if(measurement_in < thisItem.inches){ // smaller than smallest drill
    text_s1 = String("< min");
    text_s2 = String("drill size");

    text_s = String("< min size");
    set = 1;
  }else{
    while(thisItem.inches != 0){ // loop unit
      
      PROGMEM_readAnything(&drill [x], thisItem);
      //  PROGMEM_readAnything(&drill [x+1], nextItem);
      // Serial.print('.');
      if(measurement_in <= thisItem.inches){
        set = 1;
        inches_std = thisItem.inches;
        percent = 100 * (thisItem.inches - measurement_in) / measurement_in;

        // percent_s = String("(" + String(percent, 1) + "%)");
        text_s = String(String(thisItem.text) + "," + String(percent, 0) + "%");
        text_s1 = String(thisItem.text);          
        if(percent > 0){
          sign = "+";
        }
        text_s2 = String(sign + String(percent, 0) + "%");

        break;
      }

      x++; 
    }
  }
  if(set == 0){
    text_s_num = "> max size";
    text_s1_num = String("> max");
    text_s2_num = String("drill size");
  } 
  //
  //  extra bits
  //
  PROGMEM_readAnything(&drill_num [0], thisItem_num);

  if(measurement_in < thisItem_num.inches){ // smaller than smallest drill
    text_s1_num = String("< min");
    text_s2_num = String("drill size");

    text_s_num = String("< min size");
    set = 1;
  }else{
    while(thisItem_num.inches != 0){ // loop unit
      
      PROGMEM_readAnything(&drill_num [x], thisItem_num);
      //  PROGMEM_readAnything(&drill [x+1], nextItem);
      // Serial.print('.');
      if(measurement_in <= thisItem_num.inches){
        set = 1;
        inches_num = thisItem_num.inches;
        percent = 100 * (thisItem_num.inches - measurement_in) / measurement_in;

        // percent_s = String("(" + String(percent, 1) + "%)");
        text_s_num = String(String(thisItem_num.text) + "," + String(percent, 0) + "%");
        text_s1_num = String(thisItem_num.text);          
        if(percent > 0){
          sign = "+";
        }
        text_s2_num = String(sign + String(percent, 0) + "%");

        break;
      }

      x++; 
    }
  }
  if(set == 0){
    text_s_num = "> max size";
    text_s1_num = String("> max");
    text_s2_num = String("drill size");
  } 

  // check which is closest
  if(inches_num != 999 && inches_std == 999){
    //  std bits out of spec, numb bit found
    text_s = text_s_num;
    text_s1 = text_s1_num;
    text_s2 = text_s2_num;
    if(SERIAL_ENABLED){Serial.println(String("Drill-all(S/N): min num-bit closest" +  String(inches_std,3) + "/" + String(inches_num,3)));}
  }else if( abs(measurement_in - inches_std) > abs(measurement_in - inches_num)){
    // closest bit is numbered bits
    text_s = text_s_num;
    text_s1 = text_s1_num;
    text_s2 = text_s2_num;
    if(SERIAL_ENABLED){Serial.println(String("Drill-all(S/N): num-bit closest" + String(inches_std,3) + "/" + String(inches_num,3)));}
  }else{ 
    // else closest bit is std, so keep the text the same
    if(SERIAL_ENABLED){Serial.println(String("Drill-all(S/N): std closest" +  String(inches_std,3) + "/" + String(inches_num,3)));}
  }


  if(output_oled && OLED_ENABLED){
    oled_clear_text_zone();
    oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
    oled_display_text2(0,OLED_X_POS_DEFAULT,Y_POS_2ND_LINE_DEFAULT,1,text_s2); // (line,pos_x,pos_y,size,text)
  }
  if(output_serial){
    Serial.print("Drill-all: ");
    Serial.println(text_s);
  }

  
}





void calc_fraction(uint8_t output_serial, uint8_t output_oled){
  // Fractions
  //    shows +/- percenage greater-than/less-than

  String name_s = "Fraction";

  // initialize
  uint8_t x=0;
  uint8_t set = 0;
  float percent = 0;
  String percent_s = "";
  String text_s = "";
  String text_s1 = "";
  String text_s2 = "";
  String text_s3 = "";
  String sign = "";
  String alt_sign = "  ";

oled_debug_text("ssnns");

  // split interger and fraction of currect reading
  //  data table only has up to 1 to save mem space
  double intpart, fracpart;
  String inttext = "";
  fracpart = modf(measurement_in, &intpart);
    // Serial.println(intpart);
  if(intpart >= 1){
    inttext = String(String(intpart,0) + "-");
    inttext.trim();
  }
  // float measurement_tmp = measurement_in;

 

  //initalize
  alt_measur_table_6 thisItem;
  alt_measur_table_6 nextItem;
  // get first element
  PROGMEM_readAnything(&fraction [0], thisItem);
  if(fracpart < thisItem.inches *0.5 ){ // smaller than smallest 
    text_s1 = "0\"";
    text_s2 = "";
    set = 1;
  }else{
    // loop through element until it matches
    while(thisItem.inches != 0){


      PROGMEM_readAnything(&fraction [x], thisItem);
      PROGMEM_readAnything(&fraction [x+1], nextItem);

      if( 
        fracpart < (thisItem.inches + nextItem.inches)/2
        &&  nextItem.inches != 0
        ){ 
      //   // percentage sign        
          percent = 100 * (thisItem.inches - fracpart) / fracpart;  
          percent_s = String(percent,0);
          // percent_s.trim();
          // Serial.print(percent);
          // if(fracpart >= fraction_table_inches[x]){
            // alt_sign = "(+";
          text_s1 = String(String(inttext) + String(thisItem.text));
          if(percent > 0){
            sign = "+";
          }
          text_s2 = String(sign + percent_s + "%");
          percent_s = String(String(percent, 0) + "%");
          // }else{
            // percent_s = String("(" + String(percent, 1) + "%)");
          // }
          set = 1;

      //   // fraction_text_s = fraction_table_text[x]; //String(String(fraction_table_text[x]) + sign + String(percent, 0) + "%");
          // memcpy_P (&tmp_text, &text [x], sizeof tmp_text);
          text_s = String(inttext + thisItem.text + percent_s);
          break;
      }
      x++; 
    }

  }
  if(set == 0){
    text_s1 = "> 6\"";        
    text_s2 = "";
  }
  if(output_oled && OLED_ENABLED){
    oled_clear_text_zone();
    oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
    oled_display_text2(0,OLED_X_POS_DEFAULT,Y_POS_2ND_LINE_DEFAULT,1,text_s2); // (line,pos_x,pos_y,size,text)
  } 
  if(output_serial){
    Serial.print(name_s + ": ");
    Serial.println(text_s);
  }
}





void calc_nut(uint8_t output_serial, uint8_t output_oled){
  // Using measurements_in

  // char nut_sign[1];
  // char nut_text[20]; 
  String nut_text_s = "";
  String text_s1 = "";
  String text_s2 = "";
  String text_s3 = "";
  String sign = "";
  // example text
  // '7/32"           +10%'
  // '#0, #1, 5/32    - 5%'

  // Nuts
  uint8_t x=0;
  uint8_t set = 0;
  float percent = 0;
  String name = "nut";

  alt_measur_table_7 thisItem; // 7 char length
  // alt_measur_table nextItem;
  // get first element
  PROGMEM_readAnything(&nut [0], thisItem);

  if(measurement_in < thisItem.inches){ // smaller than smallest nut
    nut_text_s = String("< min nut size");
    text_s1 = String("< min");
    text_s2 = String(name + " size");

    set = 1;
  }else{
    while(thisItem.inches != 0){ // loop unit
      
      PROGMEM_readAnything(&nut [x], thisItem);
      // Serial.print('.');
      if(measurement_in <= thisItem.inches){
        set = 1;
          percent = 100 * (thisItem.inches - measurement_in) / measurement_in;
          if(percent > 0){
            sign = "+";
          }
          text_s2 = String(sign + String(percent, 0) + "%");
          text_s1 = String(thisItem.text);
          // percent_s = String("(" + String(percent, 1) + "%)");
          nut_text_s = String(String(thisItem.text) + "," + String(percent, 0) + "%");
          break;
      }

      x++; 
    }

  }
  if(set == 0){
    nut_text_s = "> max nut size";
    text_s1 = String("> max");
    text_s2 = String(name + " size");

  }
  if(output_oled && OLED_ENABLED){
    oled_clear_text_zone();
    oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
    oled_display_text2(0,OLED_X_POS_DEFAULT,Y_POS_2ND_LINE_DEFAULT,1,text_s2); // (line,pos_x,pos_y,size,text)
  }
  if(output_serial){
    Serial.print("Nut: ");
    Serial.println(nut_text_s);
  }
}








// DISABLED wire sizes, ran out of progmem
//
// // Wire AWG for solid wire
// void calc_awg_solid(uint8_t output_serial, uint8_t output_oled){

//   String name = "AWG";

//   // initialize
//   String text_s = "";
//   String text_s1 = "";
//   String text_s2 = "";
//   String text_s3 = "";
//   String sign = "";
//   uint8_t x=0;
//   uint8_t set = 0;
//   float percent = 0;
//   alt_measur_table thisItem;
  
//   // get first element
//   PROGMEM_readAnything(&wire_solid [0], thisItem); // get [text, inches] from mem

//   if(measurement_in < thisItem.inches){ // smaller than smallest 
//     text_s = String("< min AWG");
//     text_s1 = String("< min");
//     text_s2 = String("AWG size");
//     if(output_oled && OLED_ENABLED){
// 			oled_clear_text_zone();
//       oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
//       oled_display_text2(0,OLED_X_POS_DEFAULT,Y_POS_2ND_LINE_DEFAULT,1,text_s2); // (line,pos_x,pos_y,size,text)
//     }
//     set = 1;
//   }else{
//     while(thisItem.inches != 0){ // loop unit
//       PROGMEM_readAnything(&wire_solid [x], thisItem); // get [text, inches] from mem
//       if(measurement_in <= thisItem.inches){
//         set = 1;
//           percent = 100 * (thisItem.inches - measurement_in) / measurement_in;
//           if(percent > 0){
//             sign = "+";
//           }
//           text_s2 = String(sign + String(percent, 0) + "%");
//           text_s1 = String(thisItem.text);
//           text_s = String(String(thisItem.text) + "," + String(percent, 0) + "%");
//           break;
//       }
//       x++; 
//     }

//     if(set){
//       if(output_oled && OLED_ENABLED){
// 			  oled_clear_text_zone();
//         oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
//         oled_display_text2(0,OLED_X_POS_DEFAULT,Y_POS_2ND_LINE_DEFAULT,1,text_s2); // (line,pos_x,pos_y,size,text)
//       }
//     }
//   }
//   if(set == 0){
//     text_s = "> max AWG";
//     text_s1 = String("< min");
//     text_s2 = String("AWG");
//     if(output_oled && OLED_ENABLED){
// 			oled_clear_text_zone();
//       oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
//       oled_display_text2(0,OLED_X_POS_DEFAULT,Y_POS_2ND_LINE_DEFAULT,1,text_s2); // (line,pos_x,pos_y,size,text)
//     }
//   }

//   if(output_serial){
//     Serial.print(name + ": ");
//     Serial.println(text_s);
//   }
  
// }




// DISABLED wire sizes, ran out of progmem
// void calc_awg_stranded(uint8_t output_serial, uint8_t output_oled){
// // Wire AWG for stranded wire
//   String name = "AWG(str)";

//   // initialize
//   String text_s = "";
//   String text_s1 = "";
//   String text_s2 = "";
//   String text_s3 = "";
//   String sign = "";
//   uint8_t x=0;
//   uint8_t set = 0;
//   float percent = 0;
//   alt_measur_table thisItem;
  
//   // get first element
//   PROGMEM_readAnything(&wire_stranded [0], thisItem); // get [text, inches] from mem

//   if(measurement_in < thisItem.inches){ // smaller than smallest 
//     text_s = String("< min AWG");
//     text_s1 = String("< min");
//     text_s2 = String("AWG");
//     if(output_oled && OLED_ENABLED){
// 			oled_clear_text_zone();
//       oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
//       oled_display_text2(0,OLED_X_POS_DEFAULT,Y_POS_2ND_LINE_DEFAULT,1,text_s2); // (line,pos_x,pos_y,size,text)
//     }
//     set = 1;
//   }else{
//     // for(uint8_t x=0;)
//     while(thisItem.inches != 0){ // loop unit
//       PROGMEM_readAnything(&wire_solid [x], thisItem); // get [text, inches] from mem
//       if(measurement_in <= thisItem.inches){
//         set = 1;
//           percent = 100 * (thisItem.inches - measurement_in) / measurement_in;
//           if(percent > 0){
//             sign = "+";
//           }
//           text_s2 = String(sign + String(percent, 0) + "%");
//           text_s1 = String(thisItem.text);

//           text_s = String(String(thisItem.text) + "," + String(percent, 0) + "%");
//           break;
//       }
//       x++; 
//     }

//     if(set){
//       if(output_oled && OLED_ENABLED){
// 			  oled_clear_text_zone();
//         oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
//         oled_display_text2(0,OLED_X_POS_DEFAULT,Y_POS_2ND_LINE_DEFAULT,1,text_s2); // (line,pos_x,pos_y,size,text)
//       }
//     }
//   }
//   if(set == 0){
//     text_s = "> max AWG";
//     text_s1 = String("< min");
//     text_s2 = String("AWG");
//     if(output_oled && OLED_ENABLED){
// 			oled_clear_text_zone();
//       oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
//       oled_display_text2(0,OLED_X_POS_DEFAULT,Y_POS_2ND_LINE_DEFAULT,1,text_s2); // (line,pos_x,pos_y,size,text)
//     }
//   }

//   if(output_serial){
//     Serial.print(name + ": ");
//     Serial.println(text_s);
//   }
   
// }

