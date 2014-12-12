#pragma once

#include "ActorWithHealthBar.h"
#include "Waypoint.h"

namespace zombiebatNS
{
	const float SPEED=150;
	const float LOSE_DISTANCE_SQRD = pow(600,2);
	const float CHASE_DISTANCE_SQRD = pow(200,2);
	const float ENGAGE_DISTANCE_SQRD = pow(75,2);
	const float WEAPON_COOLDOWN = .5;
	const float RECOIL_TIME = 0.25;
	const float DAMAGE = 1;
	const COLOR_ARGB COLOR = graphicsNS::RED;
};

class ZombieBat: public ActorWithHealthBar
{
protected:
	SootNSickle *game;
	ActorWithHealthBar* targetEntity;
	Waypoint path;
	WEAPON type;
	int numBullets;
	float weaponCooldown;
	float recoilCooldown;
	float personalSpeed;

	float personalChaseDistanceSQRD;
	float personalEngageDistanceSQRD;

	bool target, shoot, checked;

public:
	ZombieBat();
	~ZombieBat();

	bool initialize(SootNSickle * game, int width, int height, int ncols, TextureManager *textureM, TextureManager* hbTexM);

	void update(float frametime);

	bool ai(float time, ActorWithHealthBar &t);

	void create(VECTOR2 loc);

	bool getHunting() {return target;}

	void nextWaypoint();

	Waypoint* getWaypoint();

	void setWaypoint(Waypoint* wp);

	void vectorTrack(float time);
	void deltaTrack(float time);
	void evade(float time);

};