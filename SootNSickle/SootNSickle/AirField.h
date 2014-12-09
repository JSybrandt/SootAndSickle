#pragma once

#include "Building.h"

namespace AirFieldNS
{
	const int PEOPLE_PER_TRIP = 15;
	const int TIME_PER_TRIP = 20;
	const int CAPACITY = 15;
	const float RADIUS = 75;
};


class AirField : public Building
{
private:
	float coolDown;
public:
	AirField():Building(){coolDown = 0; setCapacity(AirFieldNS::CAPACITY);setCollisionRadius(AirFieldNS::RADIUS);}
	void create(VECTOR2 loc){Building::create(loc); coolDown = AirFieldNS::TIME_PER_TRIP;}
	void update(float frameTime);
};