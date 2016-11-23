#include <Adafruit_NeoPixel.h>

// ピン設定
const int acceleration_x_analogpin = 0;
const int acceleration_y_analogpin = 1;
const int acceleration_z_analogpin = 2;
const int led_pin = 6;
const int flash_pin = 7;
const int encoder_counterclockwise_pin = 2;
const int encoder_clockwise_pin = 4;
const int encoder_switch_analogpin = 3;
const int cyan_pin = 9;
const int magenta_pin = 10;
const int yellow_pin = 11;

// const int num_leds = 45;   // 制御するledの数

int default_rotation = 1;
int direction_rotation = 0;   // どっちに回したか保管用
int current_rotation = default_rotation;   // 現在の値保管用
int old_rotation = default_rotation;   // 一個前の値保管用


int sw_reset_count = 0;

// Adafruit_NeoPixel rgbled = Adafruit_NeoPixel(num_leds, led_pin, NEO_GRB + NEO_KHZ800);

// int x, y, z;
// int small_error = 100;   // 誤差範囲の一番小さい値(Flash用の誤差の値)
// int medium_error = 125;
// int large_error = 250;
// int low_acceleration = 24;   // 急激な加速度の検知
// int high_acceleration = 1000;   // 急激な加速度の検知


void setup() {
  Serial.begin(9600);
  pinMode(encoder_counterclockwise_pin, INPUT_PULLUP);
  pinMode(encoder_clockwise_pin, INPUT_PULLUP);
}

void loop() {
  rotation();

  int encoder_switch_val = analogRead(encoder_switch_analogpin);
  if(encoder_switch_val <= 1019){
    mode_color_change(current_rotation);
  }
  if(current_rotation == 1){
    if(encoder_switch_val > 1021){
      mode_color_change(0);
      mode_normal();
    }
  }
  if(current_rotation == 2){
    if(encoder_switch_val > 1022){
      mode_color_change(0);
      mode_sugoroku();
    }
  }
  if(current_rotation == 3){
    if(encoder_switch_val > 1019){
      mode_color_change(0);
      mode_art();
    }
  }
  if(current_rotation == 4){
    if(encoder_switch_val > 1022){
      mode_color_change(0);
      mode_bomb();
    }
  }
}