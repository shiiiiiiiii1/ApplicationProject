void mode_bomb() {
  delay(mode_change_delay);
  change_ledcolor(255, 255, 255);
  int total_score_bomb = 0;
  int max_score = 30;
  while(1){
    acceleration_read();
    // フリスビー投げられた時の処理
    if(x<low_acceleration || high_acceleration<x || y<low_acceleration || high_acceleration<y){
      delay(100);
      int z_sum = acceleration_decision();
      if(total_score_bomb == 0){
        change_ledcolor(0, 0, 255);
      }
      if(z_sum < error_small){
        total_score_sugoroku += 1;
        return_loop_bomb(total_score_bomb, max_score);
      }
      if(error_small < z_sum && z_sum < error_samll_middle){
        total_score_sugoroku += 2;
        return_loop_bomb(total_score_bomb, max_score);
      }
      if(error_samll_middle < z_sum && z_sum < error_middle){
        total_score_sugoroku += 3;
        return_loop_bomb(total_score_bomb, max_score);
      }
      if(error_middle < z_sum && z_sum < error_large_middle){
        total_score_sugoroku += 4;
        return_loop_bomb(total_score_bomb, max_score);
      }
      if(error_large_middle < z_sum && z_sum < error_large){
        total_score_sugoroku += 5;
        return_loop_bomb(total_score_bomb, max_score);
      }
      if(error_large < z_sum){
        total_score_sugoroku += 6;
        return_loop_bomb(total_score_bomb, max_score);
      }
    }

    int encoder_switch_val = analogRead(encoder_switch_analogpin);
    if(encoder_switch_val >= 1020){
      delay(mode_change_delay);
      break;
    }
  }
}