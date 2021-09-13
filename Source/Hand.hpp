#pragma once

#include "DataTypes.hpp"

#define TILE_MASK_VAL 0b0111
#define TILE_MASK_DORA 0b1000
#define TILE_UNIQUE_COUNT 55

class Hand {

	//Zero is the highest bit, 3 is the lowest bit
	//Zero is used for the dora indicator
	//This should kind of be seen as one big 256 bit int, where 4 bits are reserved for each tile
	uint64_t m_Hand[4];

public:
	Hand();

	//Returns the count of the tile in the hand
	int32 HasTile(uint64 tile) const;

	//Returns false if no errors ocurred
	bool DiscardTile(uint64 tile);

	//Returns false if no errors ocurred
	bool AddTile(uint64 tile);

	void PrintHand() const;

private:
	//Returns -1 if not found, otherwise returns the index of first found in m_Hand + 1 (because of dora)
	char HasTileQuick(uint64 tile) const;

	char GetEmptyPos(uint64 tile) const;

	byte GetTileBitSet(uint64 tile) const;

	void SetTileBitSet(uint64 tile, byte bitset);
};