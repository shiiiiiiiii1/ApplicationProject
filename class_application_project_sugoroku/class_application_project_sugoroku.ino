#include <Adafruit_NeoPixel.h>

const int num_leds = 1;   // 制御するledの数
const int led_pin = 6;   // led degital I/O pin
const int flash_pin = 7;   // flash degital I/O pin

Adafruit_NeoPixel rgbled = Adafruit_NeoPixel(num_leds, led_pin, NEO_GRB + NEO_KHZ800);

int x, y, z;
int total_score = 0;   // すごろく的なやつのスコア
int score6 = 50;   // score判定
int score5 = 100;
int score4 = 150;
int score3 = 200;
int score2 = 250;
int score1 = 300;
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

    if(score5 < z_sum && z_sum < score6){
      total_score += 6;
      change_ledcolor(0, 0, 255);
      return_loop();
    }
    if(score4 < z_sum && z_sum < score5){
      total_score += 5;
      change_ledcolor(0, 255, 255);
      return_loop();
    }
    if(score3 < z_sum && z_sum < score4){
      total_score += 4;
      change_ledcolor(0, 255, 0);
      return_loop();
    }
    if(score2 < z_sum && z_sum < score3){
      total_score += 3;
      change_ledcolor(255, 255, 0);
      return_loop();
    }
    if(score1 < z_sum && z_sum < score2){
      total_score += 2;
      change_ledcolor(255, 105, 180);
      return_loop();
    }
    if(z_sum < score1){
      total_score += 1;
      change_ledcolor(255, 0, 0);
      return_loop();
    }
  }
}


void change_ledcolor(int r, int g, int b) {
  for(int i=0; i<num_leds; i++){
    rgbled.setPixelColor(i, rgbled.Color(r, g, b));
    rgbled.show();
  }
}

void score_led() {
  total_score = total_score>num_leds ? total_score-num_leds : total_score;
  if(total_score < num_leds){
    for(int i=0; i<total_score; i++){
      rgbled.setPixelColor(i, rgbled.Color(255, 0, 0));
      rgbled.show();
    }
    for(int i=total_score; i<num_leds; i++){
      rgbled.setPixelColor(i, rgbled.Color(0, 0, 0));
      rgbled.show();
    }
  }
  if(total_score == num_leds){
    delay(50);
    digitalWrite(flash_pin, HIGH);
    delay(50);
    digitalWrite(flash_pin, LOW);
  }
}

void return_loop() {
  while(1){
    delay(50);
    acceleration_read();
    if(x<low_acceleration || high_acceleration<x || y<low_acceleration || high_acceleration<y){
      score_led();
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