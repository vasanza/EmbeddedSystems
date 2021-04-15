

#include "config.h"


void pin_init(){
DDRB = 0XFF; //PuertoB salida
 DDRC = 0b11; //Pines0y 1 del puerto C como salida
 PORTD |= (1<<PD2); //Activar resistencia de PULLUP en PIN2 l puerto D
}