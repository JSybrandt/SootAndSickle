#pragma once

#include "Actor.h"

namespace PowerFieldNS{
	const float DEFAULT_RADIUS = 256;
};

class PowerField: public Actor
{
private:
	
public:
	PowerField(){setActive(false);setCollisionRadius(PowerFieldNS::DEFAULT_RADIUS);}
	void setFieldRadius(float n){
		VECTOR2 trueCenter = getCenter();
		setScale(n/PowerFieldNS::DEFAULT_RADIUS);
		setCenter(trueCenter);
	}

};