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

int number1 =0,number2 =0,number3 =0,number4 =0;
int inter = 0;
void receiveEvent(int howMany) { //Pq não posso por um delay ???
  while (Wire.available()) { // loop through all but the last
    number1 = Wire.read(); // Read fist value
    if (number1 == 0){
      number1 = Wire.read();
    }
    number2 = Wire.read();
    number3 = Wire.read();
    number4 = Wire.read();
    mov(number1,number2,number3,number4); 
  }
}

void requestEvent() {
  float data[3];
  data[0] = 1;
  data[1] = 2;
  Wire.write((byte*) &data, 2 * sizeof(float));
}
