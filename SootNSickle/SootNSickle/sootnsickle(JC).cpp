// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Game Engine Part 1
// Chapter 4 RedSpace.cpp v1.0
// RedSpace is the class we create.

#include "sootnsickle.h"

//=============================================================================
// Constructor
//=============================================================================
SootNSickle::SootNSickle()
{
	srand(time(0));


	worldSizes = new VECTOR2[GameState::SIZE];
	worldSizes[GameState::TitleScreen] = VECTOR2(GAME_WIDTH,GAME_HEIGHT);
	worldSizes[GameState::Level1] = VECTOR2(4000,4000);
	worldSizes[GameState::Level2] = VECTOR2(4000,4000);
	worldSizes[GameState::Level3] = VECTOR2(4000,4000);
	worldSizes[GameState::FeelingLucky] = VECTOR2(GAME_WIDTH,GAME_HEIGHT);

	currentState = TitleScreen;

	paused = false;
	controls.up = 'W';
	controls.down = 'S';
	controls.left = 'A';
	controls.right = 'D';
	controls.pause = 'P';

	cursorSelection = -1;

	wasClickedLastFrame = false;

	mineralLevel = 0;

	population = 0;
	idlePopulation = 0;
	capacity = 0;
	upgradePoints = 0;
	tutorialSelection = 0;
	showTutorial = false;

	audioIntroCountdown = AUDIO_INTRO_TIME;
	playingIntro = true;
	levelTextCooldown = 0;
}

//=============================================================================
// Destructor
//=============================================================================
SootNSickle::~SootNSickle()
{
	releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void SootNSickle::initialize(HWND hwnd)
{
	Game::initialize(hwnd); // throws GameError

	zs1.initialize(this);
	zs2.initialize(this);

	if(!mainMenuBackgroundTex.initialize(graphics,MENU_BACKGROUND_IMAGE))
		throw GameError(1,"Failed to init menu background tex");

	if(!mainMenuButtonTex.initialize(graphics,MAIN_MENU_BUTTON_IMAGE))
		throw GameError(1,"Failed to init menu button tex");

	if(!mainMenuBackground.initialize(graphics,0,0,0,&mainMenuBackgroundTex))
		throw GameError(1,"failed to make menu background");

	for(int i = 0 ; i < MAIN_MENU_OPTION_COUNT; i++)
	{
		if(!mainMenuOptions[i].initialize(graphics,0,120,1,&mainMenuButtonTex))
			throw GameError(1,"failed to make menu button");
		mainMenuOptions[i].setCurrentFrame(i);
	}

	if(!logoTex.initialize(graphics,LOGO_IMAGE))
		throw GameError(1,"failed to make icon tex");

	if(!logo.initialize(graphics,0,0,0,&logoTex))
		throw GameError(1,"Failed to init icon");

	if(!gameOverTex.initialize(graphics,GAMEOVER_IMAGE))
		throw GameError(1,"failed to make icon tex");

	if(!gameOver.initialize(graphics,0,0,0,&gameOverTex))
		throw GameError(1,"Failed to init gameover");

	//
	//Initializing Textures
	//

	if(!backgroundTex.initialize(graphics,BACKGROUND_IMAGE))
		throw GameError(1,"Failed to init background tex");

	if(!transportShipTex.initialize(graphics,TRANSPORT_SHIP_IMAGE))
		throw GameError(1,"Failed to init transport ship tex");

	if(!particleTex.initialize(graphics,PARTICLE_IMAGE))
		throw GameError(6,"Failed to init particle tex");


	if(!buttonTex.initialize(graphics,BUTTON_IMAGE))
		throw GameError(2,"Failed to init button text");

	if(!guiOverlayTex.initialize(graphics,GUI_OVERLAY_IMAGE))
		throw GameError(6,"Failed to init gui overlay tex");

	if(!baseTex.initialize(graphics,BASE_IMAGE))
		throw GameError(6,"Failed to init base tex");

	if(!healthBarTex.initialize(graphics,HEALTH_BAR_IMAGE))
		throw GameError(6,"Failed to init health bar tex");

	if(!powerFieldTex.initialize(graphics,POWER_FIELD_IMAGE))
		throw GameError(6,"Failed to init power field tex");

	if(!powerSupplyTex.initialize(graphics,POWER_SUPPLY_IMAGE))
		throw GameError(6,"Failed to init power Supply tex");

	if(!iconTex.initialize(graphics,ICON_IMAGE))
		throw GameError(6,"Failed to init icon tex");

	if(!cursorTex.initialize(graphics,CURSOR_IMAGE))
		throw GameError(6,"Failed to init cursor tex");

	if(!cursor.initialize(graphics,0,CURSOR_HEIGHT,0,&cursorTex))
		throw GameError(9,"Failed to init cursor");

	if(!infoText.initialize(graphics,20,true,false,"Verdana"))
		throw GameError(9,"Failed to init mine text");


	if(!buildingText.initialize(graphics,20,false,false,"Verdana"))
		throw GameError(9,"Failed to init mine text");

	if(!levelText.initialize(graphics,80,true,true,"Copperplate Gothic"))
		throw GameError(9,"Failed to init level text");

	if(!mineralTex.initialize(graphics,MINERAL_IMAGE))
		throw GameError(6,"Failed to init mineral tex");

	if(!factoryTex.initialize(graphics,FACTORY_IMAGE))
		throw GameError(6,"Failed to init factory tex");

	if(!extractorTex.initialize(graphics,EXTRACTOR_IMAGE))
		throw GameError(6,"Failed to init extractor tex");
	if(!turretgTex.initialize(graphics,TURRETG_IMAGE))
		throw GameError(6,"Failed to init extractor tex");
	if(!turretaTex.initialize(graphics,TURRETA_IMAGE))
		throw GameError(6,"Failed to init extractor tex");
	if(!standTex.initialize(graphics,TURRETBASE_IMAGE))
		throw GameError(6,"Failed to init extractor tex");	
	if(!houseTex.initialize(graphics,HOUSE_IMAGE))
		throw GameError(6,"Failed to init house tex");	
	if(!airFieldTex.initialize(graphics,AIR_FIELD_IMAGE))
		throw GameError(6,"Failed to init house tex");
	if(!zombieTex.initialize(graphics,ZOMBIE_IMAGE))
		throw GameError(6,"Failed to init zombie tex");
	if(!zombieBatTex.initialize(graphics,ZOMBIEBAT_IMAGE))
		throw GameError(6,"Failed to init zombiebat tex");
	//
	//Initializing actors
	//
	if(!background.initialize(graphics,0,0,0,&backgroundTex))
		throw GameError(9,"Failed to init background");

	if(!guiOverlay.initialize(graphics,0,0,0,&guiOverlayTex))
		throw GameError(9,"Failed to init gui overlay");

	if(!base.initialize(this,0,0,0,&baseTex,&healthBarTex,&powerFieldTex,&infoText))
		throw GameError(6,"Failed to init base");

	for(int i = 0 ; i < MAX_PARTICLES; i++)
	{
		if(!particles[i].initialize(this,0,0,0,&particleTex))
			throw GameError(-1*i,"FAILED TO MAKE particle!");
	}

	for(int i = 0 ; i < MAX_BUTTONS; i++)
	{
		if(!buttons[i].initialize(this,ButtonNS::WIDTH,ButtonNS::HEIGHT,ButtonNS::COLS,&buttonTex,&iconTex))
			throw GameError(-1*i,"FAILED TO MAKE button!");
	}

	for(int i = 0 ; i < MAX_POWER_SUPPLIES; i++)
	{
		if(!powerSupplies[i].initialize(this,0,0,0,&powerSupplyTex,&healthBarTex,&powerFieldTex,&buildingText))
			throw GameError(-1*i,"FAILED TO MAKE powerSupply!");
	}

	for(int i = 0 ; i < MAX_MINERALS; i++)
	{
		if(!minerals[i].initialize(this,0,0,0,&mineralTex,&buildingText))
			throw GameError(-1*i,"FAILED TO MAKE mineral!");
	}

	for(int i = 0 ; i < MAX_EXTRACTORS; i++)
	{
		if(!extractors[i].initialize(this,0,0,0,&extractorTex,&healthBarTex,&buildingText))
			throw GameError(-1*i,"FAILED TO MAKE extractor!");
	}

	for(int i = 0; i < MAX_GROUND_TURRETS; i++) {
		if(!turrets[i].initialize(this,0,0,0,&turretgTex,&standTex,&healthBarTex,&buildingText))
			throw GameError(-1*i,"FAILED TO MAKE agturret!");
	}
	for(int i = 0; i < MAX_AIR_TURRETS; i++) {
		if(!aaturrets[i].initialize(this,0,0,0,&turretaTex,&standTex,&healthBarTex,&buildingText))
			throw GameError(-1*i,"FAILED TO MAKE aaturret!");
	}

	for(int i = 0; i < MAX_FACTORIES; i++) {
		if(!factories[i].initialize(this,0,0,0,&factoryTex,&healthBarTex,&buildingText))
			throw GameError(-1*i,"FAILED TO MAKE factory!");
	}
	for(int i = 0; i < MAX_HOUSES; i++){
		if(!houses[i].initialize(this,0,0,0,&houseTex,&healthBarTex,&buildingText))
			throw GameError(-1*i,"FAILED TO MAKE house!");
	}

	for(int i = 0; i < MAX_AIR_FIELDS; i++)
		if(!airFields[i].initialize(this,0,0,0,&airFieldTex,&healthBarTex,&buildingText,&transportShipTex))
			throw GameError(-1*i,"FAILED TO MAKE air field!");
	for(int i = 0; i < MAX_GROUND_ENEMIES; i++) {
		if(!zombies[i].initialize(this,ZOMBIE_WIDTH,ZOMBIE_HEIGHT,ZOMBIE_COL,&zombieTex,&healthBarTex))
			throw GameError(-1*i,"FAILED TO MAKE zombie!");
		zombies[i].setFrames(0, 3);   // animation frames
		zombies[i].setCurrentFrame(0);     // starting frame
		zombies[i].setFrameDelay(0.25f); 
	}
	for(int i = 0; i < MAX_AIR_ENEMIES; i++) {
		if(!zombieBats[i].initialize(this,BAT_WIDTH,BAT_HEIGHT,BAT_COL,&zombieBatTex,&healthBarTex))
			throw GameError(-1*i,"FAILED TO MAKE zombieBat!");
		zombieBats[i].setFrames(0, 3);   // animation frames
		zombieBats[i].setCurrentFrame(0);     // starting frame
		zombieBats[i].setFrameDelay(BAT_DELAY);
	}
	menuLoad();

	audio->playCue(SC_OPENING);

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void SootNSickle::update()
{


	if(playingIntro)
	{
		audioIntroCountdown-=frameTime;
		if(audioIntroCountdown <= 0)
		{
			audio->playCue(SC_MAIN_LOOP);
			playingIntro = false;
		}
	}

	switch (currentState){
	case TitleScreen:
		menuUpdate();
		break;
	default:
		levelsUpdate();
	}

}

void SootNSickle::menuUpdate(bool reset)
{
	static int selection = 0;

	if(showGameOverScreen)
	{
		if(input->wasKeyPressed(VK_RETURN))
		{
			showGameOverScreen = false;
		}
	}
	else
	{
		if(input->wasKeyPressed(controls.up))
			selection--;
		if(input->wasKeyPressed(controls.down))
			selection++;

		if(selection < 0) selection = MAIN_MENU_OPTION_COUNT-1;
		if(selection >= MAIN_MENU_OPTION_COUNT) selection = 0;

		int choice = -1;

		if(input->wasKeyPressed(VK_RETURN))
		{
			choice = selection;
		}

		VECTOR2 initPosit(866,313);
		VECTOR2 verticalDisp(0,120);
		VECTOR2 selectedDisp(-50,0);
		for(int i = 0 ; i < MAIN_MENU_OPTION_COUNT; i++)
		{
			if(input->getMouseX()> mainMenuOptions[i].getX() && input->getMouseX() < mainMenuOptions[i].getX()+mainMenuOptions[i].getWidth()
				&&input->getMouseY()> mainMenuOptions[i].getY() && input->getMouseY() < mainMenuOptions[i].getY()+mainMenuOptions[i].getHeight())
			{
				selection = i;
				if(input->getMouseLButton())
					choice = i;
			}

			VECTOR2 currLoc = initPosit + i*verticalDisp;
			if(i==selection) currLoc+= selectedDisp;
			mainMenuOptions[i].setX(currLoc.x);
			mainMenuOptions[i].setY(currLoc.y);

		}

		if(choice == 0)
			level1Load();
		else if (choice == 1)
			system("START https://www.youtube.com/watch?v=PX-KhvY7xxs&feature=youtu.be");
		else if (choice == 2)
			showIcon = !showIcon;
		else if (choice == 3)
			exitGame();
	}

}

void SootNSickle::levelsUpdate()
{

	if(input->wasKeyPressed('R'))
	{
		level1Load();
	}
	if(input->wasKeyPressed('C'))
	{
		VECTOR2 screen (GAME_WIDTH,GAME_HEIGHT);
		screen *= 0.5;
		screenLoc = base.getCenter() - screen;
	}

	if(input->getMouseRButton())
	{
		raiseAllButtons();
	}

	if(input->wasKeyPressed(controls.pause))
	{
		paused = !paused;
	}

	if(paused) return;

	levelTimer -= frameTime;
	if(levelTimer <= 0) {
		switch(currentState) {
		case Level1:
			level2Load();
			break;
		case Level2:
			level3Load();
			break;
		}
	}

	levelTextCooldown = max(levelTextCooldown-frameTime,0);
	
	secondsSurvived+=frameTime;

	VECTOR2 in(0,0);

	if(input->isKeyDown(controls.up))
		in.y -= 1;
	if(input->isKeyDown(controls.down))
		in.y += 1;
	if(input->isKeyDown(controls.left))
		in.x -= 1;
	if(input->isKeyDown(controls.right))
		in.x += 1;

	D3DXVec2Normalize(&in,&in);
	in*=SCREEN_SPEED*frameTime;
	screenLoc += in;

	updateScreen();

	int newCapacity = 0;

	base.update(frameTime);
	newCapacity += BaseNS::HOUSING;


	for(int i = 0 ; i < MAX_POWER_SUPPLIES; i++)
	{
		powerSupplies[i].update(frameTime);
	}

	for(int i = 0 ; i < MAX_EXTRACTORS; i++)
	{
		extractors[i].update(frameTime);
	}

	for(int i = 0 ; i < MAX_PARTICLES; i++)
	{
		particles[i].update(frameTime);
	}
	for(int i = 0; i < MAX_FACTORIES; i++)
	{
		factories[i].update(frameTime);
	}
	for(int i = 0; i < MAX_HOUSES; i++)
	{
		houses[i].update(frameTime);
		if(houses[i].getActive() && houses[i].getPower())
			newCapacity+=HouseNS::HOUSING*houses[i].getLevel();
	}
	for(int i = 0; i < MAX_AIR_FIELDS; i++)
	{
		airFields[i].update(frameTime);
	}
	for(int i = 0; i < MAX_GROUND_TURRETS; i++)
	{
		turrets[i].update(frameTime);
	}
	for(int i = 0; i < MAX_AIR_TURRETS; i++)
	{
		aaturrets[i].update(frameTime);
	}
	for(int i = 0; i < MAX_GROUND_ENEMIES; i++)
		zombies[i].update(frameTime);
	for(int i = 0; i < MAX_AIR_ENEMIES; i++)
		zombieBats[i].update(frameTime);
	zs1.update(frameTime);
	zs2.update(frameTime);
	zs3.update(frameTime);

	capacity = newCapacity;
	if(population > capacity) population = capacity;

	//check first click
	if(!wasClickedLastFrame && input->getMouseLButton())
	{
		bool buttonClicked = false;
		for(int i = 0; i < MAX_BUTTONS;i++)
		{
			buttonClicked = buttonClicked||buttons[i].checkClick();
		}
		if(!buttonClicked) checkClick();
	}
	wasClickedLastFrame = input->getMouseLButton();
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void SootNSickle::ai()
{
	VECTOR2 collision;

	//ZOMBIES
	for(int i = 0; i < MAX_GROUND_ENEMIES; i++) {
		if(zombies[i].getActive()) {
			for(int j = 0; j < MAX_GROUND_TURRETS; j++) {
				if(turrets[j].getActive())
					if(zombies[i].ai(frameTime, turrets[j]))
						break;
			}
			for(int j = 0; j < MAX_AIR_TURRETS; j++) {
				if(aaturrets[j].getActive())
					if(zombies[i].ai(frameTime, aaturrets[j]))
						break;
			}
			zombies[i].ai(frameTime, base);
			for(int j = 0; j < MAX_HOUSES; j++) {
				if(houses[j].getActive())
					if(zombies[i].ai(frameTime, houses[j]))
						break;
			}
			for(int j = 0; j < MAX_AIR_FIELDS; j++) {
				if(airFields[j].getActive())
					if(zombies[i].ai(frameTime, airFields[j]))
						break;
			}
			for(int j = 0; j < MAX_FACTORIES; j++) {
				if(factories[j].getActive())
					if(zombies[i].ai(frameTime, factories[j]))
						break;
			}
			for(int j = 0; j < MAX_EXTRACTORS; j++) {
				if(extractors[j].getActive())
					if(zombies[i].ai(frameTime, extractors[j]))
						break;
			}
			for(int j = 0; j < MAX_POWER_SUPPLIES; j++) {
				if(powerSupplies[j].getActive())
					if(zombies[i].ai(frameTime, powerSupplies[j]))
						break;
			}
		}
	}

	//ZOMBIEBATS
	for(int i = 0; i < MAX_AIR_ENEMIES; i++) {
		if(zombieBats[i].getActive()) {
			
			for(int j = 0; j < MAX_POWER_SUPPLIES; j++) {
				if(powerSupplies[j].getActive())
					if(zombieBats[i].ai(frameTime, powerSupplies[j]))
						break;
			}
			for(int j = 0; j < MAX_HOUSES; j++) {
				if(houses[j].getActive())
					if(zombieBats[i].ai(frameTime, houses[j]))
						break;
			}
			for(int j = 0; j < MAX_AIR_FIELDS; j++) {
				if(airFields[j].getActive())
					if(zombieBats[i].ai(frameTime, airFields[j]))
						break;
			}
			zombieBats[i].ai(frameTime, base);	
		}
	}

	//GROUND TURRETS
	for(int i = 0; i < MAX_GROUND_TURRETS; i++) {
		if(turrets[i].getActive())
			for(int j = 0; j < MAX_GROUND_ENEMIES; j++)
				if(zombies[j].getActive())
					turrets[i].ai(frameTime, zombies[j]);
	}

	//AIR TURRETS
	for(int i = 0; i < MAX_AIR_TURRETS; i++) {
		if(aaturrets[i].getActive())
		for(int j = 0; j < MAX_AIR_ENEMIES; j++)
			if(zombieBats[j].getActive())		
				aaturrets[i].ai(frameTime, zombieBats[j]);
	}
}
//=============================================================================
// Handle collisions
//=============================================================================
void SootNSickle::collisions()
{
	VECTOR2 collision;
	for(int i = 0; i < MAX_GROUND_ENEMIES; i++) {
		if(zombies[i].getActive() && zombies[i].collidesWith(*zombies[i].getWaypoint(), collision))
			zombies[i].nextWaypoint();
	}
	for(int i = 0; i < MAX_AIR_ENEMIES; i++) {
		if(zombieBats[i].getActive() && zombieBats[i].collidesWith(*zombieBats[i].getWaypoint(), collision))
			zombieBats[i].nextWaypoint();
	}
}

//=============================================================================
// Render game items
//=============================================================================
void SootNSickle::render()
{
	graphics->spriteBegin();                // begin drawing sprites

	switch (currentState){
	case TitleScreen:
		menuRender();
		break;
	default:
		levelsRender();
	}

	graphics->spriteEnd();                  // end drawing sprites


}

void SootNSickle::menuRender()
{
	VECTOR2 UIScreenLoc(0,0);

	if(showGameOverScreen)
	{
		gameOver.draw(UIScreenLoc);
		infoText.print("SECONDS ALIVE:",200,350);
		infoText.print(std::to_string((int)secondsSurvived),400,350);
		infoText.print("ENEMIES KILLED:",200,375);
		infoText.print(std::to_string((int)enemeiesKilled),400,375);
		infoText.print("MINERALS MINED:",200,400);
		infoText.print(std::to_string((int)mineralsMined),400,400);
		infoText.print("SCORE:",200,450);
		infoText.print(std::to_string(getScore()),400,450);

		//maxes
		infoText.print("HIGH SCORES:",600,350);
		infoText.print(std::to_string((int)MaxSecondsSurvived),800,350);
		infoText.print(std::to_string((int)MaxEnemeiesKilled),800,375);
		infoText.print(std::to_string((int)MaxMineralsMined),800,400);
		infoText.print(std::to_string((int)MaxScore),800,450);
		infoText.print("PRESS ENTER TO CONTINUE",500,600);
		if(victory)
			infoText.print("VICTORY",500,650);
	}
	else
	{
		mainMenuBackground.draw(UIScreenLoc);
		for(int i = 0 ; i < MAIN_MENU_OPTION_COUNT; i++)
		{
			mainMenuOptions[i].draw(UIScreenLoc);
		}
	}
	if(showIcon)
		logo.draw(UIScreenLoc);
}

void SootNSickle::levelsRender()
{
	background.draw(screenLoc);

	base.getPowerField().draw(screenLoc);

	for(int i = 0; i < MAX_POWER_SUPPLIES;i++)
	{
		powerSupplies[i].getPowerField().draw(screenLoc);
	}

	for(int i = 0 ; i < MAX_PARTICLES; i++)
	{
		particles[i].draw(screenLoc);
	}

	base.draw(screenLoc);

	for(int i = 0; i < MAX_POWER_SUPPLIES;i++)
	{
		powerSupplies[i].draw(screenLoc);
	}

	for(int i = 0; i < MAX_MINERALS;i++)
		minerals[i].draw(screenLoc);

	for(int i = 0; i < MAX_EXTRACTORS;i++)
		extractors[i].draw(screenLoc);

	for(int i = 0; i < MAX_FACTORIES; i++)
		factories[i].draw(screenLoc);

	for(int i = 0; i < MAX_HOUSES; i++)
		houses[i].draw(screenLoc);

	for(int i = 0; i < MAX_GROUND_TURRETS; i++) {
		turrets[i].draw(screenLoc);
	}
	for(int i = 0; i < MAX_AIR_TURRETS; i++) {
		aaturrets[i].draw(screenLoc);
	}
	for(int i = 0; i < MAX_AIR_FIELDS; i++) {
		airFields[i].draw(screenLoc);
	}
	for(int i = 0; i < MAX_GROUND_ENEMIES; i++) {
		zombies[i].draw(screenLoc);
	}
	for(int i = 0; i < MAX_AIR_ENEMIES; i++) {
		zombieBats[i].draw(screenLoc);
	}

	guiOverlay.draw(VECTOR2(0,0));
	for(int i = 0 ; i < MAX_BUTTONS;i++)
	{

		int cost = -1;
		switch(buttons[i].getButtonType())
		{
		case ButtonNS::ButtonType::POWER_SUPPLY_SELECTION:cost = POWER_SUPPLY_COST; break;	
		case ButtonNS::ButtonType::GROUND_TURRET_SELECTION:cost = GROUND_TURRET_COST;break;
		case ButtonNS::ButtonType::AIR_TURRET_SELECTION: cost = AIR_TURRET_COST;break;
		case ButtonNS::ButtonType::FACTORY_SELECTION: cost = FACTORY_COST; break;
		case ButtonNS::ButtonType::EXTRACTOR_SELECTION: cost = EXTRACTOR_COST; break;
		case ButtonNS::ButtonType::HOUSE_SELECTION: cost = HOUSE_COST; break;
		case ButtonNS::ButtonType::AIR_FIELD_SELECTION: cost = AIR_FIELD_COST; break;
		}
		if(cost > 0)
		{
			RECT r;
			r.bottom = buttons[i].getY();
			r.left = buttons[i].getX();
			r.top = r.bottom - 20;
			r.right = r.left + buttons[i].getWidth();
			infoText.print(std::to_string(cost),r, DT_CENTER|DT_VCENTER);
		}

		buttons[i].draw(VECTOR2(0,0));
	}

	if(cursorSelection >= 0 && cursorSelection < (int)ButtonNS::SIZE)
	{
		cursor.setCenter(getMouseInWorld());
		cursor.draw(screenLoc);
	}

	infoText.print("MINERALS",20,5);
	infoText.print("IDLE/TOTAL/MAX",150,5);
	infoText.print("UPGRADE",400,5);
	infoText.print("Level Timer: ",1100,5);

	infoText.print(std::to_string((int)mineralLevel),20,25);
	infoText.print(std::to_string(idlePopulation) + "/" + std::to_string(population)+ "/" + std::to_string(capacity),150,25);
	infoText.print(std::to_string((int)upgradePoints),400,25);
	infoText.print(std::to_string((int)levelTimer),1220,5);

	if(levelTextCooldown>0)
	{
		float ex = 1-levelTextCooldown/SHOW_TEXT_TIME;
		float alpha = (1-pow(4*ex-1,4)); //dont ask
		levelText.setFontColor(Graphics::calculateAlpha(alpha));
	
		RECT screen;
		screen.left = 0;
		screen.top = -alpha*20;
		screen.right = GAME_WIDTH;
		screen.bottom = GAME_HEIGHT;
		levelText.print(levelString,screen,DT_CENTER|DT_VCENTER);
	}
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void SootNSickle::releaseAll()
{
	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void SootNSickle::resetAll()
{
	Game::resetAll();
	return;
}



void SootNSickle::menuLoad()
{

	currentState = TitleScreen;
	deactivateAll();

	mainMenuBackground.setVisible(true);
	mainMenuBackground.setX(0);
	mainMenuBackground.setY(0);

	for(int i = 0 ; i < MAIN_MENU_OPTION_COUNT; i++)
	{
		mainMenuOptions[i].setVisible(true);
	}

	tutorialSelection = 0;
	showTutorial = false;
	showIcon = false;
	logo.setX(10);
	logo.setY(GAME_HEIGHT - logo.getHeight()-10);
	gameOver.setX(0);gameOver.setY(0);
	showGameOverScreen = false;

}

void SootNSickle::level1Load()
{
	mineralsMined = 0;
	enemeiesKilled = 0;
	buildingsDestroyed = 0;
	secondsSurvived = 0;
	victory = false;

	levelTimer = 120;
	currentState = Level1;
	deactivateAll();
	base.create(getCurrentWorldSize()*0.5);

	for(float theta = 0; theta < 2*PI; theta+= PI/14)
	{
		for(float r = base.getWidth()+200; r < getCurrentWorldSize().x*1.4;r+=150)
		{
			if(rand()%((int)sqrt(0.35*r))==7)
			{
				VECTOR2 dist(r,0);
				dist = rotateVector(dist,theta);
				dist += getCurrentWorldSize()*0.5;

				if(dist.x > 50 && dist.x < getCurrentWorldSize().x-50 && dist.y > 50 && dist.y < getCurrentWorldSize().y-50)
				{
					MineralPatch* m = spawnMinerals(dist,randPM5()*MineralNS::DEFAULT_MINERALS*(r/2000));
					if(!isBuildingLocationLegal(m)) m->setActive(false);
				}	
			}
		}
	}


	path1.add(VECTOR2(1200,200));
	path1.add(VECTOR2(800,200));
	path1.add(VECTOR2(600,600));
	path1.add(base.getCenter());


	zs1.setCenter(VECTOR2(getCurrentWorldSize().x+(randmax(200)),getCurrentWorldSize().y/2+(randmax(200))));
	zs1.setManager(&path1);
	zs1.addWave(2, GROUND, 10);
	zs1.addWave(1, AIR, 0);
	zs1.addWave(5, GROUND, 15);
	zs1.addWave(3, AIR, 0);
	zs1.addWave(20, GROUND, 30);
	zs1.addWave(9, AIR, 0);

	guiLoad();

	capacity = 25;
	addPopulation(10);

	mineralLevel = 1000;

	screenLoc = base.getCenter() - VECTOR2(GAME_WIDTH/2,GAME_HEIGHT/2);
	updateScreen();

	levelTextCooldown = SHOW_TEXT_TIME;
	levelString = "SURVIVE";
}

void SootNSickle::level2Load()
{
	levelTimer = 420;
	currentState = Level2;
	resetZombies();
	healBuildings();

	path1.add(VECTOR2(1200,200));
	path1.add(VECTOR2(800,200));
	path1.add(VECTOR2(600,600));
	path1.add(base.getCenter());
	zs1.setCenter(VECTOR2(getCurrentWorldSize().x+(randmax(200)),getCurrentWorldSize().y/2+(randmax(200))));
	zs1.setManager(&path1);

	zs1.addWave(3, GROUND, 10);
	zs1.addWave(2, AIR, 0);

	zs1.addWave(10, GROUND, 15);
	zs1.addWave(3, AIR, 0);
	zs1.addWave(3, AIR, 3);

	zs1.addWave(35, GROUND, 27);
	zs1.addWave(12, AIR, 0);

	path2.add(VECTOR2(800,getCurrentWorldSize().y-100));
	path2.add(VECTOR2(1000, getCurrentWorldSize().y-400));
	path2.add(base.getCenter());

	zs2.setCenter(VECTOR2(0,getCurrentWorldSize().y+(randmax(200))));
	zs2.setManager(&path2);
	zs2.addWave(1, GROUND, 10);
	zs2.addWave(2, AIR, 0);
	zs2.addWave(2, GROUND, 15);
	zs2.addWave(5, AIR, 0);
	zs2.addWave(5, GROUND, 30);
	zs2.addWave(15, AIR, 0);

	levelTextCooldown = SHOW_TEXT_TIME;
	levelString = "LEVEL 2";
}

void SootNSickle::level3Load()
{
	levelTimer = 420;
	currentState = Level3;
	healBuildings();
	resetZombies();

	path1.add(VECTOR2(1200,200));
	path1.add(VECTOR2(800,200));
	path1.add(VECTOR2(600,600));
	path1.add(base.getCenter());

	zs1.setCenter(VECTOR2(getCurrentWorldSize().x+(randmax(200)),getCurrentWorldSize().y/2+(randmax(200))));
	zs1.setManager(&path1);
	zs1.addWave(5, GROUND, 10);
	zs1.addWave(3, AIR, 0);
	zs1.addWave(15, GROUND, 15);
	zs1.addWave(4, AIR, 0);
	zs1.addWave(4, AIR, 3);
	zs1.addWave(4, AIR, 3);

	zs1.addWave(50, GROUND, 24);
	zs1.addWave(18, AIR, 0);

	path2.add(VECTOR2(600,getCurrentWorldSize().y*3/4));
	path2.add(VECTOR2(1000, getCurrentWorldSize().y/2));
	path2.add(base.getCenter());

	zs2.setCenter(VECTOR2(0,getCurrentWorldSize().y+(randmax(200))));
	zs2.setManager(&path2);
	zs2.addWave(2, GROUND, 15);
	zs2.addWave(3, AIR, 0);

	zs2.addWave(3, GROUND, 20);
	zs2.addWave(8, AIR, 0);

	zs2.addWave(8, GROUND, 30);
	zs2.addWave(20, AIR, 0);

	path3.add(VECTOR2(1000,getCurrentWorldSize().y/4));
	path3.add(VECTOR2(800, getCurrentWorldSize().y/2));
	path3.add(base.getCenter());

	zs3.setCenter(VECTOR2(0,0));
	zs3.setManager(&path2);

	zs3.addWave(5, GROUND, 15);
	zs3.addWave(5, AIR, 2);

	zs3.addWave(10, GROUND, 18);
	zs3.addWave(10, AIR, 2);

	zs3.addWave(20, GROUND, 28);
	zs3.addWave(20, AIR, 2);

	levelTextCooldown = SHOW_TEXT_TIME;
	levelString = "LEVEL 3: Final Level";
}

void SootNSickle::feelingLuckyLoad()
{
	currentState = FeelingLucky;
	deactivateAll();


}

void SootNSickle::guiLoad()
{
	int type = 0;
	bool cellNewLine = true;
	tutorial.setX(0);tutorial.setY(0);
	for(float y = GAME_HEIGHT*0.7;y<GAME_HEIGHT-ButtonNS::HEIGHT;y+=ButtonNS::HEIGHT+20)
		for(float x = GAME_WIDTH*0.8;x<GAME_WIDTH-ButtonNS::WIDTH;x+=ButtonNS::WIDTH+10)
		{
			if(type == ButtonNS::ButtonType::SELL_SELECTION && cellNewLine)
			{
				cellNewLine = false;
				break;
			}
			spawnButton(VECTOR2(x,y),(ButtonNS::ButtonType)type);
			type++;
			if(type >= (int)ButtonNS::ButtonType::SIZE) return;

		}
	
}

void SootNSickle::updateScreen()
{
	if(screenLoc.x<0)screenLoc.x=0;
	if(screenLoc.y<0)screenLoc.y=0;
	if(screenLoc.x+GAME_WIDTH>worldSizes[currentState].x)screenLoc.x=worldSizes[currentState].x-GAME_WIDTH;
	if(screenLoc.y+GAME_HEIGHT>worldSizes[currentState].y)screenLoc.y=worldSizes[currentState].y-GAME_HEIGHT;
}

PowerSupply* SootNSickle::spawnPowerSupply(VECTOR2 loc)
{
	for(int i = 0 ; i < MAX_POWER_SUPPLIES; i++)
	{
		if(!powerSupplies[i].getActive())
		{
			powerSupplies[i].create(loc);
			return &powerSupplies[i];
		}
	}
	return nullptr;
}

Factory* SootNSickle::spawnFactory(VECTOR2 loc)
{
	for(int i = 0; i < MAX_FACTORIES; i++)
	{
		if(!factories[i].getActive())
		{
			factories[i].create(loc);
			return &factories[i];
		}
	}
	return nullptr;
}

Button * SootNSickle::spawnButton(VECTOR2 loc,ButtonNS::ButtonType t)
{
	for(int i = 0; i < MAX_BUTTONS; i++)
	{
		if(!buttons[i].getActive())
		{
			buttons[i].create(loc,t);
			return &buttons[i];
		}
	}
	return nullptr;
}

Particle* SootNSickle::spawnParticle(VECTOR2 loc,VECTOR2 vel, COLOR_ARGB c,float lifespan,bool reverseFade)
{
	for(int i = 0; i < MAX_PARTICLES; i++)
	{
		if(!particles[i].getActive())
		{
			particles[i].create(loc,vel,c,lifespan,reverseFade);
			return &particles[i];
		}
	}

	return nullptr;
}



void SootNSickle::spawnParticleCloud(VECTOR2 loc, COLOR_ARGB c, int n)
{
	float dir,spd;
	VECTOR2 v(1,0);
	for(int i = 0; i < n; i++)
	{
		dir = rand01()*2*PI;
		spd = rand01()*particleNS::CLOUD_VEL;
		spawnParticle(loc,rotateVector(v,dir)*spd,c);
	}
}

void SootNSickle::spawnParticleCone(VECTOR2 loc,float dir, COLOR_ARGB c, int n)
{
	float currentdir,spd;
	VECTOR2 v(1,0);
	for(int i = 0; i < n; i++)
	{
		currentdir = rand01()*PI/4-PI/8+dir;
		spd = (rand01()/2+0.5)*particleNS::CONE_VEL;
		spawnParticle(loc,rotateVector(v,currentdir)*spd,c);
	}
}

Extractor* SootNSickle::spawnExtractor(VECTOR2 loc)
{
	for(int i = 0; i < MAX_EXTRACTORS; i++)
	{
		if(!extractors[i].getActive())
		{
			extractors[i].create(loc);
			return &extractors[i];
		}
	}

	return nullptr;
}
MineralPatch* SootNSickle::spawnMinerals(VECTOR2 loc, float ammount)
{
	for(int i = 0; i < MAX_MINERALS; i++)
	{
		if(!minerals[i].getActive())
		{
			minerals[i].create(loc,ammount);
			return &minerals[i];
		}
	}

	return nullptr;
}

Turret* SootNSickle::spawnTurret(VECTOR2 loc)
{
	for(int i = 0; i < MAX_GROUND_TURRETS; i++)
	{
		if(!turrets[i].getActive())
		{
			turrets[i].create(loc, 0);
			return &turrets[i];
		}
	}

	return nullptr;
}

Turret* SootNSickle::spawnAATurret(VECTOR2 loc)
{
	for(int i = 0; i < MAX_AIR_TURRETS; i++)
	{
		if(!aaturrets[i].getActive())
		{
			aaturrets[i].create(loc, 0);
			return &aaturrets[i];
		}
	}

	return nullptr;
}

Zombie* SootNSickle::spawnZombie(VECTOR2 loc)
{
	for(int i = 0; i < MAX_GROUND_ENEMIES; i++)
	{
		if(!zombies[i].getActive())
		{
			zombies[i].create(loc);
			return &zombies[i];
		}
	}

	return nullptr;
}

ZombieBat* SootNSickle::spawnZombieBat(VECTOR2 loc)
{
	for(int i = 0; i < MAX_AIR_ENEMIES; i++)
	{
		if(!zombieBats[i].getActive())
		{
			zombieBats[i].create(loc);
			return &zombieBats[i];
		}
	}

	return nullptr;
}

House* SootNSickle::spawnHouse(VECTOR2 loc)
{
	for(int i = 0; i < MAX_HOUSES; i++)
	{
		if(!houses[i].getActive())
		{
			houses[i].create(loc);
			return &houses[i];
		}
	}

	return nullptr;
}
AirField* SootNSickle::spawnAirField(VECTOR2 loc)
{
	for(int i = 0; i < MAX_AIR_FIELDS; i++)
	{
		if(!airFields[i].getActive())
		{
			airFields[i].create(loc);
			return &airFields[i];
		}
	}

	return nullptr;
}

void SootNSickle::deactivateAll()
{
	mineralLevel = population = idlePopulation = 0;

	cursorSelection = -1;
	for(int i = 0 ; i < MAX_FACTORIES;i++)
		factories[i].setActive(false);
	for(int i = 0 ; i < MAX_MINERALS; i++)
		minerals[i].setActive(false);
	for(int i = 0 ; i < MAX_EXTRACTORS; i++)
		extractors[i].setActive(false);
	for(int i = 0 ; i < MAX_POWER_SUPPLIES; i++)
		powerSupplies[i].setActive(false);
	for(int i = 0 ; i < MAX_PARTICLES; i++)
		particles[i].setActive(false);
	for(int i = 0 ; i < MAX_BUTTONS; i++)
		buttons[i].setActive(false);
	for(int i = 0; i < MAX_HOUSES; i++)
		houses[i].setActive(false);
	for(int i = 0 ; i < MAX_GROUND_TURRETS; i++)
		turrets[i].setActive(false);
	for(int i = 0 ; i < MAX_AIR_TURRETS; i++)
		aaturrets[i].setActive(false);
	for(int i = 0 ; i < MAX_HOUSES;i++)
		houses[i].setActive(false);
	for(int i = 0 ; i < MAX_AIR_FIELDS;i++)
		airFields[i].setActive(false);
	for(int i = 0 ; i < MAX_GROUND_ENEMIES;i++)
		zombies[i].setActive(false);
	for(int i = 0 ; i < MAX_AIR_ENEMIES;i++)
		zombieBats[i].setActive(false);
	base.setActive(false);
	path1.clear();
	path2.clear();
	path3.clear();
	zs1.clear();
	zs2.clear();
	zs3.clear();
}

void SootNSickle::resetZombies()
{
	for(int i = 0 ; i < MAX_GROUND_ENEMIES;i++)
		zombies[i].setActive(false);
	for(int i = 0 ; i < MAX_AIR_ENEMIES;i++)
		zombieBats[i].setActive(false);
	path1.clear();
	path2.clear();
	path3.clear();
	zs1.clear();
	zs2.clear();
	zs3.clear();
}

void SootNSickle::onBaseDeath()
{
	menuLoad();
	updateMaxes();
	showGameOverScreen = true;
}
void SootNSickle::raiseAllButtons(){
	for(int i = 0; i < MAX_BUTTONS;i++)
	{
		buttons[i].isPressed=false;
	}
	cursorSelection = -1;
}
void SootNSickle::buttonOnClick(Button* caller){
	raiseAllButtons();
	caller->isPressed = true;
	cursorSelection = (int) caller->getButtonType();
	cursor.setCurrentFrame(cursorSelection);
}


void SootNSickle::checkClick()
{

	if(cursorSelection == ButtonNS::POWER_SUPPLY_SELECTION && mineralLevel > POWER_SUPPLY_COST)
	{

		PowerSupply * p = spawnPowerSupply(getMouseInWorld());
		if(!isBuildingLocationLegal(p)) p->setActive(false);
		else
		{
			refreshPower();
			mineralLevel-=POWER_SUPPLY_COST;
			audio->playCue(SC_BUILDING);
		}
	}
	//custom for extractors (only build on mineral patch)
	else if(cursorSelection == ButtonNS::EXTRACTOR_SELECTION&& mineralLevel > EXTRACTOR_COST)
	{

		for(int i = 0 ; i < MAX_MINERALS; i++)
		{
			if(minerals[i].getActive())
			{
				VECTOR2 disp = getMouseInWorld() - minerals[i].getCenter();
				if(D3DXVec2LengthSq(&disp) <= pow(minerals[i].getRadius(),2))
				{
					bool noOtherExtractor = true;
					for(int j = 0 ; j < MAX_EXTRACTORS;j++)
					{
						if(extractors[j].getActive())
						{
							disp = getMouseInWorld() - extractors[j].getCenter();
							if(D3DXVec2LengthSq(&disp) <= pow(extractors[j].getRadius(),2))
							{
								noOtherExtractor = false;
								break;
							}
						}
					} //end extractos

					if(noOtherExtractor)
					{
						spawnExtractor(minerals[i].getCenter());
						refreshPower();
						mineralLevel-=EXTRACTOR_COST;
						audio->playCue(SC_BUILDING);
					}
				}
			}
		}//end minerals

	}//end extractor placement click
	else if(cursorSelection == ButtonNS::GROUND_TURRET_SELECTION&& mineralLevel > GROUND_TURRET_COST)
	{
		Turret * p = spawnTurret(getMouseInWorld());
		if(!isBuildingLocationLegal(p)) p->setActive(false);
		else
		{
			refreshPower();
			mineralLevel-=GROUND_TURRET_COST;
			audio->playCue(SC_BUILDING);
		}
	}
	else if(cursorSelection == ButtonNS::AIR_TURRET_SELECTION&& mineralLevel > AIR_TURRET_COST)
	{
		Turret * p = spawnAATurret(getMouseInWorld());
		if(!isBuildingLocationLegal(p)) p->setActive(false);
		else
		{
			refreshPower();
			mineralLevel-=GROUND_TURRET_COST;
			audio->playCue(SC_BUILDING);
		}
	}
	else if(cursorSelection == ButtonNS::FACTORY_SELECTION&& mineralLevel > FACTORY_COST)
	{
		Factory * p = spawnFactory(getMouseInWorld());
		if(!isBuildingLocationLegal(p)) p->setActive(false);
		else
		{
			refreshPower();
			mineralLevel-=FACTORY_COST;
			audio->playCue(SC_BUILDING);
		}
	}
	else if(cursorSelection == ButtonNS::HOUSE_SELECTION&& mineralLevel > HOUSE_COST)
	{
		House * p = spawnHouse(getMouseInWorld());
		if(!isBuildingLocationLegal(p)) p->setActive(false);
		else
		{
			refreshPower();
			mineralLevel-=HOUSE_COST;
			audio->playCue(SC_BUILDING);
		}
	}
	else if(cursorSelection == ButtonNS::AIR_FIELD_SELECTION&& mineralLevel > AIR_FIELD_COST)
	{
		AirField * p = spawnAirField(getMouseInWorld());
		if(!isBuildingLocationLegal(p)) p->setActive(false);
		else
		{
			refreshPower();
			mineralLevel-=AIR_FIELD_COST;
			audio->playCue(SC_BUILDING);
		}
	}
	else if(cursorSelection == ButtonNS::SELL_SELECTION)
	{
		attemptToSellBuilding();
	}
	else if(cursorSelection == ButtonNS::UPGRADE_SELECTION && upgradePoints > 1)
	{
		attemptToUpgradeBuilding();
	}
	else if(cursorSelection == ButtonNS::DEACTIVATE_SELECTION)
	{
		attemptToTogglePower();
	}
}

bool SootNSickle::isBuildingLocationLegal(Actor* newBuilding)
{
	VECTOR2 v;
	if(newBuilding->collidesWith(base,v))return false;
	for(int i = 0; i < MAX_POWER_SUPPLIES;i++)
	{
		if((&powerSupplies[i]!=newBuilding)&&newBuilding->collidesWith(powerSupplies[i],v))
			return false;
	}
	for(int i = 0; i < MAX_EXTRACTORS;i++)
	{
		if((&extractors[i]!=newBuilding)&&newBuilding->collidesWith(extractors[i],v))
			return false;
	}
	for(int i = 0; i < MAX_MINERALS;i++)
	{
		if((&minerals[i]!=newBuilding)&&newBuilding->collidesWith(minerals[i],v))
			return false;
	}
	for(int i = 0; i < MAX_GROUND_TURRETS; i++) {
		if((&turrets[i]!=newBuilding)&&newBuilding->collidesWith(turrets[i],v))
			return false;
	}
	for(int i = 0; i < MAX_AIR_TURRETS; i++) {
		if((&aaturrets[i]!=newBuilding)&&newBuilding->collidesWith(aaturrets[i],v))
			return false;
	}
	for(int i = 0; i < MAX_FACTORIES; i++) {
		if((&factories[i]!=newBuilding)&&newBuilding->collidesWith(factories[i],v))
			return false;
	}
	for(int i = 0; i < MAX_HOUSES; i++){
		if((&houses[i]!=newBuilding)&&newBuilding->collidesWith(houses[i],v))
			return false;
	}
	for(int i = 0; i < MAX_AIR_FIELDS; i++){
		if((&airFields[i]!=newBuilding)&&newBuilding->collidesWith(airFields[i],v))
			return false;
	}
	return true;
}

void SootNSickle::attemptToSellBuilding()
{
	VECTOR2 disp;
	VECTOR2 mouse = getMouseInWorld();

	for(int i = 0; i < MAX_POWER_SUPPLIES;i++)
	{
		if(powerSupplies[i].getActive())
		{
			disp = mouse - powerSupplies[i].getCenter();
			if(D3DXVec2Length(&disp) < powerSupplies[i].getRadius())
			{
				powerSupplies[i].setActive(false);
				idlePopulation += powerSupplies[i].getStaff();
				mineralLevel += POWER_SUPPLY_COST*SELL_BACK_RATE;
				audio->playCue(SC_SELL);
			}
		}
	}
	for(int i = 0; i < MAX_EXTRACTORS;i++)
	{
		if(extractors[i].getActive())
		{
			disp = mouse - extractors[i].getCenter();
			if(D3DXVec2Length(&disp) < extractors[i].getRadius())
			{
				extractors[i].setActive(false);
				idlePopulation += extractors[i].getStaff();
				mineralLevel += EXTRACTOR_COST*SELL_BACK_RATE;
				audio->playCue(SC_SELL);
			}
		}
	}
	for(int i = 0; i < MAX_GROUND_TURRETS; i++) {
		if(turrets[i].getActive())
		{
			disp = mouse - turrets[i].getCenter();
			if(D3DXVec2Length(&disp) < turrets[i].getRadius())
			{
				turrets[i].setActive(false);
				idlePopulation += turrets[i].getStaff();
				mineralLevel += GROUND_TURRET_COST*SELL_BACK_RATE;
				audio->playCue(SC_SELL);
			}
		}
	}
	for(int i = 0; i < MAX_AIR_TURRETS; i++) {
		if(aaturrets[i].getActive())
		{
			disp = mouse - aaturrets[i].getCenter();
			if(D3DXVec2Length(&disp) < aaturrets[i].getRadius())
			{
				aaturrets[i].setActive(false);
				idlePopulation += aaturrets[i].getStaff();
				mineralLevel += AIR_TURRET_COST*SELL_BACK_RATE;
				audio->playCue(SC_SELL);
			}
		}
	}
	for(int i = 0; i < MAX_FACTORIES; i++) {
		if(factories[i].getActive())
		{
			disp = mouse - factories[i].getCenter();
			if(D3DXVec2Length(&disp) < factories[i].getRadius())
			{
				factories[i].setActive(false);
				idlePopulation += factories[i].getStaff();
				mineralLevel += FACTORY_COST*SELL_BACK_RATE;
				audio->playCue(SC_SELL);
			}
		}
	}
	for(int i = 0; i < MAX_HOUSES; i++){
		if(houses[i].getActive())
		{
			disp = mouse - houses[i].getCenter();
			if(D3DXVec2Length(&disp) < houses[i].getRadius())
			{
				houses[i].setActive(false);
				mineralLevel += HOUSE_COST*SELL_BACK_RATE;
				audio->playCue(SC_SELL);
			}
		}
	}
	for(int i = 0; i < MAX_AIR_FIELDS; i++){
		if(airFields[i].getActive())
		{
			disp = mouse - airFields[i].getCenter();
			if(D3DXVec2Length(&disp) < airFields[i].getRadius())
			{
				airFields[i].setActive(false);
				idlePopulation += airFields[i].getStaff();
				mineralLevel += AIR_FIELD_COST*SELL_BACK_RATE;
				audio->playCue(SC_SELL);
			}
		}
	}
	refreshPower();
}

void SootNSickle::attemptToUpgradeBuilding()
{
	VECTOR2 disp;
	VECTOR2 mouse = getMouseInWorld();

	disp = mouse - base.getCenter();
	if(D3DXVec2Length(&disp) < base.getRadius())
	{
		upgradePoints-=1;
		base.upgrade();
		audio->playCue(SC_UPGRADE);
	}

	for(int i = 0; i < MAX_POWER_SUPPLIES;i++)
	{
		if(powerSupplies[i].getActive()&&powerSupplies[i].getLevel()<3)
		{
			disp = mouse - powerSupplies[i].getCenter();
			if(D3DXVec2Length(&disp) < powerSupplies[i].getRadius())
			{
				upgradePoints-=1;
				powerSupplies[i].upgrade();
				audio->playCue(SC_UPGRADE);
			}
		}
	}
	for(int i = 0; i < MAX_EXTRACTORS;i++)
	{
		if(extractors[i].getActive()&&extractors[i].getLevel()<3)
		{
			disp = mouse - extractors[i].getCenter();
			if(D3DXVec2Length(&disp) < extractors[i].getRadius())
			{
				upgradePoints-=1;
				extractors[i].upgrade();
				audio->playCue(SC_UPGRADE);
			}
		}
	}
	for(int i = 0; i < MAX_GROUND_TURRETS; i++) {
		if(turrets[i].getActive()&&turrets[i].getLevel()<3)
		{
			disp = mouse - turrets[i].getCenter();
			if(D3DXVec2Length(&disp) < turrets[i].getRadius())
			{
				upgradePoints-=1;
				turrets[i].upgrade();
				audio->playCue(SC_UPGRADE);
			}
		}
	}
	for(int i = 0; i < MAX_AIR_TURRETS; i++) {
		if(aaturrets[i].getActive()&&aaturrets[i].getLevel()<3)
		{
			disp = mouse - aaturrets[i].getCenter();
			if(D3DXVec2Length(&disp) < aaturrets[i].getRadius())
			{
				upgradePoints-=1;
				aaturrets[i].upgrade();
				audio->playCue(SC_UPGRADE);
			}
		}
	}
	for(int i = 0; i < MAX_FACTORIES; i++) {
		if(factories[i].getActive()&&factories[i].getLevel()<3)
		{
			disp = mouse - factories[i].getCenter();
			if(D3DXVec2Length(&disp) < factories[i].getRadius())
			{
				upgradePoints-=1;
				factories[i].upgrade();
				audio->playCue(SC_UPGRADE);
			}
		}
	}
	for(int i = 0; i < MAX_HOUSES; i++){
		if(houses[i].getActive()&&houses[i].getLevel()<3)
		{
			disp = mouse - houses[i].getCenter();
			if(D3DXVec2Length(&disp) < houses[i].getRadius())
			{
				upgradePoints-=1;
				houses[i].upgrade();
				audio->playCue(SC_UPGRADE);
			}
		}
	}
	for(int i = 0; i < MAX_AIR_FIELDS; i++){
		if(airFields[i].getActive()&&airFields[i].getLevel()<3)
		{
			disp = mouse - airFields[i].getCenter();
			if(D3DXVec2Length(&disp) < airFields[i].getRadius())
			{
				upgradePoints-=1;
				airFields[i].upgrade();
				audio->playCue(SC_UPGRADE);
			}
		}
	}
}

void SootNSickle::attemptToTogglePower()
{
	VECTOR2 disp;
	VECTOR2 mouse = getMouseInWorld();
	

	for(int i = 0; i < MAX_POWER_SUPPLIES;i++)
	{
		if(powerSupplies[i].getActive())
		{
			disp = mouse - powerSupplies[i].getCenter();
			if(D3DXVec2Length(&disp) < powerSupplies[i].getRadius())
			{
				powerSupplies[i].powerToggle = ! powerSupplies[i].powerToggle;
			}
		}
	}
	for(int i = 0; i < MAX_EXTRACTORS;i++)
	{
		if(extractors[i].getActive())
		{
			disp = mouse - extractors[i].getCenter();
			if(D3DXVec2Length(&disp) < extractors[i].getRadius())
			{
				extractors[i].powerToggle = ! extractors[i].powerToggle;
			}
		}
	}
	for(int i = 0; i < MAX_GROUND_TURRETS; i++) {
		if(turrets[i].getActive())
		{
			disp = mouse - turrets[i].getCenter();
			if(D3DXVec2Length(&disp) < turrets[i].getRadius())
			{
				turrets[i].powerToggle = ! turrets[i].powerToggle;
			}
		}
	}
	for(int i = 0; i < MAX_AIR_TURRETS; i++) {
		if(aaturrets[i].getActive())
		{
			disp = mouse - aaturrets[i].getCenter();
			if(D3DXVec2Length(&disp) < aaturrets[i].getRadius())
			{
				aaturrets[i].powerToggle = ! aaturrets[i].powerToggle;
			}
		}
	}
	for(int i = 0; i < MAX_FACTORIES; i++) {
		if(factories[i].getActive())
		{
			disp = mouse - factories[i].getCenter();
			if(D3DXVec2Length(&disp) < factories[i].getRadius())
			{
				factories[i].powerToggle = ! factories[i].powerToggle;
			}
		}
	}
	for(int i = 0; i < MAX_HOUSES; i++){
		if(houses[i].getActive())
		{
			disp = mouse - houses[i].getCenter();
			if(D3DXVec2Length(&disp) < houses[i].getRadius())
			{
				houses[i].powerToggle = ! houses[i].powerToggle;
			}
		}
	}
	for(int i = 0; i < MAX_AIR_FIELDS; i++){
		if(airFields[i].getActive())
		{
			disp = mouse - airFields[i].getCenter();
			if(D3DXVec2Length(&disp) < airFields[i].getRadius())
			{
				airFields[i].powerToggle = ! airFields[i].powerToggle;
			}
		}
	}
}

void SootNSickle::refreshPower()
{
	VECTOR2 v;
	std::stack<PowerSupply*> s;

	for(int k = 0 ; k < MAX_EXTRACTORS; k++)
		extractors[k].setPower(extractors[k].collidesWith(base.getPowerField(),v));
	for(int i = 0; i < MAX_FACTORIES; i++) 
		factories[i].setPower(factories[i].collidesWith(base.getPowerField(),v));
	for(int i = 0; i < MAX_GROUND_TURRETS; i++) 
		turrets[i].setPower(turrets[i].collidesWith(base.getPowerField(),v));
	for(int i = 0; i < MAX_AIR_TURRETS; i++) 
		aaturrets[i].setPower(aaturrets[i].collidesWith(base.getPowerField(),v));
	for(int i = 0; i < MAX_HOUSES; i++)
		houses[i].setPower(houses[i].collidesWith(base.getPowerField(),v));
	for(int i = 0; i < MAX_AIR_FIELDS; i++)
		airFields[i].setPower(airFields[i].collidesWith(base.getPowerField(),v));

	for(int i = 0; i < MAX_POWER_SUPPLIES;i++)
	{
		if(powerSupplies[i].getActive())
		{
			VECTOR2 disp = base.getCenter()-powerSupplies[i].getCenter(); 
			float distSqrd = D3DXVec2LengthSq(&disp);

			if(powerSupplies[i].collidesWith(base.getPowerField(),v)){
				powerSupplies[i].setPower(true);
				s.push(&powerSupplies[i]);
			}

			else
				powerSupplies[i].setPower(false);
		}
	}

	while(!s.empty())
	{
		PowerSupply * currPwrSupp = s.top();
		s.pop();

		if(currPwrSupp->getPower())
		{
			for(int i = 0; i < MAX_POWER_SUPPLIES;i++)
			{
				if(powerSupplies[i].getActive()
					&&!powerSupplies[i].getPower()
					&&currPwrSupp->getPowerField().collidesWith(powerSupplies[i],v))
				{
					powerSupplies[i].setPower(true);
					s.push(&powerSupplies[i]);
				}
			}
			for(int k = 0 ; k < MAX_EXTRACTORS; k++)
			{
				if(!extractors[k].getPower()&&currPwrSupp->getPowerField().collidesWith(extractors[k],v))
					extractors[k].setPower(true);
			}
			for(int i = 0; i < MAX_FACTORIES; i++) 
			{
				if(!factories[i].getPower()&&currPwrSupp->getPowerField().collidesWith(factories[i],v))
					factories[i].setPower(true);
			}
			for(int i = 0; i < MAX_GROUND_TURRETS; i++) 
			{
				if(!turrets[i].getPower()&&currPwrSupp->getPowerField().collidesWith(turrets[i],v))
					turrets[i].setPower(true);
			}
			for(int i = 0; i < MAX_AIR_TURRETS; i++) 
			{
				if(!aaturrets[i].getPower()&&currPwrSupp->getPowerField().collidesWith(aaturrets[i],v))
					aaturrets[i].setPower(true);
			}
			for(int i = 0; i < MAX_HOUSES; i++) 
			{
				if(!houses[i].getPower()&&currPwrSupp->getPowerField().collidesWith(houses[i],v))
					houses[i].setPower(true);
			}
			for(int i = 0; i < MAX_AIR_FIELDS; i++) 
			{
				if(!airFields[i].getPower()&&currPwrSupp->getPowerField().collidesWith(airFields[i],v))
					airFields[i].setPower(true);
			}
		}
	}
}

MineralPatch* SootNSickle::findMineableMinerals(Extractor * caller)
{
	VECTOR2 v;
	for(int i = 0 ; i < MAX_MINERALS;i++)
	{
		if(minerals[i].getActive())
		{
			VECTOR2 dist = caller->getCenter()-minerals[i].getCenter();
			//close enough to mine
			if(D3DXVec2LengthSq(&dist) < ExtractorNS::MINING_RANGE*ExtractorNS::MINING_RANGE)
				return &minerals[i];
		}

	}
	return nullptr;
}


void SootNSickle::updateMaxes()
{
	std::fstream fin;
	fin.open("scores.txt",std::ios::in);
	if(fin)
	{
		fin>>MaxMineralsMined;
		fin>>MaxEnemeiesKilled;
		fin>>MaxBuildingsDestroyed;
		fin>>MaxSecondsSurvived;
		fin>>MaxScore;
	}
	else
	{
		MaxMineralsMined = 0;
		MaxEnemeiesKilled = 0;
		MaxBuildingsDestroyed = 0;
		MaxSecondsSurvived = 0;
		MaxScore = 0;
	}
	fin.close();

	MaxMineralsMined = max(MaxMineralsMined,mineralsMined);
	MaxEnemeiesKilled = max(MaxEnemeiesKilled,enemeiesKilled);
	MaxBuildingsDestroyed = max(MaxBuildingsDestroyed,buildingsDestroyed);
	MaxSecondsSurvived = max(MaxSecondsSurvived,secondsSurvived);
	MaxScore = max(MaxScore,getScore());

	std::fstream fout;
	fout.open("scores.txt",std::ios::out);
	fout<<MaxMineralsMined<<std::endl;
	fout<<MaxEnemeiesKilled<<std::endl;
	fout<<MaxBuildingsDestroyed<<std::endl;
	fout<<MaxSecondsSurvived<<std::endl;
	fout<<MaxScore<<std::endl;
	fout.close();
}

void SootNSickle::healBuildings() {
			for(int i = 0; i < MAX_POWER_SUPPLIES;i++)
			{
				powerSupplies[i].heal(50);
			}
			for(int i = 0 ; i < MAX_EXTRACTORS; i++)
			{
				extractors[i].heal(50);
			}
			for(int i = 0; i < MAX_FACTORIES; i++) 
			{
				factories[i].heal(50);
			}
			for(int i = 0; i < MAX_GROUND_TURRETS; i++) 
			{
				turrets[i].heal(50);
			}
			for(int i = 0; i < MAX_AIR_TURRETS; i++) 
			{
				aaturrets[i].heal(50);
			}
			for(int i = 0; i < MAX_HOUSES; i++) 
			{
				houses[i].heal(50);
			}
			for(int i = 0; i < MAX_AIR_FIELDS; i++) 
			{
				airFields[i].heal(50);
			}
}