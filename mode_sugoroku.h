void mode_sugoroku() {
  delay(mode_change_delay);
  change_ledcolor(255, 255, 255);
  int total_score = 0;   // すごろくモードでの初期化
  while(1){
    acceleration_read();
    // フリスビー投げられた時の処理
    if(x<low_acceleration || high_acceleration<x || y<low_acceleration || high_acceleration<y){
      delay(100);
      int z_sum = acceleration_decision();
      if(z_sum < error_small){
        total_score += 6;
        change_ledcolor(0, 0, 255);
        return_loop_sugoroku(total_score);
      }
      if(error_small < z_sum && z_sum < error_samll_middle){
        total_score += 5;
        change_ledcolor(0, 255, 255);
        return_loop_sugoroku(total_score);
      }
      if(error_samll_middle < z_sum && z_sum < error_middle){
        total_score += 4;
        change_ledcolor(0, 255, 0);
        return_loop_sugoroku(total_score);
      }
      if(error_middle < z_sum && z_sum < error_large_middle){
        total_score += 3;
        change_ledcolor(255, 255, 0);
        return_loop_sugoroku(total_score);
      }
      if(error_large_middle < z_sum && z_sum < error_large){
        total_score += 2;
        change_ledcolor(255, 105, 180);
        return_loop_sugoroku(total_score);
      }
      if(error_large < z_sum){
        total_score += 1;
        change_ledcolor(255, 0, 0);
        return_loop_sugoroku(total_score);
      }
    }

    int encoder_switch_val = analogRead(encoder_switch_analogpin);
    if(encoder_switch_val >= 1020){
      delay(mode_change_delay);
      break;
    }
  }
}