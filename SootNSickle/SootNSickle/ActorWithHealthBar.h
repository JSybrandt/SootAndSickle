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
	bool initialize(SootNSickle *gamePtr, int width, int height, int ncols,TextureManager *textureM,TextureManager* hbTexM);
	void draw(VECTOR2 screenLoc);
	void damage(float ammount);
	void heal(float ammount);
	void setMaxHealth(float val);
	void update(float frameTime);
	bool isHealthBarVisible;
protected:
	HealthBar healthBar;
	float maxHeath;

	SootNSickle* game;
	
};