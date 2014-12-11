#pragma once

#include "Building.h"

namespace AirFieldNS
{
	const int PEOPLE_PER_TRIP = 15;
	const int TIME_PER_TRIP = 20;
	const int CAPACITY = 15;
	const float RADIUS = 75;
	const float HEALTH = 60;

	const VECTOR2 shipDisp(112,70);
};


class AirField : public Building
{
private:
	float coolDown;
	Image ship;
	VECTOR2 shipStartLoc;
	VECTOR2 shipPath;
public:
	AirField():Building(){coolDown = 0; setCapacity(AirFieldNS::CAPACITY);setCollisionRadius(AirFieldNS::RADIUS); setMaxHealth(AirFieldNS::HEALTH);}
	void create(VECTOR2 loc);
	void update(float frameTime);
	void draw(VECTOR2 screenLoc);
	bool initialize(SootNSickle *gamePtr, int width, int height, int ncols,TextureManager *textureM,TextureManager* hbTexM,TextDX* infoText, TextureManager *shipTex);
	void setPower(bool b);
};