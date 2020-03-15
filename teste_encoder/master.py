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

def Controle_Remoto(func):
    if vel == 8:
        x = [250,250]
    elif vel == 2:
        x = [-250,-250]
    elif vel == 5:
        x = [0,0]
    elif vel == 6:
        x = [250,-250]
    elif vel == 4:
        x = [-250,250]
    bus.write_i2c_block_data(addr,0 ,x)


wd = 0
we = 0
print("Entre com o tipo de movimentacao")
print("1 - Controle remoto,  2 controle manual")
n1 = input(">>>>    ")

while numb ==1:
    if n1 == 1:
        print("Entre com a movimentacao")
        vel = input(">>>>    ")
        Controle_Remoto(vel)
        sleep(0.5)        

    elif n1 ==2:
        we+=1
        wd+=1
        sinal = 0
        W = [we,wd,sinal]
        bus.write_i2c_block_data(addr,0 ,W)
        sleep(0.05)
        if wd == 250:
            W = [0,0,0]
            bus.write_i2c_block_data(addr,0 ,W)
            break


