/*****************************************************
Project : Indikator
Version : 1.0 
Date    : 25.10.2009
Author  : Denis Chupilko
Company : AH-064
Comments: MK #2

Chip type               : ATtiny2313
AVR Core Clock frequency: 8,000000 MHz
Memory model            : Tiny
External RAM size       : 0
Data Stack size         : 32
*****************************************************/

#include <tiny2313.h>
#include <delay.h>

// Declare your global variables here
int q = 0, w = 0;
int _1j = 3, _1i = 3;
int _2j = 2, _2i = 3;
int _3j = 3, _3i = 6;
int _4j = 5, _4i = 1;
const int delay = 1250;

unsigned char _number[11] = {
    0x3F,   //0   00111111
    0x06,   //1   00000110  
    0x5B,   //2   01011011
    0x4F,   //3   01001111
    0x66,   //4   01100110
	0x6D,   //5   01101101
	0x7D,   //6   01111101
    0x07,   //7   00000111
    0x7F,   //8   01111111
    0x6F,   //9   01101111
    0x00    //blank
};

void main(void)
{
{// Declare your local variables here

// Crystal Oscillator division factor: 1
#pragma optsize-
CLKPR=0x80;
CLKPR=0x00;
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

// Input/Output Ports initialization
// Port A initialization
// Func2=In Func1=Out Func0=In 
// State2=T State1=0 State0=T 
PORTA=0x00;
DDRA=0x02;

// Port B initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0 
PORTB=0x00;
DDRB=0xFF;

// Port D initialization
// Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0 
PORTD=0x00;
DDRD=0x7F;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=FFh
// OC0A output: Disconnected
// OC0B output: Disconnected
TCCR0A=0x00;
TCCR0B=0x00;
TCNT0=0x00;
OCR0A=0x00;
OCR0B=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=FFFFh
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// Interrupt on any change on pins PCINT0-7: Off
GIMSK=0x00;
MCUCR=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x00;

// Universal Serial Interface initialization
// Mode: Disabled
// Clock source: Register & Counter=no clk.
// USI Counter Overflow Interrupt: Off
USICR=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;}

while (1)
{
    for (q=0; q<100; ++q)
    {
        // Светофор 1
        PORTD = ~_number[_1j];
        PORTB.0 = 1;
        delay_us(delay);
        PORTB.0 = 0;
        PORTD = ~_number[_1i];
        PORTB.1 = 1;
        delay_us(delay);
        PORTB.1 = 0;  
                    
        // Светофор 2
        PORTD = ~_number[_2j];
        PORTB.2 = 1;
        delay_us(delay);
        PORTB.2 = 0;
        PORTD = ~_number[_2i];
        PORTB.3 = 1;
        delay_us(delay);
        PORTB.3 = 0;
                        
        // Светофор 3
        PORTD = ~_number[_3j];
        PORTB.4 = 1;
        delay_us(delay);
        PORTB.4 = 0;
        PORTD = ~_number[_3i];
        PORTB.5 = 1;
        delay_us(delay);
        PORTB.5 = 0;
                
        // Светофор 4
        PORTD = ~_number[_4j];
        PORTB.6 = 1;
        delay_us(delay);
        PORTB.6 = 0;
        PORTD = ~_number[_4i];
        PORTB.7 = 1;
        delay_us(delay);
        PORTB.7 = 0;  
    }
        
    // Установка времени для следующей итерации
    if (w == 0)
    {
        if (_1i == 1 && _1j == 10)
            { _1j=3; _1i=6; }
        if (_2i == 1 && _2j == 10)
            { _2j=4; _2i=6; }
        if (_3i == 1 && _3j == 10)
            { _3j=3; _3i=0; }
        if (_4i == 1 && _4j == 10)
            { _4j=1; _4i=5; w = 1; }
    }
    
    else
    {
        if (_1i == 1 && _1j == 10)
            { _1j=3; _1i=4; w = 0; }
        if (_2i == 1 && _2j == 10)
            { _2j=2; _2i=4; }
        if (_3i == 1 && _3j == 10)
            { _3j=4; _3i=0; }
        if (_4i == 1 && _4j == 10)
            { _4j=5; _4i=5; }
    }
        
    if (_1i == 0)
    {
        _1i = 9;
        --_1j;
    }
    else
        --_1i;

    if (_1j == 0)
        _1j = 10;  
            
    if (_2i == 0)
    {
        _2i = 9;
        --_2j;
    }
    else
        --_2i;
        
    if (_2j == 0)
        _2j = 10;
            
    if (_3i == 0)
    {
        _3i = 9;
        --_3j;
    }
    else
        --_3i;

    if (_3j == 0)
        _3j = 10;
            
    if (_4i == 0)
    {
        _4i = 9;
        --_4j;
    }
    else
        --_4i;
        
    if (_4j == 0)
        _4j = 10;        
};
}
