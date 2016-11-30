void mode_art() {
Serial.println("art mode start");
  delay(mode_change_delay);
  int current_H = 0;
  change_ledcolor(255, 0, 0);
  while(1){
    acceleration_read();
    int x_map = map(x, 0, 1023, -511, 512);
    int y_map = map(y, 0, 1023, -511, 512);
    int z_map = map(z, 0, 1023, 512, -511);
    // 加速度合成
    float x2 = pow(x_map, 2.0);
    float y2 = pow(y_map, 2.0);
    float z2 = pow(z_map, 2.0);
    int acceleration = sqrt(x2 + y2 + z2);
    if(acceleration < 190 || 250 < acceleration){
      int acceleration_map;
      acceleration_map = acceleration<190 ? map(acceleration, 220, 0, 0, 220) : acceleration;   // 加速度を0を基準とした値に変換
      acceleration_map = 250<acceleration ? map(acceleration, 220, 880, 0, 660) : acceleration;   // 加速度を0を基準とした値に変換
      int conversion_H = map(acceleration_map, 0, 660, 0, H_lap);   // 加速度をHの変化量と照らし合わせる値に変換
      // current_H が、最終的に一周よりも大きい値になってしまうかどうかの判定。
      if(current_H+conversion_H <= H_lap){
        current_H = change_rgb(current_H, conversion_H);
      }
      if(H_lap < current_H+conversion_H){   // current_H が、最終的に一周よりも大きい値になってしまう場合。
        change_rgb(current_H, H_lap-current_H);
        current_H = change_rgb(0, current_H+conversion_H-H_lap);
      }
    }

    int encoder_switch_val = analogRead(encoder_switch_analogpin);
    if(encoder_switch_val >= 1020){
      delay(mode_change_delay);
      break;
    }
  }
}