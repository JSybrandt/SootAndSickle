#include "Waypoint.h"

Waypoint::Waypoint():Actor()
{
	parent = nullptr;
	child = nullptr;
	setActive(false);

}

void Waypoint::update(float frametime)
{
	if(getActive())
	{
		

	}
}

void Waypoint::draw(VECTOR2 screenLoc)
{
	if(getActive())
	{
		Actor::draw(screenLoc);
	}
}


void Waypoint::create(VECTOR2 loc, COLOR_ARGB c)
{
	setActive(true);
	setCenter(loc);
	setVelocity(VECTOR2(0,0));
	setColorFilter(c);
}