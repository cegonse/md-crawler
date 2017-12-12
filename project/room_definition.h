#pragma once

#include <genesis.h>


#define	MAP_MAX_TARGET_ROOMS	4
#define MAX_ROOMS 256


struct room_definition
{
	const s8 plane_width;
	const s8 plane_height;
	const s16 spawn_x;
	const s16 spawn_y;
	const u8 collision_boxes;

	const u16 *plane_data;
	const s16 *collision_data;
	const TileSet *tileset_data;
	const Palette *palette_data;

	const u8 warp_boxes;
	const s16 *warp_data;
	const u8 warp_target_rooms[MAP_MAX_TARGET_ROOMS];
	const s16 warp_target_rooms_spawn_x[MAP_MAX_TARGET_ROOMS];
	const s16 warp_target_rooms_spawn_y[MAP_MAX_TARGET_ROOMS];
};
