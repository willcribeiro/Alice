void ControleDeVelocidadeEsq(int n_esq, float setpoint_esq) {
  //Serial.println("Entrei");
  we = (2 * Pi * n_esq) / (periodTime * 20);//Calculo da velocidade W de uma roda
  /* Controlar PID da roda ESQUERDA*/
  //Serial.println(we);
  error_esq = setpoint_esq - we;
  cntrlP_esq = kp * error_esq;
  cntrlI_esq = cntrlI_esq + ki * error_esq * periodTime;
  cntrlD_esq = kd * (error_esq - lastError_esq) / periodTime;
  cntrlSignal_esq = (cntrlP_esq + cntrlI_esq + cntrlD_esq) + 40; //Sinal de controle PWM
  
  if (cntrlSignal_esq >= 200 || cntrlSignal_esq <= -200 ) { //Saturador
    cntrlSignal_esq = 200;
  }
  if (cntrlSignal_esq < 0 ) {
    cntrlSignal_esq = -cntrlSignal_esq;
    /*Acionamento do motor*/
    analogWrite(pinEnableMotorA, cntrlSignal_esq);
    digitalWrite(pinSentido1MotorA, HIGH);
    digitalWrite(pinSentido2MotorA, LOW);
  }
  else {
   // Serial.println(cntrlSignal_esq);
    analogWrite(pinEnableMotorA, cntrlSignal_esq);
    digitalWrite(pinSentido1MotorA, LOW);
    digitalWrite(pinSentido2MotorA, HIGH);
    
  }
}
