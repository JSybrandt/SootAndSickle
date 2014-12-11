#pragma once
#include "Building.h"
#include "PowerField.h"

namespace PowerSupplyNS{
	const float POWER_RADIUS = 350;
	const float EXTEND_PER_LEVEL = 50;
	const float BUILDING_RADIUS = 50;
	const float BOOT_TIME = 1;
	const float HEALTH = 5;
};

class PowerSupply : public Building
{
private:
	PowerField field;
	float bootCooldown;
	bool hasPowerLastFrame;
public:
	PowerSupply();
	bool initialize(SootNSickle *gamePtr, int width, int height, int ncols,TextureManager *textureM,TextureManager* hbTexM,TextureManager* pwrTex,TextDX * text);
	void update(float frameTime);
	void create(VECTOR2 loc);
	PowerField& getPowerField(){return field;}
	void setActive(bool b){field.setActive(b);ActorWithHealthBar::setActive(b);}
	void setPower(bool b){
		if(!hasPowerLastFrame&&b)
			audio->playCue(SC_POWER_ON);
		Building::setPower(b);
		field.setActive(b);	
	}
	void upgrade(){Building::upgrade(); field.setFieldRadius(PowerSupplyNS::POWER_RADIUS + getLevel()*PowerSupplyNS::EXTEND_PER_LEVEL);}
};