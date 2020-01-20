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

const byte Encoder_C1 = 2;
const byte Encoder_C2 = 4;
byte Encoder_C1Last;
int duracao;
boolean Direcao;

const int AIA = 9;  // (pwm) pino 9 conectado ao pino A-IA do Módulo
const int AIB = 5;  // (pwm) pino 5 conectado ao pino A-IB do Módulo
const int BIA = 10; // (pwm) pino 10 conectado ao pino B-IA do Módulo
const int BIB = 6;  // (pwm) pino 6 conectado ao pino B-IB do Módulo
 
byte speed = 255;  // Mude este valor (0-255) para controlar a velocidade dos motores
 
void setup() {
  Serial.begin(57600);
  pinMode(AIA, OUTPUT); // Colocando os pinos como saída
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);

  EncoderInit();
}
 
void loop() {//O programa ficará em loop, girando um motor para um lado, depois para o outro e depois troca de motor e repete
  forward();
  Serial.print("Pulso: ");
  Serial.println(duracao);
  delay(1000);
  
}
 
void backward()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, speed);
  analogWrite(BIA, 0);
  analogWrite(BIB, speed);
}
 
void forward()
{
  analogWrite(AIA, speed);
  analogWrite(AIB, 0);
  analogWrite(BIA, speed);
  analogWrite(BIB, 0);
}
 
void left()
{
  analogWrite(AIA, speed);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, speed);
}
 
void right()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, speed);
  analogWrite(BIA, speed);
  analogWrite(BIB, 0);
}


void EncoderInit()
{
  pinMode(Encoder_C2, INPUT);
  attachInterrupt(0, calculapulso, CHANGE);
}

void calculapulso()
{
  int Lstate = digitalRead(Encoder_C1);
  if ((Encoder_C1Last == LOW) && Lstate == HIGH)
  {
    int val = digitalRead(Encoder_C2);
    if (val == LOW && Direcao)
    {
      Direcao = false; //Reverse
    }
    else if (val == HIGH && !Direcao)
    {
      Direcao = true;  //Forward
    }
  }
  Encoder_C1Last = Lstate;

  if (!Direcao)  duracao++;
  else  duracao--;
}
