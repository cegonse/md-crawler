#include <genesis.h>

#include "system.h"
#include "character.h"
#include "gfx.h"
#include "stage.h"


#define CONTROLLER_DIRECTION_MASK(ctl)  (ctl & 0xF)


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


static const struct stage test_stage = {
	.num_colliders = 2,
	.colliders = {
		[0] = {
			.position.x = 32,
			.position.y =  152,
			.size.x = 64,
			.size.y = 16,
		},
		[1] = {
			.position.x = 96,
			.position.y =  176,
			.size.x = 64,
			.size.y = 16,
		},
	},
};


int main()
{
	u8 detected_controllers;

	System_Init(&detected_controllers);

	VDP_loadTileSet(&basic_tiles_def, TILE_USERINDEX, TRUE);
	VDP_setPalette(PAL0 + 2, basic_tiles_pal_def.data);

	Stage_DebugDraw(&test_stage);

	Character_Init(&main_character);
	Character_SetSprite(&main_character, &basic_character_def, 1);

	while (1)
	{
		u8 pad_state = JOY_readJoypad(JOY_1);

		if (pad_state & BUTTON_A) {
			Character_OnJump(&main_character);
		}

		Character_Update(&main_character, joy_to_direction[CONTROLLER_DIRECTION_MASK(pad_state)], &test_stage);
		System_EndFrame();
	}

	return (0);
}
