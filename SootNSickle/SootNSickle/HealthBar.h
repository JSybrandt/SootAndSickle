#pragma once

#include "Actor.h"

namespace HealthBarNS{
	const int ACTIVE_FRAME = 0;
	const int BASE_FRAME = 1;
	const int WIDTH = 100;
	const int HEIGHT = 20;
	const float DEFAULT_MAX = 100;

};

class HealthBar:public Actor{
public:
	bool initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM);
	void setMaxValue(float n);
	void setCurrentValue(float n);
	void draw(VECTOR2 screenLoc);
private:
	void updateActiveRec();
	float maxValue,currentValue;
	Image activeImg;
};