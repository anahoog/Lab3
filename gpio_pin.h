#ifndef __GPIO_PIN_H__
#define __GPIO_PIN_H__

class GPIO {
    private:

        typedef void (*HandlerFunction_t)(void);

        static unsigned char * PORTD;
        static unsigned char * DDRD;
        static unsigned char * PIND;

        static unsigned char * EICRA;
        static unsigned char * EIMSK;

        static unsigned char * PORTB;
        static unsigned char * DDRB;
        static unsigned char * PINB;

        unsigned char mask;

    public:
        static HandlerFunction_t int0_handler;
        static HandlerFunction_t int1_handler;

        enum GPIO_Direction_t
        {
            OUTPUT = 0,
            INPUT = 1,
            INPUT_PULLUP = 2,
            INTERRUPT_LOW = 3,
            INTERRUPT_CHANGE = 4,
            INTERRUPT_FALLING = 5,
            INTERRUPT_RISING = 6
        };

GPIO(int pin, GPIO_Direction_t dir, HandlerFunction_t func = 0);

~GPIO();

void set(bool state);

void set();

void clear ();

bool get();



};

#endif
