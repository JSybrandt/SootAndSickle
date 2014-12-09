#include"AirField.h"
#include"sootnsickle.h"

void AirField::update(float frameTime)
{
	Building::update(frameTime);
	if(getPower())
	{
		if(coolDown<=0)
		{
			coolDown = AirFieldNS::TIME_PER_TRIP;
			game->addPopulation(AirFieldNS::PEOPLE_PER_TRIP);
		}
		coolDown -= getEffectiveness() * frameTime;
	}
}