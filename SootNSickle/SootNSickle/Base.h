#pragma once

#include "ActorWithHealthBar.h"
#include "PowerField.h"

//justin 

namespace BaseNS{
	const int SMOKE_PARTICLES_PER_FRAME = 3;
	const int MAX_EMBERS_PER_FRAME = 2;
	const float SMOKE_SPEED = 50;
	const float EMBER_SPEEED = 40;
	const float SMOKE_LIFETIME = 5;
	const float EMBER_LIFETIME = 6;
	const float BASE_POWER_RADIUS = 300;
	const float BUILDING_RADIUS = 75;
};

class Base:public ActorWithHealthBar{
public:
	Base(){maxHeath = 100;windDir = PI*1.3; setCollisionRadius(BaseNS::BUILDING_RADIUS);}

	void update(float frameTime);

	PowerField & getPowerField(){return field;}

	bool initialize(SootNSickle *gamePtr, int width, int height, int ncols,TextureManager *textureM,TextureManager* hbTexM,TextureManager* pwrTex);

	void setActive(bool b){field.setActive(b);ActorWithHealthBar::setActive(b);}
	//void draw(VECTOR2 screenLoc);

private:
	float windDir;

	PowerField field;

};
