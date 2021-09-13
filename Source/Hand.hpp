#pragma once

#include "DataTypes.hpp"

#define HAND_TILE_MASK_VAL 0b0111
#define HAND_TILE_MASK_DORA 0b1000
#define HAND_TILE_UNIQUE_COUNT 34 // Klopt niet, hoort 34 te zijn

#define HAND_TILE_START_PINZU 0b1Ull
#define HAND_TILE_START_MANZU (HAND_TILE_START_PINZU << 9Ull)
#define HAND_TILE_START_SOUZU (HAND_TILE_START_MANZU << 9Ull)
#define HAND_TILE_START_WINDS (HAND_TILE_START_SOUZU << 9Ull)
#define HAND_TILE_START_DRAGONS (HAND_TILE_START_WINDS << 4Ull)

#define HAND_TILE_MASK_PINZU 0b111111111Ull
#define HAND_TILE_MASK_MANZU (HAND_TILE_MASK_PINZU << 9Ull)
#define HAND_TILE_MASK_SOUZU (HAND_TILE_MASK_MANZU << 9Ull)
#define HAND_TILE_MASK_WINDS (0b1111Ull << (3Ull * 9Ull))
#define HAND_TILE_MASK_DRAGONS (0b111Ull << ((3Ull * 9Ull) + 4Ull))

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

	static void PrintTile(uint64 tile);

private:
	//Returns -1 if not found, otherwise returns the index of first found in m_Hand + 1 (because of dora)
	char HasTileQuick(uint64 tile) const;

	char GetEmptyPos(uint64 tile) const;

	byte GetTileBitSet(uint64 tile) const;

	void SetTileBitSet(uint64 tile, byte bitset);
};