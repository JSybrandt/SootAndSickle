#include "WPManager.h"

using namespace wpmanagerNS;

WPManager::WPManager() {

}

//Activate a new Waypoint, place it at the location, and attach it to the chain.
void WPManager::add(VECTOR2 loc) {
	for(int i = 0; i < WPM_SIZE; i++) {
		if(!chain[i].getActive()) {
			chain[i].setActive(true);
			chain[i].setCenter(loc);

			if(i > 0)
				chain[i].add(&chain[i-1]);
			break;
		}
	}
}

Waypoint* WPManager::get() {
	return &chain[0];
}

void WPManager::clear() {
	for(int i = 0; i < WPM_SIZE; i++) {
		chain[i].setParent(nullptr);
		chain[i].setChild(nullptr);
		chain[i].setActive(false);
	}
}

