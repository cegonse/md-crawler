#include <genesis.h>

#include "system.h"
#include "character.h"
#include "gfx.h"


static Character main_character;

static s8 joy_to_direction[16] = {
	[0] = 0,
	[BUTTON_UP] = 0,
	[BUTTON_DOWN] = 0,
	[BUTTON_UP | BUTTON_LEFT] = -1,
	[BUTTON_DOWN | BUTTON_LEFT] = -1,
	[BUTTON_LEFT] = -1,
	[BUTTON_UP | BUTTON_RIGHT] = 1,
	[BUTTON_DOWN | BUTTON_RIGHT] = 1,
	[BUTTON_RIGHT] = 1,
};


int main()
{
	u8 detected_controllers;

	System_Init(&detected_controllers);

	Character_Init(&main_character);
	Character_SetSprite(&main_character, &basic_character_def, 1);
	
	while (1)
	{
		u8 pad_state = JOY_readJoypad(JOY_1);

		Character_Update(&main_character, joy_to_direction[pad_state]);
		System_EndFrame();
	}

	return (0);
}
