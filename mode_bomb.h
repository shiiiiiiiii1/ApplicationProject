void mode_bomb() {
Serial.println("bomb mode start");
  delay(MODE_CHANGE_DELAY);
  change_ledcolor(255, 255, 255);
  int total_score = 0;
  while(1){
    acceleration_read();
    // フリスビー投げられた時の処理
    if(x<LOW_ACCELERATION || HIGH_ACCELERATION<x || y<LOW_ACCELERATION || HIGH_ACCELERATION<y){
      delay(100);
      int z_sum = acceleration_decision();
      if(total_score == 0){
        change_ledcolor(0, 255, 0);
      }
      if(z_sum < ERROR_SMALL){
        total_score += 1;
        total_score = return_loop_bomb(total_score);
      }
      if(ERROR_SMALL < z_sum && z_sum < ERROR_SMALL_MIDDLE){
        total_score += 2;
        total_score = return_loop_bomb(total_score);
      }
      if(ERROR_SMALL_MIDDLE < z_sum && z_sum < ERROR_MIDDLE){
        total_score += 3;
        total_score = return_loop_bomb(total_score);
      }
      if(ERROR_MIDDLE < z_sum && z_sum < ERROR_LARGE_MIDDLE){
        total_score += 4;
        total_score = return_loop_bomb(total_score);
      }
      if(ERROR_LARGE_MIDDLE < z_sum && z_sum < ERROR_LARGE){
        total_score += 5;
        total_score = return_loop_bomb(total_score);
      }
      if(ERROR_LARGE < z_sum){
        total_score += 6;
        total_score = return_loop_bomb(total_score);
      }
    }

    int encoder_switch_val = analogRead(ENCODER_CLOCKWISE_PIN);
    if(encoder_switch_val >= 1020){
      delay(MODE_CHANGE_DELAY);
      break;
    }
  }
}