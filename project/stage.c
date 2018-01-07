#include "stage.h"


u8 Stage_CheckCollisions(struct vector2 *position, struct vector2 *size, fix32 dxf, fix32 dyf, const struct stage *stage)
{
	u8 i;
	u8 collision = kSTAGE_NO_COLLISION;

	s16 w = fix32ToInt(size->x);
	s16 h = fix32ToInt(size->y);
	s16 x = fix32ToInt(position->x) + fix32ToInt(dxf);
	s16 y = fix32ToInt(position->y) + fix32ToInt(dyf) + 9;

	for (i=0; i<stage->num_colliders; ++i) {
		const struct collider *collider = &stage->colliders[i];

		collision = ((y < collider->position.y + collider->size.y) && (h + y > collider->position.y)) &&
			((x < collider->position.x + collider->size.x) && (x + w > collider->position.x));

		if (collision != kSTAGE_NO_COLLISION) {
			return collision;
		}
	}

	return collision;
}


void Stage_DebugDraw(const struct stage *stage)
{
	s16 x, y, h, w;
	u8 i, j, k;

	for (i=0; i<stage->num_colliders; ++i) {
		x = stage->colliders[i].position.x;
		y = stage->colliders[i].position.y;
		w = stage->colliders[i].size.x;
		h = stage->colliders[i].size.y;

		for (j=x; j != x+w; j+=8) {
			for (k=y; k != y+h; k+=8) {
				VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0 + 2,0,0,0,TILE_USERINDEX), j/8, k/8);
			}
		}
	}
}
