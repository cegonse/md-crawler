// Node.JS tool to convert JSON Tiled maps to C headers
// (c) Cesar Gonzalez Segura 2017
var fs = require("fs");

if (process.argv.length != 3) {
	console.log("Usage: tiled2c [in.json]");
	process.exit(1);
}

// File names and data
var inName = process.argv[2];
var inMap = JSON.parse(fs.readFileSync(inName));

// Fetch the map properties
var mapName = inMap.properties.map_name;
var mapTileset = inMap.properties.tileset_name;
var mapPalette = inMap.properties.tileset_palette;
var spawnX = inMap.properties.spawn_x;
var spawnY = inMap.properties.spawn_y;
var outName = mapName + ".h";

// Create the output C header
var outFile = "// Created with tiled2c.js\n";
outFile += "#ifndef _" + mapName + "_\n";
outFile += "#define _" + mapName + "_\n\n";
outFile += "#include \"../room_definition.h\"\n";

// Write the data for the plane A layer
var planTiles = null;
var planData = null;

for (var i = 0; i < inMap.layers.length; ++i) {
	if (inMap.layers[i].name == "PlaneA") {
		planData = inMap.layers[i];
		planTiles = planData.data;
		break;
	}
}

if (planData && planTiles) {
	outFile += "#define " + mapName + "_" + planData.name + "_HEIGHT\t" + planData.height + "\n";
	outFile += "#define " + mapName + "_" + planData.name + "_WIDTH\t" + planData.width + "\n\n";

	outFile += "static const u16 " + mapName + "_" + planData.name + "["+ planTiles.length +"] = {\n";
	var k = 0;

	for (var j = 0; j < planTiles.length; j++) {
		if (k == 0) {
			outFile += "\t";
		}

		outFile += planTiles[j].toString() + ", ";
		k++;

		if (k == 16) {
			outFile += "\n";
			k = 0;
		}
	}

	outFile += "};\n\n";
}

// Write the collision data
var collisionEdges = null;

for (var i = 0; i < inMap.layers.length; ++i) {
	if (inMap.layers[i].name == "Collision") {
		collisionEdges = inMap.layers[i].objects;
		break;
	}
}

if (collisionEdges) {
	outFile += "#define " + mapName + "_COLLISION_EDGE_COUNT\t" + collisionEdges.length + "\n\n";
	outFile += "static const s16 " + mapName + "_collision_data[" + (collisionEdges.length * 4).toString() + "] = {\n";

	for (var i = 0; i < collisionEdges.length; ++i) {
		var ed = collisionEdges[i];

		outFile += "\t" + Math.floor(ed.x).toString() + ", " + Math.floor(ed.y).toString() + ", " + 
						  Math.floor(ed.width).toString() + ", " + Math.floor(ed.height).toString() + ",\n";
	}

	outFile += "};\n\n";
}

// Write the warp data
var warpEdges = null;

for (var i = 0; i < inMap.layers.length; ++i) {
	if (inMap.layers[i].name == "Warp") {
		warpEdges = inMap.layers[i].objects;
		break;
	}
}

if (warpEdges) {
	outFile += "#define " + mapName + "_WARP_EDGE_COUNT\t" + warpEdges.length + "\n\n";
	outFile += "static const s16 " + mapName + "_warp_data[" + (warpEdges.length * 4).toString() + "] = {\n";

	for (var i = 0; i < warpEdges.length; ++i) {
		var ed = warpEdges[i];

		outFile += "\t" + Math.floor(ed.x).toString() + ", " + Math.floor(ed.y).toString() + ", " + 
						  Math.floor(ed.width).toString() + ", " + Math.floor(ed.height).toString() + ",\n";
	}

	outFile += "};\n\n";
}

// Write the struct declaration
outFile += "static const room_t " + mapName + " = {";
outFile += "\t.tilesetData = &" + mapTileset + ",\n";
outFile += "\t.paletteData = &" + mapPalette + ",\n";
outFile += "\t.planeWidth = " + planData.width + ",\n";
outFile += "\t.planeHeight = " + planData.height + ",\n";
outFile += "\t.planeData = " + mapName + "_" + planData.name + ",\n";

if (collisionEdges) {
	outFile += "\t.collisionBoxes = " + collisionEdges.length + ",\n";
	outFile += "\t.collisionData = " + mapName + "_collision_data" + ",\n";
} else {
	outFile += "\t.collisionBoxes = 0,\n";
	outFile += "\t.collisionData = NULL,\n";
}

if (warpEdges) {
	outFile += "\t.warpBoxes = " + warpEdges.length + ",\n";
	outFile += "\t.warpData = " + mapName + "_warp_data" + ",\n";
	outFile += "\t.warpTargetRooms = {\n";

	if (warpEdges[0]) {
		outFile += "\t\t" + warpEdges[0].properties.target_room + ",\n";
	} else {
		outFile += "\t\t0,\n";
	}

	if (warpEdges[1]) {
		outFile += "\t\t" + warpEdges[1].properties.target_room + ",\n";
	} else {
		outFile += "\t\t0,\n";
	}

	if (warpEdges[2]) {
		outFile += "\t\t" + warpEdges[2].properties.target_room + ",\n";
	} else {
		outFile += "\t\t0,\n";
	}

	if (warpEdges[3]) {
		outFile += "\t\t" + warpEdges[3].properties.target_room + ",\n";
	} else {
		outFile += "\t\t0,\n";
	}

	outFile += "\t},\n";
	outFile += "\t.warpTargetRoomsSpawn_x = {\n";

	if (warpEdges[0]) {
		outFile += "\t\t" + warpEdges[0].properties.target_room_spawn_x + ",\n";
	} else {
		outFile += "\t\t0,\n";
	}

	if (warpEdges[1]) {
		outFile += "\t\t" + warpEdges[1].properties.target_room_spawn_x + ",\n";
	} else {
		outFile += "\t\t0,\n";
	}

	if (warpEdges[2]) {
		outFile += "\t\t" + warpEdges[2].properties.target_room_spawn_x + ",\n";
	} else {
		outFile += "\t\t0,\n";
	}

	if (warpEdges[3]) {
		outFile += "\t\t" + warpEdges[3].properties.target_room_spawn_x + ",\n";
	} else {
		outFile += "\t\t0,\n";
	}

	outFile += "\t},\n";
	outFile += "\t.warpTargetRoomsSpawn_y = {\n";

	if (warpEdges[0]) {
		outFile += "\t\t" + warpEdges[0].properties.target_room_spawn_y + ",\n";
	} else {
		outFile += "\t\t0,\n";
	}

	if (warpEdges[1]) {
		outFile += "\t\t" + warpEdges[1].properties.target_room_spawn_y + ",\n";
	} else {
		outFile += "\t\t0,\n";
	}

	if (warpEdges[2]) {
		outFile += "\t\t" + warpEdges[2].properties.target_room_spawn_y + ",\n";
	} else {
		outFile += "\t\t0,\n";
	}

	if (warpEdges[3]) {
		outFile += "\t\t" + warpEdges[3].properties.target_room_spawn_y + ",\n";
	} else {
		outFile += "\t\t0,\n";
	}
	
	outFile += "\t},\n";
} else {
	outFile += "\t.warpBoxes = 0,\n";
	outFile += "\t.warpData = NULL,\n";
	outFile += "\t.warpTargetRooms = NULL,\n";
	outFile += "\t.warpTargetRoomsSpawn_x = NULL,\n";
	outFile += "\t.warpTargetRoomsSpawn_y = NULL\n";
}

outFile += "};\n\n";

outFile += "#endif // _" + mapName + "_\n";

fs.writeFileSync(outName, outFile);

