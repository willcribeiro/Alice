from smbus import SMBus
from time import sleep
import struct

addr = 0x18
bus = SMBus(1)
numb = 1
velo_PWM = 255
def get_data():
    return bus.read_i2c_block_data(addr, 0);

def get_float(data, index):
    bytes = data[4*index:(index+1)*4]
    return struct.unpack('f', "".join(map(chr, bytes)))[0]

def Controle_Remoto(func):
    if vel == 'w':
        x = [velo_PWM,velo_PWM,1]
    elif vel == 's':
        x = [velo_PWM,velo_PWM,2]
    elif vel == 0:
        x = [1,0,1,0]
    bus.write_i2c_block_data(addr,0 ,x)

while numb ==1:    
    print("Entre com a movimentacao")
    vel = input(">>>>    ")
    Controle_Remoto(vel)
    sleep(0.5)     






