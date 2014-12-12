#pragma once

#include "Building.h"
#include "PowerField.h"

//justin 

namespace BaseNS{
	const int SMOKE_PARTICLES_PER_FRAME = 3;
	const int MAX_EMBERS_PER_FRAME = 2;
	const float SMOKE_SPEED = 50;
	const float EMBER_SPEEED = 40;
	const float SMOKE_LIFETIME = 5;
	const float EMBER_LIFETIME = 6;
	const float BASE_POWER_RADIUS = 400;
	const float BUILDING_RADIUS = 75;
	const float TELEPORTER_COOLDOWN = 30;
	const int PEOPLE_PER_DELIVERY = 5;
	const int HOUSING = 25;
};

class Base:public Building{
public:
	Base(){setMaxHealth(100);windDir = PI*1.3; setCollisionRadius(BaseNS::BUILDING_RADIUS);setCapacity(0);}

	void update(float frameTime);

	PowerField & getPowerField(){return field;}

	bool initialize(SootNSickle *gamePtr, int width, int height, int ncols,TextureManager *textureM,TextureManager* hbTexM,TextureManager* pwrTex, TextDX* infoText);

	void create(VECTOR2 loc){Building::create(loc);	field.setActive(true); field.setCenter(loc);cooldown = BaseNS::TELEPORTER_COOLDOWN;}

	void onDeath();
private:
	float windDir;
	float cooldown;
	PowerField field;

};
