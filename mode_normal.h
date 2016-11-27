void mode_normal() {
Serial.println("normal mode start");
delay(mode_change_delay);
change_ledcolor(255, 255, 255);
  while(1){
    acceleration_read();
    // フリスビー投げられた時の処理
    if(x<low_acceleration || high_acceleration<x || y<low_acceleration || high_acceleration<y){
      delay(100);
      int z_sum = acceleration_decision();

Serial.println(z_sum);

      if(z_sum < error_samll_middle){
        change_ledcolor(0, 0, 255);
        if(z_sum < error_small){   // フラッシュ判定
          flashing();
        }
        return_loop_normal();
      }
      if(error_samll_middle < z_sum && z_sum < error_large){
        change_ledcolor(255, 255, 0);
        return_loop_normal();
      }
      if(error_large < z_sum){
        change_ledcolor(255, 0, 0);
        return_loop_normal();
      }
    }
    int encoder_switch_val = analogRead(encoder_switch_analogpin);
    if(encoder_switch_val >= 1020){
      delay(mode_change_delay);
      break;
    }
  }
}