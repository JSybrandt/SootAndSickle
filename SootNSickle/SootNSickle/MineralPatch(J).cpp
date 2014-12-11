#include "MineralPatch.h"

MineralPatch::MineralPatch(){setActive(false);setCollisionRadius(50);}

void MineralPatch::create(VECTOR2 loc, float ammount){
	setActive(true);
	setCenter(loc);
	mineralLevel = ammount;
}

void MineralPatch::setMineralLevel(float n){if(n>0)mineralLevel > n;}


float MineralPatch::mine(float requestedAmmount){
	if(mineralLevel > requestedAmmount) 
	{
		mineralLevel -= requestedAmmount;
		return requestedAmmount;
	}
	else
	{
		float t = mineralLevel;
		mineralLevel = 0;
		setActive(false);
		return t;
	}
}

bool MineralPatch::initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM, TextDX *text)
{
	this->text = text;
	return Actor::initialize(gamePtr,width,height,ncols,textureM);
}
void MineralPatch::draw(VECTOR2 screenLoc)
{
	if(getActive())
	{
		Actor::draw(screenLoc);
		RECT textRect;
		//set text rect to be below the image
		textRect.top = getY()+getHeight()-screenLoc.y;
		textRect.left = getX()-screenLoc.x;
		textRect.right = textRect.left + getWidth();
		textRect.bottom = textRect.top + 20;

		text->print(std::to_string((int)mineralLevel),textRect,DT_CENTER|DT_VCENTER);
	}
}