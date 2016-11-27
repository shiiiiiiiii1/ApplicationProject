void mode_bomb() {
Serial.println("bomb mode start");
  delay(mode_change_delay);
  change_ledcolor(255, 255, 255);
  int total_score = 0;
  while(1){
    acceleration_read();
    // フリスビー投げられた時の処理
    if(x<low_acceleration || high_acceleration<x || y<low_acceleration || high_acceleration<y){
      delay(100);
      int z_sum = acceleration_decision();
      if(total_score == 0){
        change_ledcolor(0, 255, 0);
      }
      if(z_sum < error_small){
        total_score += 1;
        total_score = return_loop_bomb(total_score);
      }
      if(error_small < z_sum && z_sum < error_samll_middle){
        total_score += 2;
        total_score = return_loop_bomb(total_score);
      }
      if(error_samll_middle < z_sum && z_sum < error_middle){
        total_score += 3;
        total_score = return_loop_bomb(total_score);
      }
      if(error_middle < z_sum && z_sum < error_large_middle){
        total_score += 4;
        total_score = return_loop_bomb(total_score);
      }
      if(error_large_middle < z_sum && z_sum < error_large){
        total_score += 5;
        total_score = return_loop_bomb(total_score);
      }
      if(error_large < z_sum){
        total_score += 6;
        total_score = return_loop_bomb(total_score);
      }
Serial.print(total_score);
    }

    int encoder_switch_val = analogRead(encoder_switch_analogpin);
    if(encoder_switch_val >= 1020){
      delay(mode_change_delay);
      break;
    }
  }
}