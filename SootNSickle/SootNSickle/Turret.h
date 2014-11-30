#pragma once

#include "Actor.h"

class SootNSickle;

namespace turretNS{
	const float ROTATION_SPEED = PI/4;
	const float ENGAGE_DISTANCE_SQRD = pow(512,2); // replace this with "line of sight"
	const float ROTATION_WIDTH = PI/2;
	const float ROT_EPSILON = 0.001;
	const float FIRE_RATE = 0.75;
	const float REBOOT_TIME = 2;
	const VECTOR2 BULLET1_OFFSET(30,-15);
	const VECTOR2 BULLET2_OFFSET(30,15);
	const float TURRET_RADIUS = 32;
};

class Turret:public Actor
{
protected:
	SootNSickle * game;
	Actor base;
	Actor* targetEntity;
	float minDir, maxDir,rotVel;
	float weaponCooldown;
	float rebootCooldown;
	float dmg;
	WEAPON damageType;

	bool target, checked; //Target means it has a target and is within range of itself.
						  //Checked is true if it has found a new target or the old one is still alive & within range
	float personalChaseDistanceSQRD;
	float personalEngageDistanceSQRD;

public:
	Turret();

	bool initialize(SootNSickle * g, int width, int height, int ncols, TextureManager *turretTM, TextureManager *baseTM);

	void update(float frameTime);

	void animate(float frameTime);

	void draw(VECTOR2 screenLoc);

	void create(VECTOR2 loc, float dir);

	void ai(float frameTime, Actor &ent);

	void hit();
};