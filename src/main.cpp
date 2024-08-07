/*
  ESP32-CYD LVGL Boilerplate
  ==========================

  Ivan Tarozzi (itarozzi@gmail.com) 2024




  Lib dependencies
  -----------------

  - "XPT2046_Touchscreen" library by Paul Stoffregen to use the Touchscreen - https://github.com/PaulStoffregen/XPT2046_Touchscreen 
  - "TFT_eSPI" library by Bodmer to use the TFT display - https://github.com/Bodmer/TFT_eSPI
  - "lvgl" library by LVGL - https://github.com/lvgl/lvgl
*/

#include <Arduino.h>

#define SW_NAME_REV "MyApp v1.0"

//************* software serial pins used for debug (if serial0 is used for communication) *************
#define RXPIN 27
#define TXPIN 22

// CYD RGB LED Pins
#define CYD_LED_RED 4
#define CYD_LED_GREEN 16
#define CYD_LED_BLUE 17


//************* lvgl and UI includes  *************
#include <lvgl.h>
#include "ui/ui.h"
#include "ui/vars.h"
//#include "ui/actions.h"
//#include "ui/images.h"

//************* TFT display and includes  *************

#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

// Touchscreen pins
#define XPT2046_IRQ 36   // T_IRQ
#define XPT2046_MOSI 32  // T_DIN
#define XPT2046_MISO 39  // T_OUT
#define XPT2046_CLK 25   // T_CLK
#define XPT2046_CS 33    // T_CS

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

// Touchscreen coordinates: (x, y) and pressure (z)
int x, y, z;

#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];


// TFT display
TFT_eSPI tft = TFT_eSPI();
// ******************



// ** Define your action here **

// If you define custom action to change pages, then you can use these

// void action_goto_page2(lv_event_t * e){
//   loadScreen(SCREEN_ID_PAGE1);
// }
//
// void action_goto_homek(lv_event_t * e){
//   loadScreen(SCREEN_ID_MAIN);
// }


// ** Define your vars getter and setter here, if native variables are used in your project **

// bool is_led_active = false;
//
// bool get_var_led_active()
// {
//   return is_led_active;
// }
//
// void set_var_led_active(bool value) {
//   is_led_active = value;
//
//   // Cheap Yellow Display built-in RGB LED is controlled with inverted logic
//   digitalWrite(CYD_LED_BLUE, value ? LOW : HIGH);
// }


// If logging is enabled, it will inform the user about what is happening in the library
void log_print(lv_log_level_t level, const char * buf) {
  LV_UNUSED(level);
  Serial.println(buf);
  Serial.flush();
}

// Get the Touchscreen data
void touchscreen_read(lv_indev_t * indev, lv_indev_data_t * data) {
  // Checks if Touchscreen was touched, and prints X, Y and Pressure (Z)
  if(touchscreen.tirqTouched() && touchscreen.touched()) {
    // Get Touchscreen points
    TS_Point p = touchscreen.getPoint();
    // Calibrate Touchscreen points with map function to the correct width and height
    x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
    y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);
    z = p.z;

    data->state = LV_INDEV_STATE_PRESSED;

    // Set the coordinates
    data->point.x = x;
    data->point.y = y;
    // String touch_data = "X = " + String(x) + "  Y = " + String(y) + "  Z = " + String(z);
    // Serial.println(touch_data);
  }
  else {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}


// lvgl initialization for esp32 board
void lv_init_esp32(void) {

  // Register print function for debugging
  lv_log_register_print_cb(log_print);

  // Start the SPI for the touchscreen and init the touchscreen
  touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  
  touchscreen.begin(touchscreenSPI);
  // Set the Touchscreen rotation in portrait mode
  touchscreen.setRotation(3);  // 2:vertical / 3:horizontal

  // Create a display object
  lv_display_t * disp;
  // Initialize the TFT display using the TFT_eSPI library
  disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));
  
  // set rotation mode
  tft.setRotation(3);  // 0 or 1 for  portrait / 1 or 3 for landscape


  // Initialize an LVGL input device object (Touchscreen)
  lv_indev_t * indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  // Set the callback function to read Touchscreen input
  lv_indev_set_read_cb(indev, touchscreen_read);


  // you can define TFT_INVERTED as compiler param in platformio.ini
  #ifdef TFT_INVERTED
    tft.invertDisplay(true);
  #else
    tft.invertDisplay(false);
  #endif

}

void setup() {
  String LVGL_Arduino = String("LVGL Library Version: ") + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

  // Serial.begin(19200);
  Serial.begin(115200, SERIAL_8N1, RXPIN, TXPIN);
  
  Serial.println(SW_NAME_REV);
  Serial.println(LVGL_Arduino);

  pinMode(CYD_LED_RED, OUTPUT);
  pinMode(CYD_LED_GREEN, OUTPUT);
  pinMode(CYD_LED_BLUE, OUTPUT);

  digitalWrite(CYD_LED_BLUE, HIGH);
  digitalWrite(CYD_LED_GREEN, HIGH);
  digitalWrite(CYD_LED_RED, HIGH);

  


/*
  tft.init();
  tft.setRotation(2);*/

  // // Start LVGL
  lv_init();

  // // Init TFT and Touch for esp32
  lv_init_esp32();


  // Integrate EEZ Studio GUI
  ui_init();

}



void loop() {

  static long last_ms = 0;

  long now_ms = millis();

  // your task here or in callbacks
  // ...


  lv_task_handler();  // let the GUI do its work
  lv_tick_inc(now_ms - last_ms);     // tell LVGL how much time has passed

  last_ms = now_ms;
  delay(5);           // let this time pass

}
