#include "Factory.h"

#include "sootnsickle.h"

void Factory::update(float frameTime)
{
	if(getActive())
	{
		Building::update(frameTime);

		game->upgradePoints+=(frameTime/FactoryNS::SECONDS_PER_POINT)*getEffectiveness();
		//TODO:link into stuff
	}
}
