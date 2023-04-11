#include "gpio_pin.h"
#include "uart.h"

enum State_t{
    OFF = 0,
    W1,
    ON,
    W2
};

UART uart(19200);

volatile State_t state = OFF;
bool botao;
static bool led_state = 1;

void trata_botao(){
    uart.put_s('i');
    botao =1;
}


GPIO led(5, GPIO::OUTPUT);
//GPIO bot(2, GPIO::INPUT_PULLUP);
GPIO bot(2, GPIO::INTERRUPT_FALLING, trata_botao);

//GPIO botao_up(3, GPIO::INPUT_PULLUP);


static unsigned char * EICRA;
static unsigned char * EIMSK;

void setup(){
    //setar sensibilidade da INT0 para Rising edge (0b11 = 0x03)
    //habilitar INT0 (0x01)
   // *EICRA &= ~0x03;
   // *EICRA |= 0x02;
   // *EICRA = (*EICRA & ~0x03) | 0x02;
    //*EIMSK |= 0x01;
    __asm__ ("sei");
}

void delay(unsigned int times){
    while (times--){
        unsigned int x = 0xffff;
        while(x--);
    }
}

void loop(){

    //delay(10);
    uart.put_s(uart.get_s());
    //uart.put_s(uart.getLine());
    switch (state)   {
        case OFF:
            if(botao == 1){
                led.set();
                state = W1;
            }
            break;

        case W1:
            delay(10);
            botao = 0;
            state = ON;
            break;

        case W2:
            delay(10);
            botao = 0;
            state = OFF;
            break;
 
        case ON:
            if(botao == 1){
                led.clear();
                state = W2;
            }
            break;

        default:
            break;
        }
}

int main(){
   setup();
    while(true) loop();
}
