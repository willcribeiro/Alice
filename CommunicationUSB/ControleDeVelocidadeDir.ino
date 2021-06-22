float ControleDeVelocidadeDir(int n_dir, float setpoint_dir) {
  /* Calculo da velocidade W de uma roda */
  wd = (2 * Pi * n_dir) / (periodTime * 20);

  /* Controlar PID da roda DIREITA*/
  error_dir = setpoint_dir - wd;
  cntrlP_dir = kp * error_dir;
  cntrlI_dir = cntrlI_dir + ki * error_dir * periodTime;
  cntrlD_dir = kd * (error_dir - lastError_dir) / periodTime;

  /* Sinal de controle PWM */
  cntrlSignal_dir = (cntrlP_dir + cntrlI_dir + cntrlD_dir) + 60;

  /* Saturador */
  if (cntrlSignal_dir >= 254 ) cntrlSignal_dir = 254;
  if (cntrlSignal_dir <= -254) cntrlSignal_dir = -254;

  /*Acionamento do motor sentido negativo de mov*/
  if (cntrlSignal_dir < 0 ) {
    cntrlSignal_dir = -cntrlSignal_dir;
    motor2.setSpeed(cntrlSignal_dir);
    motor2.run(FORWARD);
  }

  /*Acionamento do motor sentido positivo de mov*/
  else {
    motor2.setSpeed(cntrlSignal_dir);
    motor2.run(BACKWARD);
  }
}
