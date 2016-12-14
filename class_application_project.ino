#include <Adafruit_NeoPixel.h>
// ピン設定
const int ACCELERATION_X_ANALOGPIN = 0;
const int ACCELERATION_Y_ANALOGPIN = 1;
const int ACCELERATION_Z_ANALOGPIN = 2;
const int LED_PIN = 6;
const int FLASH_PIN = 7;
const int ENCODER_COUNTERCLOCKWISE_PIN = 2;
const int ENCODER_CLOCKWISE_PIN = 4;
const int ENCODER_SWITCH_PIN = 3;
const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;
// 固定変数
const int DEFAULT_ROTATION = 1;
const int NUM_LEDS = 45;   // 制御するledの数
const int BRIGHTNESS_LED = 50;   // ledの明るさ設定値(0~255)
const int ERROR_SMALL = 100;   // 誤差範囲の一番小さい値(Flash用の誤差の値)
const int ERROR_SMALL_MIDDLE = 125;
const int ERROR_MIDDLE = 150;
const int ERROR_LARGE_MIDDLE = 175;
const int ERROR_LARGE = 200;
const int LOW_ACCELERATION = 24;   // 急激な加速度の検知の差分
const int HIGH_ACCELERATION = 1000;   // 急激な加速度の検知
const int MODE_CHANGE_DELAY = 1500;   // モードの開始・終了までのdelay
const int H_LAP = 120;   // artmodeの色変化の一周を何分割にするか(1/3できる数が良い)
// rgbledのインスタンスの生成
Adafruit_NeoPixel rgbled = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
// グローバル変数
int x, y, z;
int current_rotation = DEFAULT_ROTATION;   // 現在の値保管用
// ヘッダーファイルの読み込み
#include "function.h"
#include "mode_normal.h"
#include "mode_art.h"
#include "mode_sugoroku.h"
#include "mode_bomb.h"

void setup() {
  Serial.begin(9600);
  rgbled.begin();
  pinMode(ENCODER_COUNTERCLOCKWISE_PIN, INPUT_PULLUP);
  pinMode(ENCODER_CLOCKWISE_PIN, INPUT_PULLUP);
  pinMode(FLASH_PIN, OUTPUT);
  digitalWrite(FLASH_PIN, LOW);
  for(int i=0; i<=NUM_LEDS; i++){
    rgbled.setBrightness(BRIGHTNESS_LED);   // 明るさ指定(0~255)
    rgbled.setPixelColor(i, rgbled.Color(255, 255, 255));
    rgbled.show();   // 反映
  }
}

void loop() {
  rotation();

  int encoder_switch_val = analogRead(ENCODER_SWITCH_PIN);
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