#include "gpio_pin.h"

unsigned char * GPIO::PORTD = (unsigned char *)0x2B;
unsigned char * GPIO::DDRD = (unsigned char *) 0x2A;
unsigned char * GPIO::PIND = (unsigned char *) 0x29;

unsigned char * GPIO::EICRA = (unsigned char*) 0x69;
unsigned char * GPIO::EIMSK = (unsigned char*) 0x3D;

//unsigned char * GPIO::PORTB = (unsigned char *)0x25;
//unsigned char * GPIO::DDRB = (unsigned char *) 0x24;
//unsigned char * GPIO::PINB = (unsigned char *) 0x23;

GPIO::HandlerFunction_t GPIO::int0_handler = 0;
GPIO::HandlerFunction_t GPIO::int1_handler = 0;

extern "C"{
    void __vector_1() __attribute__((signal));
    void __vector_2() __attribute__((signal));
}

void __vector_1(){
    GPIO::int0_handler();
}
void __vector_2(){
    GPIO::int1_handler();
}

GPIO::GPIO (int pin, GPIO_Direction_t dir, HandlerFunction_t func){

    static unsigned char * MUCR = (unsigned char *) 0x55;

    mask = 1 << pin;                   
    if(dir == OUTPUT){
        *DDRD = *DDRD | mask;
    }
    else if (dir == INPUT){ 
        *DDRD = *DDRD & ~mask;
    }
    else if(dir == INPUT_PULLUP){
        *DDRD = *DDRD & ~mask; 
        *PORTD = *PORTD | mask;  
        *MUCR = *MUCR & 0xEF;
    }
    else{
        unsigned char sens = dir -3;
        *DDRD = *DDRD & ~mask;
        *PORTD = *PORTD | mask;  

        if(pin == 2 ) {
            int0_handler = func;
            *EICRA = (*EICRA & 0xfc) | sens;
            *EIMSK = *EIMSK | 0x01;

        }
        else if(pin == 3) {
            int1_handler = func;
            *EICRA = (*EICRA & 0xf3) | ( sens << 2);
            *EIMSK = *EIMSK | 0x02;
        }
    }
}

GPIO::~GPIO(){

}

//Set: escrever valor do pino para "state"
void GPIO::set(bool state){
    if(state) this->set();
    else this -> clear();
}

// escreve 1 no pino
void GPIO::set(){
    *PORTD = *PORTD | mask;
}

//escreve 0 no pino
void GPIO::clear (){
    *PORTD = *PORTD & ~mask; // 1101 1111
}

// ler e retorna o valor do pino
bool GPIO::get(){

    // pegar o valor PIND somente daquela posição & mask
    unsigned char x = *PIND;

    if((x & mask)>0){
        return true;
    }else{
        return false;
    }
}
