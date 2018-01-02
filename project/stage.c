#include "stage.h"


static inline u8 checkCollision(const struct collider *collider, struct vector2 *position, struct vector2 *size) {
	return (position->x < collider->position.x + collider->size.x &&
			position->x + size->x >= collider->position.x &&
			position->y < collider->position.y + collider->size.y &&
			size->y + position->y > collider->position.y);
}


u8 Stage_CheckCollisions(struct vector2 *position, struct vector2 *size, const struct stage *stage)
{
	u8 i;
	const struct collider *collider;

	for (i=0; i<stage->num_colliders; ++i) {
		collider = &stage->colliders[i];

		if (checkCollision(collider, position, size)) {
			return 1;
		}
	}

	return 0;
}
