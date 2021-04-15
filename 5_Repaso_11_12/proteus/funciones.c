
#include "funciones.h"

void recibir_encender_led(){
 if(is_data_ready()){
	if (get_RX_buffer()[0]=='H' && get_RX_buffer()[1]==0){

	 serial_println_str("encendido");
	PORTB =  (1<<PB0);
	 }else{

           serial_println_str("apagado");
	 PORTB &= ~(1<<PB0); 
}}}

void recibirint(){
 if(is_data_ready()){
	 //serial_println_str(get_RX_buffer());
	 recibido = get_RX_buffer();
	serial_println_str(recibido);
	 arreglocreadoint(recibido);
	if (array_numint[0]==1){
	PORTB =  (1<<PB0);
	 }

	 else{
	 PORTB &= ~(1<<PB0); 
} } }


void recibirfloat(){
 if(is_data_ready()){
	 //serial_println_str(get_RX_buffer());
	 
	 recibido = get_RX_buffer();
	serial_println_str(recibido);
	 
	 arreglocreadofloat(recibido);
	 float hj = array_numfloat[0];
	 //PORTB = array_numint[0];
	if (hj>1.2 ){
	PORTB = (1<<PB0); ;
	 }

	 else{
	 PORTB &= ~(1<<PB0); 
} } }


void arreglocreadoint(char* reci){
    char *token1 = strtok(reci, ","); 
    int i = 0;
    // Keep printing tokens while one of the 
    // delimiters present in str[]. 
    while (token1 != NULL) 
    { 
       // printf("%s\n", token);
         array_numint[i] =atoi(token1);
	 token1 = strtok(NULL, ",");
	 i++;
    } 
  
}

void arreglocreadofloat(char* reci){

    char *token = strtok(reci, ","); 
    int i = 0;
    // Keep printing tokens while one of the 
    // delimiters present in str[]. 
    while (token != NULL) 
    { 
       // printf("%s\n", token);
         array_numfloat[i] =atof(token);
	 token = strtok(NULL, ",");
	 i++;
    }
}
