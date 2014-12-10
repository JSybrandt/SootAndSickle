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
public:
	Building(){setActive(false); setCapacity(BuildingNS::DEFAULT_CAPACITY);setStaff(0);setPower(false);setCollisionRadius(BuildingNS::RADIUS);}
	bool initialize(SootNSickle *gamePtr, int width, int height, int ncols,TextureManager *textureM,TextureManager* hbTexM,TextDX* infoText);
	void draw(VECTOR2 screenLoc);
	void update(float frameTime);
	void create(VECTOR2 loc);

	bool getPower(){return hasPower;}
	void setPower(bool n){hasPower = n;}

	int getStaff(){return numStaff;}
	void setStaff(int n){numStaff = min(capacity,max(0,n));}
	void setCapacity(int n){capacity = max(0,n);}
	void modifyStaff(int n){numStaff += n; min(capacity,max(0,numStaff));}
	int getCapacity(){return capacity;}

	float getEffectiveness(){return (getStaff()/((float)getCapacity()));}

	void onDeath();
};