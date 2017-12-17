#pragma once

#include <genesis.h>

#define SYSTEM_GPU_SAFE(x)	do \
							{ \
								SYS_disableInts(); \
								x \
								SYS_enableInts(); \
							} while(0);

#define kCONTROLLER_STATE_NONE		0
#define kCONTROLLER_STATE_ONE_3BTN	1
#define kCONTROLLER_STATE_ONE_6BTN	2
#define kCONTROLLER_STATE_TWO_3BTN	4
#define kCONTROLLER_STATE_TWO_6BTN	8

void System_Init(u8 *controller);

void System_EndFrame();
