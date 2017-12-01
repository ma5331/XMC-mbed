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
	char buffer[20] = {0};

	functionpointer=callback_rx;
	pc.read((uint16_t*)buffer, 10, functionpointer, SERIAL_EVENT_RX_CHARACTER_MATCH);

	while (1)
	{

	}
}
