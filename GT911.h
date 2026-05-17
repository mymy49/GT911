/*
 * Copyright (c) 2015 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#ifndef YSS_MOD_CTOUCH_GT911__H_
#define YSS_MOD_CTOUCH_GT911__H_

#include <drv/Gpio.h>
#include <drv/I2c.h>
#include <yss/Trigger.h>
#include <yss/Thread.h>
#include <util/ElapsedTime.h>
#include <hal/PointerDevice.h>

/*
	This is a module of the GT911, a capacitive touchscreen IC.
*/
class GT911 : private Trigger, private Thread, private Mutex, public PointerDevice
{
public :
	struct config_t
	{
		I2c &peri;
		pin_t isrPin;
		pin_t resetPin;
	};

	/*	▣ It is a function called from within the system.
	*/
	GT911(void);
	
	/*
		It is an initialization function.
		.
		@ return : Returns errors that occurred during processing.
		.
		@ config : Passes the settings defined by the config_t structure.
	*/
	error_t initialize(const config_t config);

private :
	I2c *mPeri;
	pin_t mIsr;
	bool mPenDownFlag;
	ElapsedTime mLastUpdateTime;
	uint16_t mX, mY;
	
	/*	▣ It is a function called from within the system.
		Calculates the checksum for setting changes.
		.
		@ return : Returns the calculated checksum.
		.
		@ src : Pass the source data to be used for checksum calculation.
	*/
	uint8_t calculateChksum(void *src);
	

	/*	▣ It is a function called from within the system.
		Converts the little-endian format to big-endian format for address transmission.
		.
		@ return : Returns the address after conversion to big-endian.
		.
		@ addr : Pass a little-endian address.
	*/
	uint16_t translateAddress(uint16_t addr);
	
	/*	▣ It is a function called from within the system.
		Reads multiple bytes at once from GT911.
		.
		@ return : Returns errors that occurred during processing.
		.
		@ addr : Set the address to read.
		@ des : Sets the pointer to the data buffer to read data.
		@ size : Set the total length of the data to be read.
	*/
	error_t readMultiByte(uint16_t addr, void *des, uint8_t size);

	/*	▣ It is a function called from within the system.
		Writes multiple bytes at once to GT911.
		.
		@ return : Returns errors that occurred during processing.
		.
		@ addr : Set the address to write.
		@ des : Sets the pointer to the data buffer to write data.
		@ size : Set the total length of the data to be write.
	*/
	error_t writeMultiByte(uint16_t addr, void *src, uint8_t size);

	/*	▣ It is a function called from within the system.
		Reads one byte from GT911.
		.
		@ return : Returns one byte read.
		.
		@ addr : Set the address to read.
	*/
	error_t readByte(uint16_t addr, int8_t &des);

	/*	▣ It is a function called from within the system.
		Writes one byte from GT911.
		.
		@ return : Returns errors that occurred during processing.
		.
		@ addr : Set the address to write.
		@ data : Set one byte to transmit.
	*/
	error_t writeByte(uint16_t addr, int8_t data);
	
	/*	▣ It is a function called from within the system.
		Handles GT911 interrupts.
	*/
	void trigger(void) override;
	
	/*	▣ It is a function called from within the system.
		This is a thread that detects UP events.
	*/
	void thread(void) override;
};

#endif
