#include"ActorWithHealthBar.h"

#include "sootnsickle.h"

using namespace ActorWithHealthBarNS;

bool ActorWithHealthBar::initialize(SootNSickle *gamePtr, int width, int height, int ncols,TextureManager *textureM,TextureManager* hbTexM)
{
	bool result=true;
	game = gamePtr;
	result = result && healthBar.initialize(gamePtr,HealthBarNS::WIDTH,HealthBarNS::HEIGHT,1,hbTexM);
	result = result && Actor::initialize(gamePtr,width,height,ncols,textureM);
	isHealthBarVisible = true;
	return result;
}

void ActorWithHealthBar::draw(VECTOR2 screenLoc)
{
	if(getActive()){
		Actor::draw(screenLoc);
		if(isHealthBarVisible)
			healthBar.draw(screenLoc);
	}
}


void ActorWithHealthBar::update(float frameTime)
{
	if(getActive()){
		healthBar.setCenter(VECTOR2(getCenterX(),getY()-BAR_OFFSET));
		Actor::update(frameTime);
	}
}

void ActorWithHealthBar::damage(float ammount)
{
	if(ammount > 0)
	{
		health -= ammount;
		if(health < 0) {health = 0;
			onDeath();
			setActive(false);
		}
	}
	healthBar.setCurrentValue(health);
}

void ActorWithHealthBar::heal(float ammount)
{
	if(ammount > 0)
	{
		health += ammount;
		if(health > maxHealth) health = maxHealth;
	}
	healthBar.setCurrentValue(health);
}

void ActorWithHealthBar::setMaxHealth(float val)
{
	if(val > 0)
	{
		maxHealth = val;
		if(health > maxHealth) health = maxHealth;
		healthBar.setMaxValue(maxHealth);
		healthBar.setCurrentValue(health);
	}
}
