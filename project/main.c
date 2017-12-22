#include <genesis.h>

#include "system.h"
#include "character.h"
#include "gfx.h"


static Character main_character;

static s8 joy_to_direction[16] = {
	[0] = kCHARACTER_DIRECTION_NONE,
	[BUTTON_UP] = kCHARACTER_DIRECTION_NONE,
	[BUTTON_DOWN] = kCHARACTER_DIRECTION_NONE,
	[BUTTON_UP | BUTTON_LEFT] = kCHARACTER_DIRECTION_LEFT,
	[BUTTON_DOWN | BUTTON_LEFT] = kCHARACTER_DIRECTION_LEFT,
	[BUTTON_LEFT] = kCHARACTER_DIRECTION_LEFT,
	[BUTTON_UP | BUTTON_RIGHT] = kCHARACTER_DIRECTION_RIGHT,
	[BUTTON_DOWN | BUTTON_RIGHT] = kCHARACTER_DIRECTION_RIGHT,
	[BUTTON_RIGHT] = kCHARACTER_DIRECTION_RIGHT,
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

		if (pad_state & BUTTON_A) {
			Character_OnJump(&main_character);
		}

		Character_Update(&main_character, joy_to_direction[pad_state & 0xF]);
		System_EndFrame();
	}

	return (0);
}
