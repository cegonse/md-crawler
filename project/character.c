#include "character.h"


#define kCHARACTER_JUMP_VELOCITY           FIX32(-10.0)
#define kCHARACTER_FLOOR_LIMIT             FIX32(190.0)
#define kCHARACTER_GRAVITY                 FIX32(1.0)
#define kCHARACTER_FRICTION                FIX32(0.8)
#define kCHARACTER_MIN_VELOCITY            FIX32(0.3)
#define kCHARACTER_MAX_GROUND_VELOCITY     FIX32(3.0)
#define kCHARACTER_MAX_AIR_VELOCITY        FIX32(6.0)
#define kCHARACTER_RIGHT_LIMIT             FIX32(290.0)
#define kCHARACTER_LEFT_LIMIT              FIX32(10.0)

#define CHARACTER_IS_FALLING(p)        (p->velocity.y != 0)


static fix32 direction_table[] = {
    [kCHARACTER_DIRECTION_NONE] = FIX32(0.0),
    [kCHARACTER_DIRECTION_LEFT] = FIX32(-0.8),
    [kCHARACTER_DIRECTION_RIGHT] = FIX32(0.8),
};


void Character_Init(Character *self)
{
    memset(self, 0, sizeof(Character));
    self->position.x = 100;
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

    self->sprite = SPR_addSprite(sprite, fix32ToInt(self->position.x), fix32ToInt(self->position.y), TILE_ATTR(PAL0 + palette_index, FALSE, FALSE, FALSE));

    updateAnimation(self, kCHARACTER_ANIMATION_IDLE);

    SPR_setVisibility(self->sprite, VISIBLE);

    SPR_update();
}


static inline void updatePosition(Character *self)
{
    self->position.x += self->velocity.x;
    self->position.y += self->velocity.y;

    SPR_setPosition(self->sprite, fix32ToInt(self->position.x), fix32ToInt(self->position.y));
}


static inline void updateHorizontalVelocity(Character *self, TCHARACTER_DIRECTION direction)
{
    fix32 max_velocity = CHARACTER_IS_FALLING(self) ? kCHARACTER_MAX_AIR_VELOCITY : kCHARACTER_MAX_GROUND_VELOCITY;

    if (direction == kCHARACTER_DIRECTION_NONE) {
        if (abs(self->velocity.x) > kCHARACTER_MIN_VELOCITY) {
            if (self->velocity.x > 0) {
                self->velocity.x -= kCHARACTER_FRICTION;
            } else if (self->velocity.x < 0) {
                self->velocity.x += kCHARACTER_FRICTION;
            }
        }
    } else {
        if (abs(self->velocity.x + direction_table[direction]) < max_velocity) {
            self->velocity.x += direction_table[direction];
        }
    }

    if ((self->velocity.x > 0 && self->position.x >= kCHARACTER_RIGHT_LIMIT) ||
        (self->velocity.x < 0 && self->position.x <= kCHARACTER_LEFT_LIMIT)) {
        self->velocity.x = 0;
    }
}


static inline void updateVerticalVelocity(Character *self)
{
    if (self->position.y < kCHARACTER_FLOOR_LIMIT) {
        self->velocity.y += kCHARACTER_GRAVITY;
    } else {
        if (self->velocity.y > 0) {
            self->velocity.y = 0;
            self->is_jumping = 0;
            self->position.y = kCHARACTER_FLOOR_LIMIT;
        }
    }
}


void Character_Update(Character *self, TCHARACTER_DIRECTION direction)
{
    updateHorizontalVelocity(self, direction);

    updateVerticalVelocity(self);

    updatePosition(self);
}


void Character_OnJump(Character *self)
{
    if (!self->is_jumping) {
        self->is_jumping = 1;
        self->velocity.y = kCHARACTER_JUMP_VELOCITY;
    }
}
