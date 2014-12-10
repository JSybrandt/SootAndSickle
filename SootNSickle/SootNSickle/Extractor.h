#pragma once
#include "Building.h"
#include "MineralPatch.h"

namespace ExtractorNS{
	const float DEFAULT_MINING_RATE = 10;
	const float MINING_RANGE = 150;
	const float COLLISION_RADIUS = 50;
	const int CAPACITY = 10;
	const float HEALTH = 25;
};

class Extractor : public Building
{
private:
	MineralPatch* minerals;
	bool anythingNearby;
public:
	Extractor(){setActive(false); setCollisionRadius(ExtractorNS::COLLISION_RADIUS);setMaxHealth(ExtractorNS::HEALTH);}
	void update(float frameTime);
	void create(VECTOR2 loc);
};