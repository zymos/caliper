
///////////////////////////////////////////////////////////
// Pin Assignments
//
#define   PIN_CAL_DATA        4    // data pin from caliper (yellow wire)
#define   PIN_CAL_CLK         5     // clock pin from caliper (brown wire)
#define   PIN_SOFT_POWER_OFF  7 //pin turn off, soft switch circuit (yellow wire)
#define   PIN_MODE_BUTTON     3 // (orange wire)

// #define   PIN_OLED_SDA      PIN_A4
//#define   PIN_OLED_SCL    PIN_A5


// OLED
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
// OLED display TWI address
  // Address 0x3C for 128x32
  // 0x3D (for the 128x64)
#define OLED_ADDR   0x3C
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
// #define SSD1306_NO_SPLASH 1

#define OLED_X_POS_DEFAULT 37 // default start pos for text
#define Y_POS_2ND_LINE_DEFAULT 18 // default start Y-pos for second line text


// Configuration
#define DEBUG 0 // debug messages, UART
// #define CALC_ALL_SIZES 1 // debug to calc all sizes, output on UART
#define SERIAL_ENABLED 0 // enable serial output UART


#define SHUTDOWN_TIME 990 //seconds
#define CLK_TIC_TIME 50 // microseconds (for loop)




// Caliper config
#define   T_delay_before_packet 20000 //us
#define   T_clock_check 100 // us



#define MAX_MODES 6  // number of modes
