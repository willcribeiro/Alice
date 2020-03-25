/*<function of the main program, responsible for reading the encoders>
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
