#include <Adafruit_NeoPixel.h>

#define led_pin 6   // led degital I/O pin
#define NUMPIXELS 1   // 制御するledの数

Adafruit_NeoPixel rgbled = Adafruit_NeoPixel(NUMPIXELS, led_pin, NEO_GRB + NEO_KHZ800);

int flash_pin = 7;   // flash degital I/O pin
int low_acceleration = 10;
int high_acceleration = 1000;

void setup(){
  Serial.begin(115200);
  rgbled.begin();
  rgbled.setBrightness(50);   // 明るさ指定(0~255)
  rgbled.setPixelColor(0, rgbled.Color(255, 255, 255));
  rgbled.show();   // 反映
  pinMode(flash_pin, OUTPUT);
  digitalWrite(flash_pin, LOW);
}

void loop(){
  long x, y, z;
  x = y = z = 0;
  x = analogRead(0);
  y = analogRead(1);
  z = analogRead(2);
  int small_error = 100;   // 誤差範囲の一番小さい値(Flash用の誤差の値)
  int medium_error = 125;
  int large_error = 250;

  // フリスビー投げられた時の処理
  if(x<low_acceleration || high_acceleration<x || y<low_acceleration || high_acceleration<y){
    delay(100);
    int z_before = analogRead(2);
    int z_difference = 0;
    int z_sum = 0;
    for(int i=0; i<2; i++){
      delay(50);
      z = analogRead(2);
Serial.println(z);
      z_difference = abs(z_before - z);
      z_sum = z_sum + z_difference;
      z_before = z;
    }

Serial.println(z_sum);
    if(z_sum < medium_error){
      rgbled.setPixelColor(0, rgbled.Color(0, 0, 255));
      rgbled.show();
      if(z_sum < small_error){
        delay(50);
        digitalWrite(flash_pin, HIGH);
        digitalWrite(flash_pin, LOW);
      }
      return_loop();
    }
    if(medium_error < z_sum && z_sum < large_error){
      rgbled.setPixelColor(0, rgbled.Color(255, 255, 0));
      rgbled.show();
      return_loop();
    }
    if(large_error < z_sum){
      rgbled.setPixelColor(0, rgbled.Color(255, 0, 0));
      rgbled.show();
      return_loop();
    }
  }
}

void return_loop() {
  while(1){
    delay(50);
    int x = analogRead(0);
    int y = analogRead(1);
Serial.println("in loop");
    if(x<low_acceleration || high_acceleration<x || y<low_acceleration || high_acceleration<y){
      rgbled.setPixelColor(0, rgbled.Color(255, 255, 255));
      rgbled.show();
      delay(200);
      break;
    }
  }
}