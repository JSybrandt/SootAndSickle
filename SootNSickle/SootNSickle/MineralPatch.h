#pragma once

#include "Actor.h"
#include "textDX.h"

namespace MineralNS{
	const int DEFAULT_MINERALS = 2000;
};

class MineralPatch : public Actor
{
private:
	float mineralLevel;
	TextDX* text;
public:
	MineralPatch();
	void setMineralLevel(float n);
	float mine(float requestedAmmount);
	void create(VECTOR2 loc, float ammount);
	bool initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM, TextDX *text);
	void draw(VECTOR2 screenLoc);

	
};