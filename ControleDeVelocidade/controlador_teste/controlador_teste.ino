/* ------------- Variaveis para primeiro encoder   */
const byte Encoder_C1_1 = 2;
const byte Encoder_C2_1 = 4;
byte Encoder_C1_1Last_ESQ;
long int duracao_ESQ;
boolean Direcao_ESQ;

#define pinEnableMotorA  5
#define pinEnableMotorB 6

#define pinSentido1MotorA 7
#define pinSentido2MotorA 9

#define pinSentido1MotorB 10
#define pinSentido2MotorB 11

unsigned long currentTime;
unsigned long lastTime = 0;
const unsigned long periodTime = 50;

float w = 0;
int n = 0;
float Pi = 3.1415926535;
float Setpoint = 0.5;


float cntrlP = 0;
float cntrlI = 0;
float cntrlD = 0;
float cntrlSignal = 0;
float error, lastError = 0;
float kp = 0.03;
float ki = 0.06;
float kd = 0.007;

#define ERRO_MIN 75

void setup() {
  Serial.begin(9600);
  pinMode(pinEnableMotorA, OUTPUT); // Colocando os pinos como saída
  pinMode(pinEnableMotorB, OUTPUT);
  pinMode(pinSentido1MotorA, OUTPUT);
  pinMode(pinSentido2MotorA, OUTPUT);
  pinMode(pinSentido1MotorB, OUTPUT);
  pinMode(pinSentido2MotorB, OUTPUT);
  EncoderInit();
  mov(1, 100, 1, 100);
}

void loop() {
  // Control Loop Frequency Time
  if (millis() > lastTime + periodTime)
  {
    lastTime = millis(); // Reset Timer
    noInterrupts();
    n = duracao_ESQ;
    duracao_ESQ = 0;
    interrupts();


    w = (2 * Pi * n) / (periodTime * 20); //Calculo da velocidade W de uma roda
    lastError = error; //Salvo erro passado
    error = Setpoint - w;  //Calculo novo erro
    cntrlP = kp * error;
    cntrlI = cntrlI + ki * error * periodTime;
    cntrlD = kd * (error - lastError) / periodTime;
    cntrlSignal = (cntrlP + cntrlI + cntrlD)+40;  //Sinal de controle PWM
    if (cntrlSignal >= 200 || cntrlSignal <= -200 ) { //Saturador
      cntrlSignal = 200;
    }
    if (cntrlSignal < 0 ) {
      cntrlSignal = -cntrlSignal;
      mov(2, cntrlSignal, 2, cntrlSignal);
    }

    else {
      mov(1, cntrlSignal, 1, cntrlSignal);
    }

    if(w>0.45){
      Setpoint = -0.5;
    }
    //Serial.print("cntrlSignal ");
    //Serial.println(cntrlSignal);
    //Serial.print("lastError ");
    //Serial.println(lastError);
    //Serial.print("w ");
    //Serial.println(w);

    Serial.print(cntrlSignal/10);
    Serial.print(" ");
     Serial.print(Setpoint);
    Serial.print(" ");
    //Serial.println(cntrlSignal);
    //Serial.print(" ");
    Serial.println(w);

  }
}
void mov(int SinE, int we, int SinD, int wd) {
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
}

//------------------INICIALIZACAO DO ENCODER---------
void EncoderInit()
{
  pinMode(Encoder_C2_1, INPUT);

  attachInterrupt(0, calculapulso_ESQ, CHANGE);
}

//---------------CALCULO ENCODER ESQUERDO-----------------
void calculapulso_ESQ()
{
  int Lstate = digitalRead(Encoder_C1_1);
  if ((Encoder_C1_1Last_ESQ == LOW) && Lstate == HIGH)
  {
    int val = digitalRead(Encoder_C2_1);
    if (val == LOW && Direcao_ESQ)
    {
      Direcao_ESQ = false; //Reverse
    }
    else if (val == HIGH && !Direcao_ESQ)
    {
      Direcao_ESQ = true;  //Forward
    }
  }
  Encoder_C1_1Last_ESQ = Lstate;

  if (!Direcao_ESQ)  duracao_ESQ++;
  else  duracao_ESQ--;
}
