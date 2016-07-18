#include <pebble.h>

enum Settings { setting_js_ready = 0, setting_hightlightColor, setting_standbyColor, setting_background };

static Window *mainWindow;

static Layer *layerMins;
static Layer *layerBatt;
static Layer *layerSteps;

GFont fontSquareS;
GFont fontSquareM;

TextLayer *tLayerMonth;
TextLayer *tLayerDoM;
TextLayer *tLayerDoY;

static GColor colorHighlight;
static GColor colorStandBy;
static int background = 0;

//static AppSync app;
//static uint8_t buffer[256];

static int tensX[] = { 48, 96, 96, 48, 0, 0 };
static int tensY[] = { 0, 24, 72, 96, 72, 24 };
static int hourX[] = { 20, 28, 28, 28, 28, 28, 20, 12, 6, 6, 6, 12 };
static int hourY[] = { 6, 6, 12, 20, 28, 28, 28, 28, 28, 20, 12, 6, };
static int hourW[] = { 8, 8, 14, 14, 14, 8, 8, 8, 14, 14, 14, 8 };
static int hourH[] = { 14, 14, 8, 8, 8, 14, 14, 14, 8, 8, 8, 14 };

static void draw_digit(GContext *context, int digit, int posX, int posY) {
  GColor colorF = background == 0 ? GColorWhite : GColorBlack;
  GColor colorB = background == 0 ? GColorBlack : GColorWhite;
  GColor colorH = colorHighlight; // (GColor) { .argb = (uint8_t)(0xC0 | colorHighlight) };

  graphics_context_set_fill_color(context, colorF);      
  graphics_fill_rect(context, GRect(posX, posY, 44, 44), 0, GCornerNone);
  graphics_context_set_fill_color(context, colorB);
  
  if (digit == 1) {
    graphics_fill_rect(context, GRect(30 + posX, posY, 14, 28), 0, GCornerNone);
    graphics_fill_rect(context, GRect(posX, 16 + posY, 14, 12), 0, GCornerNone);
    
    graphics_context_set_fill_color(context, colorB);      
    graphics_fill_rect(context, GRect(2 + posX, 2 + posY, 26, 12), 0, GCornerNone);
    graphics_fill_rect(context, GRect(2 + posX, 30 + posY, 40, 12), 0, GCornerNone);
    graphics_fill_rect(context, GRect(16 + posX, 14 + posY, 12, 16), 0, GCornerNone);
    
    graphics_context_set_fill_color(context, colorH);      
    graphics_fill_rect(context, GRect(3 + posX, 3 + posY, 24, 10), 0, GCornerNone);
    graphics_fill_rect(context, GRect(3 + posX, 31 + posY, 38, 10), 0, GCornerNone);
    graphics_fill_rect(context, GRect(17 + posX, 13 + posY, 10, 18), 0, GCornerNone);
  }
  else if (digit == 2) {
    graphics_context_set_fill_color(context, colorB);      
    graphics_fill_rect(context, GRect(2 + posX, 2 + posY, 40, 12), 0, GCornerNone);
    graphics_fill_rect(context, GRect(2 + posX, 16 + posY, 40, 12), 0, GCornerNone);
    graphics_fill_rect(context, GRect(2 + posX, 30 + posY, 40, 12), 0, GCornerNone);
    graphics_fill_rect(context, GRect(30 + posX, 14 + posY, 12, 2), 0, GCornerNone);
    graphics_fill_rect(context, GRect(2 + posX, 28 + posY, 12, 2), 0, GCornerNone);    
    
    graphics_context_set_fill_color(context, colorH);      
    graphics_fill_rect(context, GRect(3 + posX, 3 + posY, 38, 10), 0, GCornerNone);
    graphics_fill_rect(context, GRect(3 + posX, 17 + posY, 38, 10), 0, GCornerNone);
    graphics_fill_rect(context, GRect(3 + posX, 31 + posY, 38, 10), 0, GCornerNone);
    graphics_fill_rect(context, GRect(31 + posX, 13 + posY, 10, 4), 0, GCornerNone);
    graphics_fill_rect(context, GRect(3 + posX, 27 + posY, 10, 4), 0, GCornerNone);    
  }
  else if (digit == 3) {
    graphics_context_set_fill_color(context, colorB);      
    graphics_fill_rect(context, GRect(2 + posX, 2 + posY, 40, 12), 0, GCornerNone);
    graphics_fill_rect(context, GRect(2 + posX, 16 + posY, 28, 12), 0, GCornerNone);
    graphics_fill_rect(context, GRect(2 + posX, 30 + posY, 40, 12), 0, GCornerNone);
    graphics_fill_rect(context, GRect(30 + posX, 14 + posY, 12, 16), 0, GCornerNone);
    
    graphics_context_set_fill_color(context, colorH);      
    graphics_fill_rect(context, GRect(3 + posX, 3 + posY, 38, 10), 0, GCornerNone);
    graphics_fill_rect(context, GRect(3 + posX, 17 + posY, 28, 10), 0, GCornerNone);
    graphics_fill_rect(context, GRect(3 + posX, 31 + posY, 38, 10), 0, GCornerNone);
    graphics_fill_rect(context, GRect(31 + posX, 13 + posY, 10, 18), 0, GCornerNone);
  }
  else if (digit == 4) {
    graphics_fill_rect(context, GRect(16 + posX, posY, 12, 14), 0, GCornerNone);
    graphics_fill_rect(context, GRect(posX, 30 + posY, 28, 14), 0, GCornerNone);   
    
    graphics_context_set_fill_color(context, colorB);      
    graphics_fill_rect(context, GRect(2 + posX, 2 + posY, 12, 26), 0, GCornerNone);
    graphics_fill_rect(context, GRect(30 + posX, 2 + posY, 12, 40), 0, GCornerNone);
    graphics_fill_rect(context, GRect(14 + posX, 16 + posY, 16, 12), 0, GCornerNone);
    
    graphics_context_set_fill_color(context, colorH);      
    graphics_fill_rect(context, GRect(3 + posX, 3 + posY, 10, 24), 0, GCornerNone);
    graphics_fill_rect(context, GRect(31 + posX, 3 + posY, 10, 38), 0, GCornerNone);
    graphics_fill_rect(context, GRect(13 + posX, 17 + posY, 18, 10), 0, GCornerNone);
  }
  else if (digit == 5) {
    graphics_context_set_fill_color(context, colorB);      
    graphics_fill_rect(context, GRect(2 + posX, 2 + posY, 40, 12), 0, GCornerNone);
    graphics_fill_rect(context, GRect(2 + posX, 16 + posY, 40, 12), 0, GCornerNone);
    graphics_fill_rect(context, GRect(2 + posX, 30 + posY, 40, 12), 0, GCornerNone);
    graphics_fill_rect(context, GRect(30 + posX, 28 + posY, 12, 2), 0, GCornerNone);
    graphics_fill_rect(context, GRect(2 + posX, 14 + posY, 12, 2), 0, GCornerNone);   
    
    graphics_context_set_fill_color(context, colorH);      
    graphics_fill_rect(context, GRect(3 + posX, 3 + posY, 38, 10), 0, GCornerNone);
    graphics_fill_rect(context, GRect(3 + posX, 17 + posY, 38, 10), 0, GCornerNone);
    graphics_fill_rect(context, GRect(3 + posX, 31 + posY, 38, 10), 0, GCornerNone);
    graphics_fill_rect(context, GRect(31 + posX, 27 + posY, 10, 4), 0, GCornerNone);
    graphics_fill_rect(context, GRect(3 + posX, 13 + posY, 10, 4), 0, GCornerNone);    
  }
  else if (digit == 6) {
    graphics_context_set_fill_color(context, colorB);      
    graphics_fill_rect(context, GRect(2 + posX, 2 + posY, 12, 40), 0, GCornerNone);
    graphics_fill_rect(context, GRect(30 + posX, 16 + posY, 12, 26), 0, GCornerNone);
    graphics_fill_rect(context, GRect(14 + posX, 2 + posY, 28, 12), 0, GCornerNone);
    graphics_fill_rect(context, GRect(14 + posX, 16 + posY, 16, 12), 0, GCornerNone);
    graphics_fill_rect(context, GRect(14 + posX, 30 + posY, 16, 12), 0, GCornerNone);
    
    graphics_context_set_fill_color(context, colorH);      
    graphics_fill_rect(context, GRect(3 + posX, 3 + posY, 10, 38), 0, GCornerNone);
    graphics_fill_rect(context, GRect(31 + posX, 17 + posY, 10, 24), 0, GCornerNone);
    graphics_fill_rect(context, GRect(13 + posX, 3 + posY, 28, 10), 0, GCornerNone);
    graphics_fill_rect(context, GRect(13 + posX, 17 + posY, 18, 10), 0, GCornerNone);
    graphics_fill_rect(context, GRect(13 + posX, 31 + posY, 18, 10), 0, GCornerNone);
  }
  else if (digit == 7) {
    graphics_fill_rect(context, GRect(posX, 16 + posY, 28, 28), 0, GCornerNone);
    
    graphics_context_set_fill_color(context, colorB);      
    graphics_fill_rect(context, GRect(2 + posX, 2 + posY, 40, 12), 0, GCornerNone);
    graphics_fill_rect(context, GRect(30 + posX, 14 + posY, 12, 28), 0, GCornerNone);
    
    graphics_context_set_fill_color(context, colorH);      
    graphics_fill_rect(context, GRect(3 + posX, 3 + posY, 38, 10), 0, GCornerNone);
    graphics_fill_rect(context, GRect(31 + posX, 13 + posY, 10, 28), 0, GCornerNone);
  }
  else if (digit == 8) {
    graphics_context_set_fill_color(context, colorB);      
    graphics_fill_rect(context, GRect(2 + posX, 2 + posY, 12, 40), 0, GCornerNone);
    graphics_fill_rect(context, GRect(30 + posX, 2 + posY, 12, 40), 0, GCornerNone);
    graphics_fill_rect(context, GRect(14 + posX, 2 + posY, 16, 12), 0, GCornerNone);
    graphics_fill_rect(context, GRect(14 + posX, 16 + posY, 16, 12), 0, GCornerNone);
    graphics_fill_rect(context, GRect(14 + posX, 30 + posY, 16, 12), 0, GCornerNone);
    
    graphics_context_set_fill_color(context, colorH);      
    graphics_fill_rect(context, GRect(3 + posX, 3 + posY, 10, 38), 0, GCornerNone);
    graphics_fill_rect(context, GRect(31 + posX, 3 + posY, 10, 38), 0, GCornerNone);
    graphics_fill_rect(context, GRect(13 + posX, 3 + posY, 18, 10), 0, GCornerNone);
    graphics_fill_rect(context, GRect(13 + posX, 17 + posY, 18, 10), 0, GCornerNone);
    graphics_fill_rect(context, GRect(13 + posX, 31 + posY, 18, 10), 0, GCornerNone);
  }
  else if (digit == 9) {
    graphics_context_set_fill_color(context, colorB);      
    graphics_fill_rect(context, GRect(2 + posX, 2 + posY, 12, 26), 0, GCornerNone);
    graphics_fill_rect(context, GRect(30 + posX, 2 + posY, 12, 40), 0, GCornerNone);
    graphics_fill_rect(context, GRect(14 + posX, 2 + posY, 16, 12), 0, GCornerNone);
    graphics_fill_rect(context, GRect(14 + posX, 16 + posY, 16, 12), 0, GCornerNone);
    graphics_fill_rect(context, GRect(2 + posX, 30 + posY, 28, 12), 0, GCornerNone);
    
    graphics_context_set_fill_color(context, colorH);      
    graphics_fill_rect(context, GRect(3 + posX, 3 + posY, 10, 24), 0, GCornerNone);
    graphics_fill_rect(context, GRect(31 + posX, 3 + posY, 10, 38), 0, GCornerNone);
    graphics_fill_rect(context, GRect(13 + posX, 3 + posY, 18, 10), 0, GCornerNone);
    graphics_fill_rect(context, GRect(13 + posX, 17 + posY, 18, 10), 0, GCornerNone);
    graphics_fill_rect(context, GRect(3 + posX, 31 + posY, 30, 10), 0, GCornerNone);
  }
  else { /* do nothing */ }
}

static void time_layer_update(Layer *layer, GContext *context) {
  GColor colorF = background == 0 ? GColorWhite : GColorBlack;
  GColor colorB = background == 0 ? GColorBlack : GColorWhite;
  GColor colorH = colorHighlight; // (GColor) { .argb = (uint8_t)(0xC0 |colorHighlight) };
  GColor colorS = colorStandBy; // (GColor) { .argb = (uint8_t)(0xC0 |colorStandBy) };

  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  int tens = tick_time->tm_min / 10;
  int mins = tick_time->tm_min % 10;
  int hour = tick_time->tm_hour % 12;
   
  if (tens == 0 && mins == 0) tens = 6;
  for (int i = 0; i < 6; i++){
    int posX = 2 + tensX[i], posY = 2 + tensY[i];
    if (i < tens) {
      graphics_context_set_stroke_color(context, colorB);
      graphics_context_set_fill_color(context, colorF);      
      graphics_fill_rect(context, GRect(posX, posY, 44, 44), 0, GCornerNone);
      graphics_draw_rect(context, GRect(2 + posX, 2 + posY, 40, 40));
      graphics_context_set_fill_color(context, colorH);      
      graphics_fill_rect(context, GRect(3 + posX, 3 + posY, 38, 38), 0, GCornerNone);
    }
    else if (i == tens && mins > 0) {
      draw_digit(context, mins, posX, posY);
    }
    else {
      graphics_context_set_stroke_color(context, colorB);
      graphics_context_set_fill_color(context, colorF);      
      graphics_fill_rect(context, GRect(posX, posY, 44, 44), 0, GCornerNone);
      graphics_draw_rect(context, GRect(2 + posX, 2 + posY, 40, 40));
      graphics_context_set_fill_color(context, colorS);      
      graphics_fill_rect(context, GRect(3 + posX, 3 + posY, 38, 38), 0, GCornerNone);
    }
  }  

  graphics_context_set_stroke_color(context, colorB);
  graphics_context_set_fill_color(context, colorF);
  graphics_fill_rect(context, GRect(48 + hourX[hour], 48 + hourY[hour], hourW[hour], hourH[hour]), 0, GCornerNone);
  graphics_draw_rect(context, GRect(49 + hourX[hour], 49 + hourY[hour], hourW[hour] - 2, hourH[hour] - 2));
  
  if (bluetooth_connection_service_peek()) graphics_context_set_fill_color(context, colorH);
  else graphics_context_set_fill_color(context, colorS);
  graphics_fill_rect(context, GRect(50 + hourX[hour], 50 + hourY[hour], hourW[hour] - 4, hourH[hour] - 4), 0, GCornerNone);
  graphics_context_set_fill_color(context, colorF);
  graphics_fill_rect(context, GRect(68, 68, 8, 8), 0, GCornerNone);
  graphics_context_set_stroke_color(context, colorB);
  graphics_draw_rect(context, GRect(69, 69, 6, 6));
  graphics_context_set_fill_color(context, colorH);
  graphics_fill_rect(context, GRect(70, 70, 4, 4), 0, GCornerNone);
}

/*static void batt_layer_update(Layer *layer, GContext *context) {
  GColor colorF = background == 0 ? GColorWhite : GColorBlack;
  GColor colorH = (GColor) { .argb = (uint8_t)(0xC0 |colorHighlight) };
  GColor colorS = (GColor) { .argb = (uint8_t)(0xC0 |colorStandBy) };

  BatteryChargeState charge = battery_state_service_peek();
  int battLvl = charge.charge_percent / 10;
  
  for (int i = 0; i < 10; i++) {
    graphics_context_set_stroke_color(context, colorF);
    graphics_draw_rect(context, GRect(3 + i * 14, -1, 12, 8));
    
    if (i < battLvl) graphics_context_set_fill_color(context, colorH);
    else graphics_context_set_fill_color(context, colorS);
    graphics_fill_rect(context, GRect(5 + i * 14, 0, 8, 5), 0, GCornerNone);
  }
}*/

static void steps_layer_update(Layer* layer, GContext *context) {
  GColor colorF = background == 0 ? GColorWhite : GColorBlack;
  GColor colorH = colorHighlight; // (GColor) { .argb = (uint8_t)(0xC0 |colorHighlight) };
  GColor colorS = colorStandBy; // (GColor) { .argb = (uint8_t)(0xC0 |colorStandBy) };

  int hVal = (int)health_service_sum_today(HealthMetricStepCount);
  int meter1 = (hVal / 1000) % 10;
  int meter2 = (hVal / 100) % 10;
  int meter3 = hVal / 10000;
  int meterIndent = 6;
  
  for (int i = 0; i < 10; i++) {
    graphics_context_set_stroke_color(context, colorF);
    graphics_draw_rect(context, GRect(meterIndent + i * 13, 2, 14, 6));
    graphics_draw_rect(context, GRect(meterIndent + i * 13, 7, 14, 6));
    
    if (meter3 > 0) {
      if (i < meter1) graphics_context_set_fill_color(context, colorF);
      else graphics_context_set_fill_color(context, colorH);        
    }
    else {
      if (i < meter1) graphics_context_set_fill_color(context, colorH);
      else graphics_context_set_fill_color(context, colorS);        
    }
    graphics_fill_rect(context, GRect((meterIndent + 2) + i * 13, 4, 10, 2), 0, GCornerNone);
    
    if (i < meter2) graphics_context_set_fill_color(context, colorH);
    else graphics_context_set_fill_color(context, colorS);
    graphics_fill_rect(context, GRect((meterIndent + 2) + i * 13, 9, 10, 2), 0, GCornerNone);
  }
}

static void time_handler(struct tm *tick_time, TimeUnits units_changed) {
  layer_mark_dirty(layerMins);

  BatteryChargeState charge = battery_state_service_peek();
  int battLvl = charge.charge_percent;

  static char dayOfMo[] = "..";
  static char dayOfYr[] = "...";
  static char month[] = "...";
  
  strftime(dayOfMo, sizeof(".."), "%d", tick_time);
  strftime(dayOfYr, sizeof("..."), "%j", tick_time);
  snprintf(month, sizeof("..."), "%i", battLvl);
  
  text_layer_set_text(tLayerDoM, dayOfMo);
  text_layer_set_text(tLayerDoY, dayOfYr);
  text_layer_set_text(tLayerMonth, month);
}

static void main_window_load_handler(Window *window) {
  fontSquareS = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_SQUARE_20));
  fontSquareM = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_SQUARE_24));
    
  layerMins = layer_create(GRect(0, 12, 144, 144));
  layer_set_update_proc(layerMins, time_layer_update);
  
  //layerBatt = layer_create(GRect(0, 0, 144, 12));
  //layer_set_update_proc(layerBatt, batt_layer_update);
  
  layerSteps = layer_create(GRect(0, 156, 144, 12));
  layer_set_update_proc(layerSteps, steps_layer_update);
  
  tLayerMonth = text_layer_create(GRect(98, 10, 48, 26));
  text_layer_set_background_color(tLayerMonth, GColorClear);
  text_layer_set_text_color(tLayerMonth, GColorWhite);
  text_layer_set_text_alignment(tLayerMonth, GTextAlignmentCenter);
  text_layer_set_font(tLayerMonth, fontSquareM);
  text_layer_set_text(tLayerMonth, "...");
  
  tLayerDoM = text_layer_create(GRect(98, 124, 46, 26));
  text_layer_set_background_color(tLayerDoM, GColorClear);
  text_layer_set_text_color(tLayerDoM, GColorWhite);
  text_layer_set_text_alignment(tLayerDoM, GTextAlignmentCenter);
  text_layer_set_font(tLayerDoM, fontSquareM);
  text_layer_set_text(tLayerDoM, "..");
  
  tLayerDoY = text_layer_create(GRect(2, 12, 48, 24));
  text_layer_set_background_color(tLayerDoY, GColorClear);
  text_layer_set_text_color(tLayerDoY, GColorWhite);
  text_layer_set_text_alignment(tLayerDoY, GTextAlignmentCenter);
  text_layer_set_font(tLayerDoY, fontSquareS);
  text_layer_set_text(tLayerDoY, "...");
   
  layer_add_child(window_get_root_layer(mainWindow), layerMins);
  //layer_add_child(window_get_root_layer(mainWindow), layerBatt);
  layer_add_child(window_get_root_layer(mainWindow), layerSteps);
  layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(tLayerDoM));
  layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(tLayerDoY));
  layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(tLayerMonth));
}

static void main_window_unload_handler(Window *window) {
  fonts_unload_custom_font(fontSquareS);
  fonts_unload_custom_font(fontSquareM);
  layer_destroy(layerMins);
  //layer_destroy(layerBatt);
  layer_destroy(layerSteps);
  text_layer_destroy(tLayerMonth);
  text_layer_destroy(tLayerDoM);
  text_layer_destroy(tLayerDoY);
}

static void bluetooth_handler(bool btConn) {
  if (btConn) vibes_short_pulse();
  else vibes_long_pulse();
  layer_mark_dirty(layerMins);
}

/*static void battery_handler(BatteryChargeState charge) {
  layer_mark_dirty(layerBatt);
}*/

/*static void tuple_changed_callback(const uint32_t key, const Tuple* tuple_new, const Tuple* tuple_old, void* context) {
  int value = tuple_new->value->uint8;
  switch (key) {
    case setting_hightlightColor:
      colorHighlight = value;
      persist_write_int(setting_hightlightColor, value);
      break;
    case setting_standbyColor:
      colorStandBy = value;
      persist_write_int(setting_standbyColor, value);
      break;
    case setting_background:
      background = value;
      if (value == 0) {
        window_set_background_color(mainWindow, GColorBlack);
      }
      else {
        window_set_background_color(mainWindow, GColorWhite);
      }
      persist_write_int(setting_background, value);
      break;
  }
  APP_LOG(APP_LOG_LEVEL_DEBUG, "settings: [%i:%i]", (int)key, value);
  layer_mark_dirty(layerMins);
  layer_mark_dirty(layerBatt);
  layer_mark_dirty(layerSteps);
}*/

static void inbox_received_handler(DictionaryIterator *iter, void *context) {
  Tuple* hColor = dict_find(iter, MESSAGE_KEY_Highlight);
  if (hColor) {
    colorHighlight = GColorFromHEX(hColor->value->int32);
    persist_write_int(0, hColor->value->int32);
  }
  Tuple* sColor = dict_find(iter, MESSAGE_KEY_Standby);
  if (sColor) {
    colorStandBy = GColorFromHEX(sColor->value->int32);
    persist_write_int(1, sColor->value->int32);
  }
  Tuple *bColor = dict_find(iter, MESSAGE_KEY_Background);
  if (bColor) {
    if (bColor->value->int32 == 0) { 
      window_set_background_color(mainWindow, GColorBlack); 
      text_layer_set_text_color(tLayerDoM, GColorWhite);
      text_layer_set_text_color(tLayerDoY, GColorWhite);
      text_layer_set_text_color(tLayerMonth, GColorWhite);
    }
    else { 
      window_set_background_color(mainWindow, GColorWhite); 
      text_layer_set_text_color(tLayerDoM, GColorBlack);
      text_layer_set_text_color(tLayerDoY, GColorBlack);
      text_layer_set_text_color(tLayerMonth, GColorBlack);
    }
    background = bColor->value->int32;
    persist_write_int(2, background);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "bkgd val: %i", background);
  }
  
  layer_mark_dirty(layerMins);
  layer_mark_dirty(layerSteps);
}

static void app_error_callback(DictionaryResult dict_error, AppMessageResult app_message_error, void* context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "app error %d", app_message_error);
}

static void init(void) {
  colorHighlight = persist_exists(0) ? GColorFromHEX(persist_read_int(0)) : GColorLightGray;
  colorStandBy = persist_exists(1) ? GColorFromHEX(persist_read_int(1)) : GColorDarkGray;
  background = persist_exists(2) ? persist_read_int(2) : 0;
  
  mainWindow = window_create();
  window_set_background_color(mainWindow, GColorBlack);
  
  window_set_window_handlers(mainWindow, (WindowHandlers) {
    .load = main_window_load_handler,
    .unload = main_window_unload_handler
  });
  
  /*Tuplet tuples[] = {
    TupletInteger(setting_hightlightColor, colorHighlight),
    TupletInteger(setting_standbyColor, colorStandBy),
    TupletInteger(setting_background, background)
  };*/
  
  app_message_register_inbox_received(inbox_received_handler);
  app_message_open(128, 128);
  
  /*app_message_open(160, 160);
  app_sync_init(&app, buffer, sizeof(buffer), tuples, ARRAY_LENGTH(tuples), tuple_changed_callback, app_error_callback, NULL);
  app_sync_get(&app, 0);*/
  
  tick_timer_service_subscribe(MINUTE_UNIT, time_handler);
  bluetooth_connection_service_subscribe(bluetooth_handler);
  //battery_state_service_subscribe(battery_handler);

  window_stack_push(mainWindow, true);
}

void deinit(void) {
  window_destroy(mainWindow);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
