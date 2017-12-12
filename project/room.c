#include "room.h"
#include "system.h"


static void commitTileDataToVdp(struct room_definition *room, u8 palette_index, u8 tilemap_index)
{
	u8 x = room->plane_width-1, y = room->plane_height-1;

	SYSTEM_GPU_SAFE
	(
		do
		{
			VDP_setTileMapXY(PLAN_A,
					TILE_ATTR_FULL(PAL0 + palette_index,FALSE,FALSE,FALSE,
					TILE_USERINDEX + room->plane_data[x+room->plane_width*y] - 1 + tilemap_index),
					x, y);

			if (x != 0) {
				--x;
			} else {
				if (y != 0) {
					x = room->plane_width-1;
					--y;
				} else {
					break;
				}
			}
		} while (x + y != 0);
	)
}


void Room_Load(struct room_definition *room, s16 *room_transform_x, s16 *room_transform_y, u8 palette_index, u8 tilemap_index)
{
	VDP_loadTileSet(room->tileset_data, TILE_USERINDEX + tilemap_index, TRUE);

	// Clear the map with the background color
	VDP_fillTileMap(VDP_PLAN_A, TILE_ATTR_FULL(PAL0 + palette_index, FALSE, FALSE, FALSE, TILE_USERINDEX + room->tileset_data->numTile - 1), 0, 64*64);

	// Move the tile plane to center the room
	*room_transform_x = VDP_getScreenWidth() / 2 - 8 * room->plane_width / 2;
	*room_transform_y = -VDP_getScreenHeight() / 2 + 8 * room->plane_height / 2;
	
	VDP_setHorizontalScroll(PLAN_A, *room_transform_x);
	VDP_setVerticalScroll(PLAN_A, *room_transform_y);

	commitTileDataToVdp(room, palette_index, tilemap_index);
}

