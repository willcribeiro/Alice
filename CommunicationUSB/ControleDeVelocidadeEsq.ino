void ControleDeVelocidadeEsq(int n_esq, float setpoint_esq) {
  /* Calculo da velocidade W de uma roda */
  we = (2 * Pi * n_esq) / (periodTime * 20);

  /* Controlar PID da roda ESQUERDA*/
  error_esq = setpoint_esq - we;
  cntrlP_esq = kp * error_esq;
  cntrlI_esq = cntrlI_esq + ki * error_esq * periodTime;
  cntrlD_esq = kd * (error_esq - lastError_esq) / periodTime;
  /* Sinal de controle PWM */
  cntrlSignal_esq = (cntrlP_esq + cntrlI_esq + cntrlD_esq) + 60 ;

  /* Saturador */
  if (cntrlSignal_esq >= 254 ) cntrlSignal_dir = 254;
  if ( cntrlSignal_esq <= -254) cntrlSignal_dir = -254;

  /*Acionamento do motor sentido negativo de mov*/
  if (cntrlSignal_esq < 0 ) {
    cntrlSignal_esq = -cntrlSignal_esq;
    motor1.setSpeed(cntrlSignal_esq);
    motor1.run(FORWARD);
  }
  /*Acionamento do motor sentido positivo de mov*/
  else {
    motor1.setSpeed(cntrlSignal_esq);
    motor1.run(BACKWARD);
  }
}
