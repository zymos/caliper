///////////////////////////////////////////////////////////////////////////////////
// Alt sizing types
//
// nut, screw wire
//
// probable could do in a single fuction instead but im not smart enough
//


#pragma once
#include <Arduino.h>  // for type definitions
#include "common.h" //global vars
#include "config.h" //config vars
#include "PROGMEM_readAnything.h"




void calc_screw_all(uint8_t output_serial, uint8_t output_oled){
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

  alt_measur_table thisItem;
  // alt_measur_table nextItem;
  // get first element
  PROGMEM_readAnything(&screw_all [0], thisItem);

  if(measurement_in < thisItem.inches){ // smaller than smallest nut
    text_s1 = String("< min");
    text_s2 = String("screw size");  
    text_s = String(text_s1 + text_s2);

    if(output_oled){
			oled_clear_text_zone();
      oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
      oled_display_text2(0,OLED_X_POS_DEFAULT,Y_POS_2ND_LINE_DEFAULT,1,text_s2); // (line,pos_x,pos_y,size,text)
    }
    set = 1;
  }else{
    while(thisItem.inches != 0){ // loop unit
      
      PROGMEM_readAnything(&screw_all [x], thisItem);
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
      // if(measurement_in >= nut_table_inch[x] && measurement_in < nut_table_max[x]){
      //   // found the correct size
      //   set = 1;
      //   if(measurement_in < nut_table_inches[x]){
      //     percent = 100 * (nut_table_inches[x] - measurement_in) / measurement_in;
      //     nut_text_s = String(String(nut_table_text[x]) + " -" + String(percent, 0) + "%");
      //   }else{
      //     percent = 100 * ( measurement_in - nut_table_inches[x])  / measurement_in;
      //     nut_text_s = String(String(nut_table_text[x]) + " +" + String(percent, 0) + "%");
      //   }
      // }
      x++; 
    }
    if(set){
      if(output_oled){
			  oled_clear_text_zone();
        oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
        oled_display_text2(0,OLED_X_POS_DEFAULT,Y_POS_2ND_LINE_DEFAULT,1,text_s2); // (line,pos_x,pos_y,size,text)
      }
    }
  }
  if(set == 0){
    text_s1 = "> max";
    text_s2 = "screw size";
    text_s = String(text_s1 + text_s2);
    if(output_oled){
			oled_clear_text_zone();
      oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
      oled_display_text2(0,OLED_X_POS_DEFAULT,Y_POS_2ND_LINE_DEFAULT,1,text_s2); // (line,pos_x,pos_y,size,text)
    }
  }

  if(output_serial){
    Serial.print("Screw: ");
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

  alt_measur_table thisItem;
  // alt_measur_table nextItem;
  // get first element
  PROGMEM_readAnything(&screw [0], thisItem);

  if(measurement_in < thisItem.inches){ // smaller than smallest nut
    text_s1 = String("< min");
    text_s2 = String("screw size");  
    text_s = String(text_s1 + text_s2);

    if(output_oled){
			oled_clear_text_zone();
      oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
      oled_display_text2(0,OLED_X_POS_DEFAULT,Y_POS_2ND_LINE_DEFAULT,1,text_s2); // (line,pos_x,pos_y,size,text)
    }
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
      // if(measurement_in >= nut_table_inch[x] && measurement_in < nut_table_max[x]){
      //   // found the correct size
      //   set = 1;
      //   if(measurement_in < nut_table_inches[x]){
      //     percent = 100 * (nut_table_inches[x] - measurement_in) / measurement_in;
      //     nut_text_s = String(String(nut_table_text[x]) + " -" + String(percent, 0) + "%");
      //   }else{
      //     percent = 100 * ( measurement_in - nut_table_inches[x])  / measurement_in;
      //     nut_text_s = String(String(nut_table_text[x]) + " +" + String(percent, 0) + "%");
      //   }
      // }
      x++; 
    }
    if(set){
      if(output_oled){
			  oled_clear_text_zone();
        oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
        oled_display_text2(0,OLED_X_POS_DEFAULT,Y_POS_2ND_LINE_DEFAULT,1,text_s2); // (line,pos_x,pos_y,size,text)
      }
    }
  }
  if(set == 0){
    text_s1 = "> max";
    text_s2 = "screw size";
    text_s = String(text_s1 + text_s2);
    if(output_oled){
			oled_clear_text_zone();
      oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
      oled_display_text2(0,OLED_X_POS_DEFAULT,Y_POS_2ND_LINE_DEFAULT,1,text_s2); // (line,pos_x,pos_y,size,text)
    }
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

  alt_measur_table thisItem;
  // alt_measur_table prevItem;
  // alt_measur_table prev2Item;
  // alt_measur_table nextItem;


  // alt_measur_table nextItem;
  // get first element
  PROGMEM_readAnything(&drill [0], thisItem);

  if(measurement_in < thisItem.inches){ // smaller than smallest nut
    text_s1 = String("< min");
    text_s2 = String("drill size");
    if(output_oled){
			oled_clear_text_zone();
      oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
      oled_display_text2(0,OLED_X_POS_DEFAULT,Y_POS_2ND_LINE_DEFAULT,1,text_s2); // (line,pos_x,pos_y,size,text)
    }
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
          // if(x >= 1){
          //   PROGMEM_readAnything(&drill [x-1], prevItem);
          //   text_s2 = String(prevItem.text + String(" <<") + text_s2);
          // }
          // if(nextItem.inches != 0){
          //   text_s2 = String(text_s2 + String(">> ") + String(nextItem.text));
          // }

          // if(x >= 2){
          //   PROGMEM_readAnything(&drill [x-2], prev2Item);
          //   text_s2 = String(prev2Item.text + '>>' +text_s2);
          // }
          break;
      }
      // if(measurement_in >= nut_table_inch[x] && measurement_in < nut_table_max[x]){
      //   // found the correct size
      //   set = 1;
      //   if(measurement_in < nut_table_inches[x]){
      //     percent = 100 * (nut_table_inches[x] - measurement_in) / measurement_in;
      //     nut_text_s = String(String(nut_table_text[x]) + " -" + String(percent, 0) + "%");
      //   }else{
      //     percent = 100 * ( measurement_in - nut_table_inches[x])  / measurement_in;
      //     nut_text_s = String(String(nut_table_text[x]) + " +" + String(percent, 0) + "%");
      //   }
      // }
      x++; 
    }

    if(set){
      if(output_oled){
			  oled_clear_text_zone();
        oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
        oled_display_text2(0,OLED_X_POS_DEFAULT,Y_POS_2ND_LINE_DEFAULT,1,text_s2); // (line,pos_x,pos_y,size,text)
      }
    }
  }
  if(set == 0){
    text_s = "> max size";
    text_s1 = String("> max");
    text_s2 = String("drill size");
    if(output_oled){
			oled_clear_text_zone();
      oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
      oled_display_text2(0,OLED_X_POS_DEFAULT,Y_POS_2ND_LINE_DEFAULT,1,text_s2); // (line,pos_x,pos_y,size,text)
    }
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
  // example text
  // '7/32"           +10%'
  // '#0, #1, 5/32    - 5%'

  // Nuts
  uint8_t x=0;
  uint8_t set = 0;
  float percent = 0;

  alt_measur_table thisItem;
  // alt_measur_table prevItem;
  // alt_measur_table prev2Item;
  // alt_measur_table nextItem;


  // alt_measur_table nextItem;
  // get first element
  PROGMEM_readAnything(&drill_all [0], thisItem);

  if(measurement_in < thisItem.inches){ // smaller than smallest nut
    text_s1 = String("< min");
    text_s2 = String("drill size");
    if(output_oled){
			oled_clear_text_zone();
      oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
      oled_display_text2(0,OLED_X_POS_DEFAULT,Y_POS_2ND_LINE_DEFAULT,1,text_s2); // (line,pos_x,pos_y,size,text)
    }
    text_s = String("< min size");
    set = 1;
  }else{
    while(thisItem.inches != 0){ // loop unit
      
      PROGMEM_readAnything(&drill_all [x], thisItem);
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
          // if(x >= 1){
          //   PROGMEM_readAnything(&drill [x-1], prevItem);
          //   text_s2 = String(prevItem.text + String(" <<") + text_s2);
          // }
          // if(nextItem.inches != 0){
          //   text_s2 = String(text_s2 + String(">> ") + String(nextItem.text));
          // }

          // if(x >= 2){
          //   PROGMEM_readAnything(&drill [x-2], prev2Item);
          //   text_s2 = String(prev2Item.text + '>>' +text_s2);
          // }
          break;
      }
      // if(measurement_in >= nut_table_inch[x] && measurement_in < nut_table_max[x]){
      //   // found the correct size
      //   set = 1;
      //   if(measurement_in < nut_table_inches[x]){
      //     percent = 100 * (nut_table_inches[x] - measurement_in) / measurement_in;
      //     nut_text_s = String(String(nut_table_text[x]) + " -" + String(percent, 0) + "%");
      //   }else{
      //     percent = 100 * ( measurement_in - nut_table_inches[x])  / measurement_in;
      //     nut_text_s = String(String(nut_table_text[x]) + " +" + String(percent, 0) + "%");
      //   }
      // }
      x++; 
    }

    if(set){
      if(output_oled){
			  oled_clear_text_zone();
        oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
        oled_display_text2(0,OLED_X_POS_DEFAULT,Y_POS_2ND_LINE_DEFAULT,1,text_s2); // (line,pos_x,pos_y,size,text)
      }
    }
  }
  if(set == 0){
    text_s = "> max size";
    text_s1 = String("> max");
    text_s2 = String("drill size");
    if(output_oled){
			oled_clear_text_zone();
      oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
      oled_display_text2(0,OLED_X_POS_DEFAULT,Y_POS_2ND_LINE_DEFAULT,1,text_s2); // (line,pos_x,pos_y,size,text)
    }
  }

  if(output_serial){
    Serial.print("Drill: ");
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
  alt_measur_table thisItem;
  alt_measur_table nextItem;
  // get first element
  PROGMEM_readAnything(&fraction [0], thisItem);
  if(fracpart < thisItem.inches *0.5 ){ // smaller than smallest 
    text_s1 = "0\"";
    if(output_oled){
			oled_clear_text_zone();
      oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
    }
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

    if(set){
      if(output_oled){
			  oled_clear_text_zone();
        oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
        oled_display_text2(0,OLED_X_POS_DEFAULT,Y_POS_2ND_LINE_DEFAULT,1,text_s2); // (line,pos_x,pos_y,size,text)
      }
    }
  }
  if(set == 0){
    text_s1 = "> 6\"";        
    if(output_oled){
			oled_clear_text_zone();
      oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
    }

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

  alt_measur_table thisItem;
  // alt_measur_table nextItem;
  // get first element
  PROGMEM_readAnything(&nut [0], thisItem);

  if(measurement_in < thisItem.inches){ // smaller than smallest nut
    nut_text_s = String("< min nut size");
    text_s1 = String("< min");
    text_s2 = String(name + " size");
    if(output_oled){
			oled_clear_text_zone();
      oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
      oled_display_text2(0,OLED_X_POS_DEFAULT,Y_POS_2ND_LINE_DEFAULT,1,text_s2); // (line,pos_x,pos_y,size,text)
    }
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
      // if(measurement_in >= nut_table_inch[x] && measurement_in < nut_table_max[x]){
      //   // found the correct size
      //   set = 1;
      //   if(measurement_in < nut_table_inches[x]){
      //     percent = 100 * (nut_table_inches[x] - measurement_in) / measurement_in;
      //     nut_text_s = String(String(nut_table_text[x]) + " -" + String(percent, 0) + "%");
      //   }else{
      //     percent = 100 * ( measurement_in - nut_table_inches[x])  / measurement_in;
      //     nut_text_s = String(String(nut_table_text[x]) + " +" + String(percent, 0) + "%");
      //   }
      // }
      x++; 
    }

    if(set){
      if(output_oled){
			  oled_clear_text_zone();
        oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
        oled_display_text2(0,OLED_X_POS_DEFAULT,Y_POS_2ND_LINE_DEFAULT,1,text_s2); // (line,pos_x,pos_y,size,text)
      }
    }
  }
  if(set == 0){
    nut_text_s = "> max nut size";
    text_s1 = String("> max");
    text_s2 = String(name + " size");
    if(output_oled){
			oled_clear_text_zone();
      oled_display_text2(0,OLED_X_POS_DEFAULT,0,2,text_s1); // (line,pos_x,pos_y,size,text)
      oled_display_text2(0,OLED_X_POS_DEFAULT,Y_POS_2ND_LINE_DEFAULT,1,text_s2); // (line,pos_x,pos_y,size,text)
    }
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
//     if(output_oled){
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
//       if(output_oled){
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
//     if(output_oled){
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
//     if(output_oled){
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
//       if(output_oled){
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
//     if(output_oled){
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

