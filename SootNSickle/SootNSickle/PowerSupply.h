#pragma once
#include "Building.h"
#include "PowerField.h"

namespace PowerSupplyNS{
	const float POWER_RADIUS = 350;
	const float BUILDING_RADIUS = 50;
	const float BOOT_TIME = 1;
	const float HEALTH = 5;
};

class PowerSupply : public Building
{
private:
	PowerField field;
	float bootCooldown;
public:
	PowerSupply();
	bool initialize(SootNSickle *gamePtr, int width, int height, int ncols,TextureManager *textureM,TextureManager* hbTexM,TextureManager* pwrTex,TextDX * text);
	void update(float frameTime);
	void create(VECTOR2 loc);
	PowerField& getPowerField(){return field;}
	void setActive(bool b){field.setActive(b);ActorWithHealthBar::setActive(b);}
	void setPower(bool b){Building::setPower(b);field.setActive(b);}
};