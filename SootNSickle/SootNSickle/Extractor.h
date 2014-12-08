#pragma once
#include "ActorWithHealthBar.h"
#include "MineralPatch.h"

namespace ExtractorNS{
	const float DEFAULT_MINING_RATE = 10;
	const float MINING_RANGE = 100;
	const float COLLISION_RADIUS = 50;
};

class Extractor : public ActorWithHealthBar
{
private:
	MineralPatch* minerals;
	bool anythingNearby;
public:
	Extractor(){setActive(false); setCollisionRadius(ExtractorNS::COLLISION_RADIUS);}
	void update(float frameTime);
	void create(VECTOR2 loc);
	bool hasPower;
};