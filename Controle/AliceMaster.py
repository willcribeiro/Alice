from smbus import SMBus
from time import sleep
import struct

addr = 0x18
bus = SMBus(1)
numb = 1

def get_data():
    return bus.read_i2c_block_data(addr, 0);

def get_float(data, index):
    bytes = data[4*index:(index+1)*4]
    return struct.unpack('f', "".join(map(chr, bytes)))[0]

while numb ==1:
    


    print("Entre com os valores")
    n1 = input("Sentido M1 >>>>   ")
    n2 = input("Velocidade M1 >>>>   ")
    n3 = input("Sentido M2 >>>>   ")
    n4 = input("Velocidade M2 >>>>   ")
    x = [n1,n2,n3,n4]
    bus.write_i2c_block_data(addr,0 ,x)
    sleep(0.2)




