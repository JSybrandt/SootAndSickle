#include"Cursor.h"
#include "SootNSickle.h"
bool Cursor::initialize(SootNSickle * g, int width, int height, int ncols, TextureManager *textureM)
{
	game = g;
	return Actor::initialize(g,width,height,ncols,textureM);
}

void Cursor::update(float frametime)	
{
	setRadians(getRadians()+(cursorNS::ROTATION_SPEED*frametime));
	setCenter(game->getMouseInWorld());
}