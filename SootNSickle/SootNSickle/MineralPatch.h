#pragma once

#include "Actor.h"



class MineralPatch : public Actor
{
private:
	float mineralLevel;
public:
	MineralPatch(){setActive(false);}
	void create(VECTOR2 loc, float ammount){
		setActive(true);
		setCenter(loc);
		mineralLevel = ammount;
	}
	void setMineralLevel(float n){if(n>0)mineralLevel > n;}
	float mine(float requestedAmmount){
		if(mineralLevel > requestedAmmount) 
		{
			mineralLevel -= requestedAmmount;
			return requestedAmmount;
		}
		else
		{
			float t = mineralLevel;
			mineralLevel = 0;
			setActive(false);
			return t;
		}
	}
};