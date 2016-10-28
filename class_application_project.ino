#include <Adafruit_NeoPixel.h>

#define PIN 6   // degital I/O pin
#define NUMPIXELS 1   // 制御するledの数

Adafruit_NeoPixel rgbled = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup(){
  rgbled.begin();
  rgbled.setBrightness(50);   // 明るさ指定(0~255)
  rgbled.setPixelColor(0, rgbled.Color(255, 255, 255));
  rgbled.show();   // 反映
}

void loop(){
  long x, y, z;
  x = y = z = 0;
  x = analogRead(0);
  y = analogRead(1);
  z = analogRead(2);
  int x_ave = 503;
  int y_ave = 510;
  int z_ave = 704;
  int small_error = 50;   // 誤差範囲の一番小さい値
  int medium_error = 100;
  int large_error = 150;
  int emergency_error = 300;   // 急な加速度を検知するのに測る誤差の値

  // フリスビー投げられた時の処理
  if(x < x_ave - emergency_error || x_ave + emergency_error < x){   // 急激な加速度を検知したら(投げたら)
    while(1){   // 無限ループ
      int x_throw_ave = 0;   // 空中で進んでる時の数値の初期化
      int y_throw_ave = 0;
      int z_throw_ave = 0;
      if(x_ave - emergency_error <= x && x <= x_ave + emergency_error){   // 加速度が平均に近い値であったら
        for(int i = 0; i < 30; i++){   // 加速度の値を取得して30回分の平均を出す
          x_throw_ave = x_throw_ave + x;
          y_throw_ave = y_throw_ave + y;
          z_throw_ave = z_throw_ave + z;
        }
        x_throw_ave = x_throw_ave / 30;
        y_throw_ave = y_throw_ave / 30;
        z_throw_ave = z_throw_ave / 30;
/**
ここにledの判定の制御を記述
**/
      } else {   // 急激な加速度を検知したら(キャッチしたら)
        rgbled.setPixelColor(0, rgbled.Color(255, 255, 255));
        rgbled.show();
        break;
      }
    }
  }

}