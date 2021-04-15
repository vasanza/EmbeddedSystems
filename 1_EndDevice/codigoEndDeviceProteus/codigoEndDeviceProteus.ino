#include <Arduino_FreeRTOS.h>

TaskHandle_t TaskLed_Handler;

//variables globales
int led = 13;
int led_pwm=11;
long int ADCsensor = 0;
int Datos1[240]={};//4 horas de datos
int index=0;
int estado =0;
int RXTrama[5];
int TramaS[5] ={0x24,0x31,0x41,0x00,0x54};//sensor
int TramaA[5] ={0x24,0x31,0x42,0x00,0x57};//actuador
int IdCoordinador =0x36;//'6'
// Sensor AD-0
//24 31 41 00 54
// Actuador PWM-11
//24 31 42 FF A8
//24 31 42 7F 28
//24 31 42 00 57

// End Device
void TaskBlink( void *pvParameters );
void TaskRxTrama( void *pvParameters );
void TaskAnalogRead( void *pvParameters );// Sensor


void setup() {
  pinMode(A0, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led_pwm, OUTPUT);
  Serial.begin(9600);
  xTaskCreate(
    TaskBlink
    ,  "Blink"   // A name just for humans
    , 128  // Stack size
    , NULL
    , 0  // priority
    , &TaskLed_Handler); // Variable que apunta al task (opcional)
    
  xTaskCreate(
    TaskRxTrama
    , "Blink"   // A name just for humans
    , 128  // Stack size
    , NULL
    ,1  // priority
    , NULL );
  
  xTaskCreate(
    TaskAnalogRead
    ,  "AnalogRead"
    ,  128 // This stack size can be checked & adjusted by reading Highwater
    ,  NULL
    ,  3  // priority
    ,  NULL );

  vTaskSuspend(TaskLed_Handler);
}

void loop()
{
}
/*---------------------- Tasks ---------------------*/
void TaskBlink(void *pvParameters)  // This is a task.
{
  for (;;){
      digitalWrite(led, HIGH);
      vTaskDelay( 500 / portTICK_PERIOD_MS );
      digitalWrite(led, LOW);
      vTaskDelay( 500 / portTICK_PERIOD_MS );
      vTaskSuspend(TaskLed_Handler);
  }
}

void TaskRxTrama(void *pvParameters)  // This is a Main task.
{
  for (;;){
      if(Serial.available()){
        if(estado==0 and Serial.read () == 0x24){
          RXTrama[estado]=0x24;estado=1;
        }else if(estado>0){
          RXTrama[estado]=Serial.read ();
          estado+=1;
          if(estado>4){
            estado=0;
            if(RXTrama[0]==TramaS[0] and RXTrama[1]==TramaS[1] and RXTrama[2]==TramaS[2] and RXTrama[3]==TramaS[3]and RXTrama[4]==TramaS[4]){
               //Serial.println("Valores en sensor "+String(index));
         Serial.println(String(index));
               //Enviar todos los datos almacenados usando la trama de envio al coordinador*******
                for(int k=0;k<index;k+=1){
                  //vTaskDelay( 500 / portTICK_PERIOD_MS );
                  Serial.write(0x24);
                  Serial.write(0x36);
                  Serial.write(0x41);                  
                  Serial.print(Datos1[k]);
                  Serial.write(0x53 ^ int(Datos1[k]));
                  Serial.println();
                }
                index=0;//<----------------------------------
                //vTaskResume(TaskLed_Handler);
                //vTaskDelay( 2000 / portTICK_PERIOD_MS );
            }
            if(RXTrama[0]==TramaA[0] and RXTrama[1]==TramaA[1] and RXTrama[2]==TramaA[2]){
              if(RXTrama[4] == (((RXTrama[0] ^ RXTrama[1]) ^ RXTrama[2]) ^ RXTrama[3])){
                //Serial.println("Valor PWM en salida");
                analogWrite(led_pwm,RXTrama[3]);//PWM output
                //vTaskResume(TaskLed_Handler);
                //vTaskDelay( 2000 / portTICK_PERIOD_MS );
              }
            }
          }
        }
     }
  }
}

void TaskAnalogRead(void *pvParameters)  // This is a Main task.
{
  for (;;){
      ADCsensor=0;
      for(int j=0;j<15;j++){//durante 60 datos en 1min
        ADCsensor += analogRead(A0)*9/1023;// [0 - 9]
        vTaskDelay( 1000 / portTICK_PERIOD_MS );//cada 1 segundo
      }
      ADCsensor /= 15;//60
      Datos1[index]=ADCsensor;index+=1;
  }
}
