#pragma once
//justin

#include "Actor.h"

class SootNSickle;

namespace ButtonNS
{
	const int WIDTH = 50;
	const int HEIGHT = 50;
	const int COLS = 2;

	const int RAISED_FRAME = 0;
	const int PRESSED_FRAME = 1;

	//must be in the order of the images
	enum ButtonType{
		POWER_SUPPLY_SELECTION=0,
		GROUND_TURRET_SELECTION,
		AIR_TURRET_SELECTION,
		FACTORY_SELECTION,
		EXTRACTOR_SELECTION,
		HOUSE_SELECTION,
		AIR_FIELD_SELECTION,
		SELL_SELECTION,
		UPGRADE_SELECTION,
		SIZE//must be last
	};

	const int ICON_HEIGHT = 50;
};

class Button;


class Button: public Actor
{
public:
	Button();

	bool initialize(SootNSickle *gamePtr, int width, int height, int ncols,TextureManager *textureM,TextureManager *iconM);

	bool checkClick();
	
	bool isPressed;

	ButtonNS::ButtonType getButtonType(){return type;}

	void create(VECTOR2 loc, ButtonNS::ButtonType t);

	void draw(VECTOR2 screenLoc);

private:
	Image icon;
	ButtonNS::ButtonType type;
	SootNSickle* game;
};