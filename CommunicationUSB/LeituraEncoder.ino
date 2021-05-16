
//------------------INICIALIZACAO DO ENCODER---------
void EncoderInit()
{
  pinMode(Encoder_C2_1, INPUT);
  pinMode(Encoder_C2_2, INPUT);

  attachInterrupt(1, calculapulso_ESQ, CHANGE);
  attachInterrupt(0, calculapulso_DIR, CHANGE);
}

//---------------CALCULO ENCODER ESQUERDO-----------------
void calculapulso_ESQ()
{
  int Lstate = digitalRead(Encoder_C1_2);
  if ((Encoder_C1_1Last_ESQ == LOW) && Lstate == HIGH)
  {
    int val = digitalRead(Encoder_C2_2);
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

  if (!Direcao_ESQ)  duracao_ESQ--;
  else  duracao_ESQ++;
}
//-----------------------CALCULO DO ENCODER DIREITO-------------------
void calculapulso_DIR()
{
 int Lstate = digitalRead(Encoder_C1_1);
  if ((Encoder_C1_1Last_DIR == LOW) && Lstate == HIGH)
  {
    int val = digitalRead(Encoder_C2_1);
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

  if (!Direcao_DIR)  duracao_DIR++;
  else  duracao_DIR--;
}
