#include "Board.hpp"
#include "Hand.hpp"
#include <stdio.h>

//Eerste 4 bits, waarde, windrichting, draaksoort
//5e & 6e bits, soort (pinzu, manzu souzu, speciaal)
//7e bit dora (alleen bij 5)
//
//1

#define NUM_NORM_TILES 108
#define NUM_SPEC_TILES 28
#define NUM_TILES NUM_NORM_TILES + NUM_SPEC_TILES

std::vector<unsigned short>* start;
std::vector<unsigned short>* shuffled;

unsigned short make_normal_tile(int type, int value) {
	unsigned short ret = 0;

	if (type < 3) {
		ret += value;
		ret += (type << 4);
	}
	else {
		if (type == 3)
			ret += value;
		else
			ret += (value + 1) << 2;
		ret += 3 << 4;
	}
	return ret;
}

void fill(std::vector<unsigned short>* vector) {
	int t = 0;
	int v = 0;
	for (int i = 0; i < NUM_NORM_TILES; i++) {
		if (t < 3) {
			vector->push_back(make_normal_tile(t, (v % 9) + 1));
			vector->push_back(make_normal_tile(t, (v % 9) + 1));
			vector->push_back(make_normal_tile(t, (v % 9) + 1));
			vector->push_back(make_normal_tile(t, (v % 9) + 1));
			v++;
		}
		if (v % 9 == 0)
			t++;
	}
	v = 0;
	t = 3;
	for (int i = 0; i < NUM_NORM_TILES; i++) {
		vector->push_back(make_normal_tile(t, (v % 4)));
		vector->push_back(make_normal_tile(t, (v % 4)));
		vector->push_back(make_normal_tile(t, (v % 4)));
		vector->push_back(make_normal_tile(t, (v % 4)));
		v++;
		if (v % 4 == 0)
			t++;
	}
}

char tile_char(unsigned short tile) {
	char type;
	switch ((tile & (11 << 4)) >> 4) {
	case 0:
		type = 'p';
		break;
	case 1:
		type = 'm';
		break;
	case 2:
		type = 's';
		break;
	case 3:
		if ((tile & 0b1100) == 0)
			type = 'w';
		else
			type = 'd';
		break;
	default:
		type = 'u';
		break;
	}
	return type;
}

void print_tile(unsigned short tile) {
	printf("%c%u", tile_char(tile), tile & 0b1111);
}

//int main() {
//	start = new std::vector<unsigned short>();
//	shuffled = new std::vector<unsigned short>();
//
//	unsigned short test_tile = make_normal_tile(3, 0);
//	char test_char = tile_char(test_tile);
//
//	fill(start);
//	printf("[");
//	bool begin = 0;
//	for (int i = 0; i < NUM_TILES; i++) {
//		if (begin) {
//			printf(", ");
//		}
//		else
//			begin = 1;
//		print_tile(start->at(i));
//	}
//	return 0;
//}

int main() {
	Board* board = new Board();
	Hand* hand = new Hand();
	board->GenerateWall();
	//hand->AddTile((uint64)1 << (uint64)31);
	//hand->AddTile((uint64)1 << (uint64)32);
	//hand->AddTile((uint64)1 << (uint64)33);
	//hand->AddTile((uint64) 1 << (uint64) 31);
	hand->PrintHand();
	Board::PrintWall(board->GetWall());
	/*for (uint64 i = 1; i < (1ull << 63); i <<= 1ull) {
		Hand::PrintTile(i);
		printf(" ");
	}*/
	Board::PrintWallWithHand(board->GetWall());
	delete board;
}