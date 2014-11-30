#pragma once

#include "ActorWithHealthBar.h"
#include "HealthBar.h"

//justin 

namespace BaseNS{
	const int SMOKE_PARTICLES_PER_FRAME = 3;
	const int MAX_EMBERS_PER_FRAME = 2;
	const float SMOKE_SPEED = 50;
	const float EMBER_SPEEED = 40;
	const float SMOKE_LIFETIME = 5;
	const float EMBER_LIFETIME = 6;
};

class Base:public ActorWithHealthBar{
public:
	Base(){maxHeath = 100;windDir = PI*1.3;}

	void update(float frameTime);
private:
	float windDir;

};
