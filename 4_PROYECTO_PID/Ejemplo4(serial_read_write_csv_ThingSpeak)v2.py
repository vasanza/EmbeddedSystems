#!/usr/bin/env python
import time
import serial
import numpy
import csv
import requests
import json

#Serial Communication
try:
	ser = serial.Serial(
	port='/dev/ttyS1',
	baudrate = 9600,
	parity=serial.PARITY_NONE,
	stopbits=serial.STOPBITS_ONE,
	bytesize=serial.EIGHTBITS,
	timeout=1
	)
	#communication loop
	arr = []
	contador=0
	datos=[]
	cntSeg=0
	DataRead=[]
	
	while contador<200: #number of samples
		DataRead=[]
		Datain=[]
		Dataout=[]
		ser.flush()
		time.sleep(0.1)
		try:
			DataRead=ser.readline().strip()
			DataRead=DataRead[DataRead.find("$")+1:DataRead.find("#")]
			Datos=DataRead
			Dataout=DataRead[0:DataRead.find(",")]
			Datain=DataRead[DataRead.find(",")+1:len(DataRead)]
			if len(Datain) > 0 and len(Dataout) > 0:
				datos=DataRead
				print datos
				#Datain=datos[0:datos.find(",")]
				#print Datain
				#Dataout=datos[datos.find(",")+1:len(datos)]
				#print Dataout
				arr.insert(contador,[contador, Dataout,Datain])
				contador+=1
				cntSeg+=1
			#thingspeak solo permite hacer consulta y envio de datos cada 15seg
			if cntSeg > 14: #Write data to Thingsboard
				print("Enviando datos a thingspeak")
				print str(Datain)
				print str(Dataout)
        			enviar = requests.get("https://api.thingspeak.com/update?api_key=S1EIDYYP6ZRR02FI&field1="+str(Dataout)+"&field2="+str(Datain))
				cntSeg=0
				#status thingspeak
			        if enviar.status_code == requests.codes.ok:
			                if enviar.text != '0':
                         			print("Datos enviados correctamente")
                			else:
                         			print("Tiempo de espera insuficiente (>15seg)")
        			else:
                			print("Error en el request: ",enviar.status_code)
		except:
			break
	
	print arr
	print len(arr)
	#write csv file
	with open('Datos.csv', 'w') as file:
		fieldnames=['Item','output','input']
		write = csv.writer(file)
		write.writerow(fieldnames)
		write.writerows(arr) 
except KeyboardInterrupt: #close serial comunication when user force stop
	print ()
	ser.close()
