#include "Base.h"
#include "sootnsickle.h"

using namespace BaseNS;
void Base::update(float frameTime)
{
	if(getActive()){

		Building::update(frameTime);

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


		cooldown-=frameTime;
		if(cooldown <= 0 )
		{
			cooldown = BaseNS::TELEPORTER_COOLDOWN;
			game->addPopulation(BaseNS::PEOPLE_PER_DELIVERY);
		}
		
	}
}

//void Base::draw(VECTOR2 screenLoc)
//{
//	if(getActive())
//	{
//		field.draw(screenLoc);
//		ActorWithHealthBar::draw(screenLoc);
//	}
//}

bool Base::initialize(SootNSickle *gamePtr, int width, int height, int ncols,TextureManager *textureM,TextureManager* hbTexM,TextureManager* pwrTex)
{
	bool res = field.initialize(gamePtr,0,0,0,pwrTex);
	field.setFieldRadius(BASE_POWER_RADIUS);
	return res&ActorWithHealthBar::initialize(gamePtr,width,height,ncols,textureM,hbTexM);
}