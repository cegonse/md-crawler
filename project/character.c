#include "character.h"


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

    self->sprite = SPR_addSprite(sprite, self->position[kCHARACTER_DIRECTION_HORIZONTAL], self->position[kCHARACTER_DIRECTION_VERTICAL], 
                        TILE_ATTR(PAL0 + palette_index, FALSE, FALSE, FALSE));

    updateAnimation(self, kCHARACTER_ANIMATION_IDLE);

    SPR_setVisibility(self->sprite, VISIBLE);
}


static inline void updatePosition(Character *self)
{
    SPR_setPosition(self->sprite, self->position[kCHARACTER_DIRECTION_HORIZONTAL], self->position[kCHARACTER_DIRECTION_VERTICAL]);
}


void Character_Update(Character *self, s8 direction)
{
    self->position[kCHARACTER_DIRECTION_HORIZONTAL] += direction;

    if (self->acceleration[kCHARACTER_DIRECTION_VERTICAL] < 4) {
        self->acceleration[kCHARACTER_DIRECTION_VERTICAL]++;
    }

    if (direction != 0) {
        if ((direction > 0 && self->acceleration[kCHARACTER_DIRECTION_HORIZONTAL] < 3) ||
            (direction < 0 && self->acceleration[kCHARACTER_DIRECTION_HORIZONTAL] > -3)) {
            self->acceleration[kCHARACTER_DIRECTION_HORIZONTAL] += direction;
        }
    } else {
        if (self->acceleration[kCHARACTER_DIRECTION_HORIZONTAL] > 0) {
            self->acceleration[kCHARACTER_DIRECTION_HORIZONTAL]--;
        } else if (self->acceleration[kCHARACTER_DIRECTION_HORIZONTAL] < 0) {
            self->acceleration[kCHARACTER_DIRECTION_HORIZONTAL]++;
        }
    }

    if (self->position[kCHARACTER_DIRECTION_VERTICAL] < 200) {
        self->position[kCHARACTER_DIRECTION_VERTICAL] += self->acceleration[kCHARACTER_DIRECTION_VERTICAL];
    } else {
        self->position[kCHARACTER_DIRECTION_VERTICAL] = 200;
    }

    if ((self->acceleration[kCHARACTER_DIRECTION_HORIZONTAL] > 0 && self->position[kCHARACTER_DIRECTION_HORIZONTAL] < 300) ||
        (self->acceleration[kCHARACTER_DIRECTION_HORIZONTAL] < 0 && self->position[kCHARACTER_DIRECTION_HORIZONTAL] > 20)) {
        self->position[kCHARACTER_DIRECTION_HORIZONTAL] += self->acceleration[kCHARACTER_DIRECTION_HORIZONTAL];
    }

    updatePosition(self);
}
