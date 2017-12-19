#pragma once

#include <genesis.h>
#include "vector2.h"


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
    kCHARACTER_DIRECTION_NONE = 0,
    kCHARACTER_DIRECTION_LEFT,
    kCHARACTER_DIRECTION_RIGHT,
} TCHARACTER_DIRECTION;


typedef struct character {
    Sprite *sprite;
    TCHARACTER_ANIMATION current_animation;

    struct vector2 position;
    struct vector2 acceleration;
    struct vector2 velocity;
} Character;

void Character_Init(Character *self);

void Character_SetSprite(Character *self, const SpriteDefinition *sprite, u8 palette_index);

void Character_Update(Character *self, TCHARACTER_DIRECTION direction);
