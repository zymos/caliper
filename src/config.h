
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
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// OLED display TWI address
  // Address 0x3C for 128x32
  // 0x78 -> 0x3C (for the 128x64) set on back
  // 0x7A -> 0x3D (for the 128x64)
#define OLED_ADDR   0x3C
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
// #define SSD1306_NO_SPLASH 1

#define OLED_X_POS_DEFAULT 30 // default start pos for text
#define Y_POS_2ND_LINE_DEFAULT 18 // default start Y-pos for second line text


// Configuration
#define DEBUG 0 // debug messages, UART (SERIAL must be enabled)
#define DEBUG2 0 // more debug, UART (SERIAL must be enabled)
#define OLED_DEBUG 0 // output debug info on OLED
// #define CALC_ALL_SIZES 1 // debug to calc all sizes, output on UART
#define SERIAL_ENABLED 0 // enable serial output UART, when enabled, oled is disabled to avoid mem overload

#define OLED_ENABLED 1 // you may have to disable when SERIAL_ENABLED

// #define SHUTDOWN_TIME 90 //seconds
#define SHUTDOWN_TIME 999 //seconds

#define CLK_TIC_TIME 50 // microseconds (for loop)




// Caliper config
#define   T_delay_before_packet 20000 //us
#define   T_clock_check 100 // us



#define MAX_MODES 6  // number of modes, increase to add different sizings
