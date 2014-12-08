#include "Extractor.h"
#include "sootnsickle.h"

void Extractor::create(VECTOR2 loc)
{
	hasPower = false;
	setCenter(loc);
	setActive(true);
	minerals = nullptr;
	anythingNearby = true;
}

void Extractor::update(float frameTime)
{
	if(getActive())
	{
		ActorWithHealthBar::update(frameTime);
		if(hasPower)
		{
			game->spawnParticleCloud(getCenter(),graphicsNS::GRAY,1);
			if(anythingNearby)
			{
				if(minerals==nullptr)
					minerals=game->findMineableMinerals(this);
					if(minerals==nullptr)
						anythingNearby = false;
				else
				{
					game->addMinerals(minerals->mine(ExtractorNS::DEFAULT_MINING_RATE*frameTime));
					game->spawnParticleCloud(getCenter(),graphicsNS::CYAN,1);
				}
			}

		}
	}
}