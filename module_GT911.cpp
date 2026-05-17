/*
 * Copyright (c) 2015 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#include "GT911.h"
//#include <yss/event.h>
//#include <drv/Exti.h>
//#include <yss/debug.h>
#include <std_ext/string.h>
//#include <util/ElapsedTime.h>
//#include <config.h>

#define ADDR			0xBA

#define REG_PID			0x8140
#define REG_STATUS		0x814E
#define REG_P1_COORD	0x814F
#define REG_CFG			0x8047
#define REG_CFG_CHKSUM	0x80FF
#define REG_CFG_FRESH	0x8100

struct Gt911config_t
{
	uint8_t version;				// 0x8047
	uint16_t xOutputMax;			// 0x8048
	uint16_t yOutputMax;			// 0x804A
	uint8_t touchNumber;			// 0x804C
	uint8_t moduleSwitch1;			// 0x804D
	uint8_t moduleSwitch2;			// 0x804E
	uint8_t shakeCount;				// 0x804F
	uint8_t filter;					// 0x8050
	uint8_t largeTouch;				// 0x8051
	uint8_t noiseReduction;			// 0x8052
	uint8_t screenTouchLevel;		// 0x8053
	uint8_t screenLeaveLevel;		// 0x8054
	uint8_t lowPowerControl;		// 0x8055
	uint8_t refreshRate;			// 0x8056
	uint8_t xThreshold;				// 0x8057
	uint8_t yThreshold;				// 0x8058
	uint8_t reserved1[2];			// 0x8059
	uint8_t space[2];				// 0x805B
	uint8_t miniFilter;				// 0x805D
	uint8_t stretchR0;				// 0x805E
	uint8_t stretchR1;				// 0x805F
	uint8_t stretchR2;				// 0x8060
	uint8_t stretchRM;				// 0x8061
	uint8_t drvGroupANum;			// 0x8062
	uint8_t drvGroupBNum;			// 0x8063
	uint8_t sensorNum;				// 0x8064
	uint8_t freqAFactor;			// 0x8065
	uint8_t freqBFactor;			// 0x8066
	uint16_t pannelBitFreq;			// 0x8067
	uint16_t pannelSensorTime;		// 0x8069
	uint8_t pannelTxGain;			// 0x806B
	uint8_t pannelRxGain;			// 0x806C
	uint8_t pannelDumpShift;		// 0x806D
	uint8_t drvFrameControl;		// 0x806E
	uint8_t chargingLevelUp;		// 0x806F
	uint8_t moduleSwitch3;			// 0x8070
	uint8_t gestureDis;				// 0x8071
	uint8_t gestureLongPressTime;	// 0x8072
	uint8_t xySlopeAdjust;			// 0x8073
	uint8_t gestureControl;			// 0x8074
	uint8_t gestureSwitch1;			// 0x8075
	uint8_t gestureSwitch2;			// 0x8076
	uint8_t gestureRefreshRate;		// 0x8077
	uint8_t gestureTouchLevel;		// 0x8078
	uint8_t newGreenWakeUpLevel;	// 0x8079
	uint8_t freqHoppingStart;		// 0x807A
	uint8_t freqHoppingEnd;			// 0x807B
	uint8_t noiseDetectTimes;		// 0x807C
	uint8_t hoppingFlag;			// 0x807D
	uint8_t hoppingThreshold;		// 0x807E
	uint8_t noiseThreshold;			// 0x807F
	uint8_t noiseMinThreshold;		// 0x8080
	uint8_t reserved2;				// 0x8081
	uint8_t hoppingSensorGroup;		// 0x8082
	uint8_t hoppingSeg1Normalize;	// 0x8083
	uint8_t hoppingSeg1Factor;		// 0x8084
	uint8_t mainClockAdjust;		// 0x8085
	uint8_t hoppingSeg2Normalize;	// 0x8086
	uint8_t hoppingSeg2Factor;		// 0x8087
	uint8_t reserved3;				// 0x8088
	uint8_t hoppingSeg3Normalize;	// 0x8089
	uint8_t hoppingSeg3Factor;		// 0x808A
	uint8_t reserved4;				// 0x808B
	uint8_t hoppingSeg4Normalize;	// 0x808C
	uint8_t hoppingSeg4Factor;		// 0x808D
	uint8_t reserved5;				// 0x808E
	uint8_t hoppingSeg5Normalize;	// 0x808F
	uint8_t hoppingSeg5Factor;		// 0x8090
	uint8_t reserved6;				// 0x8091
	uint8_t hoppingSeg6Normalize;	// 0x8092
	uint8_t key1;					// 0x8093
	uint8_t key2;					// 0x8094
	uint8_t key3;					// 0x8095
	uint8_t key4;					// 0x8096
	uint8_t keyArea;				// 0x8097
	uint8_t keyTouchLevel;			// 0x8098
	uint8_t keyLeaveLevel;			// 0x8099
	uint8_t keySens[2];				// 0x809A
	uint8_t keyRestrain;			// 0x809C
	uint8_t keyRestrainTime;		// 0x809D
	uint8_t gestureLargeTouch;		// 0x809E
	uint8_t reserved7[2];			// 0x809F
	uint8_t hotknotNoiseMap;		// 0x80A1
	uint8_t linkThreshold;			// 0x80A2
	uint8_t pXyThreshold;			// 0x80A3
	uint8_t gHotDumpShift;			// 0x80A4
	uint8_t gHotRxGain;				// 0x80A5
	uint8_t freqGain0;				// 0x80A6
	uint8_t freqGain1;				// 0x80A7
	uint8_t freqGain2;				// 0x80A8
	uint8_t freqGain3;				// 0x80A9
	uint8_t reserved8[9];			// 0x80AA
	uint8_t combineDis;				// 0x80B3
	uint8_t splitSet;				// 0x80B4
	uint8_t reserved9[2];			// 0x80B5
	uint8_t sensorCh[14];			// 0x80B7
	uint8_t reserved10[16];			// 0x80C5
	uint8_t driverCh[26];			// 0x80D5
	uint8_t reserved11[16];			// 0x80EF
	uint8_t chksum;					// 0x80FF
	uint8_t configFresh;			// 0x8100
}__attribute__((packed));

GT911::GT911(void)
{
	
}

error_t GT911::initialize(const config_t config)
{
	error_t result;
	uint8_t data[4];
	
	mPeri = &config.peri;
	mIsr = config.isrPin;
	mPenDownFlag = false;

	if(config.resetPin.port)
	{
		config.resetPin.port->setOutput(config.resetPin.pin, false);
		
		// Sequence to set the address to 0xBA
		mIsr.port->setAsOutput(mIsr.pin);
		mIsr.port->setOutput(mIsr.pin, false);
		thread::delay(10);
		config.resetPin.port->setOutput(config.resetPin.pin, true);
		thread::delay(5);
		mIsr.port->setAsInput(mIsr.pin);
	}
	thread::delay(50);
	
	result = readMultiByte(REG_PID, data, 4);
	if(result != error_t::ERROR_NONE)
	{
		goto error_handler;
	}
	
	if(data[0] != '9' || data[1] != '1' || data[2] != '1'|| data[3] != 0)
	{
		result = error_t::UNKNOWN_DEVICE;
		goto error_handler;
	}
	
	result = activateTrigger(512);
	if(result != error_t::ERROR_NONE)
		goto error_handler ;
	
	result = runThread(512);
	if(result != error_t::ERROR_NONE)
		goto error_handler ;

	runThread();

#if defined(__M4xx_FAMILY)
	// It passed a trigger ID to make it work in conjunction with GPIO interrupts.
	result = mIsr.port->setGpioInterrupt(mIsr.pin, Gpio::EDGE_FALLING, getTriggerId());
#else

#endif
	if(result != error_t::ERROR_NONE)
		goto error_handler;

	return error_t::ERROR_NONE;

error_handler :
	deactivateTriger();
	stopThread();
	return result;
}

uint8_t GT911::calculateChksum(void *src)
{
	uint8_t chksum = 0, *data = (uint8_t*)src;
	
	for(uint32_t i = 0; i < sizeof(Gt911config_t) - 2; i++)
	{
		chksum += data[i];
	}

	return (~chksum) + 1;
}

error_t GT911::readByte(uint16_t addr, int8_t &des)
{
	error_t result;

	addr = translateAddress(addr);

	mPeri->lock();
	result = mPeri->send(ADDR, (int8_t*)&addr, 2, 100);
	if(result == error_t::ERROR_NONE)
	{
		result = mPeri->receive(ADDR, (int8_t*)&des, 1, 100);
	}
	mPeri->stop();
	mPeri->unlock();

	return result;
}

uint16_t GT911::translateAddress(uint16_t addr)
{
	uint8_t buf = (uint8_t)addr;

	addr >>= 8;
	addr |= (uint16_t)buf << 8;

	return addr;
}

error_t GT911::readMultiByte(uint16_t addr, void *des, uint8_t size)
{
	error_t rt = error_t::UNKNOWN;

	addr = translateAddress(addr);

	mPeri->lock();
	if(mPeri->send(ADDR, &addr, 2, 100) == error_t::ERROR_NONE)
	{
		rt = mPeri->receive(ADDR, des, size, 100);
	}
	mPeri->stop();
	mPeri->unlock();

	return rt;
}

error_t GT911::writeMultiByte(uint16_t addr, void *src, uint8_t size)
{
	error_t result = error_t::UNKNOWN;
	uint8_t *data = new uint8_t[size + 2];

	addr = translateAddress(addr);

	if(data != nullptr)
	{
		memcpy(&data[0], &addr, 2);
		memcpy(&data[2], src, size);
		mPeri->lock();
		result = mPeri->send(ADDR, data, size + 2, 500);
		mPeri->stop();
		mPeri->unlock();

		delete[] data;

		return result;
	}
	else
		return error_t::MALLOC_FAILED;
}

error_t GT911::writeByte(uint16_t addr, int8_t data)
{
	error_t result = error_t::UNKNOWN;
	uint8_t buf[3] = {(uint8_t)(addr >> 8), (uint8_t)addr, (uint8_t)data};

	mPeri->lock();
	result = mPeri->send(ADDR, buf, 3, 100);
	mPeri->stop();
	mPeri->unlock();

	return result;
}

void GT911::trigger(void)
{
	uint8_t data[8];
	int8_t status;
	
	lock();

	if(readByte(REG_STATUS, status) == error_t::ERROR_NONE && status & 0x80)
	{
		writeByte(REG_STATUS, 0);
		readMultiByte(REG_P1_COORD, data, sizeof(data));

		mX = (uint16_t)data[2] << 8 | (uint16_t)data[1];
		mY = (uint16_t)data[4] << 8 | (uint16_t)data[3];

		if(!mPenDownFlag)
		{
			mPenDownFlag = true;
			pushDownEvent(mX, mY);
		}
		else 
		{
			pushDragEvent(mX, mY);
		}
		
		mLastUpdateTime.reset();
	}

	unlock();
}

void GT911::thread(void)
{
	while(1)
	{
		lock();
		if(mPenDownFlag && mLastUpdateTime.getMsec() >= 100)
		{
			mPenDownFlag = false;
			pushUpEvent(mX, mY);
		}
		unlock();

		thread::yield();
	}
}
