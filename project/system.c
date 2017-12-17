#include "system.h"


static inline void setScreenResolution()
{
	if (IS_PALSYSTEM) {
		VDP_setScreenWidth320();
		VDP_setScreenHeight240();
	} else {
		VDP_setScreenWidth320();
		VDP_setScreenHeight224();
	}
}


static inline void initVdp()
{
	SPR_init(0,0,0);
	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
	VDP_setPlanSize(64, 64);
}


static void detectControllers(u8 *controllers)
{
	u8 first_port_state, second_port_state;

	first_port_state = JOY_getJoypadType(PORT_1);
	second_port_state = JOY_getJoypadType(PORT_2);

	if (first_port_state == JOY_TYPE_PAD3) {
		*controllers |= kCONTROLLER_STATE_ONE_3BTN;
	} else if (first_port_state == JOY_TYPE_PAD6) {
		*controllers |= kCONTROLLER_STATE_ONE_6BTN;
	}

	if (second_port_state == JOY_TYPE_PAD3) {
		*controllers |= kCONTROLLER_STATE_TWO_3BTN;
	}
	else if (second_port_state == JOY_TYPE_PAD6) {
		*controllers |= kCONTROLLER_STATE_TWO_6BTN;
	}
}


void System_Init(u8 *controllers)
{
	SYSTEM_GPU_SAFE
	(
		initVdp();
		setScreenResolution();
	)

	detectControllers(controllers);
}


void System_EndFrame()
{
	SPR_update();
	VDP_waitVSync();
}
