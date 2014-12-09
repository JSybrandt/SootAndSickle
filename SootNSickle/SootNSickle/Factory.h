#pragma once

#include "Building.h"

namespace FactoryNS{
	const int DEFAULT_CAPACITY = 15;
	const int TEXT_RECT_HEIGHT = 25;
};

class Factory : public Building
{
private:
public:

	void update(float frameTime);

	void create(VECTOR2 loc){Building::create(loc);setCapacity(FactoryNS::DEFAULT_CAPACITY);}
};