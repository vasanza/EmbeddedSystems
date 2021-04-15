#include "funciones.h"

int main()
 { 

pin_init();
serial_begin();
   while (1){
//recibir_encender_led();
serial_println_str("4,5,9");

_delay_ms(200);
}
   return 0;
 }