#pragma once

#include "Turret.h"

namespace aaturretNS{
	const float ROTATION_SPEED = PI;
	const float ENGAGE_DISTANCE_SQRD = pow(512,2); // replace this with "line of sight"
	const float ROTATION_WIDTH = PI/2;
	const float ROT_EPSILON = 0.001;
	const float FIRE_RATE = 0.33;
	const float REBOOT_TIME = 1;
	const VECTOR2 BULLET1_OFFSET(30,-15);
	const VECTOR2 BULLET2_OFFSET(30,15);
	const float TURRET_RADIUS = 32;
	const int CAPACITY = 1;
};

class AATurret:public Turret
{
protected:


public:
	AATurret();

	bool initialize(SootNSickle * g, int width, int height, int ncols, TextureManager *turretTM, TextureManager *baseTM, TextureManager* hbTexM,TextDX * text);

	void update(float frameTime);

	void animate(float frameTime);

	void draw(VECTOR2 screenLoc);

	void create(VECTOR2 loc, float dir);

	void ai(float frameTime, Actor &ent);

	void hit();

};