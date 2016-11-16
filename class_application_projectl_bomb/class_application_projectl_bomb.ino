#include <Adafruit_NeoPixel.h>

const int num_leds = 1;   // 制御するledの数
const int led_pin = 6;   // led degital I/O pin
const int flash_pin = 7;   // flash degital I/O pin

Adafruit_NeoPixel rgbled = Adafruit_NeoPixel(num_leds, led_pin, NEO_GRB + NEO_KHZ800);

int x, y, z;
int small_error = 100;   // 誤差範囲の一番小さい値(Flash用の誤差の値)
int medium_error = 125;
int large_error = 250;
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

    if(z_sum < medium_error){
      change_ledcolor(0, 0, 255);
      if(z_sum < small_error){   // フラッシュ判定
        delay(50);
        digitalWrite(flash_pin, HIGH);
        delay(50);
        digitalWrite(flash_pin, LOW);
      }
      return_loop();
    }
    if(medium_error < z_sum && z_sum < large_error){
      change_ledcolor(255, 255, 0);
      return_loop();
    }
    if(large_error < z_sum){
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

void return_loop() {
  while(1){
    delay(50);
    acceleration_read();
    if(x<low_acceleration || high_acceleration<x || y<low_acceleration || high_acceleration<y){
      change_ledcolor(255, 255, 255);
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