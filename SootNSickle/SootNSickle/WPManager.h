/*
Caelan Mayberry
Waypoint Manager:
	its purpose is to maintain a chain of waypoints, for easy creation and addition of waypoints.
*/

#pragma once
#include "Waypoint.h"

namespace wpmanagerNS {
	const int WPM_SIZE = 10;
}

using namespace wpmanagerNS;

class WPManager {
protected:
	Waypoint chain[WPM_SIZE];
	
public:
	WPManager();
	
	void add(VECTOR2 loc);
	Waypoint* get();
	void clear();

};