#include <stdio.h>
#include <stdlib.h>
#include "fifo.h"
#include "uart.h"

volatile unsigned char * UART::UBRR0H = (unsigned char *) 0xC5;
volatile unsigned char * UART::UBRR0L = (unsigned char *) 0xC4;
volatile unsigned char * UART::UCSRA = (unsigned char *) 0xC0;
volatile unsigned char * UART::UCSRB = (unsigned char *) 0xC1;
volatile unsigned char * UART::UCSRC = (unsigned char *) 0xC2;
volatile unsigned char * UART::UDR = (unsigned char *) 0xC6;

long frequencia = 16e6;


UART::UART(long u){

    fifo fila(5); 
    int ubrr = u;
    ubrr = (frequencia/(16*(u)))-1;

    *UBRR0H = (unsigned char)(ubrr >> 8);
    *UBRR0L = (unsigned char) ubrr;
    *UCSRB = (1 << 4) | (1 << 3);
    *UCSRC = (3 << 1);

 /*   int x = (frequencia/(16*(u)))-1;
    char str[16];
    sprintf(str, "%d\n", x);
    puts_s(str);
    //printf("%d\n", ubrr);
    */
}
void UART::puts_s(const char *c){
    while (*c != '\0')
        put_s(*c++);
}

UART::~UART(){

}

void UART::put_s(const char c){
    while (!(* UCSRA & ( 1<< 5)));
    * UDR = c;
}


char UART::get_s(){
    while (!(* UCSRA & (1 << 7)));
    return *UDR;
}

//void UART::getLine(){
 //  char c;

    // do {
    //     c = UART::get_s();
    //     buffer
    // }
    // while((bufIdx < buffer.) && (c != '\r'));

    //buffer[bufIdx] = 0;
//}