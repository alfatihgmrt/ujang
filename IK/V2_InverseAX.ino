/*
   teta  = sudut coxa_v2
   teta1_v2 = sudut femur
   teta2_v2 = sudut tibia

   @param    kaki_v2    posisi_x    posisi_y    posisi_z    status_jalan
*/

float L1_v2 = 0;
float L2_v2 = 55;
float L3_v2 = 75;


void IK_v2 (uint8_t kaki_v2, float pos_X_v2, float pos_Y_v2, float posZ_v2, int w_v2){
  float posX_v2 = pos_X_v2;
  float posY_v2 = pos_Y_v2;
  float posXa_v2, Xa_v2; //posXa_v2: variabel x yang dimasukkan ke rumus x dan z. Xa_v2: atan dari y/x lalu dimasukkan ke rumus posXa_v2. 

  if (pos_X_v2 < 0){
    posX_v2 = pos_X_v2 * -1;
  }
  if (pos_Y_v2 < 0){
    posY_v2 = pos_Y_v2 * -1;
  }

  Xa_v2 = atan2(posY_v2, posX_v2);


  posXa_v2 = posX_v2 / cos(Xa_v2);

    float teta1_v2 = ((atan2(pos_Y_v2, pos_X_v2))* 180.0 / PI);
    float teta3_v2 = acos((posXa_v2*posXa_v2 + posZ_v2*posZ_v2 - L2_v2*L2_v2 - L3_v2*L3_v2) / (2 * L2_v2 * L3_v2));
    // Calculate theta1
    float k1_v2 = L2_v2 + L3_v2 * cos(teta3_v2);
    float k2_v2 = L3_v2 * sin(teta3_v2);
    float teta2_v2 = (atan2(posZ_v2, posXa_v2)) + (atan2(k2_v2, k1_v2));

    teta2_v2 = teta2_v2 * 180 / M_PI;
    teta3_v2 = teta3_v2 *  180 / M_PI;
    // Serial.println("teta 1: " + String(teta2_v2) + " teta 2: " + String(teta3_v2));

  if (isnan(teta1_v2)) {
    teta1_v2 = 0; 
  }
  if (isnan(teta2_v2)) {
    teta2_v2 = 0; 
  }
  if (isnan(teta3_v2)) {
    teta3_v2 = 0; 
  }
  
  // Serial.print(" - teta1_v2 ");
  // Serial.print(teta1_v2);
  // Serial.print(" - teta2_v2 ");
  // Serial.print(teta2_v2);
  Serial.print("teta3_v2 ");
  Serial.println(teta3_v2);
 
  //forward/backward
  switch (w_v2) {
    case 0:
      if (kaki_v2 == 0) {
        // pulsa_kaki[kaki_v2][0] = coxa_v2[0] + (teta1_v2 *-1); //coxa_v2
        // pulsa_kaki[kaki_v2][0] = coxa_v2[0] + (teta1_v2 *-1) + 10; //coxa_v2
        pulsa_kaki[kaki_v2][0] = coxa_v2[0] + (teta1_v2 *-1) ; //coxa_v2
        posisiCoxa_v2(kaki_v2);
        pulsa_kaki[kaki_v2][1] = 150 + teta2_v2 - 2; //femur
        posisiFemur_v2(kaki_v2);
        pulsa_kaki[kaki_v2][2] = 50 + teta3_v2 + 12; //tibia
       
      }
      else if (kaki_v2 == 1) {
        pulsa_kaki[kaki_v2][0] = coxa_v2[1] + (teta1_v2 *-1) ; //coxa_v2
        posisiCoxa_v2(kaki_v2);
        pulsa_kaki[kaki_v2][1] = 150 + teta2_v2 - 5; //femur
        posisiFemur_v2(kaki_v2);
        pulsa_kaki[kaki_v2][2] = 50 + teta3_v2 + 10; //tibia
       
      }
      else if (kaki_v2 == 2) {
        // pulsa_kaki[kaki_v2][0] = coxa_v2[2] + (teta1_v2 *-1); //coxa_v2
        pulsa_kaki[kaki_v2][0] = coxa_v2[2] + (teta1_v2 *-1); //coxa_v2
        posisiCoxa_v2(kaki_v2);
        pulsa_kaki[kaki_v2][1] = 150 + teta2_v2; //femur
        posisiFemur_v2(kaki_v2);
        pulsa_kaki[kaki_v2][2] = 50 + teta3_v2 + 30; //tibia
       
      }
      else if (kaki_v2 == 3) {
        // pulsa_kaki[kaki_v2][0] = coxa_v2[3] + (teta1_v2 *-1); //coxa_v2
        pulsa_kaki[kaki_v2][0] = coxa_v2[3] + (teta1_v2 *-1) ; //coxa_v2
        posisiCoxa_v2(kaki_v2);
        pulsa_kaki[kaki_v2][1] = 150 + teta2_v2 ; //femur
        posisiFemur_v2(kaki_v2);
        pulsa_kaki[kaki_v2][2] = 50 + teta3_v2 + 12; //tibia
       
      }
      // Serial.print("\nkaki "+ String(kaki_v2) + "  ");
      // Serial.print(" " + String(pulsa_kaki[kaki_v2][0]));
      // Serial.print(" " + String(pulsa_kaki[kaki_v2][1]));
      // Serial.print(" " + String(pulsa_kaki[kaki_v2][2]));
      // Serial.println();
      break;
      case 1:
      if (kaki_v2 == 0) {
        pulsa_kaki[kaki_v2][0] = teta1_v2; //coxa_v2
        posisiCoxa_v2(kaki_v2);
        pulsa_kaki[kaki_v2][1] = teta2_v2; //femur
        posisiFemur_v2(kaki_v2);
        pulsa_kaki[kaki_v2][2] = teta3_v2; //tibia
      }
      // Serial.print("\nkaki "+ String(kaki_v2) + "  ");
      // Serial.print(" " + String(pulsa_kaki[kaki_v2][0]));
      // Serial.print(" " + String(pulsa_kaki[kaki_v2][1]));
      // Serial.print(" " + String(pulsa_kaki[kaki_v2][2]));
      // Serial.println();
      break;
      case 2: //edited(Imki)
      Serial.println("IK_v2");
      if (kaki_v2 == 0) {
        pulsa_kaki[kaki_v2][0] = coxa_v2[0] + (teta1_v2) ; //coxa_v2
        posisiCoxa_v2(kaki_v2);
        pulsa_kaki[kaki_v2][1] = 147 + teta2_v2; //femur
        posisiFemur_v2(kaki_v2);
        pulsa_kaki[kaki_v2][2] = 63 + teta3_v2; //tibia
       
      }
      else if (kaki_v2 == 1) {
        pulsa_kaki[kaki_v2][0] = coxa_v2[1] + (teta1_v2) + 1; //coxa_v2
        posisiCoxa_v2(kaki_v2);
        pulsa_kaki[kaki_v2][1] = 147 + teta2_v2; //femur
        posisiFemur_v2(kaki_v2);
        pulsa_kaki[kaki_v2][2] = 60 + teta3_v2; //tibia
       
      }
      else if (kaki_v2 == 2) {
        pulsa_kaki[kaki_v2][0] = coxa_v2[2] + (teta1_v2); //coxa_v2
        posisiCoxa_v2(kaki_v2);
        pulsa_kaki[kaki_v2][1] = 148 + teta2_v2; //femur
        posisiFemur_v2(kaki_v2);
        pulsa_kaki[kaki_v2][2] = 65 + teta3_v2; //tibia
       
      }
      else if (kaki_v2 == 3) {
        pulsa_kaki[kaki_v2][0] = coxa_v2[3] + (teta1_v2) ; //coxa_v2
        posisiCoxa_v2(kaki_v2);
        pulsa_kaki[kaki_v2][1] = 147 + teta2_v2; //femur
        posisiFemur_v2(kaki_v2);
        pulsa_kaki[kaki_v2][2] = 60 + teta3_v2; //tibia
       
      }
      break;
      case 3: // Gaada yang ditambah dan dikurang. Gaada ralat untuk setiap servo
      Serial.println("IK_v2");
      if (kaki_v2 == 0) {
        pulsa_kaki[kaki_v2][0] = coxa_v2[0] + (teta1_v2); //coxa_v2
        posisiCoxa_v2(kaki_v2);
        pulsa_kaki[kaki_v2][1] = 150 + teta2_v2; //femur
        posisiFemur_v2(kaki_v2);
        pulsa_kaki[kaki_v2][2] = 60 + teta3_v2; //tibia
       
      }
      else if (kaki_v2 == 1) {
        pulsa_kaki[kaki_v2][0] = coxa_v2[1] + (teta1_v2); //coxa_v2
        posisiCoxa_v2(kaki_v2);
        pulsa_kaki[kaki_v2][1] = 150 + teta2_v2; //femur
        posisiFemur_v2(kaki_v2);
        pulsa_kaki[kaki_v2][2] = 60 + teta3_v2; //tibia
       
      }
      else if (kaki_v2 == 2) {
        pulsa_kaki[kaki_v2][0] = coxa_v2[2] + (teta1_v2); //coxa_v2
        posisiCoxa_v2(kaki_v2);
        pulsa_kaki[kaki_v2][1] = 150 + teta2_v2; //femur
        posisiFemur_v2(kaki_v2);
        pulsa_kaki[kaki_v2][2] = 60 + teta3_v2; //tibia
       
      }
      else if (kaki_v2 == 3) {
        pulsa_kaki[kaki_v2][0] = coxa_v2[3] + (teta1_v2) ; //coxa_v2
        posisiCoxa_v2(kaki_v2);
        pulsa_kaki[kaki_v2][1] = 150 + teta2_v2; //femur
        posisiFemur_v2(kaki_v2);
        pulsa_kaki[kaki_v2][2] = 60 + teta3_v2; //tibia
       
    }
  }
}


void IKDebug_v2(int kaki_v2) {
  while(1){
    Serial.print(pulsa_kaki[kaki_v2][0]); Serial.print('\t');
    Serial.print(pulsa_kaki[kaki_v2][1]); Serial.print('\t');
    Serial.println(pulsa_kaki[kaki_v2][2]);
    delay(500);
  }
}

int posisiCoxa_v2(int kaki_v2) {
  if (kaki_v2 == 0) {      //kanan depan
    min_coxa_v2 = 100; //batas kearah cw
    max_coxa_v2 = 200; //batas kearah ccw
  }
  else if (kaki_v2 == 1) { //kanan blkg
    min_coxa_v2 = 100;
    max_coxa_v2 = 200;
  }
  else if (kaki_v2 == 2) { //kiri blkg
    min_coxa_v2 = 100;
    max_coxa_v2 = 200;
  }
  else if (kaki_v2 == 3) { //kiri dpn
    min_coxa_v2 = 100;
    max_coxa_v2 = 200;
  }

  if (pulsa_kaki[kaki_v2][0] < min_coxa_v2)
    pulsa_kaki[kaki_v2][0] = min_coxa_v2;
  else if (pulsa_kaki[kaki_v2][0] > max_coxa_v2)
    pulsa_kaki[kaki_v2][0] = max_coxa_v2;
  else{
    pulsa_kaki[kaki_v2][0] = pulsa_kaki[kaki_v2][0];
    Serial.print("Coxa ");
    Serial.print(kaki_v2);
    Serial.print(" aman: ");
    Serial.println(pulsa_kaki[kaki_v2][0]);
  }

  return pulsa_kaki[kaki_v2][0];
}

int posisiFemur_v2(int kaki_v2) {
  if (kaki_v2 == 0) {       //kanan depan
    min_Fem_v2 = 100;       //batas kebawah
    max_Fem_v2 = 230;       //batas keatas
  }
  else if (kaki_v2 == 1) {  //kanan blkg
    min_Fem_v2 = 100;
    max_Fem_v2 = 230;
  }
  else if (kaki_v2 == 2) {  //kiri blkg
    min_Fem_v2 = 100;
    max_Fem_v2 = 230;
  }
  else if (kaki_v2 == 3) {  //kiri dpn
    min_Fem_v2 = 100;
    max_Fem_v2 = 230;
  }

  if (pulsa_kaki[kaki_v2][1] < min_Fem_v2){
    pulsa_kaki[kaki_v2][1] = min_Fem_v2;
  }
  else if (pulsa_kaki[kaki_v2][1] > max_Fem_v2) {
    pulsa_kaki[kaki_v2][1] = max_Fem_v2;
    Serial.print("Femur ");
    Serial.print(kaki_v2);
    Serial.print("> batas max: ");
    Serial.println(pulsa_kaki[kaki_v2][1]);
  }
  else{
    pulsa_kaki[kaki_v2][1] = pulsa_kaki[kaki_v2][1];
    Serial.print("Femur ");
    Serial.print(kaki_v2);
    Serial.print(" aman: ");
    Serial.println(pulsa_kaki[kaki_v2][1]);
    Serial.print("Tibia ");
    Serial.print(kaki_v2);
    Serial.print(" aman: ");
    Serial.println(pulsa_kaki[kaki_v2][2]);
  }
  return pulsa_kaki[kaki_v2][1];
}
