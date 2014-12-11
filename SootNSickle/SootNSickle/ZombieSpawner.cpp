#pragma once
#include "ZombieSpawner.h"
#include "sootnsickle.h"

ZombieSpawner::ZombieSpawner(){
	spawnTimer = 0;
	resetTimer = 10;
	alive = true;
}

bool ZombieSpawner::initialize(SootNSickle* g) {
	game = g;
	return true;
}

void ZombieSpawner::setCenter(VECTOR2 loc) {
	center = loc;
}

void ZombieSpawner::create(int zombies) {
	for(int i = 0; i < zombies; i++) {
		Zombie* z = game->spawnZombie(VECTOR2(center.x+randmax(200),center.y+(randmax(200))));
		z->setWaypoint(wpm->get());
	}
}

void ZombieSpawner::addWave(int zombies, float time) {
	if(spawnTimer == 0)
		spawnTimer = time;
	auto it = waves.begin();
	waves.insert(it, std::pair<int, float>(zombies,time));
	alive = true;

}
void ZombieSpawner::update(float frameTime) {
	if(alive) {
		spawnTimer -= frameTime;
		if(waves.size() == 0)
			alive = false;
		else if(spawnTimer <= 0 && alive) {
			int zombies = waves.at(waves.size()-1).first;
			float timer = waves.at(waves.size()-1).second;
			waves.pop_back();
			spawnTimer = timer;
			create(zombies);
		}
	}
}

/*
BUGLIST:


*/