float ControleDeVelocidadeDir(int n_dir, float setpoint_dir) {
  wd = (2 * Pi * n_dir) / (periodTime * 20);//Calculo da velocidade W de uma roda
  /* Controlar PID da roda ESQUERDA*/
  error_dir = setpoint_dir - wd;
  cntrlP_dir = kp * error_dir;
  cntrlI_dir = cntrlI_dir + ki * error_dir * periodTime;
  cntrlD_dir = kd * (error_dir - lastError_dir) / periodTime;
  cntrlSignal_dir = (cntrlP_dir + cntrlI_dir + cntrlD_dir) + 40; //Sinal de controle PWM

  if (cntrlSignal_dir >= 200 || cntrlSignal_dir <= -200 ) { //Saturador
    cntrlSignal_dir = 200;
  }
  if (cntrlSignal_dir < 0 ) {
    cntrlSignal_dir = -cntrlSignal_dir;
    /*Acionamento do motor*/
    analogWrite(pinEnableMotorB, cntrlSignal_dir);
    digitalWrite(pinSentido1MotorB, HIGH);
    digitalWrite(pinSentido2MotorB, LOW);
  }
  else {
    analogWrite(pinEnableMotorB, cntrlSignal_dir);
    digitalWrite(pinSentido1MotorB, LOW);
    digitalWrite(pinSentido2MotorB, HIGH);
  }
}
