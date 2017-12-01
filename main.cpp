#include "mbed.h"

Serial pc(USBTX, USBRX);

void callback_rx(int events)
{
	static int pos = 0;

	pos++;
}

event_callback_t functionpointer;

int main()
{
	char buffer[] = "Hello World!";

	functionpointer=callback_rx;

	while (1)
	{
		if (pc.readable())
		{
			pc.getc();
			pc.write((uint8_t*)buffer, 12, functionpointer);
		}
	}
}
