#include "character.h"


static fix32 direction_table[] = {
    [kCHARACTER_DIRECTION_NONE] = FIX32(0.0),
    [kCHARACTER_DIRECTION_LEFT] = FIX32(-0.3),
    [kCHARACTER_DIRECTION_RIGHT] = FIX32(0.3),
};


void Character_Init(Character *self)
{
    memset(self, 0, sizeof(Character));
}


static inline void updateAnimation(Character *self, TCHARACTER_ANIMATION animation)
{
    self->current_animation = animation;
    SPR_setAnim(self->sprite, self->current_animation);
}


void Character_SetSprite(Character *self, const SpriteDefinition *sprite, u8 palette_index)
{
    if (self->sprite != NULL) {
        SPR_releaseSprite(self->sprite);
    }

    VDP_setPalette(PAL0 + palette_index, sprite->palette->data);

    self->sprite = SPR_addSprite(sprite, 0, 0, TILE_ATTR(PAL0 + palette_index, FALSE, FALSE, FALSE));

    updateAnimation(self, kCHARACTER_ANIMATION_IDLE);

    SPR_setVisibility(self->sprite, VISIBLE);
}


static inline void updatePosition(Character *self)
{
    u16 pixel_x, pixel_y;

    pixel_x = fix32ToInt(self->position.x);
    pixel_y = fix32ToInt(self->position.y);

    SPR_setPosition(self->sprite, pixel_x, pixel_y);
}


void Character_Update(Character *self, TCHARACTER_DIRECTION direction)
{
    fix32 gravity = FIX32(1.0);
    fix32 floor = FIX32(180.0);
    fix32 friction = FIX32(0.8);
    fix32 horizontal_direction = direction_table[direction];

    if (self->velocity.x > 0 && horizontal_direction == 0) {
        self->velocity.x -= friction;
    } else if (self->velocity.x < 0 && horizontal_direction == 0) {
        self->velocity.x += friction;
    }

    if (horizontal_direction != 0) {
        self->velocity.x += horizontal_direction;
    } else {
        self->velocity.x = 0;
    }

    if (self->position.y < floor) {
        self->velocity.y += gravity;
    } else {
        self->velocity.y = 0;
    }

    self->position.x += self->velocity.x;
    self->position.y += self->velocity.y;

    updatePosition(self);
}
