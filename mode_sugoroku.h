void mode_sugoroku() {
Serial.println("sugoroku mode start");
  delay(MODE_CHANGE_DELAY);
  change_ledcolor(255, 255, 255);
  int total_score = 0;   // すごろくモードでの初期化
  while(1){
    acceleration_read();
    // フリスビー投げられた時の処理
    if(x<LOW_ACCELERATION || HIGH_ACCELERATION<x || y<LOW_ACCELERATION || HIGH_ACCELERATION<y){
      delay(100);
      int z_sum = acceleration_decision();
      if(z_sum < ERROR_SMALL){
        total_score += 6;
        change_ledcolor(0, 0, 255);
        return_loop_sugoroku(total_score);
      }
      if(ERROR_SMALL < z_sum && z_sum < ERROR_SMALL_MIDDLE){
        total_score += 5;
        change_ledcolor(0, 255, 255);
        return_loop_sugoroku(total_score);
      }
      if(ERROR_SMALL_MIDDLE < z_sum && z_sum < ERROR_MIDDLE){
        total_score += 4;
        change_ledcolor(0, 255, 0);
        return_loop_sugoroku(total_score);
      }
      if(ERROR_MIDDLE < z_sum && z_sum < ERROR_LARGE_MIDDLE){
        total_score += 3;
        change_ledcolor(255, 255, 0);
        return_loop_sugoroku(total_score);
      }
      if(ERROR_LARGE_MIDDLE < z_sum && z_sum < ERROR_LARGE){
        total_score += 2;
        change_ledcolor(255, 105, 180);
        return_loop_sugoroku(total_score);
      }
      if(ERROR_LARGE < z_sum){
        total_score += 1;
        change_ledcolor(255, 0, 0);
        return_loop_sugoroku(total_score);
      }
    }

    if( digitalRead(ENCODER_SWITCH_PIN) ){
Serial.println("sugoroku mode end");
      delay(MODE_CHANGE_DELAY);
      break;
    }
  }
}