#include "HealthBar.h"

using namespace HealthBarNS;

void HealthBar::setCurrentValue(float n)
{
	if(n>0 && n <= maxValue)
		currentValue = n;
	updateActiveRec();
}

void HealthBar::setMaxValue(float n)
{
	if(n>0)
		maxValue = n;
	if(currentValue > maxValue)
		currentValue = maxValue;
	updateActiveRec();
}

void HealthBar::updateActiveRec()
{
	setScale(max(0.5,maxValue / WIDTH));
	activeImg.setScale(max(0.5,maxValue/WIDTH));
	int activeWidth = (currentValue / maxValue)*getWidth();
	RECT activeRec = activeImg.getSpriteDataRect();
	activeRec.right = activeWidth;
	activeImg.setSpriteDataRect(activeRec);
}

void HealthBar::draw(VECTOR2 screenLoc)
{
	activeImg.setX(getX());
	activeImg.setY(getY());

	Actor::draw(screenLoc);
	activeImg.draw(screenLoc);
}

bool HealthBar::initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM)
{
	bool result = true;

	result = result && activeImg.initialize(gamePtr->getGraphics(),width,height,ncols,textureM);

	result = result && Actor::initialize(gamePtr,width,height,ncols,textureM);

	activeImg.setCurrentFrame(ACTIVE_FRAME);
	setCurrentFrame(BASE_FRAME);

	//maxValue = DEFAULT_MAX;
	//currentValue = DEFAULT_MAX;

	return result;
}