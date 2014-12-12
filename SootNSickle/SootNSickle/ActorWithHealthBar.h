#pragma once

#include "Actor.h"
#include "HealthBar.h"

class SootNSickle;

namespace ActorWithHealthBarNS{
	const float BAR_OFFSET = 20;
};

class ActorWithHealthBar:public Actor
{
public:
	ActorWithHealthBar():Actor(){maxHealth=100;healthBar.setMaxValue(100); damageType = GROUND;}
	bool initialize(SootNSickle *gamePtr, int width, int height, int ncols,TextureManager *textureM,TextureManager* hbTexM);
	void draw(VECTOR2 screenLoc);
	void damage(float ammount);
	void heal(float ammount);
	virtual void setMaxHealth(float val);
	float getMaxHealth(){return maxHealth;}
	void  setHealth(float n){health = min(maxHealth,max(0,n)); healthBar.setCurrentValue(health);}
	void update(float frameTime);
	bool isHealthBarVisible;
private:
	HealthBar healthBar;
	float maxHealth;
	virtual void onDeath(){};
protected:
	SootNSickle* game;
	WEAPON damageType;
	
};