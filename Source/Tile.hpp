#pragma once
#include "DataTypes.hpp"

struct Tile {

	enum Type {
		PINZU,
		MANZU,
		SOUZU,
		DRAGON,
		WIND,
		UNKOWN
	};

	enum TileValue : byte {
		VAL_ONE			= 1,
		VAL_TWO			= 2,
		VAL_THREE		= 3,
		VAL_FOUR		= 4,
		VAL_FIVE		= 5,
		VAL_SIX			= 6,
		VAL_SEVEN		= 7,
		VAL_EIGHT		= 8,
		VAL_NINE		= 9,
		WIND_EAST		= 1,
		WIND_SOUTH		= 2,
		WIND_WEST		= 3,
		WIND_NORTH		= 4,
		DRAGON_RED		= 1,
		DRAGON_GREEN	= 2,
		DRAGON_WHITE	= 3,
		UNKOWN
	};

	static byte MakeTile(Type type, TileValue value);

	static Type GetType(Tile tile);

	static Type GetType(byte byte);


};