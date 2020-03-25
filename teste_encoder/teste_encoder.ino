/*<Program to test the motors and encoder to project Alice>
  Copyright (C) <2020>  <William Ribeiro>
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.*/

#include <Wire.h>

/* ------  Variaveis globais  ---------- */
float Pi = 3.1415926535;
int X = 0, Y = 0, teta = 0;
int CE = 830;  //Resolucao do encoder
int RD = 3.3;  //right wheel
int RE = 3.3;  //Left wheel
int B = 20;  //Distancia entre rodas
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


const int AIA = 9;  // (pwm) pino 9 conectado ao pino A-IA do Módulo
const int AIB = 5;  // (pwm) pino 5 conectado ao pino A-IB do Módulo
const int BIA = 10; // (pwm) pino 10 conectado ao pino B-IA do Módulo
const int BIB = 6;  // (pwm) pino 6 conectado ao pino B-IB do Módulo

byte speed = 153;  // Mude este valor (0-255) para controlar a velocidade dos motores

void setup() {
  Serial.begin(57600);
  pinMode(AIA, OUTPUT); // Colocando os pinos como saída
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
  EncoderInit();
  Wire.begin(0x18);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}


void odometria(int ND, int NE) {
  X = X + (RD * ND + RE * NE) * (Pi / CE) * cos(teta);
  Y = Y + (RD * ND + RE * NE) * (Pi / CE) * sin(teta);
  teta = teta + (RD * ND - RE * NE) * (2 * Pi / CE) / B;
  Serial.println(X);
}

void mov(int we, int wd) {
  if (we < 0 and wd < 0) {
    analogWrite(AIA, abs(we));
    analogWrite(AIB, 0);
    analogWrite(BIA, 0);
    analogWrite(BIB, abs(wd));
  }

  else if (we >= 0 and wd >= 0) {
    analogWrite(AIA, 0);
    analogWrite(AIB, we);
    analogWrite(BIA, wd);
    analogWrite(BIB, 0);
  }
}

void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
    int number1 = Wire.read(); // Read fist value
    if (number1 == 0)
      number1 = Wire.read();
    int number2 = Wire.read();
    int sinal = Wire.read();
    //sentido de giro
    if (sinal == 1) {
      number1 = number1 * -1;
      number2 = number2 * -1;
    }
    mov(number1, number2);
  }
}

void requestEvent() {
  float data[2];
  data[0] = duracao_DIR;
  data[1] = duracao_ESQ;
  Wire.write((byte*) &data, 3 * sizeof(float));
}


void loop() {//O programa ficará em loop, girando um motor para um lado, depois para o outro e depois troca de motor e repete
  delay(100);
}


void backward()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, speed);
  analogWrite(BIA, 0);
  analogWrite(BIB, speed);
}



void EncoderInit()
{
  pinMode(Encoder_C2_1, INPUT);
  pinMode(Encoder_C2_2, INPUT);

  attachInterrupt(0, calculapulso_ESQ, CHANGE);
  attachInterrupt(1, calculapulso_DIR, CHANGE);
}

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
