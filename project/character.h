#pragma once

#include <genesis.h>


#define kCHARACTER_TILE_SIZE     15


typedef enum character_animation {
    kCHARACTER_ANIMATION_IDLE = 0,
    kCHARACTER_ANIMATION_WALK,
    kCHARACTER_ANIMATION_JUMP_START,
    kCHARACTER_ANIMATION_JUMP_AIR,
    kCHARACTER_ANIMATION_JUMP_END,
    kCHARACTER_ANIMATION_JUMP_HIT,
    kCHARACTER_ANIMATION_JUMP_SLASH,
} TCHARACTER_ANIMATION;


typedef enum character_direction {
    kCHARACTER_DIRECTION_HORIZONTAL = 0,
    kCHARACTER_DIRECTION_VERTICAL,
    kCHARACTER_DIRECTION_MAX,
} TCHARACTER_DIRECTION;


typedef struct character {
    Sprite *sprite;
    TCHARACTER_ANIMATION current_animation;

    u16 position[kCHARACTER_DIRECTION_MAX];
    s8 acceleration[kCHARACTER_DIRECTION_MAX];
} Character;

void Character_Init(Character *self);

void Character_SetSprite(Character *self, const SpriteDefinition *sprite, u8 palette_index);

void Character_Update(Character *self, s8 direction);
