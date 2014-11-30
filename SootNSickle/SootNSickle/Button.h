#pragma once
//justin

#include "Actor.h"

namespace ButtonNS
{
	const int WIDTH = 50;
	const int HEIGHT = 50;
	const int COLS = 2;

	const int RAISED_FRAME = 0;
	const int PRESSED_FRAME = 1;
};

class Button: public Actor
{
public:
	Button();

	bool initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM,int raised,int pressed);

	bool isClicked();
	
	bool isPressed;

	void setRaisedFrame(int n){raisedFrame=n;}
	void setPressedFrame(int n){pressedFrame=n;}

	void create(VECTOR2 loc);

private:

	int raisedFrame,pressedFrame;
	bool mouseLastFrame;

};