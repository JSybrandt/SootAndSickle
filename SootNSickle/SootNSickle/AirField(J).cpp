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

		ship.setCenter(shipStartLoc + shipPath*(1-(coolDown/AirFieldNS::TIME_PER_TRIP)));
	}
	else
		coolDown = 0;
}


void AirField::draw(VECTOR2 screenLoc)
{
	if(getActive())
	{
		Building::draw(screenLoc);
		if(getPower())
		{
			ship.draw(screenLoc);
		}	
	}
}

bool AirField::initialize(SootNSickle *gamePtr, int width, int height, int ncols,TextureManager *textureM,TextureManager* hbTexM,TextDX* infoText, TextureManager *shipTex)
{
	bool result = ship.initialize(gamePtr->getGraphics(),0,0,0,shipTex);
	return result && Building::initialize(gamePtr,width,height,ncols,textureM,hbTexM,infoText);
}

void AirField::create(VECTOR2 loc)
{
	Building::create(loc);
	coolDown = AirFieldNS::TIME_PER_TRIP;
	VECTOR2 shipEndLoc = VECTOR2(getX(),getY())+AirFieldNS::shipDisp;
	shipStartLoc.y = 4096;
	shipStartLoc.x = shipEndLoc.x;
	shipPath = shipEndLoc - shipStartLoc;
}

void AirField::setPower(bool b)
{
	if(getPower() && !b)
	{
		game->spawnParticleCloud(ship.getCenter(),graphicsNS::RED);
	}
	Building::setPower(b);
}