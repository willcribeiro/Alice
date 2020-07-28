from smbus import SMBus
from time import sleep
import struct

addr = 0x18
bus = SMBus(1)
numb = 1

velocidade_maxima = 200

def get_data():
    return bus.read_i2c_block_data(addr, 0);

def get_float(data, index):
    bytes = data[4*index:(index+1)*4]
    return struct.unpack('f', "".join(map(chr, bytes)))[0]

def Controle_Remoto(func):
    if vel == 8:
        x = [1,velocidade_maxima,1,velocidade_maxima]
    elif vel == 2:
        x = [2,velocidade_maxima,2,velocidade_maxima]
    elif vel == 5:
        x = [1,0,2,0]
    elif vel == 6:
        x = [1,velocidade_maxima,2,velocidade_maxima]
    elif vel == 4:
        x = [2,velocidade_maxima,1,velocidade_maxima]
    bus.write_i2c_block_data(addr,0 ,x)
    


wd = 0
we = 0

while numb ==1:
    print("Entre com a movimentacao")
    vel = input(">>>>    ")
    Controle_Remoto(vel)
    sleep(0.5)     

