void odometria(int ND, int NE) {
  X = X + (RD * ND + RE * NE) * (Pi / CE) * cos(teta);
  Y = Y + (RD * ND + RE * NE) * (Pi / CE) * sin(teta);
  teta = teta + (RD * ND - RE * NE) * (2 * Pi / CE) / B;
}
