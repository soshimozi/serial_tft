/*
The MIT License (MIT)
Copyright (c) 2016 Scott McCain

Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*******************************************************************************************************************
* Filename:	eeprom.cpp
* Created:	6/14/2016 5:23:41 PM
* Author:	Scott McCain
*******************************************************************************************************************
*
*/

 #include <avr/io.h>
 #include "eeprom.h"
 
 inline void EEPROM_write(uint16_t uiAddress, uint8_t ucData)
 {
	 /* Wait for completion of previous write */
	 while(EECR & (1<<EEPE));

	 /* Set up address and Data Registers */
	 EEAR = uiAddress;
	 EEDR = ucData;

	 /* Write logical one to EEMPE */
	 EECR |= (1<<EEMPE);

	 /* Start eeprom write by setting EEPE */
	 EECR |= (1<<EEPE);
 }

 inline uint8_t EEPROM_read(uint16_t uiAddress)
 {
	 /* Wait for completion of previous write */
	 while(EECR & (1<<EEPE));

	 /* Set up address register */
	 EEAR = uiAddress;

	 /* Start eeprom read by writing EERE */
	 EECR |= (1<<EERE);

	 /* Return data from Data Register */
	 return EEDR;
 }