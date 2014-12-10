#include "Button.h"
#include "sootnsickle.h"
using namespace ButtonNS;
//justin

Button::Button()
{
	isPressed = false;
	setActive(false);
}

void Button::draw(VECTOR2 screenLoc)
{
	if(getActive()){
		if(isPressed) {
			setCurrentFrame(PRESSED_FRAME);
			icon.setCenter(getCenter()+VECTOR2(0,4));
		}
		else {
			setCurrentFrame(RAISED_FRAME);
			icon.setCenter(getCenter());

		}
		Actor::draw(screenLoc);
		icon.draw(screenLoc);
	}
}

//only called on first click
bool Button::checkClick()
{
	bool result = false;
	if(getActive())
	{
		VECTOR2 mousePos(input->getMouseX(),input->getMouseY());
		mousePos.x -= getX(); mousePos.y -= getY();
		if(mousePos.x >= 0 && mousePos.x < getWidth() && mousePos.y >= 0 && mousePos.y < getHeight())
		{
			isPressed = !isPressed;
			result = true;

			game->buttonOnClick(this);

		}

	}
	return result;
}

void Button::create(VECTOR2 loc, ButtonType t)
{
	setActive(true);
	setX(loc.x);
	setY(loc.y);
	isPressed = false;
	type = t;
	icon.setCenter(getCenter());
	icon.setVisible(true);
	icon.setCurrentFrame((int)t);
}


bool Button::initialize(SootNSickle *gamePtr, int width, int height, int ncols,TextureManager *textureM,TextureManager *iconM)
{
	game = gamePtr;
	bool result = icon.initialize(game->getGraphics(),0,ICON_HEIGHT,0,iconM);
	return result && Actor::initialize(gamePtr,width,height,ncols,textureM);
}