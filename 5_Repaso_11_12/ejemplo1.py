import serial
import time

atmega = serial.Serial('/dev/ttyS1',9600)   #para raspberry '/dev/ttyS0'
print("conectado por serial")

time.sleep(2)

try:
    while(1):
        comando = input("introduzca comando (H/L): ")
        atmega.write(comando.encode())
        atmega.write('\r\n'.encode())
        if comando == 'H':
            print ("led encendido")
        elif comando == 'L':
            print ("led apagado")

except(KeyboardInterrupt,SystemExit):
    print("")
    print("hasta la vista ")
    atmega.close()
