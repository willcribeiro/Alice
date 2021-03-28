/*<Main program, responsible for the movement of the robot, being received the angular speed of the wheels by I2C>
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
/* ------------- Variaveis para primeiro encoder -----------------*/
const byte Encoder_C1_1 = 2;
const byte Encoder_C2_1 = 4;
byte Encoder_C1_1Last_ESQ;
long int duracao_ESQ;
boolean Direcao_ESQ;

/* ------------- Variaveis para segundo encoder ------------------*/
const byte Encoder_C1_2 = 3;
const byte Encoder_C2_2 = 8;
byte Encoder_C1_1Last_DIR;
long int duracao_DIR;
boolean Direcao_DIR;


const int AIA = 9;  // (pwm) pino 9 conectado ao pino A-IA do Módulo
const int AIB = 5;  // (pwm) pino 5 conectado ao pino A-IB do Módulo
const int BIA = 10; // (pwm) pino 10 conectado ao pino B-IA do Módulo
const int BIB = 6;  // (pwm) pino 6 conectado ao pino B-IB do Módulo
/* ----------------- Comeco do codigo ----------------------------- */
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
/*----- Funcao para movimentacao das rodas,  com base na vel angular que foi fornecida ------------------*/
void mov(int we, int wd) {
  if (we < 0 and wd < 0) { //Sentido Positivo de giro
    analogWrite(AIA, abs(we));
    analogWrite(AIB, 0);
    analogWrite(BIA, 0);
    analogWrite(BIB, abs(wd));
  }
  else if (we >= 0 and wd >= 0) { //Sentido Negativo de Giro
    analogWrite(AIA, 0);
    analogWrite(AIB, we);
    analogWrite(BIA, wd);
    analogWrite(BIB, 0);
  }
  
  else if (we > 0 and wd < 0) { //Giro em sentido horário
    analogWrite(AIA, we);
    analogWrite(AIB, 0);
    analogWrite(BIA, wd);
    analogWrite(BIB, 0);
  }
   else if (we < 0 and wd > 0) { //Giro em sentido anti-horário
    analogWrite(AIA, 0);
    analogWrite(AIB, we);
    analogWrite(BIA, 0);
    analogWrite(BIB, wd);
  }
}

void loop() {//O programa ficará em loop, girando um motor para um lado, depois para o outro e depois troca de motor e repete
  delay(100);
}
