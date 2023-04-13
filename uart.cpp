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
        
fifo <char, 10> UART::buffer;


long frequencia = 16e6;


extern "C"{
    void __vector_18() __attribute__((signal)); //vector 19
    void __vector_19() __attribute__((signal));
}

void __vector_18(){ //uso futuro
    //GPIO::int0_handler();
}
void __vector_19(){
    UART::tratar_int();
}


UART::UART(long u) {

    int ubrr = u;
    ubrr = (frequencia/(16*(u)))-1;

    *UBRR0H = (unsigned char)(ubrr >> 8);
    *UBRR0L = (unsigned char) ubrr;
    *UCSRB = (1 << 4) | (1 << 3);
    *UCSRC = (3 << 1);

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
void UART::put(const char c){
    buffer.enfileira_uart(c);
    * UCSRB |= 1 << 5;
}

void UART::tratar_int(){
    if(!buffer.vazia()){
        * UDR = buffer.desenfileira();
    }else{
        * UCSRB &= ~(1<<5);
    }

}
//tirar da fila e colocar no udr

char UART::get_s(){
    while (!(* UCSRA & (1 << 7)));
    return *UDR;
}
