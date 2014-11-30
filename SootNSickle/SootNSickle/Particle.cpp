#include "Particle.h"

Particle::Particle():Actor()
{
	setActive(false);
	setRadians(utilityNS::rand01()*2*PI);
}

void Particle::update(float frametime)
{
	if(getActive())
	{
		age += frametime;
		if(age>=lifespan) 
			active = false;
		setCenter(getCenter()+frametime*velocity);

	}
}

void Particle::draw(VECTOR2 screenLoc)
{
	if(getActive())
	{
		COLOR_ARGB c;
		if(reverseFade)
			c = Graphics::calculateAlpha(age/lifespan)&colorFilter;
		else
			c = Graphics::calculateAlpha(1-(age/lifespan))&colorFilter;
		Actor::draw(screenLoc,c);
	}
}


void Particle::create(VECTOR2 loc,VECTOR2 vel, COLOR_ARGB c,float lifespan,bool reverseFade)
{

	setActive(true);
	age = utilityNS::rand01()*(lifespan/2);
	setCenter(loc);
	setVelocity(vel);
	setColorFilter(c);
	this->lifespan = lifespan;
	this->reverseFade = reverseFade;

}