//---------------------------------Definicao de variáveis globais-------------------------------------
/* Velocidade Angular e linear */
float we = 0.0;
float wd = 0.0;
int pulsos_E = 0;
int pulsos_D = 0;
/* Variaveis para envio */
int EnvioX = 0;
int EnvioY = 0;
int EnvioTETA = 0;
/* Constantes e definicoes do robo */
float Pi = 3.1415926535;
float X = 0, Y = 0, teta = 0;
int CE = 700;  //Resolucao do encoder
int RD = 3.4;  //right wheel
int RE = 3.4;  //Left wheel
int B = 19.5;  //Distancia entre rodas
/*  Variáveis detempo  */
unsigned long currentTime;
unsigned long lastTime = 0;
const unsigned long periodTime = 50;

/*Variaveis de controle PID roda esquerda */
float cntrlP_esq = 0;
float cntrlI_esq = 0;
float cntrlD_esq = 0;
float cntrlSignal_esq = 0;
float error_esq, lastError_esq = 0;
float Setpoint_esq = 0;
/*Variaveis de controle PID roda direita */
float cntrlP_dir = 0;
float cntrlI_dir = 0;
float cntrlD_dir = 0;
float cntrlSignal_dir = 0;
float error_dir, lastError_dir = 0;
float Setpoint_dir = 0;

float kp = 0.03;
float ki = 0.06;
float kd = 0.007;

/* Variaveis aux*/


/* ------------- Variaveis para primeiro encoder   */
const byte Encoder_C1_1 = 2;
const byte Encoder_C2_1 = 4;
byte Encoder_C1_1Last_DIR;
long int duracao_DIR;
boolean Direcao_DIR;

/* ------------- Variaveis para segundo encoder   */
const byte Encoder_C1_2 = 3;
const byte Encoder_C2_2 = 8;
byte Encoder_C1_1Last_ESQ;
long int duracao_ESQ;
boolean Direcao_ESQ;

byte speed = 100; // Mude este valor (0-255) para controlar a velocidade dos motores
/* Definicao dos pinos da ponte H.
  Enable e sentido de cada motor (horario ou anti-horario)
  Motor A -> ESQUERDO,  Motor B -> DIREITO*/
#define pinEnableMotorA  6  
#define pinEnableMotorB 5

#define pinSentido1MotorA 7
#define pinSentido2MotorA 9

#define pinSentido1MotorB 10
#define pinSentido2MotorB 11

void setup() {
  Serial.begin(9600);
  pinMode(pinEnableMotorA, OUTPUT); // Colocando os pinos como saída
  pinMode(pinEnableMotorB, OUTPUT);
  pinMode(pinSentido1MotorA, OUTPUT);
  pinMode(pinSentido2MotorA, OUTPUT);
  pinMode(pinSentido1MotorB, OUTPUT);
  pinMode(pinSentido2MotorB, OUTPUT);
  EncoderInit();
}

void loop() {
 // if (Serial.available() > 0) {
   // Setpoint_dir = Serial.read() - '0';
   // Setpoint_esq = Serial.read() - '0';

   // Setpoint_dir = Setpoint_dir/100;
    //Setpoint_esq = Setpoint_esq/100;
  //}
  Setpoint_dir = 0.5;
  Setpoint_esq = 0.5;
  if (millis() > lastTime + periodTime) { //Periodo amostral
    lastTime = millis(); // Reset Timer
    /* Leitura dos encoders*/
    noInterrupts();
    pulsos_E = duracao_ESQ;
    duracao_ESQ = 0;
    pulsos_D = duracao_DIR;
    duracao_DIR = 0;
    interrupts();
    /* Realizar a odometria e o controle de vel */
    odometria(pulsos_D, pulsos_E);
    ControleDeVelocidadeEsq(pulsos_E, Setpoint_esq);
    ControleDeVelocidadeDir(pulsos_D, Setpoint_dir);

    Serial.print(Setpoint_esq);
    Serial.print(" ");
    Serial.print(wd);
    Serial.print(" ");
    
    Serial.println(we);
    
    //EnvioX = X * 100;
    //EnvioY = Setpoint_dir * 100;
    //EnvioTETA = Setpoint_esq * 100;
    //Serial.print(EnvioX); Serial.print(",");
    //Serial.print(EnvioY); Serial.print(",");
    //Serial.println(EnvioTETA);

  }

}
