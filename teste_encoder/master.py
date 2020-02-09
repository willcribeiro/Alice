from smbus import SMBus

addr = 0x18
bus = SMBus(1)
numb = 1

print("Entre com a movimentação")
while numb ==1:
    n1 = input(">>>>    ")
    bus.write_byte_data(addr,0,numb)
