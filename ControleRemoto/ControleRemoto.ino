#include <math.h>
#include <AFMotor.h>

//---------------------------------Definicao de variáveis globais-------------------------------------
/* Velocidade Angular e linear */
float we = 0.0;
float wd = 0.0;
float we_ref = 0.0;
float wd_ref = 0.0;
int pulsos_E = 0;
int pulsos_D = 0;
float V;
float W;
/* Variaveis para envio */
int EnvioX = 0;
int EnvioY = 0;
int EnvioTETA = 0;
/* Constantes e definicoes do robo */
float Pi = 3.1415926535;
float X = 0, Y = 0, teta = 0;
int CE = 700;  //Resolucao do encoder
int RD = 3.56;  //right wheel
int RE = 3.56;  //Left wheel
int B = 18.2;  //Distancia entre rodas
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
/*Variaveis de controle PID roda direita */
float cntrlP_dir = 0;
float cntrlI_dir = 0;
float cntrlD_dir = 0;
float cntrlSignal_dir = 0;
float error_dir, lastError_dir = 0;


float kp = 0.03;
float ki = 0.06;
float kd = 0.007;

/* Variaveis aux*/
float delta_x;
float delta_y;
float Theta_ref;
float Theta_Robo;
float delta_theta;
float delta_theta2;
float delta_l_ref;
float delta_l;

int comando;
/*Motor 2 - Esquerdo */
const byte Encoder_C1_2 = 19;
const byte Encoder_C2_2 = 33;
byte Encoder_C1_1Last_DIR;
long int duracao_DIR;
boolean Direcao_DIR;

/*Motor 1 - Esquerdo */
const byte Encoder_C1_1 = 18;
const byte Encoder_C2_1 = 31;
byte Encoder_C1_1Last_ESQ;
long int duracao_ESQ;
boolean Direcao_ESQ;

byte speed = 100; // Mude este valor (0-255) para controlar a velocidade dos motores
/* Definicao dos pinos da ponte H.
  Enable e sentido de cada motor (horario ou anti-horario)
  Motor A -> ESQUERDO,  Motor B -> DIREITO*/

/*  PONTOS FINAIS  */
int xf = 100;
int yf = 0;

/*  Ganhos do controlador */
float k_theta = 0.06;
float k_l = 0.01;

AF_DCMotor motor1(1);  //Motor Esquerdo
AF_DCMotor motor2(2);  //Motor Direito

void setup() {
  Serial.begin(9600);
  motor1.setSpeed(0); //Vel.  Inicial como 0
  motor2.setSpeed(0);
  EncoderInit();
}

void loop() {
  if (millis() > lastTime + periodTime) { //Periodo amostral
    lastTime = millis(); // Reset Timer
    /* Leitura dos encoders*/
    noInterrupts();
    pulsos_E = duracao_ESQ;
    duracao_ESQ = 0;
    pulsos_D = duracao_DIR;
    duracao_DIR = 0;
    interrupts();

    /* Realizar a odometria */
    odometria(pulsos_D, pulsos_E);


    if (Serial.available() > 0) {
      comando = Serial.read() - '0';
      EnvioX = X * 100;
      EnvioY = Y * 100;
      EnvioTETA = teta * 100;
      Serial.print(EnvioX); Serial.print(",");
      Serial.print(EnvioY); Serial.print(",");
      Serial.println(EnvioTETA);

      switch (comando) {
        case 2:
          motor1.setSpeed(144.75);
          motor2.setSpeed(150);
          motor1.run(FORWARD);
          motor2.run(FORWARD);
          break;
        case 8:
          motor1.setSpeed(144.75);
          motor2.setSpeed(150);
          motor1.run(BACKWARD);
          motor2.run(BACKWARD);
          break;
        case 6:
          motor1.setSpeed(120);
          motor2.setSpeed(120);
          motor1.run(BACKWARD);
          motor2.run(FORWARD);
          break;
        case 4:
          motor1.setSpeed(120);
          motor2.setSpeed(120);
          motor1.run(FORWARD);
          motor2.run(BACKWARD);
          break;
        case 5:
          motor1.setSpeed(0);
          motor2.setSpeed(0);
          motor1.run(RELEASE);
          motor2.run(RELEASE);
          break;
        default:
          motor1.setSpeed(0);
          motor2.setSpeed(0);
          motor1.run(RELEASE);
          motor2.run(RELEASE);
      }
    }
  }
}
