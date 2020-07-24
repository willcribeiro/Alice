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
        x = [1,170]
        y = [1,170]
    elif vel == 2:
        x = [2,170]
        x = [2,170]
    elif vel == 5:
        x = [1,0]
        y = [2,0]
    elif vel == 6:
        x = [1,170]
        y = [2,170]
    elif vel == 4:
        x = [2,170]
        x = [1,170]
    bus.write_i2c_block_data(addr,0 ,x)
    bus.write_i2c_block_data(addr,0 ,y)


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
        n1 = input(">>>>   ")
        n2 = input(">>>>   ")
        n3 = input(">>>>   ")
        n4 = input(">>>>   ")
        x = [n1,n2]
        y = [n3,n4]
        bus.write_i2c_block_data(addr,0 ,x)
        bus.write_i2c_block_data(addr,0 ,y)
        sleep(0.2)
        data = get_data()
        print(get_float(data, 0))
        print(get_float(data, 1))


