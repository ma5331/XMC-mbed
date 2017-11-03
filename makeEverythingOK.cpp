#include "mbed.h"
#include "TextLCD.h"

#define ENABLE 1
#define DISABLE 0


DigitalOut buzzer(p1_13);
DigitalOut RW(p0_3);	// LCD
//DigitalIn Make_ok_btn(p2_1); 	//p2_1 = S2
DigitalIn Make_ok_btn(p0_1, PullUp); 	//p0_1 = BUTTON
char roll_txt[] = "                        If everything is still not OK, try checking your settings of perception of objective reality.                   ";
char rolltxt2[] = "                        Press to resume your misery.                        ";

TextLCD LCD(p0_2, p0_4, p1_9, p1_10, p1_11, p1_12, TextLCD::LCD20x4);
int severeness_time = 0;

Timer severness;	// For make ok duration
Timer t; // For loop control

enum STATE {
	DISPLAY_PRESS_OK,
	IDLE,
	CHECK_SEVERENESS,
	MAKE_OK,
	DISP_TOO_BAD,
	TOO_BAD,
	DISPLAY_ROLL_TEXT,
	DISPLAY_OK,
	OK_NOW,
	RESET
};



void make_everything_ok(float percentage);
uint8_t display_rolling_text(uint8_t enable, uint8_t line, char *text,uint16_t len);
void siren(uint8_t enable, uint32_t speed);



int main2() {

	STATE state = DISPLAY_PRESS_OK;

//	Make_ok_btn.mode(PullUp);
	LCD.cls();

	while(1) {

		switch (state) {
			case DISPLAY_PRESS_OK:									// Clear display
				LCD.printf("\n  Press button to\n make everything OK");		// Show message
				state = IDLE;
				break;
			case IDLE:
				// Wait for button press
				if(!Make_ok_btn) {
					severness.reset();
					severness.start();			// Start timer for btn press duration
					state = CHECK_SEVERENESS;
				}
				break;
			case CHECK_SEVERENESS:
				// Wait for release of button
				if(Make_ok_btn) {
					// Set make OK time proportional to press duration
					severeness_time = severness.read_ms();
					severness.stop();
					severness.reset();	// Reset timer
					t.reset();
					t.start();
					LCD.cls();
					LCD.printf("Making everything OK    in progress");
					state = MAKE_OK;
				}
				break;
			case MAKE_OK:
				static float perc = 0;

				if(t.read_ms()>25) {
					if(Make_ok_btn) {
						if(perc<100){
							make_everything_ok(perc);
							perc = (perc + 0.7/(1+severeness_time/4000.0));
							if(500000-(uint16_t)perc*20000>0)
								siren(ENABLE,500000-(uint16_t)perc*20000);
							else
								siren(ENABLE,0);
						} else {
							siren(DISABLE,0);
							perc = 0;
							LCD.cls();
							LCD.printf("Everything is OK now");

							state = DISPLAY_ROLL_TEXT;
						}
					} else {

						state = DISP_TOO_BAD;
					}
					// Reset timer to control next loop execution
					t.reset();
				}

				break;
			case DISP_TOO_BAD:
				if(Make_ok_btn) {
					perc = 0;
					LCD.cls();
					LCD.printf("      Too bad!\n  Things are still\n       not OK");
					siren(DISABLE,0);

					state = TOO_BAD;
				}
				break;
			case TOO_BAD:
				display_rolling_text(ENABLE,3,rolltxt2,sizeof(rolltxt2));
				if(!Make_ok_btn) {
					LCD.cls();
					display_rolling_text(DISABLE,3,rolltxt2,sizeof(rolltxt2));
					state = RESET;
				}
				break;
			case DISPLAY_ROLL_TEXT:
				if(display_rolling_text(ENABLE,2,roll_txt,sizeof(roll_txt))==1)
					state = DISPLAY_OK;
				else if(!Make_ok_btn) {
					display_rolling_text(DISABLE,2,roll_txt,sizeof(roll_txt));
					state =  OK_NOW;
				}
				break;
			case DISPLAY_OK:
				if(Make_ok_btn) {
					LCD.cls();
					LCD.printf("Everything is OK now");
					LCD.locate(0,3);
					LCD.printf(" Press to continue  ");
					state = OK_NOW;
				}
				break;
			case OK_NOW:
				if(!Make_ok_btn) {
					state = RESET;
				}
				break;
			case RESET:
				if(Make_ok_btn) {
					LCD.cls();
					state = DISPLAY_PRESS_OK;
				}
				break;

			default:
				state = RESET;
				break;
		}
	}

	return 0;
}

void make_everything_ok(float percentage) {
	static char a = 0b11111111;
	char full = 0b11111111;
	static uint8_t state = 0;

	for (int k = 0; k < int(20.0*percentage/100.0); ++k) {
		LCD.locate(k,2);
		LCD.printf("%c",full);
	}

	switch (state) {
		case 0:
			a = 0b11111111;
			state = state + 1;
			break;
		case 1:
			a = 0b11111110;
			state = state + 1;
			break;
		case 2:
			a = 0b11111111;
			state = state + 1;
			break;
		case 3:
			a = 0b11111110;
			state = 0;
			break;
		default:
			break;
	}

	LCD.locate(int(20.0*percentage/100),2);
	LCD.printf("%c",a);

}


uint8_t display_rolling_text(uint8_t enable, uint8_t line, char *text,uint16_t len) {

	uint8_t nr_cols = 20;	// Number of columns on LCD
	static char *start;
	static uint8_t state = 0;
	uint8_t ret = 0;
	char c;
	if(enable==1) {
		switch (state) {
			case 0:
				start = text;
				state = 1;
				break;
			case 1:
				if(start<text+len-nr_cols) {
					for (uint16_t i = 0; i < nr_cols; i++) {
						LCD.locate(i,line);
						c = *(start+i);
						LCD.printf("%c",c);
					}
					start = start + 1;
					for (int j = 0; j < 1700000; ++j);
				} else {
					ret = 1;
					state = 0;
				}
				break;
			default:
				break;
		}
	} else
		state = 0;

	return ret;

}

void siren(uint8_t enable, uint32_t speed) {
	static uint8_t state = 0;
	if(enable==1) {
		switch (state) {
			case 0:
				buzzer = 1;
				state = 1;
				break;
			case 1:
				buzzer = 0;
				state = 0;
				break;
			default:
				break;
		}
	} else {
		buzzer = 0;
	}


}

