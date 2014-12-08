#include"PowerSupply.h"
#include"sootnsickle.h"
using namespace PowerSupplyNS;

PowerSupply::PowerSupply()
{
	setActive(false);
	setCollisionRadius(BUILDING_RADIUS);
	setPower(false);
	bootCooldown = 0;
}

void PowerSupply::update(float frameTime)
{
	if(getActive())
	{
		ActorWithHealthBar::update(frameTime);

		if(hasPower&&bootCooldown>0){
			bootCooldown -= frameTime;
			if(bootCooldown<0)
				bootCooldown=0;
			field.setColorFilter(Graphics::calculateAlpha((BOOT_TIME-bootCooldown)/BOOT_TIME));
		}

		if(hasPower){
			game->spawnParticleCloud(getCenter(),graphicsNS::CYAN,1);
			game->spawnParticleCloud(getCenter(),graphicsNS::YELLOW,1);
		}
	}
}

//void PowerSupply::draw(VECTOR2 screenLoc)
//{
//	if(getActive())
//	{
//		field.draw(screenLoc);
//		ActorWithHealthBar::draw(screenLoc);
//	}
//}

bool PowerSupply::initialize(SootNSickle *gamePtr, int width, int height, int ncols,TextureManager *textureM,TextureManager* hbTexM,TextureManager* pwrTex)
{
	bool res = field.initialize(gamePtr,0,0,0,pwrTex);
	field.setFieldRadius(POWER_RADIUS);
	return res&ActorWithHealthBar::initialize(gamePtr,width,height,ncols,textureM,hbTexM);
}

void PowerSupply::create(VECTOR2 loc)
{
	setActive(true);
	setCenter(loc);
	field.setCenter(loc);
	setHealth(100);
	bootCooldown = BOOT_TIME;
	field.setColorFilter(Graphics::calculateAlpha(0));
}