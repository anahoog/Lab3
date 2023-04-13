#ifndef __UART_H__
#define __UART_H__
#include "fifo.h"

class UART
{
    private:
        static volatile unsigned char * UBRR0H;
        static volatile unsigned char * UBRR0L;
        static volatile unsigned char * UCSRA;
        static volatile unsigned char * UCSRB;
        static volatile unsigned char * UCSRC;
        static volatile unsigned char * UDR;
        

    public:
        static fifo <char, 10> buffer;
        UART( long u);
        ~UART(); 
        char get_s();
        void put(const char c);
        void put_s(const char c);
        void puts_s(const char *c);
        static void tratar_int();
        



};
#endif