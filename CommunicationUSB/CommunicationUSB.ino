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


float kp = 0.002;
float ki = 2.5;
float kd = 0.01;

/* Variaveis aux*/
float delta_x;
float delta_y;
float Theta_ref;
float Theta_Robo;
float delta_theta;
float delta_theta2;
float delta_l_ref;
float delta_l;
int cont = 0;
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

/*  PONTOS FINAIS  */
int xf = 100;
int yf = 0;

/*  Ganhos do controlador */
float k_theta = 0.02;
float k_l = 0.015;

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
    /* Correcao no teta robo */
    Theta_Robo = teta;
    if (Theta_Robo > Pi) {
      Theta_Robo = Theta_Robo - 2 * Pi;
    }
    else if (Theta_Robo < -Pi) {
      Theta_Robo = Theta_Robo + 2 * Pi;
    }

    /* Calculo dos Delta x e y */
    delta_x = xf - X;
    delta_y = yf - Y;

    /* Calculo do Theta estrela/Referencial */
    Theta_ref = atan2(delta_y, delta_x);

    /* Calculo do delta l do referencial e delta Theta*/
    delta_l_ref = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
    delta_theta = Theta_ref - Theta_Robo;

    /*Adequação do angulo para ficar contido de -Pi a Pi*/
    if (delta_theta > Pi) {
      delta_theta = delta_theta - 2 * Pi;
    }
    else if (delta_theta < -Pi) {
      delta_theta = delta_theta + 2 * Pi;
    }

    /* Caluclo do delta L */
    delta_l = delta_l_ref * cos(delta_theta);

    /* Calculo da velocidade linear e angular */
    V = k_l * delta_l;
    if (V > 0.4) V = 0.4;  /* Limitador da velocidade máxima */

    W = k_theta * delta_theta;

    /* velocidades das juntas */
    wd_ref = (V / RD) + (B / (2 * RD)) * W;
    we_ref = (V / RE) - (B / (2 * RE)) * W;

    /* Acionamento dos motores */
    ControleDeVelocidadeEsq(pulsos_E, we_ref);
    ControleDeVelocidadeDir(pulsos_D, wd_ref);

    /* Condicao de parada do robo */
    if (delta_l_ref <= 6) {
      cont = cont + 1;
      if (cont == 1) {
        xf = 100;
        yf = 100;
      }
      else if (cont == 2) {
        xf = 0;
        yf = 100;
      }
      else if (cont == 3) {
        xf = 0;
        yf = 0;
      }

      else if (cont == 4) {
        while (1) {
          motor1.setSpeed(0);
          motor2.setSpeed(0);
          motor1.run(RELEASE);
          motor2.run(RELEASE);
        }
      }

    }
    //EnvioX = X * 100;
    //EnvioY = Setpoint_dir * 100;
    //EnvioTETA = Setpoint_esq * 100;
    //Serial.print(EnvioX); Serial.print(",");
    //Serial.print(EnvioY); Serial.print(",");
    //Serial.println(EnvioTETA);
  }
}
