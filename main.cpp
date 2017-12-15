#include "mbed.h"

PwmOut led(LED1);

int main(void)
{
	led.period_us(1000);
	led.pulsewidth_us(50);

    while (1)
    {
    }
}
