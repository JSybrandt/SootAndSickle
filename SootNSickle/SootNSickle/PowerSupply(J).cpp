#include"PowerSupply.h"
#include"sootnsickle.h"
using namespace PowerSupplyNS;

PowerSupply::PowerSupply()
{
	Building::Building();
	setActive(false);
	setCollisionRadius(BUILDING_RADIUS);
	setPower(false);
	bootCooldown = 0;

	setCapacity(0);

	setMaxHealth(HEALTH);
}

void PowerSupply::update(float frameTime)
{
	if(getActive())
	{
		Building::update(frameTime);

		if(getPower()&&bootCooldown>0){
			bootCooldown -= frameTime;
			if(bootCooldown<0)
				bootCooldown=0;
			field.setColorFilter(Graphics::calculateAlpha((BOOT_TIME-bootCooldown)/BOOT_TIME));
		}

		if(getPower()){
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

bool PowerSupply::initialize(SootNSickle *gamePtr, int width, int height, int ncols,TextureManager *textureM,TextureManager* hbTexM,TextureManager* pwrTex, TextDX * text)
{
	bool res = field.initialize(gamePtr,0,0,0,pwrTex);
	field.setFieldRadius(POWER_RADIUS);
	return res&Building::initialize(gamePtr,width,height,ncols,textureM,hbTexM,text);
}

void PowerSupply::create(VECTOR2 loc)
{
	Building::create(loc);
	field.setCenter(loc);
	setHealth(100);
	bootCooldown = BOOT_TIME;
	field.setColorFilter(Graphics::calculateAlpha(0));
}