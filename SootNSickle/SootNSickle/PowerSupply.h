#pragma once
#include "ActorWithHealthBar.h"
#include "PowerField.h"

namespace PowerSupplyNS{
	const float POWER_RADIUS = 250;
	const float BUILDING_RADIUS = 50;
	const float BOOT_TIME = 1;
};

class PowerSupply : public ActorWithHealthBar
{
private:
	PowerField field;
	bool hasPower;
	float bootCooldown;
public:
	PowerSupply();
	bool initialize(SootNSickle *gamePtr, int width, int height, int ncols,TextureManager *textureM,TextureManager* hbTexM,TextureManager* pwrTex);
	void update(float frameTime);
	void create(VECTOR2 loc);
	PowerField& getPowerField(){return field;}
	//void draw(VECTOR2 screenLoc);
	void setPower(bool b)
	{
		field.setActive(b);
		field.setVisible(b);
		hasPower=b;
	}

	bool getPower(){return hasPower;}
	void setActive(bool b){field.setActive(b);ActorWithHealthBar::setActive(b);}
};