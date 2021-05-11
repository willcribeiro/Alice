//---------------------------------Definicao de variáveis globais-------------------------------------
float we = 0.0;
float wd = 0.0;
int EnvioX = 0;
int EnvioY = 0;
int EnvioTETA = 0;
float Pi = 3.1415926535;
float X = 0, Y = 0, teta = 0;
int CE = 700;  //Resolucao do encoder
int RD = 3.4;  //right wheel
int RE = 3.4;  //Left wheel
int B = 19.5;  //Distancia entre rodas
long int LE, LD;

/* ------------- Variaveis para primeiro encoder   */
const byte Encoder_C1_1 = 2;
const byte Encoder_C2_1 = 4;
byte Encoder_C1_1Last_ESQ;
long int duracao_ESQ;
boolean Direcao_ESQ;
/* ------------- Variaveis para segundo encoder   */
const byte Encoder_C1_2 = 3;
const byte Encoder_C2_2 = 8;
byte Encoder_C1_1Last_DIR;
long int duracao_DIR;
boolean Direcao_DIR;


byte speed = 100; // Mude este valor (0-255) para controlar a velocidade dos motores

#define pinEnableMotorA  5
#define pinEnableMotorB 6

#define pinSentido1MotorA 7
#define pinSentido2MotorA 9

#define pinSentido1MotorB 10
#define pinSentido2MotorB 11
 
void setup(){
    
  Serial.begin(9600);  
  pinMode(pinEnableMotorA, OUTPUT); // Colocando os pinos como saída
  pinMode(pinEnableMotorB, OUTPUT);
  pinMode(pinSentido1MotorA, OUTPUT);
  pinMode(pinSentido2MotorA, OUTPUT);
  pinMode(pinSentido1MotorB, OUTPUT);
  pinMode(pinSentido2MotorB, OUTPUT);
  EncoderInit();

}
void loop(){
  while (X < 60){
  if(Serial.available() > 0){
        int entrada = Serial.read() - '0';
        mov(1,speed,2,speed);  
       //int valorE = Serial.read() - '0'; 
       //int valorwe = Serial.read() - '0'; 
       //int valorD = Serial.read() - '0'; 
       //int valorwd = Serial.read() - '0'; 
       //if (entrada == 5){
        //mov(1,200,1,200);  
        //Serial.print(entrada);
      // }
      // else if (entrada == 0){
        //mov(1,0,1,0);  
        //Serial.print(entrada);
       //}
    }
    //Realizar a Leitura do encoder
    //Fazer odometria
   // Serial.print(we);Serial.print(",");
    //Serial.println(wd);
    delay(50);
  }
  mov(1,0,1,0);
 }
void odometria(int ND, int NE) {
  X = X + (RD * ND + RE * NE) * (Pi / CE) * cos(teta);//Faltando redução 1:34
  Y = Y + (RD * ND + RE * NE) * (Pi / CE) * sin(teta);
  teta = teta + (RD * ND - RE * NE) * (2 * Pi / CE) / B;
  EnvioX = X*100;
  EnvioY = Y*100;
  EnvioTETA = teta*100;
  Serial.print(EnvioX);Serial.print(",");
  Serial.print(EnvioY);Serial.print(",");
  Serial.println(EnvioTETA);
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
    
  odometria(duracao_DIR,duracao_ESQ);
  duracao_DIR = 0;
  duracao_ESQ = 0;
}
//------------------INICIALIZACAO DO ENCODER---------
void EncoderInit()
{
  pinMode(Encoder_C2_1, INPUT);
  pinMode(Encoder_C2_2, INPUT);

  attachInterrupt(0, calculapulso_ESQ, CHANGE);
  attachInterrupt(1, calculapulso_DIR, CHANGE);
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
//-----------------------CALCULO DO ENCODER DIREITO-------------------
void calculapulso_DIR()
{
  int Lstate = digitalRead(Encoder_C1_2);
  if ((Encoder_C1_1Last_DIR == LOW) && Lstate == HIGH)
  {
    int val = digitalRead(Encoder_C2_2);
    if (val == LOW && Direcao_DIR)
    {
      Direcao_DIR = false; //Reverse
    }
    else if (val == HIGH && !Direcao_DIR)
    {
      Direcao_DIR = true;  //Forward
    }
  }
  Encoder_C1_1Last_DIR = Lstate;

  if (!Direcao_DIR)  duracao_DIR--;
  else  duracao_DIR++;
}
