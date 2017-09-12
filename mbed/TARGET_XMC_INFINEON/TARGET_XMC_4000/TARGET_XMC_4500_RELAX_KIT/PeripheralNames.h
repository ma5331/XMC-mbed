/* mbed Microcontroller Library
 * Copyright (c) 2013 Nordic Semiconductor
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MBED_PERIPHERALNAMES_H
#define MBED_PERIPHERALNAMES_H

#include <cmsis.h>

#ifdef __cplusplus
extern "C" {
#endif

#define STDIO_UART_TX     p5_1
#define STDIO_UART_RX     p1_5
#define STDIO_UART        UART_1

typedef enum {
    UART_1 = (int)USIC0_CH0,
	UART_2 = (int)USIC0_CH1,
	UART_3 = (int)USIC1_CH0,
	UART_4 = (int)USIC1_CH1,
	UART_5 = (int)USIC2_CH0,
	UART_6 = (int)USIC2_CH1,

} UARTName;


typedef enum {
    SPI_0 = (int)USIC0_CH0_BASE,
    SPI_1 = (int)USIC0_CH1_BASE,
    SPIS = (int)USIC0_CH0_BASE
} SPIName;

typedef enum {
    PWM_1  = (int)CCU40_CC40,
    PWM_2  = (int)CCU40_CC41,
	PWM_3  = (int)CCU40_CC42,
	PWM_4  = (int)CCU40_CC43,
    PWM_5  = (int)CCU41_CC40,
    PWM_6  = (int)CCU41_CC41,
	PWM_7  = (int)CCU41_CC42,
	PWM_8  = (int)CCU41_CC43,
    PWM_9  = (int)CCU42_CC40,
    PWM_10 = (int)CCU42_CC41,
	PWM_11 = (int)CCU42_CC42,
	PWM_12 = (int)CCU42_CC43,
} PWMName;

typedef enum {
    I2C_1 = (int)USIC0_CH0,
	I2C_2 = (int)USIC0_CH1,
	I2C_3 = (int)USIC1_CH0,
	I2C_4 = (int)USIC1_CH1,
	I2C_5 = (int)USIC2_CH0,
	I2C_6 = (int)USIC2_CH1,
} I2CName;

typedef enum {
	DAC_0 = (int)DAC,
} DACName;

typedef enum {
    VADC_0 = (int)VADC_G0,
	VADC_1 = (int)VADC_G1,
	VADC_2 = (int)VADC_G2,
	VADC_3 = (int)VADC_G3,
} ADCName;

#ifdef __cplusplus
}
#endif

#endif
