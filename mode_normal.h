void mode_normal() {
Serial.println("normal mode start");
  delay(MODE_CHANGE_DELAY);
  change_ledcolor(255, 255, 255);
  while(1){
    acceleration_read();
    // フリスビー投げられた時の処理
    if(x<LOW_ACCELERATION || HIGH_ACCELERATION<x || y<LOW_ACCELERATION || HIGH_ACCELERATION<y){
      delay(100);
      int z_sum = acceleration_decision();

Serial.println(z_sum);

      if(z_sum < ERROR_SMALL_MIDDLE){
        change_ledcolor(0, 0, 255);
        if(z_sum < ERROR_SMALL){   // フラッシュ判定
          flashing();
        }
        return_loop_normal();
      }
      if(ERROR_SMALL_MIDDLE < z_sum && z_sum < ERROR_LARGE){
        change_ledcolor(255, 255, 0);
        return_loop_normal();
      }
      if(ERROR_LARGE < z_sum){
        change_ledcolor(255, 0, 0);
        return_loop_normal();
      }
    }
    int encoder_switch_val = analogRead(ENCODER_CLOCKWISE_PIN);
    if(encoder_switch_val >= 1020){
      delay(MODE_CHANGE_DELAY);
      break;
    }
  }
}