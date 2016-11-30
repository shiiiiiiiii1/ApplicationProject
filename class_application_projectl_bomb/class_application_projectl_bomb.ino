#include <Adafruit_NeoPixel.h>

const int num_leds = 45;   // 制御するledの数
const int led_pin = 6;   // led degital I/O pin
const int flash_pin = 7;   // flash degital I/O pin

Adafruit_NeoPixel rgbled = Adafruit_NeoPixel(num_leds, led_pin, NEO_GRB + NEO_KHZ800);

int x, y, z;
int total_score = 0;   // すごろく的なやつのスコア
int over_score = 30;
int score1 = 50;   // score判定
int score2 = 100;
int score3 = 150;
int score4 = 200;
int score5 = 250;
int low_acceleration = 24;   // 急激な加速度の検知
int high_acceleration = 1000;   // 急激な加速度の検知


void setup(){
  rgbled.begin();
  for(int i=0; i<=num_leds; i++){
    rgbled.setBrightness(50);   // 明るさ指定(0~255)
    rgbled.setPixelColor(i, rgbled.Color(255, 255, 255));
    rgbled.show();   // 反映
  }
  pinMode(flash_pin, OUTPUT);
  digitalWrite(flash_pin, LOW);
}

void loop(){
  acceleration_read();

  // フリスビー投げられた時の処理
  if(x<low_acceleration || high_acceleration<x || y<low_acceleration || high_acceleration<y){
    if(total_score == 0){
      change_ledcolor(0, 0, 255);
    }
    delay(100);
    int z_before_val = analogRead(2);
    int z_difference = 0;
    int z_sum = 0;
    for(int i=0; i<2; i++){
      delay(50);
      z = analogRead(2);
      z_difference = abs(z_before_val - z);
      z_sum += z_difference;
      z_before_val = z;
    }

    if(z_sum < score1){
      total_score += 1;
      return_loop_bomb();
    }
    if(score1 < z_sum && z_sum < score2){
      total_score += 2;
      return_loop_bomb();
    }
    if(score2 < z_sum && z_sum < score3){
      total_score += 3;
      return_loop_bomb();
    }
    if(score3 < z_sum && z_sum < score4){
      total_score += 4;
      return_loop_bomb();
    }
    if(score4 < z_sum && z_sum < score5){
      total_score += 5;
      return_loop_bomb();
    }
    if(score5 < z_sum){
      total_score += 6;
      return_loop_bomb();
    }
  }
}


void change_ledcolor(int r, int g, int b) {
  for(int i=0; i<num_leds; i++){
    rgbled.setPixelColor(i, rgbled.Color(r, g, b));
    rgbled.show();
  }
}

void change_rgb_bomb(int current_H){
  if(current_H <= 120) {
    R = map(current_H, 0, 120, 255, 0);
    G = map(current_H, 0, 120, 0, 255);
    B = 0;
  } else if (current_H <= 240) {
    G = map(current_H, 120, 240, 255, 0);
    B = map(current_H, 120, 240, 0, 255);
    R = 0;
  } else {
    B = map(current_H, 240, 360, 255, 0);
    R = map(current_H, 240, 360, 0, 255);
    G= 0;
  }
  change_ledcolor(R, G, B);
}

void remaind_decision(int current_score) {
  if(25 <= current_score){
    change_ledcolor(255, 0, 0);
  }
  if(current_score < 25){
    float conversion_H_score = map(current_score, 0, 29, 119, 0);
    R = map(conversion_H_score, 0, 120, 255, 0);
    G = map(conversion_H_score, 0, 120, 0, 255);
    B = 0;
    change_ledcolor(R, G, B);
  }
}

void return_loop_bomb() {
  while(1){
    delay(50);
    acceleration_read();
    if(x<low_acceleration || high_acceleration<x || y<low_acceleration || high_acceleration<y){
      remaind_decision(total_score);
      if(total_score >= over_score){
        delay(50);
        digitalWrite(flash_pin, HIGH);
        delay(50);
        digitalWrite(flash_pin, LOW);
        total_score = 0;
      }
      delay(200);
      break;
    }
  }
}

void acceleration_read() {
  x = analogRead(0);
  y = analogRead(1);
  z = analogRead(2);
  x = x<10 ? 0 : x;
  x = x>1013 ? 1023 : x;
  y = y<10 ? 0 : y;
  y = y>1013 ? 1023 : y;
  z = z<10 ? 0 : z;
  z = z>1013 ? 1023 : z;
}