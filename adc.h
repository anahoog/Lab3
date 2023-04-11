#ifndef __ADC_H__
#define __ADC_H__

class ADC{

    private:
        static unsigned char * ADCSRA;
        static unsigned char * ADLAR;
        static unsigned char * ADCL;
        static unsigned char * ADCH;
        static unsigned char * ADCSRB;
        static const unsigned char REFS0 = 0;
        static const unsigned char REFS1 = 0;

        
    public:
        enum ref{
            aref_on = 0,
            aref_avcc = 1,
            reserved = 2,
            aref_in = 3
        };

        enum channel_in{
            adc0,
            adc1,
            adc2,
            adc3,
            adc4,
            adc5,
            adc6,
            adc7,
            adc8
        };
    
    ADC(int channel, ref reft);
    
    ~ADC();

    void start();

    void stop ();

    bool get();

    char sample_v (float v);
    
    char sample (int a);


        
};

#endif
