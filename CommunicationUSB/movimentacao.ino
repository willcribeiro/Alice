void mov(int SinE, int w_e, int SinD, int wd) {
 
  analogWrite(pinEnableMotorA, wd);
  analogWrite(pinEnableMotorB, we);
  if (SinE == 2) {
    digitalWrite(pinSentido1MotorA, HIGH);
    digitalWrite(pinSentido2MotorA, LOW);
  }
  if (SinE == 1) {
    digitalWrite(pinSentido1MotorA, LOW);
    digitalWrite(pinSentido2MotorA, HIGH);
  }

  if (SinD == 2) {
    digitalWrite(pinSentido1MotorB, HIGH);
    digitalWrite(pinSentido2MotorB, LOW);
  }
  if (SinD == 1) {
    digitalWrite(pinSentido1MotorB, LOW);
    digitalWrite(pinSentido2MotorB, HIGH);
  }

  odometria(duracao_DIR, duracao_ESQ);
  duracao_DIR = 0;
  duracao_ESQ = 0;
}
