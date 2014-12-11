#pragma once

#include "ActorWithHealthBar.h"
#include "textDX.h"


namespace BuildingNS{
	const int DEFAULT_CAPACITY = 10;
	const float RADIUS = 50;
};

class Building : public ActorWithHealthBar{

private:
	TextDX* text;
	int numStaff, capacity;
	bool hasPower;
	int level;
public:
	Building():ActorWithHealthBar(){setActive(false); setCapacity(BuildingNS::DEFAULT_CAPACITY);setStaff(0);setPower(false);setCollisionRadius(BuildingNS::RADIUS);level = 1;}
	bool initialize(SootNSickle *gamePtr, int width, int height, int ncols,TextureManager *textureM,TextureManager* hbTexM,TextDX* infoText);
	void draw(VECTOR2 screenLoc);
	void update(float frameTime);
	void create(VECTOR2 loc);

	bool getPower(){return hasPower&&powerToggle;}
	virtual void setPower(bool n){hasPower = n;}

	int getStaff(){return numStaff;}
	void setStaff(int n){numStaff = min(capacity,max(0,n));}
	void setCapacity(int n){capacity = max(0,n);}
	void modifyStaff(int n){numStaff += n; min(capacity,max(0,numStaff));}
	int getCapacity(){return capacity;}

	float getEffectiveness(){ 
		if(getCapacity()>0)
			return (getStaff()/((float)getCapacity()))*(getLevel()+(getLevel()-1)*1.25);
		else
			return (getLevel()+(getLevel()-1)*1.25);
	}

	virtual void upgrade(){
		level = min(level+1,3);
		setMaxHealth(getMaxHealth()*1.2);
		setHealth(getMaxHealth());
	}
	int getLevel(){return level;}

	void onDeath();

	TextDX* getText(){return text;}

	bool powerToggle;
};