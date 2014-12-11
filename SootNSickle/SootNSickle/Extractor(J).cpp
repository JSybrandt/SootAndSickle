#include "Extractor.h"
#include "sootnsickle.h"

void Extractor::create(VECTOR2 loc)
{
	Building::create(loc);
	minerals = nullptr;
	anythingNearby = true;
	setCapacity(ExtractorNS::CAPACITY);
}

void Extractor::update(float frameTime)
{
	if(getActive())
	{
		//i rewrite the building logic because i need to take into account minerals
		ActorWithHealthBar::update(frameTime);
		if(anythingNearby&&getPower())
		{
			if(game->getIdlePop() > 0 && getStaff() < getCapacity())
			{
				modifyStaff(1);
				game->removeIdlePop(1);
			}
		}
		else if(getStaff() > 0)
		{
			modifyStaff(-1);
			game->addIdlePop(1);
		}

		if(getPower())
		{
			game->spawnParticleCloud(getCenter(),graphicsNS::GRAY,1);
			if(anythingNearby)
			{
				if(minerals==nullptr||!minerals->getActive())
					minerals=game->findMineableMinerals(this);
					if(minerals==nullptr)
						anythingNearby = false;
				else
				{
					game->addMinerals(minerals->mine(ExtractorNS::DEFAULT_MINING_RATE*frameTime*getEffectiveness()));
					game->spawnParticleCloud(getCenter(),graphicsNS::CYAN,1);
				}
			}

		}
	}
}

//void Extractor::draw(VECTOR2 screenLoc){
//
//	if(getActive())
//	{
//	ActorWithHealthBar::draw(screenLoc);
//
//		if(getCapacity() > 0 )
//			{
//				RECT textRect;
//				//set text rect to be below the image
//				textRect.top = getY()+getHeight()-screenLoc.y;
//				textRect.left = getX()-screenLoc.x;
//				textRect.right = textRect.left + getWidth();
//				textRect.bottom = textRect.top +20;
//		
//				getText()->print(std::to_string(getStaff())+"/"+std::to_string(getCapacity()),textRect,DT_CENTER|DT_VCENTER);
//			}
//	}
//}