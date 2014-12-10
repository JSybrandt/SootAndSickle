#pragma once

#include "Building.h"

namespace FactoryNS{
	const int DEFAULT_CAPACITY = 15;
	const int TEXT_RECT_HEIGHT = 25;
	const int HEALTH = 80;
	const int SECONDS_PER_POINT = 20;
};

class Factory : public Building
{
private:
public:

	Factory():Building(){setMaxHealth(FactoryNS::HEALTH);}

	void update(float frameTime);

	void create(VECTOR2 loc){Building::create(loc);setCapacity(FactoryNS::DEFAULT_CAPACITY);}
};