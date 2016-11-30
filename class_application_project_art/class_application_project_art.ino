/*
* 変数名などの整理をして実際のモード切り替えのコードに移植する。
*
*/

#include <Adafruit_NeoPixel.h>

const int num_leds = 45;   // 制御するledの数
const int led_pin = 6;   // led degital I/O pin
const int flash_pin = 7;   // flash degital I/O pin

const int H_lap = 120;   // Hの一周の分割数。大きくするほど一周するのに時間がかかる。

Adafruit_NeoPixel rgbled = Adafruit_NeoPixel(num_leds, led_pin, NEO_GRB + NEO_KHZ800);

int x, y, z, R, G, B, acceleration;
int current_H = 0;


void setup(){
Serial.begin(9600);
  rgbled.begin();
  for(int i=0; i<=num_leds; i++){
    rgbled.setBrightness(10);   // 明るさ指定(0~255)
    rgbled.setPixelColor(i, rgbled.Color(255, 255, 255));
    rgbled.show();   // 反映
  }
  pinMode(flash_pin, OUTPUT);
  digitalWrite(flash_pin, LOW);
}

void loop(){
  // 加速度検知
  acceleration_read();

  // 加速度変換
  int x_map = map(x, 0, 1023, -511, 512);
  int y_map = map(y, 0, 1023, -511, 512);
  int z_map = map(z, 0, 1023, 512, -511);

  // 加速度の合成
  float x2 = pow(x_map, 2.0);
  float y2 = pow(y_map, 2.0);
  float z2 = pow(z_map, 2.0);
  acceleration = sqrt(x2 + y2 + z2);

  // 加速度が発生している時
  if(acceleration < 190 || 250 < acceleration){
    int acceleration_map, conversion_H;
    acceleration_map = acceleration<190 ? map(acceleration, 220, 0, 0, 220) : acceleration;   // 加速度を0を基準とした値に変換
    acceleration_map = 250<acceleration ? map(acceleration, 220, 880, 0, 660) : acceleration;   // 加速度を0を基準とした値に変換
    conversion_H = map(acceleration_map, 0, 660, 0, H_lap);   // 加速度をHの変化量と照らし合わせる値に変換

    // current_H が、最終的に一周よりも大きい値になってしまうかどうかの判定。
    if(current_H+conversion_H <= H_lap){
Serial.println("no over H_lap !!!");
Serial.println(current_H+conversion_H);
      current_H = change_rgb(current_H, conversion_H);
    }
    if(H_lap < current_H+conversion_H){   // current_H が、最終的に一周よりも大きい値になってしまう場合。
Serial.println("over H_lap !!!");
      change_rgb(current_H, H_lap-current_H);
      current_H = change_rgb(0, current_H+conversion_H-H_lap);
    }
  }
  delay(50);
}


int change_rgb(int current_H, int conversion_H){
  int while_finish_val = current_H+conversion_H;
  while(current_H < while_finish_val){
    if(current_H <= H_lap/3) {
      R = map(current_H, 0, H_lap/3, 255, 0);
      G = map(current_H, 0, H_lap/3, 0, 255);
      B = 0;
    }
    if(H_lap/3 < current_H && current_H <= H_lap*2/3){
      G = map(current_H, H_lap/3, H_lap*2/3, 255, 0);
      B = map(current_H, H_lap/3, H_lap*2/3, 0, 255);
      R = 0;
    }
    if(H_lap*2/3 < current_H){
      B = map(current_H, H_lap*2/3, H_lap, 255, 0);
      R = map(current_H, H_lap*2/3, H_lap, 0, 255);
      G= 0;
    }
    change_ledcolor(R, G, B);
    current_H++;
  }
  return current_H;
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