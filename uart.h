#ifndef __UART_H__
#define __UART_H__

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
             
        UART( long u);
        ~UART(); 
        char get_s();
        //char getLine();
        void put_s(const char c);
        void puts_s(const char *c);
        



};
#endif