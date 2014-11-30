#include "Base.h"
#include "sootnsickle.h"

using namespace BaseNS;
void Base::update(float frameTime)
{
	
	for(int i = 0 ; i < SMOKE_PARTICLES_PER_FRAME;i++)
	{
		float dir = (utilityNS::rand01()-0.5)*PI*0.4 + windDir;
		VECTOR2 smokeVel(SMOKE_SPEED,0);
		smokeVel = utilityNS::rotateVector(smokeVel,dir);
		game->spawnParticle(getCenter(),smokeVel,graphicsNS::GRAY,SMOKE_LIFETIME);
	}

	int numEmbers = rand()%MAX_EMBERS_PER_FRAME;

	for(int i = 0; i < numEmbers; i++)
	{
		float dir = (utilityNS::rand01()-0.5)*PI*0.2 + windDir;
		VECTOR2 emberVel(EMBER_SPEEED,0);
		emberVel = utilityNS::rotateVector(emberVel,dir);
		game->spawnParticle(getCenter(),emberVel,graphicsNS::RED,EMBER_LIFETIME,true);
	}


	ActorWithHealthBar::update(frameTime);

}