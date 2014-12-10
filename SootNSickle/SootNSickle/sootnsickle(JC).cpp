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
	worldSizes[GameState::Level1] = VECTOR2(GAME_WIDTH*2,GAME_HEIGHT*2);
	worldSizes[GameState::Level2] = VECTOR2(GAME_WIDTH,GAME_HEIGHT);
	worldSizes[GameState::Level3] = VECTOR2(GAME_WIDTH,GAME_HEIGHT);
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


	if(!backgroundTex.initialize(graphics,BACKGROUND_IMAGE))
		throw GameError(1,"Failed to init background tex");
	

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


	if(!mineralTex.initialize(graphics,MINERAL_IMAGE))
		throw GameError(6,"Failed to init mineral tex");

	if(!factoryTex.initialize(graphics,FACTORY_IMAGE))
		throw GameError(6,"Failed to init factory tex");

	if(!extractorTex.initialize(graphics,EXTRACTOR_IMAGE))
		throw GameError(6,"Failed to init extractor tex");
	if(!turretgTex.initialize(graphics,TURRETG_IMAGE))
		throw GameError(6,"Failed to init extractor tex");
	if(!standTex.initialize(graphics,TURRETBASE_IMAGE))
		throw GameError(6,"Failed to init extractor tex");	
	if(!houseTex.initialize(graphics,HOUSE_IMAGE))
		throw GameError(6,"Failed to init house tex");	
	if(!airFieldTex.initialize(graphics,AIR_FIELD_IMAGE))
		throw GameError(6,"Failed to init house tex");

	if(!background.initialize(graphics,0,0,0,&backgroundTex))
		throw GameError(9,"Failed to init background");

	if(!guiOverlay.initialize(graphics,0,0,0,&guiOverlayTex))
		throw GameError(9,"Failed to init gui overlay");

	if(!base.initialize(this,0,0,0,&baseTex,&healthBarTex,&powerFieldTex))
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
			throw GameError(-1*i,"FAILED TO MAKE turret!");
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
		if(!airFields[i].initialize(this,0,0,0,&airFieldTex,&healthBarTex,&buildingText))
				throw GameError(-1*i,"FAILED TO MAKE air field!");
	for(int i = 0; i < MAX_GROUND_ENEMIES; i++)
		if(!zombies[i].initialize(this,0,0,0,&airFieldTex,&healthBarTex))
				throw GameError(-1*i,"FAILED TO MAKE zombie!");

	currentState = Level1;
	level1Load();

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void SootNSickle::update()
{

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
	
}

void SootNSickle::levelsUpdate()
{
	if(input->wasKeyPressed('R'))
	{
		level1Load();
	}

	if(input->getMouseRButton())
		raiseAllButtons();

	if(input->wasKeyPressed(controls.pause))
	{
		paused = !paused;
	}

	if(paused) return;


	VECTOR2 in(0,0);

	if(input->isKeyDown(controls.up))
		in.y -= 1;
	if(input->isKeyDown(controls.down))
		in.y += 1;
	if(input->isKeyDown(controls.left))
		in.x -= 1;
	if(input->isKeyDown(controls.right))
		in.x += 1;

	if(input->wasKeyPressed(VK_UP))
		base.damage(10);
	if(input->wasKeyPressed(VK_DOWN))
		base.heal(10);

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
			newCapacity+=HouseNS::HOUSING;
	}
	for(int i = 0; i < MAX_AIR_FIELDS; i++)
	{
		airFields[i].update(frameTime);
	}
	for(int i = 0; i < MAX_GROUND_TURRETS; i++)
	{
		turrets[i].update(frameTime);
	}
	for(int i = 0; i < MAX_GROUND_ENEMIES; i++)
		zombies[i].update(frameTime);

	capacity = newCapacity;
	if(population > capacity) population = capacity;

	//check fisrt click
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
	/*for(int i = 0; i < MAX_GROUND_ENEMIES; i++) {
	}*/
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
	for(int i = 0; i < MAX_AIR_FIELDS; i++) {
		airFields[i].draw(screenLoc);
	}
	for(int i = 0; i < MAX_GROUND_ENEMIES; i++) {
		zombies[i].draw(screenLoc);
	}


	guiOverlay.draw(VECTOR2(0,0));
	for(int i = 0 ; i < MAX_BUTTONS;i++)
	{
		buttons[i].draw(VECTOR2(0,0));
	}

	if(cursorSelection >= 0 && cursorSelection < (int)ButtonNS::SIZE)
	{
		cursor.setCenter(getMouseInWorld());
		cursor.draw(screenLoc);
	}

	infoText.print(std::to_string((int)mineralLevel),20,20);
	infoText.print(std::to_string(idlePopulation) + "/" + std::to_string(population)+ "/" + std::to_string(capacity),100,20);
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

}

void SootNSickle::level1Load()
{
	currentState = Level1;
	deactivateAll();
	base.create(getCurrentWorldSize()*0.5);
	path1.add(VECTOR2(1000,200));
	path1.add(base.getCenter());
	Zombie* z = spawnZombie(VECTOR2(GAME_WIDTH*2,GAME_HEIGHT));
	z->setWaypoint(path1.get());
	guiLoad();

	spawnMinerals(VECTOR2(100,100),1000);
	spawnMinerals(VECTOR2(300,500),1000);

	

	addPopulation(10);
	mineralLevel = 1000;
}

void SootNSickle::level2Load()
{
	currentState = Level2;
	deactivateAll();

	
}

void SootNSickle::level3Load()
{
	currentState = Level3;
	deactivateAll();

	
}

void SootNSickle::feelingLuckyLoad()
{
	currentState = FeelingLucky;
	deactivateAll();

}

void SootNSickle::guiLoad()
{
	int type = 0;
	for(float y = GAME_HEIGHT*0.8;y<GAME_HEIGHT-ButtonNS::HEIGHT;y+=ButtonNS::HEIGHT+10)
		for(float x = GAME_WIDTH*0.8;x<GAME_WIDTH-ButtonNS::WIDTH;x+=ButtonNS::WIDTH+10)
		{
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
	for(int i = 0; i < MAX_MINERALS; i++)
	{
		if(!turrets[i].getActive())
		{
			turrets[i].create(loc, 0);
			return &turrets[i];
		}
	}

	return nullptr;
}

Zombie* SootNSickle::spawnZombie(VECTOR2 loc)
{
	for(int i = 0; i < MAX_MINERALS; i++)
	{
		if(!zombies[i].getActive())
		{
			zombies[i].create(loc);
			return &zombies[i];
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
	for(int i = 0 ; i < MAX_HOUSES;i++)
		houses[i].setActive(false);
	for(int i = 0 ; i < MAX_AIR_FIELDS;i++)
		airFields[i].setActive(false);
	base.setActive(false);
}

void SootNSickle::onBaseDeath()
{
	
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
		}
	}
	else if(cursorSelection == ButtonNS::EXTRACTOR_SELECTION&& mineralLevel > EXTRACTOR_COST)
	{
		Extractor * p = spawnExtractor(getMouseInWorld());
		if(!isBuildingLocationLegal(p)) p->setActive(false);
		else
		{
			refreshPower();
			mineralLevel-=EXTRACTOR_COST;
		}
	}
	else if(cursorSelection == ButtonNS::GROUND_TURRET_SELECTION&& mineralLevel > GROUND_TURRET_COST)
	{
		Turret * p = spawnTurret(getMouseInWorld());
		if(!isBuildingLocationLegal(p)) p->setActive(false);
		else
		{
			refreshPower();
			mineralLevel-=GROUND_TURRET_COST;
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
		}
	}
	else if(cursorSelection == ButtonNS::SELL_SELECTION)
	{
		attemptToSellBuilding();
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
			}
		}
	}
	refreshPower();
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