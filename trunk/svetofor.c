/*****************************************************
Project : Svetofor
Version : 1.0 
Date    : 25.10.2009
Author  : Denis Chupilko
Company : AH-064
Comments: MK #1

Chip type               : ATtiny2313
AVR Core Clock frequency: 8,000000 MHz
Memory model            : Tiny
External RAM size       : 0
Data Stack size         : 32
*****************************************************/

#include <tiny2313.h>
#include <delay.h>

// Declare your global variables here
const int _count = 3;
const int _delay = 500;
const int on = 0, off = 1, blink = 2;
int q;

void delay_s(int i)
{
delay_ms(i*1000);
}
   
void _1_5_red(int i)
{
    if (i==0)
        PORTB.0 = 1;
    else if (i==1)
        PORTB.0 = 0;
}

void _1_5_green(int i)
{
    if (i==0)
        PORTB.2 = 1;
    else if (i==1)
        PORTB.2 = 0;
    else if (i==2)
    {
        for (q = 0; q<_count; ++q)
        {
            PORTB.2 = 0;
            delay_ms(_delay);
            PORTB.2 = 1;
            delay_ms(_delay);
        }
        PORTB.2 = 0;
        PORTB.1 = 1;
        delay_ms(_delay*2);
        PORTD.1 = 1;
        delay_ms(_delay*4);
        PORTD.1 = 0;
        PORTB.1 = 0;
    }
}

void _2_6_red(int i)
{
    if (i==0)
        PORTB.3 = 1;
    else if (i==1)
        PORTB.3 = 0;
}

void _2_6_green(int i)
{
    if (i==0)
        PORTB.5 = 1;
    else if (i==1)
        PORTB.5 = 0;
    else if (i==2)
    {
        for (q = 0; q<_count; ++q)
        {
            PORTB.5 = 0;
            delay_ms(_delay);
            PORTB.5 = 1;
            delay_ms(_delay);
        }
        PORTB.5 = 0;    
        PORTB.4 = 1;
        delay_ms(_delay*6);
        PORTB.4 = 0;
    }
}

void _3_7_red(int i)
{
    if (i==0)
        PORTD.0 = 1;
    else if (i==1)
        PORTD.0 = 0;
}

void _3_7_green(int i)
{
    if (i==0)
        PORTD.2 = 1;
    else if (i==1)
        PORTD.2 = 0;
    else if (i==2)
    {
        for (q = 0; q<_count; ++q)
        {
            PORTD.2 = 0;
            PORTD.5 = 0;
            delay_ms(_delay);
            PORTD.2 = 1;
            PORTD.5 = 1;
            delay_ms(_delay);
        }
        PORTD.2 = 0;
        PORTD.5 = 0;    
        PORTD.1 = 1;
        PORTD.4 = 1;
        delay_ms(_delay*2);
        PORTB.1 = 1;
        PORTB.4 = 1;
        delay_ms(_delay*4);
        PORTD.1 = 0;
        PORTD.4 = 0;
        PORTB.1 = 0;
        PORTB.4 = 0;
    }
}

void _3_arrow(int i)
{
    if (i==0)
        PORTD.6 = 1;
    else if (i==2)
    {
        for (q = 0; q<_count; ++q)
        {
            PORTD.6 = 0;
            delay_ms(_delay);
            PORTD.6 = 1;
            delay_ms(_delay);
        }
        PORTD.6 = 0;    
        PORTD.4 = 1;
        delay_ms(_delay*6);
        PORTD.4 = 0;
    }
}

void _4_8_red(int i)
{
    if (i==0)
        PORTD.3 = 1;
    else if (i==1)
        PORTD.3 = 0;
}

void _4_8_green(int i)
{
    if (i==0)
        PORTD.5 = 1;
    else if (i==1)
        PORTD.5 = 0;
}

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
// Func2=In Func1=In Func0=Out 
// State2=T State1=P State0=1 
PORTA=0x03;
DDRA=0x01;

// Port B initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=1 State6=1 State5=1 State4=1 State3=1 State2=1 State1=1 State0=1 
PORTB=0x00;
DDRB=0xFF;

// Port D initialization
// Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State6=1 State5=1 State4=1 State3=1 State2=1 State1=1 State0=1 
PORTD=0x00;
DDRD=0x7F;

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
ACSR=0x80;
}

while (1)
{
    // 1. Движение по Шевченко
    // Зажигаем красный на 3, 4, 7 и 8
    _3_7_red(on);
    _4_8_red(on);
    // Зажигаем зелёный на 1, 2, 5 и 6
    _1_5_green(on);
    _2_6_green(on);
    // Задержка 20 сек
    delay_s(20);
    // Мигаем зелёным на 2 и 6 (6 сек)
    _2_6_green(blink);
    // Зажигаем красный на 2 и 6
    _2_6_red(on);
    
    // 2. Поворот с Шевченко налево
    // Задержка 4 сек
    delay_s(4);
    // Мигаем зелёными на 1 и 5 (6 сек)
    _1_5_green(blink);
    // Зажигаем красный на 1 и 5
    _1_5_red(on);
    // Тушим красный на 3 и 7
    _3_7_red(off);
    
    // 3. Движение по Гагарина в сторону киностудии и налево
    // Зажигаем зелёный на 3 и 7
    _3_7_green(on);
    // Зажигаем стрелку
    _3_arrow(on);
    // Задержка 9 сек
    delay_s(9);
    // Мигаем стрелкой (6 сек)
    _3_arrow(blink);
    // Тушим красный на 4 и 8
    _4_8_red(off);
    
    // 4. Движение по Гагарина в сторону Фонтана
    // Зажигаем зелёный на 4 и 8
    _4_8_green(on);
    // Задержка 11 сек
    delay_s(11);
    // Мигаем зелёными на 3, 4, 7 и 8 (6 сек)
    _3_7_green(blink);
    // Тушим красный на 1, 2, 5 и 6
    _1_5_red(off);
    _2_6_red(off);
};
}