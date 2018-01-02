/*
 * stage.h
 *
 *  Created on: 2 ene. 2018
 *      Author: jamoh
 */
#pragma once

#include <genesis.h>
#include "vector2.h"

#define kMAX_COLLIDERS		64


struct collider {
	struct vector2 position;
	struct vector2 size;
};


struct stage {
	u16 num_colliders;
	struct collider colliders[kMAX_COLLIDERS];
};

u8 Stage_CheckCollisions(struct vector2 *position, struct vector2 *size, const struct stage *stage);
