#pragma once
#include"Actor.h"

class SootNSickle;

namespace cursorNS{
	const float ROTATION_SPEED = 2*PI;
};

class Cursor: public Actor
{
private:
	SootNSickle * game;
public:
	bool initialize(SootNSickle * game, int width, int height, int ncols, TextureManager *textureM);
	void update(float frametime);
};