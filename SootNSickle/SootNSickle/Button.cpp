#include "Button.h"
//justin

Button::Button()
{
	isPressed = false;
	setActive(false);
}

bool Button::isClicked()
{
	bool result = false;
	if(getActive())
	{
		bool mouseThisFrame = input->getMouseLButton();
		if(!mouseLastFrame && mouseThisFrame)
		{
			VECTOR2 mousePos(input->getMouseX(),input->getMouseY());
			mousePos.x -= getX(); mousePos.y -= getY();
			if(mousePos.x >= 0 && mousePos.x < getWidth() && mousePos.y >= 0 && mousePos.y < getHeight())
			{
				isPressed = !isPressed;
				result = true;

				if(isPressed)
					setCurrentFrame(pressedFrame);
				else
					setCurrentFrame(raisedFrame);
			}

		}
		mouseLastFrame = mouseThisFrame;

	}
	return result;
}

void Button::create(VECTOR2 loc)
{
	setActive(true);
	setX(loc.x);
	setY(loc.y);
	isPressed = false;
}


bool Button::initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM,int raised,int pressed)
{
	raisedFrame = raised;
	pressedFrame = pressed;
	setCurrentFrame(raisedFrame);
	return Actor::initialize(gamePtr,width,height,ncols,textureM);
}