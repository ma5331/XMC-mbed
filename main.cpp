#include "mbed.h"

//DigitalOut led1(LED1);
//DigitalOut led2(LED2);
//
//DigitalIn button1(BUTTON1);
//DigitalIn button2(BUTTON2);
//
//int main() {
//    while(1) {
//    	led1 = !button1;
//    	led2 = !button2;
//    }
//}

//BusOut leds(LED1, LED2);
//BusIn buttons(BUTTON1, BUTTON2);
//
//int main()
//{
//	while (1)
//	{
//		leds = ~buttons;
//	}
//}

//DigitalInOut button1(BUTTON1);
//DigitalInOut led1(LED1);
//
//int main()
//{
//	button1.input();
//	led1.output();
//
//	while (1)
//	{
//		led1 = !button1;
//	}
//}

//AnalogIn test(p15_3);
//DigitalOut led1(LED1);
//DigitalOut led2(LED2);
//
//int main()
//{
//	while(1)
//	{
//		float val = test;
//
//		if (val > 0.67)
//		{
//			led1 = 1;
//			led2 = 1;
//		}
//		else if (val > 0.33)
//		{
//			led1 = 1;
//			led2 = 0;
//		}
//		else
//		{
//			led1 = 0;
//			led2 = 0;
//		}
//	}
//}

// AnalogOut tri(p14_8);
// AnalogOut tri_inv(p14_9);
//
// AnalogIn test(p15_3);
// DigitalOut led1(LED1);
// DigitalOut led2(LED2);
//
// int main() {
//     while(1) {
//         tri = tri + 0.01;
//         wait_us(1);
//         if(tri >= 0.99) {
//             tri = 0;
//         }
//
//         tri_inv = 1-tri;
//
//		float val = test;
//
//		if (val > 0.67)
//		{
//			led1 = 1;
//			led2 = 1;
//		}
//		else if (val > 0.33)
//		{
//			led1 = 1;
//			led2 = 0;
//		}
//		else
//		{
//			led1 = 0;
//			led2 = 0;
//		}
//     }
// }
//

//PwmOut led(LED1);
//AnalogIn Ain(p15_3);
//
// int main() {
//
//     while(1)
//     {
//    	 led.period(Ain/10+0.01);
//    	 led=0.5;
//    	//wait(0.5);
//     }
// }

//Serial pc(p5_1, p1_5);
//
//int main()
//{
//	pc.printf("Hello XMC2Go!\r\n");
//
//	while(1)
//	{
//		uint8_t i;
//
//		pc.scanf("%d", &i);
//		pc.printf("Byte %d received!\r\n", i);
//	}
//}

//RawSerial pc(p5_1, p1_5, 112500);
//
//void test()
//{
//	uint8_t c = pc.getc();
//
//	pc.send_break();
//}
//
//int main()
//{
//	pc.putc(0xAA);
//
//	pc.attach(&test, SerialBase::RxIrq);
//
//	while(1)
//	{
//
//	}
//}

//Serial pc(p5_1, p1_5, 112500);
//
//event_callback_t TxCallback;
//event_callback_t RxCallback;
//
//uint16_t RxBuffer[3];
//
//void TxHandler(int events)
//{
//	static uint8_t test = 0;
//
//	test ++;
//}
//
//void RxHandler(int events)
//{
//	static uint8_t test2=0;
//
//	test2++;
//}
//
//int main()
//{
//	uint16_t buffer[] = {0xaabb, 0xccdd, 0xeeff};
//
//	TxCallback = TxHandler;
//	RxCallback = RxHandler;
//
//	//pc.write(buffer, 3, TxCallback);
//	pc.read(RxBuffer, 3, RxCallback);
//
//	while(1)
//	{
//
//	}
//}

#include "TextLCD.h"

DigitalOut RW(p0_3, 0);
TextLCD LCD(p0_2, p0_4, p1_9, p1_10, p1_11, p1_12, TextLCD::LCD20x4);

DigitalIn Enable(p1_4);

AnalogIn ADC1(p14_1);
AnalogIn ADC2(p14_2);
AnalogIn ADC3(p14_3);
AnalogIn ADC4(p14_4);
AnalogIn MODUL(p14_5);

PwmOut PWM1(p1_3);
PwmOut PWM2(p1_2);
PwmOut PWM3(p1_1);
PwmOut PWM4(p1_0);

Timer RefreshLCD;

void printHeader(uint8_t module_nr, uint8_t enable)
{
	uint16_t wl_1, wl_2;

	switch (module_nr)
	{
		case 1:
			wl_1 = 295;
			wl_2 = 310;
			break;
		case 2:
			wl_1 = 285;
			wl_2 = 365;
			break;
		case 3:
			wl_1 = 340;
			wl_2 = 375;
			break;
	}

	LCD.locate(9,0);
	if (enable)
		LCD.printf("MODUL %d On ", module_nr);
	else
		LCD.printf("MODUL %d Off", module_nr);
	LCD.locate(0,1);
	LCD.printf(" VIS  %d  %d  VIS ", wl_1, wl_2);
}

void printData(uint8_t duty1, uint8_t duty2, uint8_t duty3, uint8_t duty4)
{
	LCD.locate(0, 3);
	LCD.printf(" %03d  %03d  %03d  %03d ", duty1, duty2, duty3, duty4);
}

int main()
{
	float adc1=0;
	float adc2=0;
	float adc3=0;
	float adc4=0;

	Enable.mode(PullUp);

	PWM1.pulsewidth_ms(1);
	PWM2.pulsewidth_ms(1);
	PWM3.pulsewidth_ms(1);
	PWM4.pulsewidth_ms(1);

	LCD.cls();
	RefreshLCD.start();

	while(1)
	{
		uint8_t enable = !Enable;

		adc1 += (0.01)*(ADC1 - adc1);
		adc2 += (0.01)*(ADC2 - adc2);
		adc3 += (0.01)*(ADC3 - adc3);
		adc4 += (0.01)*(ADC4 - adc4);

		int duty1 = (int)(adc1*100);
		int duty2 = (int)(adc2*100);
		int duty3 = (int)(adc3*100);
		int duty4 = (int)(adc4*100);

		uint8_t mod;

		if (MODUL < 0.33)
			mod = 1;
		else if(MODUL < 0.67)
			mod = 2;
		else
			mod = 3;

		if (enable)
		{
			if (duty1 > 1)
				PWM1.write(duty1/100.0);
			else
				PWM1.write(0);
			if (duty2 > 1)
				PWM2.write(duty2/100.0);
			else
				PWM2.write(0);
			if (duty3 > 1)
				PWM3.write(duty3/100.0);
			else
				PWM3.write(0);
			if (duty4 > 1)
				PWM4.write(duty4/100.0);
			else
				PWM4.write(0);
		}
		else
		{
			PWM1.write(0);
			PWM2.write(0);
			PWM3.write(0);
			PWM4.write(0);
		}

		if (RefreshLCD.read_ms() > 10)
		{
			printHeader(mod, enable);
			printData(duty1, duty2, duty3, duty4);
			RefreshLCD.reset();
		}
	}
}

//Timer timer;
//DigitalOut led(LED1);
//int begin, end;
//
//int main()
//{
//	timer.start();
//	begin = timer.read_us();
//	led = !led;
//	end = timer.read_us();
//
//	printf("Toggle the led takes %d us", end - begin);
//
//	while(1)
//	{
//
//	}
//}

//Ticker timer;
//DigitalOut led1(LED1);
//
//
//void attime()
//{
//	led1=!led1;
//}
//
//int main()
//{
//	//timer.attach(&attime, 0.001);
//	timer.attach_us(&attime, 1000);
//
//	while(1)
//	{
//
//	}
//}

//Timeout start;
//Ticker timer1;
//Ticker timer2;
//DigitalOut led(LED1);
//
//
//void on()
//{
//	led=1;
//}
//
//void off()
//{
//	led=0;
//}
//
//void attimeout()
//{
//	timer2.attach(off, 0.5);
//}
//
//int main()
//{
//	led=1;
//	start.attach(&attimeout, 0.25);
//	timer1.attach(on, 0.5);
//
//	while(1)
//	{
////		led = !led;
////		wait(0.2);
//	}
//}

//#include "MPU9250.h"
//
//MPU9250 mpu(p5_0, p5_2);
//
//char tx[] = {0x3b};
//char rx[] = {0,0,0,0,0,0};
//
//void i2c_callback(int event)
//{
//	printf("%d %d %d %d %d %d", rx[0],rx[1],rx[2],rx[3],rx[4],rx[5]);
//}
//
//int main()
//{
//	int16_t acc[3] = {0};
//	float dest[3];
////	char data[20] = {0};
////	char test = 52;
////
//	mpu.initMPU9250();
//	mpu.initAK8963(dest);
//
//	mpu.readAccelData(acc);
////	mpu.i2c_->write(0x68<<1, &test, 1, 1);
////	mpu.i2c_->read(0x68<<1, (char*)data, 20, 0);
////
////	mpu.i2c_->start();
////	mpu.i2c_->write(0xd0);
////	mpu.i2c_->write(0x3b);
////	mpu.i2c_->stop();
////	mpu.i2c_->start();
////	mpu.i2c_->write(0xd1);
////	uint8_t hb = mpu.i2c_->read(1);
////	uint8_t lb = mpu.i2c_->read(0);
////	mpu.i2c_->stop();
//
//
//
//	mpu.i2c_->transfer(0xd0, tx, sizeof(tx), rx, sizeof(rx), i2c_callback);
//
//	while(1)
//	{
//
//	}
//}

//#include "MPU9150.h"
//#include "Quaternion.h"
//
//MPU9150 imu(p5_2, p5_0, p0_5);
//
//DigitalOut led(LED1);
//
//char buffer[200];
//
//int main(){
//
//    imu.initialiseDMP();
//
//    Timer timer;
//    timer.start();
//
//    imu.setFifoReset(true);
//    imu.setDMPEnabled(true);
//
//    Quaternion q1;
//    Vector3 angles;
//
//    while(true){
//
//        if(imu.getFifoCount() >= 48){
//            imu.getFifoBuffer(buffer,  48);
//            led = !led;
//        }
//
//        if(timer.read_ms() > 50){
//            timer.reset();
//
//           //This is the format of the data in the fifo,
//           /* ================================================================================================ *
//             | Default MotionApps v4.1 48-byte FIFO packet structure:                                           |
//             |                                                                                                  |
//             | [QUAT W][      ][QUAT X][      ][QUAT Y][      ][QUAT Z][      ][GYRO X][      ][GYRO Y][      ] |
//             |   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  |
//             |                                                                                                  |
//             | [GYRO Z][      ][MAG X ][MAG Y ][MAG Z ][ACC X ][      ][ACC Y ][      ][ACC Z ][      ][      ] |
//             |  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40  41  42  43  44  45  46  47  |
//             * ================================================================================================ */
//
//            /*
//            debug.printf("%d, %d, %d\r\n",  (int32_t)(((int32_t)buffer[34] << 24) + ((int32_t)buffer[35] << 16) + ((int32_t)buffer[36] << 8) + (int32_t)buffer[37]),
//                                            (int32_t)(((int32_t)buffer[38] << 24) + ((int32_t)buffer[39] << 16) + ((int32_t)buffer[40] << 8) + (int32_t)buffer[41]),
//                                            (int32_t)(((int32_t)buffer[42] << 24) + ((int32_t)buffer[43] << 16) + ((int32_t)buffer[44] << 8) + (int32_t)buffer[45]));
//
//            debug.printf("%d, %d, %d\r\n",  (int32_t)(((int32_t)buffer[16] << 24) + ((int32_t)buffer[17] << 16) + ((int32_t)buffer[18] << 8) + (int32_t)buffer[19]),
//                                            (int32_t)(((int32_t)buffer[20] << 24) + ((int32_t)buffer[21] << 16) + ((int32_t)buffer[22] << 8) + (int32_t)buffer[23]),
//                                            (int32_t)(((int32_t)buffer[24] << 24) + ((int32_t)buffer[25] << 16) + ((int32_t)buffer[26] << 8) + (int32_t)buffer[27]));
//
//            debug.printf("%d, %d, %d\r\n",  (int16_t)(buffer[29] << 8) + buffer[28],
//                                            (int16_t)(buffer[31] << 8) + buffer[30],
//                                            (int16_t)(buffer[33] << 8) + buffer[32]);
//
//            debug.printf("%f, %f, %f, %f\r\n",
//                (float)((((int32_t)buffer[0] << 24) + ((int32_t)buffer[1] << 16) + ((int32_t)buffer[2] << 8) + buffer[3]))* (1.0 / (1<<30)),
//                (float)((((int32_t)buffer[4] << 24) + ((int32_t)buffer[5] << 16) + ((int32_t)buffer[6] << 8) + buffer[7]))* (1.0 / (1<<30)),
//                (float)((((int32_t)buffer[8] << 24) + ((int32_t)buffer[9] << 16) + ((int32_t)buffer[10] << 8) + buffer[11]))* (1.0 / (1<<30)),
//                (float)((((int32_t)buffer[12] << 24) + ((int32_t)buffer[13] << 16) + ((int32_t)buffer[14] << 8) + buffer[15]))* (1.0 / (1<<30)));
//            */
//
//            q1.decode(buffer);
//            angles = q1.getEulerAngles();
//
//            //TeaPot Demo Packet for MotionFit SDK
//            /*
//            debug.putc('$'); //packet start
//            debug.putc((char)2); //assume packet type constant
//            debug.putc((char)0); //count seems unused
//            for(int i = 0; i < 16; i++){ //16 bytes for 4 32bit floats
//                debug.putc((char)(buffer[i]));
//            }
//            for(int i = 0; i < 5; i++){ //no idea, padded with 0
//                debug.putc((char)0);
//            }
//            */
//        }
//    }
//}
