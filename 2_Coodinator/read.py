#!/usr/bin/env python
import time
import serial

ser = serial.Serial(
        port='/dev/ttyS1',
        baudrate = 9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
)

arr = []
contador=0
while contador<5:
        ndatos='0'
        print "esperando ndatos"
        ser.write(str(b'\x24\x31\x41\x00\x54\x0A\x0D'))
        ndatos=ser.readline().strip()
        if ndatos>'0':
                print ndatos
                index=0
                while str(index) < ndatos:
                         print "esperando trama"
                         ByteInicio=ser.read()
                         print ByteInicio
                         if ByteInicio=='$':
                                ByteID=int(ser.read(),base=16)
                                ByteTask=int(ser.read(),base=16)
                                ByteData=int(ser.read(),base=16)
                                ByteCheckSum=ser.read()
                                #CheckSum = ((0x24 ^ ByteID) ^ ByteTask) ^ ByteDate
                                if ByteID==6:
                                        #if ByteCheckSum==CheckSum:
                                        print "trama ok"
                                        print str(ByteData)
                                        print str(ByteCheckSum)
                                        arr.insert(contador,ByteData)
                                        index+=1
                                        print str(index)
                                        contador+=1
                                        print str(contador)
        time.sleep(2)
print str(arr)
print len(arr)

