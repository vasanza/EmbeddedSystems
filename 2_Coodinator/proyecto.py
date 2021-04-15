import time
import serial
import requests
import json

try:
  ser = serial.Serial(
        port='/dev/ttyS1',
        baudrate = 9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
  )

  while True:
    pwm=0
    ser.flush()
    arr = []
    ndatos='0'
    print "esperando ndatos"
    ser.write(str(b'\x24\x31\x41\x00\x54\x0A\x0D'))
    ndatos=ser.readline().strip()
    if ndatos>'0':
        print ndatos
        index=0
        while str(index) < ndatos:
                #print "esperando trama"
                ByteInicio=ser.read()
                #print ByteInicio
                if ByteInicio=='$':
                         ByteID=int(ser.read(),base=16)
                         ByteTask=int(ser.read(),base=16)
                         ByteData=int(ser.read(),base=16)
                         ByteCheckSum=ser.read()
                         #CheckSum = ((0x24 ^ ByteID) ^ ByteTask) ^ ByteDate
                         if ByteID==6:
                                #if ByteCheckSum==CheckSum:
                                print "trama ok"
                                #print str(ByteData)
                                #print str(ByteCheckSum)
				arr.insert(index,ByteData)
                                index+=1
                                #print str(index)
        time.sleep(2)
        if ByteData > 5:
                ser.write(str(b'\x24\x31\x42\x7f\x28\x0A\x0D'))
                pwm=50
        else:
                ser.write(str(b'\x24\x31\x42\x00\x57\x0A\x0D'))
                pwm=0
        time.sleep(2)
        #Write data to Thingsboard
        enviar = requests.get("https://api.thingspeak.com/update?api_key=5KYEGAS4M2ISKXQN&field1="+str(ByteData)+"&field2="+str(pwm))
        if enviar.status_code == requests.codes.ok:
                if enviar.text != '0':
                         print("Datos enviados correctamente")
                else:
                         print("Tiempo de espera insuficiente (>15seg)")
        else:
                print("Error en el request: ",enviar.status_code)
        #Read data from Thingsboard
        recibir = requests.get("https://api.thingspeak.com/channels/1120231/feeds.json")
        jsonString = json.dumps(recibir.json(),indent=2)
        print(jsonString)
        print("-------------------------------------------------")
        jsonString = json.dumps(recibir.json().get("feeds"),indent=2)
        print(jsonString)
        print("----Mostrar la info de los primeros 3 valores----")
        num = 3 if len(recibir.json().get("feeds"))>3 else len(recibir.json().get("feeds"))

        for i in range(num):
                print("*************************************************")
                jsonString = json.dumps(recibir.json().get("feeds")[i],indent=2)
                print(jsonString)
        print("-------Mostrar solo los primeros 3 valores-------")
        for i in range(num):
                print("*************************************************")
                print("Variable1:",recibir.json().get("feeds")[i].get("field1"))
                print("Variable2:",recibir.json().get("feeds")[i].get("field2"))

        print("----Mostrar la info de los ultimos 3 valores-----")
        recibir = requests.get("https://api.thingspeak.com/channels/1120231/feeds.json?results="+str(num))
        jsonString = json.dumps(recibir.json().get("feeds"),indent=2)
        print(jsonString)
        print("-------Mostrar solo los ultimos 3 valores-------")
        for i in range(num):
                print("*************************************************")
                print("Variable1:",recibir.json().get("feeds")[i].get("field1"))
                #print("Variable2:",recibir.json().get("fedds")[i].get("field2"))
    time.sleep(11)
except KeyboardInterrupt: #close serial comunication when user force stop
  print ()
  ser.close()
