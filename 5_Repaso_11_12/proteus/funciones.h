

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "uart.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>


char* recibido;
int numero;
void recibirint();
void recibirfloat();

static volatile int array_numint[5] = {0};
static volatile float array_numfloat[5] = {0};
void arreglocreadoint(char* reci);
void arreglocreadofloat(char* reci);
void recibir_encender_led();

float getfloat(int v);