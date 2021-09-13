#pragma once

#include <vector>
#include "DataTypes.hpp"

#define NUM_NORM_TILES 108
#define NUM_SPEC_TILES 28
#define NUM_TILES (NUM_NORM_TILES + NUM_SPEC_TILES)

#define TILE_OFFSET_TYPE 4
#define TILE_OFFSET_DRAGON 2
#define TILE_OFFSET_WIND 0

#define TILE_MASK_DRAGON 0b1100
#define TILE_MASK_WIND 0b11
#define TILE_MASK_NORMAL 0b1111
#define TILE_MASK_TYPE (0b11 << TILE_OFFSET_TYPE)
#define TILE_MASK_TYPE_PINZU (0b00 << TILE_OFFSET_TYPE)
#define TILE_MASK_TYPE_MANZU (0b01 << TILE_OFFSET_TYPE)
#define TILE_MASK_TYPE_SOUZU (0b10 << TILE_OFFSET_TYPE)
#define TILE_MASK_TYPE_JIHAI (0b11 << TILE_OFFSET_TYPE)

typedef byte Tile;
typedef std::vector<Tile> Wall;

class Board {

	Wall* m_Wall;

public:
	Board();

	Board(Wall* wall);

	void GenerateWall();

	Tile PullNext();

	Tile PullBlind();

	static void PrintWall(const Wall* wall);

	static void PrintWallWithHand(const Wall* wall);

	static uint64 ConvertToHandTile(Tile tile);

	inline const Wall* GetWall() const { return m_Wall; }

private:
	Wall* GenerateClean() const;

	Tile GetTile(int type, int value) const;

	static void PrintTile(Tile tile);
};