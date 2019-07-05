#pragma once

#define allChunks 64
#define drawedChunks 5
#define PI 3.14159f
#define NUMBLOCKS 23
#define NUMNOTBLOCKS 9
#define NUMINSTRUMENTS 3
#define STARTNOTBLOCKS 64
#define STARTINSTRUMENTS 100

enum blocktype{AIR, GRASS, DIRT, STONE, LOG, LEAVE, SAND, PLANK, WBENCH, STONEBRICKS, CLAY, IRONORE, COALORE, COPPERORE, DIAMONDORE, GOLDORE, GLASS, BRICKS, BACKEDCLAY, FURNACE, EMERALDORE, CACTUS, MELON, ENDSTONE };
float const breakingTimes[] = {0, 0.75, 0.75, 2, 2, 0.3, 0.5, 0.75, 2,	 2,			  0.75,    6,		 4,		  5,		 8,			 6,		  1,	 4,		 3,			 4,		  6,		  1,	  2,	 -1};
enum notBlocktype{COAL = STARTNOTBLOCKS, IRONINGOT, COPPERINGOT, GOLDINGOT, DIAMOND, EMERALD, CLAYPIECE, STICK, BRICK};
enum instrumentType {WOODENSWORD = STARTINSTRUMENTS, WOODENAXE, WOODENPICKAXE};
typedef struct slot {
	int id;
	int num;
} slot;