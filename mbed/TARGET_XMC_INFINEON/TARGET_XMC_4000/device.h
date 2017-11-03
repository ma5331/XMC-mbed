// The 'provides' section in 'target.json' is now used to create the device's hardware preprocessor switches.
// Check the 'provides' section of the target description in 'targets.json' for more details.
/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
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
#ifndef MBED_DEVICE_H
#define MBED_DEVICE_H

#if UC_DEVICE ==  XMC4500
#define CLOCK_FREQ 		120
#endif

#define DEVICE_ANALOGIN			1

#define DEVICE_ANALOGOUT		1

#define DEVICE_PWMOUT			1

#define DEVICE_SERIAL			1
#define DEVICE_SERIAL_ASYNCH	1

#define DEVICE_I2C				1
#define DEVICE_I2C_ASYNCH		1
#define DEVICE_I2CSLAVE			0

#define DEVICE_INTERRUPTIN		1










#include <objects.h>

#endif
