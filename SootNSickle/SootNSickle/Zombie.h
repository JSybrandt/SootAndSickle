#pragma once

#include "ActorWithHealthBar.h"
#include "Waypoint.h"

class SootNSickle;

namespace zombieNS
{
	const float SPEED=200;
	const float LOSE_DISTANCE_SQRD = pow(600,2);
	const float CHASE_DISTANCE_SQRD = pow(200,2);
	const float ENGAGE_DISTANCE_SQRD = pow(100,2);
	const float WEAPON_COOLDOWN = 1;
	const float RECOIL_TIME = 0.25;
	const COLOR_ARGB COLOR = graphicsNS::RED;
	const VECTOR2 bulletDisplacement(28,18);
};

class Zombie: public ActorWithHealthBar
{
public:
	SootNSickle *game;
	ActorWithHealthBar* targetEntity;
	Waypoint path;
	WEAPON type;
	int numBullets;
	float weaponCooldown;
	float recoilCooldown;

	float personalChaseDistanceSQRD;
	float personalEngageDistanceSQRD;

	bool target, shoot, checked;

public:
	Zombie();
	~Zombie();

	bool initialize(SootNSickle * game, int width, int height, int ncols, TextureManager *textureM, TextureManager* hbTexM);

	void update(float frametime);

	void ai(float time, ActorWithHealthBar &t);

	void create(VECTOR2 loc);

	bool getHunting() {return target;}

	void nextWaypoint();

	Waypoint* getWaypoint();

	void setWaypoint(Waypoint* wp);

	void vectorTrack(float time);
	void deltaTrack(float time);
	void evade(float time);

};