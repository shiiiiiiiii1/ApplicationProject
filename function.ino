void acceleration_read() {
  x = analogRead(0);
  y = analogRead(1);
  z = analogRead(2);
  x = x<10 ? 0 : x;
  x = x>1013 ? 1023 : x;
  y = y<10 ? 0 : y;
  y = y>1013 ? 1023 : y;
  z = z<10 ? 0 : z;
  z = z>1013 ? 1023 : z;
}

void change_ledcolor(int r, int g, int b) {
  for(int i=0; i<num_leds; i++){
    rgbled.setPixelColor(i, rgbled.Color(r, g, b));
    rgbled.show();
  }
}

void flashing() {
  delay(1000);
  digitalWrite(flash_pin, HIGH);
  delay(1000);
  digitalWrite(flash_pin, LOW);

}


/* normal mode function */

void return_loop_normal() {
  while(1){
    delay(50);
    acceleration_read();
    if(x<low_acceleration || high_acceleration<x || y<low_acceleration || high_acceleration<y){
      change_ledcolor(255, 255, 255);
      delay(200);
      break;
    }
  }
}


// /* art mode function */

// void change_rgb(int current_H, int H){
//   for(int i=0; current_H<=H; current_H++){
//     if(current_H <= 120) {
//       R = map(current_H, 0, 120, 255, 0);
//       G = map(current_H, 0, 120, 0, 255);
//       B = 0;
//     } else if (current_H <= 240) {
//       G = map(current_H, 120, 240, 255, 0);
//       B = map(current_H, 120, 240, 0, 255);
//       R = 0;
//     } else {
//       B = map(current_H, 240, 360, 255, 0);
//       R = map(current_H, 240, 360, 0, 255);
//       G= 0;
//     }
//     change_ledcolor(R, G, B);
//     delay(3);
//   }
// }


// /* fugoroku mode function */

// void return_loop_sugoroku() {
//   while(1){
//     delay(50);
//     acceleration_read();
//     if(x<low_acceleration || high_acceleration<x || y<low_acceleration || high_acceleration<y){
//       score_led();
//       delay(200);
//       break;
//     }
//   }
// }

// void score_led() {
//   delay(500);
//   total_score = total_score>num_leds ? total_score-num_leds : total_score;
//   if(total_score < num_leds){
//     for(int i=0; i<total_score; i++){
//       rgbled.setPixelColor(i, rgbled.Color(255, 0, 0));
//       rgbled.show();
//     }
//     for(int i=total_score; i<num_leds; i++){
//       rgbled.setPixelColor(i, rgbled.Color(0, 0, 0));
//       rgbled.show();
//     }
//   }
//   if(total_score == num_leds){
//     delay(50);
//     digitalWrite(flash_pin, HIGH);
//     delay(50);
//     digitalWrite(flash_pin, LOW);
//   }
// }


// /* bomb mode function */

// void return_loop_bomb() {
//   while(1){
//     delay(50);
//     acceleration_read();
//     if(x<low_acceleration || high_acceleration<x || y<low_acceleration || high_acceleration<y){
//       if(total_score >= over_score){
//         delay(50);
//         digitalWrite(flash_pin, HIGH);
//         delay(50);
//         digitalWrite(flash_pin, LOW);
//         total_score = 0;
//       }
//       delay(200);
//       break;
//     }
//   }
// }