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
        x = [1,230,1,230]
    elif vel == 2:
        x = [2,170,2,170]
    elif vel == 5:
        x = [1,0,1,0]
    elif vel == 6:
        x = [1,170,2,170]
    elif vel == 4:
        x = [2,170,1,170]
    bus.write_i2c_block_data(addr,0 ,x)

wd = 0
we = 0
print("Entre com o tipo de movimentacao")
print("1 - Controle remoto,  2 controle manual")
ent = input(">>>>    ")

while numb ==1:
    if ent == 1:
        print("Entre com a movimentacao")
        vel = input(">>>>    ")
        Controle_Remoto(vel)
        sleep(0.5)     

    elif ent ==2:
        print("Entre com os valores")
        n1 = input("Sentido >>>>   ")
        n2 = input("Velocidade >>>>   ")
        n3 = input("Sentido >>>>   ")
        n4 = input("Velocidade >>>>   ")
        x = [n1,n2,n3,n4]
        bus.write_i2c_block_data(addr,0 ,x)
        sleep(0.2)
        data = get_data()
        print(get_float(data, 0))
        print(get_float(data, 1))




