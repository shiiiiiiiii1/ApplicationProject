#include <Adafruit_NeoPixel.h>

const int num_leds = 45;   // 制御するledの数
const int led_pin = 6;   // led degital I/O pin
const int flash_pin = 7;   // flash degital I/O pin

Adafruit_NeoPixel rgbled = Adafruit_NeoPixel(num_leds, led_pin, NEO_GRB + NEO_KHZ800);

int x, y, z, R, G, B, acceleration;
int H = 0;
int current_H = 0;


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
  x = map(x, 0, 1023, -511, 512);
  y = map(y, 0, 1023, -511, 512);
  z = map(z, 0, 1023, 512, -511);
  float x2 = pow(x, 2.0);
  float y2 = pow(y, 2.0);
  float z2 = pow(z, 2.0);
  acceleration = sqrt(x2 + y2 + z2);
  if(acceleration >= 85){
    acceleration = map(acceleration, 85, 886, 0, 360);
  }
  if(acceleration < 85){
    acceleration = map(acceleration, -717, 84, 360, 0);
  }
  H += acceleration;

  if(H <= 360){
    if(5 <= acceleration && acceleration <= 20){   // 動いてない場合
      change_rgb(current_H, current_H);
      // H = current_H;
      H -= acceleration;
    } else {   // 動いてる場合
      change_rgb(current_H, H);
    }
    current_H = H;
  }
  if(H > 360){
    int extra_H = H - 360;
    H = 360;
    change_rgb(current_H, H);
    current_H = 0;
    change_rgb(current_H, extra_H);
    current_H = extra_H;
    H = 0;
  }
  delay(50);
}


void change_rgb(int current_H, int H){
  for(int i=0; current_H<=H; current_H++){
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
    delay(3);
  }
}

void change_ledcolor(int r, int g, int b) {
  for(int i=0; i<num_leds; i++){
    rgbled.setPixelColor(i, rgbled.Color(r, g, b));
    rgbled.show();
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