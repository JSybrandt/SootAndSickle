#pragma once
#include "ZombieSpawner.h"
#include "sootnsickle.h"

ZombieSpawner::ZombieSpawner(){
	spawnTimer = 0;
	zombies = 0;
	resetTimer = 10;
	alive = true;
	last = false;
}

bool ZombieSpawner::initialize(SootNSickle* g) {
	game = g;
	return true;
}

void ZombieSpawner::setCenter(VECTOR2 loc) {
	center = loc;
}

void ZombieSpawner::create(int zombies, WEAPON type) {
	if(type == GROUND)
		for(int i = 0; i < zombies; i++) {
			Zombie* z = game->spawnZombie(VECTOR2(center.x+randmax(200),center.y+(randmax(200))));
			z->setWaypoint(wpm->get());
		}
	else
		for(int i = 0; i < zombies; i++) {
			ZombieBat* z = game->spawnZombieBat(VECTOR2(center.x+randmax(200),center.y+(randmax(200))));
			z->setWaypoint(wpm->get());
		}
}

void ZombieSpawner::addWave(int zombies, WEAPON type, float time) {
	std::pair<int,WEAPON> zombieType(zombies,type);
	if(spawnTimer == 0) {
		spawnTimer = time;
		this->type = type;
		this->zombies = zombies;
	}
	else {
		auto it = waves.begin();
		waves.insert(it, std::pair<std::pair<int, WEAPON>, float> (zombieType,time));
		alive = true;
	}

}
void ZombieSpawner::update(float frameTime) {
	if(alive) {
		spawnTimer -= frameTime;
		if(spawnTimer <= 0 && !last) {
			create(zombies, type);
			zombies = waves.at(waves.size()-1).first.first;
			type = waves.at(waves.size()-1).first.second;
			spawnTimer = waves.at(waves.size()-1).second;
			waves.pop_back();
			if(waves.size() == 0)
				last = true;
		}
		else if(spawnTimer <= 0 && last) {
			last = false;
			alive = false;
			create(zombies, type);
		}

	}
}

void ZombieSpawner::clear() {
	wpm = nullptr;
	waves.clear();
}

/*
BUGLIST:


*/