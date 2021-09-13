#include "Board.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Board::Board() : m_Wall(new Wall()) {

}

Board::Board(Wall* wall) : m_Wall(wall) {

}

/*
[m4, w2, s7, s3, p8, w0, p2, m2, m9, p1, s2, s5, s9, s7, p6, d4, m2, s8, s9, p5, s5, w3, p4, w3, s8, s2, m7, w0, s1, w2, d8, m5, p6, p9, p5, d8, s3, m3, m8, w3, p3, p7, w1, s7, s9, s9, d8, s4, p4, m4, m1, m8, m6, m9, p2, p4, w0, p7, p2, p1, s4, m8, s6, s3, s3, p2, p3, s4, m9, m7, d12, d12, p9, p3, m6, m5, m5, d8, m2, s5, m4, s2, m1, p1, p8, s8, m3, m7, w2, m9, m4, p7, s1, p6, p8, p3, m5, s2, s6, s8, m7, m1, w1, p9, m8, w1, s6, p7, m6, w2, d4, m3, s1, p4, d4, s5, m2, s4, p5, s6, p1, m1, p8, p9, w3, w1, p6, p5, w0, m3, m6, s7, d12, s1, d4, d12]
*/

void Board::GenerateWall() {
	Wall* temp = GenerateClean();
	short size = NUM_TILES;
	int ran_val;

	srand(time(NULL));
	while (size--) {
		ran_val = rand();
		if (size) {
			//unsigned short val = temp->at(ran_val % size);
			m_Wall->push_back(temp->at(ran_val % size));
			//Wall::iterator oval = temp->begin() + (ran_val % size);
			//Tile tile = (Tile)*oval;
			temp->erase(temp->begin() + (ran_val % size));
		}
		else
			m_Wall->push_back(temp->at(0));
	}

	delete temp;
}

void Board::PrintWall(const Wall* wall) {
	bool start = 1;
	printf("[");
	for (int i = 0; i < NUM_TILES; i++) {
		if (!start)
			printf(", ");
		else
			start = 0;
		PrintTile(wall->at(i));
	}
	printf("]\n");
}

Wall* Board::GenerateClean() const {
	Wall* ret = new Wall();
	int t, i;
	Tile temp;

	for (t = 0; t < 3; t++) {
		for (i = 1; i <= 9; i++) {
			temp = GetTile(t, i);
			ret->push_back(temp);
			ret->push_back(temp);
			ret->push_back(temp);
			ret->push_back(temp);
		}
	}

	for (t = 3; t <= 4; t++) {
		for (i = 0; i < (t == 3 ? 4 : 3); i++) {
			temp = GetTile(t, i);
			ret->push_back(temp);
			ret->push_back(temp);
			ret->push_back(temp);
			ret->push_back(temp);
		}
	}
	return ret;
}

Tile Board::GetTile(int type, int value) const {
	Tile ret = 0;

	if (type < 3) {
		ret += value;
		ret += (type << 4);
	} else {
		if (type == 3)
			ret += value;
		else
			ret += (value + 1) << 2;
		ret += 3 << 4;
	}
	return ret;
}

void Board::PrintTile(Tile tile) {
	switch (tile & TILE_MASK_TYPE) {
	case TILE_MASK_TYPE_PINZU:
		printf("p%u", tile & TILE_MASK_NORMAL);
		break;
	case TILE_MASK_TYPE_MANZU:
		printf("m%u", tile & TILE_MASK_NORMAL);
		break;
	case TILE_MASK_TYPE_SOUZU:
		printf("s%u", tile & TILE_MASK_NORMAL);
		break;
	case TILE_MASK_TYPE_JIHAI:
		if (tile & TILE_MASK_DRAGON)
			printf("d%u", tile & TILE_MASK_DRAGON);
		else
			printf("w%u", tile & TILE_MASK_WIND);
		break;
	default:
		printf("UNK");
		break;
	}
}