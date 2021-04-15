import serial
import time

atmega = serial.Serial('/dev/ttyS1',9600)   #para raspberry '/dev/ttyS0'
#print("conectado por serial")

time.sleep(1)

try:
	comando = "L"
	atmega.write(comando.encode())
	atmega.write('\r\n'.encode())

except(KeyboardInterrupt,SystemExit):
    print("")
    print("hasta la vista ")
    atmega.close()