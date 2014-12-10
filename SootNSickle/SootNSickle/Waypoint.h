// Soot And Sickle
// Caelan Mayberry
// Waypoint: A waypoint that 

#pragma once

#include "Actor.h"

namespace waypointNS {

}

class SootNSickle;

class Waypoint: public Actor {
protected:
	SootNSickle * game;
	Waypoint * parent;
	Waypoint * child;

public:
	Waypoint();

	bool initialize(SootNSickle * g, int width, int height, int ncols, TextureManager *debugTM);

	void update(float frameTime);

	void draw(VECTOR2 screenLoc);

	void create(VECTOR2 loc, COLOR_ARGB c);

	void setParent(Waypoint* parent) {this->parent = parent;}

	void setChild(Waypoint* child) {this->child = child;}

	Waypoint* getParent() {return parent;}

	Waypoint* getChild() {return child;}

	void add(Waypoint *parent) { //Linked list esque
		setParent(parent);
		parent->setChild(this);
	}

};