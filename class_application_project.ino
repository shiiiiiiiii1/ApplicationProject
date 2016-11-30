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
// 固定変数
const int default_rotation = 1;   // 回転の初期値
const int num_leds = 45;   // 制御するledの数
const int bright_led = 50;   // ledの明るさ設定値(0~255)
const int error_small = 100;   // 誤差範囲の一番小さい値(Flash用の誤差の値)
const int error_samll_middle = 125;
const int error_middle = 150;
const int error_large_middle = 175;
const int error_large = 200;
const int low_acceleration = 24;   // 急激な加速度の検知の差分
const int high_acceleration = 1000;   // 急激な加速度の検知
const int mode_change_delay = 1500;   // モードの開始・終了までのdelay
const int H_lap = 120;   // artmodeの色変化の一周を何分割にするか(1/3できる数が良い)
// rgbledのインスタンスの生成
Adafruit_NeoPixel rgbled = Adafruit_NeoPixel(num_leds, led_pin, NEO_GRB + NEO_KHZ800);
// グローバル変数
int x, y, z;
int direction_rotation = 0;   // どっちに回したか保管用
int current_rotation = default_rotation;   // 現在の値保管用
// ヘッダーファイルの読み込み
#include "function.h"
#include "mode_normal.h"
#include "mode_art.h"
#include "mode_sugoroku.h"
#include "mode_bomb.h"

void setup() {
  Serial.begin(9600);
  rgbled.begin();
  pinMode(encoder_counterclockwise_pin, INPUT_PULLUP);
  pinMode(encoder_clockwise_pin, INPUT_PULLUP);
  pinMode(flash_pin, OUTPUT);
  digitalWrite(flash_pin, LOW);
  for(int i=0; i<=num_leds; i++){
    rgbled.setBrightness(bright_led);   // 明るさ指定(0~255)
    rgbled.setPixelColor(i, rgbled.Color(255, 255, 255));
    rgbled.show();   // 反映
  }
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
      mode_art();
    }
  }
  if(current_rotation == 3){
    if(encoder_switch_val > 1019){
      mode_color_change(0);
      mode_sugoroku();
    }
  }
  if(current_rotation == 4){
    if(encoder_switch_val > 1022){
      mode_color_change(0);
      mode_bomb();
    }
  }
}