#include <Arduino_FreeRTOS.h>

TaskHandle_t TaskEnviar_Handler;

int LED_B0=8;
int LED_B1=9;
int LED_B2=10;
int LED_B3=11;

int min_max_delay_ms[] = {500,1000};
int delay_cnt = 10;// Ancho de banda [2Hz - 1KHz]

int delay_led = 250;
float Valor_RPM = 0;
float Valor_Hz=0;
int cnt=1;
float temp=0;
bool anterior=LOW;
int band=0;

void led( void *pvParameters );
void enviar( void *pvParameters );
void RPM( void *pvParameters );

void setup() {
  Serial.begin(9600);
  pinMode(LED_B1, OUTPUT);
  pinMode(LED_B2, OUTPUT);
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
    digitalWrite(LED_B1, HIGH);
    vTaskDelay(delay_led / portTICK_PERIOD_MS); //250 ms
    digitalWrite(LED_B1, LOW);
    vTaskDelay(delay_led / portTICK_PERIOD_MS); //250 ms
  }
}

void enviar( void *pvParameters ){
  for(;;){
    temp =cnt/delay_cnt;
  vTaskDelay(1/ portTICK_PERIOD_MS);//<--------------------------------------------------------------
  Valor_Hz=2*1000/temp;// Por que usamos dos flancos positivos
        vTaskDelay(1/ portTICK_PERIOD_MS);//<--------------------------------------------------------------
        Valor_RPM = 60*Valor_Hz;// Calculo para los 60Segundos

        vTaskDelay(1/ portTICK_PERIOD_MS);//<--------------------------------------------------------------
        Serial.println("Valor del cnt es: " + String(cnt ));
        vTaskDelay(1/ portTICK_PERIOD_MS);//<--------------------------------------------------------------
        Serial.println("Valor de frecuencia en Hz es: " + String(Valor_Hz));
        vTaskDelay(1/ portTICK_PERIOD_MS);//<--------------------------------------------------------------
        Serial.println("Valor de las RPM es: " + String(Valor_RPM ));

  band=0;
  cnt=0;
        vTaskSuspend(TaskEnviar_Handler);
  }
}

void RPM( void *pvParameters ){
  while(1){

      if(anterior == LOW && digitalRead(LED_B0)==HIGH ){
      band+=1;//cambia cuando existe un flanco positivo
   }
   anterior=digitalRead(LED_B0);
   
   if(band==1){//En el primer flanco positivo
      vTaskDelay(delay_cnt  / portTICK_PERIOD_MS);
      cnt+=1;
   }
   
   if(band==2){//En el segundo flanco positivo
      vTaskResume(TaskEnviar_Handler);
      vTaskDelay(500/ portTICK_PERIOD_MS);
   }
  }
}
