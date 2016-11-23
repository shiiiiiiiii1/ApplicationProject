void mode_normal() {
Serial.println("normal mode start");
delay(2000);
  while(1){
    acceleration_read();
    // フリスビー投げられた時の処理
    if(x<low_acceleration || high_acceleration<x || y<low_acceleration || high_acceleration<y){
      delay(100);
      int z_sum = acceleration_decision();

Serial.println(z_sum);

      if(z_sum < medium_error){
        change_ledcolor(0, 0, 255);
        if(z_sum < small_error){   // フラッシュ判定
          delay(1000);
          digitalWrite(flash_pin, HIGH);
          delay(1000);
          digitalWrite(flash_pin, LOW);
        }
        return_loop_normal();
      }
      if(medium_error < z_sum && z_sum < large_error){
        change_ledcolor(255, 255, 0);
        return_loop_normal();
      }
      if(large_error < z_sum){
        change_ledcolor(255, 0, 0);
        return_loop_normal();
      }
    }
    int encoder_switch_val = analogRead(encoder_switch_analogpin);
    if(encoder_switch_val >= 1020){
      delay(2000);
      break;
    }
  }
}