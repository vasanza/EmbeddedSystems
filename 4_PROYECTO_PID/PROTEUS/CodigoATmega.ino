#include <Arduino_FreeRTOS.h>

TaskHandle_t TaskEnviar_Handler;

int min_max_delay_ms[] = {500,1000};
int delay_cnt = 10;// Ancho de banda [2Hz - 1KHz]

int s=0;
float G=0;
float num=0;
float den=1;

long delay_sample=100;//ms

void led( void *pvParameters );
void enviar( void *pvParameters );
void RPM( void *pvParameters );

int incomingByte;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(5, OUTPUT);//pwm
  xTaskCreate(
    led
    ,  "BlinkLed"        // Nombre descriptivo de la función (MAX 8 caracteres)
    ,  128               // Tamaño necesario en memoria STACK
    ,  NULL              // Parámetro INICIAL a recibir (void *)
    ,  0                 // Prioridad, priridad = 3 (configMAX_PRIORITIES - 1) es la mayor, prioridad = 0 es la menor.
    ,  NULL );           // Variable que apunta al task (opcional)

  xTaskCreate(
    enviar
    ,  "envioIOT"       // Nombre descriptivo de la función (MAX 8 caracteres)
    ,  128              // Tamaño necesario en memoria STACK
    ,  NULL             // Parámetro INICIAL a recibir (void *)
    ,  0                // Prioridad, priridad = 3 (configMAX_PRIORITIES - 1) es la mayor, prioridad = 0 es la menor.
    ,  &TaskEnviar_Handler); // Variable que apunta al task (opcional)

 xTaskCreate(
    RPM
    ,  "RPM"         // Nombre descriptivo de la función (MAX 8 caracteres)
    ,  128               // Tamaño necesario en memoria STACK
    ,  NULL              // Parámetro INICIAL a recibir (void *)
    ,  0                 // Prioridad, priridad = 3 (configMAX_PRIORITIES - 1) es la mayor, prioridad = 0 es la menor.
    ,  NULL); // Variable que apunta al task (opcional)

  vTaskSuspend(TaskEnviar_Handler);
}

void loop() {
}

void led( void *pvParameters ){
  while(1){
       if (Serial.available() > 0) {
	    // read the incoming byte:
	    //Serial.readBytes(incomingByte,1);
	    //incomingByte=Serial.parseInt();
	    incomingByte=Serial.read();//<----------------
	    vTaskDelay(1/ portTICK_PERIOD_MS);
	    analogWrite(5, incomingByte);
	 }
  }
}

void enviar( void *pvParameters ){
  for(;;){       
	vTaskDelay(1/ portTICK_PERIOD_MS);
        //Serial.println(String(s));//<----------------------ASCII
	Serial.write(s);//<---- Byte
        vTaskSuspend(TaskEnviar_Handler);
  }
}

void RPM( void *pvParameters ){
  while(1){
      s=analogRead(A0)>>2;
     // vTaskDelay(1/ portTICK_PERIOD_MS);
      //analogWrite(5, s);
      vTaskDelay(1/ portTICK_PERIOD_MS);
      s=s;//*10/255;
	 
      vTaskResume(TaskEnviar_Handler);
      vTaskDelay(delay_sample/ portTICK_PERIOD_MS);
      //quiero 10 datos por estado -> 10 segundos de periodo de senal cuadrada en al entrada
  }
}