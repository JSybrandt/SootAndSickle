#pragma once

#include "WPManager.h"
#include <vector>

namespace zsNS {

}

class SootNSickle;

class ZombieSpawner {
protected:
	VECTOR2 center;
	float spawnTimer;
	float resetTimer;
	int zombies;
	WEAPON type;
	bool alive, last;
	SootNSickle* game;
	WPManager* wpm;
	std::vector<std::pair<std::pair<int, WEAPON>,float>> waves;

public:
	ZombieSpawner();

	void setActive(bool setting) { alive = setting;}
	bool getActive() {return alive;}
	void setManager(WPManager* manager) {wpm = manager;}

	bool initialize(SootNSickle* g);
	void setCenter(VECTOR2 loc);
	void create(int zombies, WEAPON type);
	void addWave(int zombies, WEAPON type, float time);
	void update(float frameTime);
	void clear();
};