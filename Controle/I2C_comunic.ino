/*<function of the main program, responsible for I2C communication>
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
