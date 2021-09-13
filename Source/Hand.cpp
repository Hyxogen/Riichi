#include "Hand.hpp"
#include <cstring>
#include <stdio.h>

Hand::Hand() {
	memset(m_Hand, 0, 4 * sizeof(uint64));
}

int32 Hand::HasTile(uint64 tile) const {
	return GetTileBitSet(tile) & TILE_MASK_VAL;
}

bool Hand::DiscardTile(uint64 tile) { // Deze werkt niet zo goed
	char pos = HasTileQuick(tile);
	if (pos < 0)
		return true;
	byte bitset = GetTileBitSet(tile);
	if ((bitset & TILE_MASK_VAL) == 0)
		return true;
	SetTileBitSet(tile, bitset - 1);
	return false;
}

bool Hand::AddTile(uint64 tile) {
	char pos = GetEmptyPos(tile);
	if (pos < 0)
		return true;
	byte bitset = GetTileBitSet(tile);
	if ((bitset & TILE_MASK_DORA) == 0 && (bitset & TILE_MASK_VAL) > 3)
		return true;
	SetTileBitSet(tile, bitset + 1);
	//m_Hand[pos] ^= tile;
	return false;
}

//First wind, then dragons
void Hand::PrintHand() const {
	char temp = 0;
	uint64 tile = 1;
	printf("[");
	for (int32 t = 0; t < 5; t++) {
		if (t < 3) {
			for (int32 v = 1; v <= 9; v++) {
				temp = HasTile(tile);
				while (temp--)
					printf("%s%d ", t == 0 ? ("P") : (t == 1 ? ("M") : "S"), v);
				tile <<= 1;
			}
		} else {
			for (int32 v = 0; v < 4; v++) {
				if (t == 4 && v == 3)
					break;
				temp = HasTile(tile);
				while (temp--)
					printf("%s%d ", t == 3 ? "W" : "D", v);
				tile <<= 1;
			}
		}
	}
	printf("]\n");
}

char Hand::HasTileQuick(uint64 tile) const { //Deze kan miss inline
	byte temp = GetTileBitSet(tile);
	temp = temp & 0b001 ? (1) : (temp & 0b010 ? (2) : (temp & 0b100 ? (3) : (-1)));
	return (char) temp;
}

char Hand::GetEmptyPos(uint64 tile) const { //Deze kan miss inline
	byte temp = GetTileBitSet(tile);
	//temp <<= ((temp & 0b001) == 0) ? (1) : (((temp & 0b010) == 0 ? (2) : ((temp == 0) & 0b100 ? (3) : (-1)));
	//temp = (temp & 0b001) == 0 ? 1 : ((temp & 0b010) == 0 ? 2 : ((temp & 0b100) == 0) ? 3 : -1);
	temp = (temp & 0b001) == 0 ? 3 : ((temp & 0b010) == 0 ? 2 : ((temp & 0b100) == 0) ? 1 : -1);
	return (char) temp;
}

byte Hand::GetTileBitSet(uint64 tile) const { //Dit kan wss naar een line zodat het in een inline kan, miss kan het zelfs in een define
	byte ret = 0;

	ret ^= (m_Hand[3] & tile) != 0;
	ret ^= ((m_Hand[2] & tile) != 0) << 1;
	ret ^= ((m_Hand[1] & tile) != 0) << 2;
	ret ^= ((m_Hand[0] & tile) != 0) << 3;
	return ret;
}

//Wordt niet op de goede plek neergezet voor waardes groter dan 1 (of meerdere keer 1 neerzetten)
void Hand::SetTileBitSet(uint64 tile, byte bitset) {
	m_Hand[0] &= ~tile;
	m_Hand[1] &= ~tile;
	m_Hand[2] &= ~tile;
	m_Hand[3] &= ~tile;
	m_Hand[0] ^= ((bitset & 0b1000) >> 3) * tile;
	m_Hand[1] ^= ((bitset & 0b0100) >> 2) * tile;
	m_Hand[2] ^= ((bitset & 0b0010) >> 1) * tile;
	m_Hand[3] ^= ((bitset & 0b0001) >> 0) * tile;
}
