#include"Building.h"
#include "sootnsickle.h"

bool Building::initialize(SootNSickle *gamePtr, int width, int height, int ncols,TextureManager *textureM,TextureManager* hbTexM,TextDX* infoText)
{
	text = infoText;
	return ActorWithHealthBar::initialize(gamePtr,width,height,ncols,textureM,hbTexM);
}
void Building::draw(VECTOR2 screenLoc)
{
	if(getActive())
	{
		ActorWithHealthBar::draw(screenLoc);
		if(capacity > 0 )
		{
			RECT textRect;
			//set text rect to be below the image
			textRect.top = getY()-screenLoc.y;
			textRect.left = getX()-screenLoc.x;
			textRect.right = textRect.left + getWidth();
			textRect.bottom = textRect.top +getHeight();

			text->print(std::to_string(numStaff)+"/"+std::to_string(capacity),textRect,DT_CENTER|DT_VCENTER);
		}
		if(level>1)
		{
			RECT textRect;
			//set text rect to be below the image
			textRect.top = getY()-screenLoc.y;
			textRect.right = getX()-screenLoc.x;
			textRect.left = textRect.right - 20;
			textRect.bottom = textRect.top + getHeight();

			text->print(std::to_string(level),textRect,DT_CENTER|DT_VCENTER);
		}
	}
}
void Building::update(float frameTime)
{
	if(getActive())
	{
		ActorWithHealthBar::update(frameTime);
		if(getPower())
		{
			if(game->getIdlePop() > 0 && numStaff < capacity)
			{
				numStaff++;
				game->removeIdlePop(1);
			}
		}
		else if(numStaff > 0)
		{
			numStaff--;
			game->addIdlePop(1);
		}
	}
}

void Building::create(VECTOR2 loc)
{
	setActive(true);
	setStaff(0);
	setPower(false);
	setCenter(loc);
	level = 1;
}

void Building::onDeath()
{
	game->removePopulation(getStaff());
	audio->playCue(SC_BUILDING_COLLAPSE);
}