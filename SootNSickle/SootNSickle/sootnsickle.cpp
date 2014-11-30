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

	if(!infoText.initialize(graphics,20,true,false,"Verdana"))
		throw GameError(9,"Failed to init mine text");

	infoText.setFontColor(graphicsNS::WHITE);

	
	if(!background.initialize(graphics,0,0,0,&backgroundTex))
		throw GameError(9,"Failed to init background");

	if(!guiOverlay.initialize(graphics,0,0,0,&guiOverlayTex))
		throw GameError(9,"Failed to init gui overlay");

	if(!base.initialize(this,0,0,0,&baseTex,&healthBarTex))
		throw GameError(6,"Failed to init base");

	for(int i = 0 ; i < MAX_PARTICLES; i++)
	{
		if(!particles[i].initialize(this,0,0,0,&particleTex))
			throw GameError(-1*i,"FAILED TO MAKE particle!");
	}

	for(int i = 0 ; i < MAX_BUTTONS; i++)
	{
		if(!buttons[i].initialize(this,ButtonNS::WIDTH,ButtonNS::HEIGHT,ButtonNS::COLS,&buttonTex,0,1))
			throw GameError(-1*i,"FAILED TO MAKE button!");
	}

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
	if(input->wasKeyPressed(controls.pause))
	{
		paused = !paused;
		ShowCursor(paused);
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
		base.damage(1);
	if(input->wasKeyPressed(VK_DOWN))
		base.heal(1);

	D3DXVec2Normalize(&in,&in);
	in*=SCREEN_SPEED*frameTime;
	screenLoc += in;
	
	updateScreen();
	
	base.update(frameTime);

	for(int i = 0 ; i < MAX_PARTICLES; i++)
	{
		particles[i].update(frameTime);
	}

	for(int i = 0; i < MAX_BUTTONS;i++)
	{
		buttons[i].isClicked();
	}

}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void SootNSickle::ai()
{
}

//=============================================================================
// Handle collisions
//=============================================================================
void SootNSickle::collisions()
{
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

	base.draw(screenLoc);

	for(int i = 0 ; i < MAX_PARTICLES; i++)
	{
		particles[i].draw(screenLoc);
	}

	guiOverlay.draw(VECTOR2(0,0));
	for(int i = 0 ; i < MAX_BUTTONS;i++)
	{
		buttons[i].draw(VECTOR2(0,0));
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

}

void SootNSickle::level1Load()
{
	currentState = Level1;
	deactivateAll();
	base.setCenter(getCurrentWorldSize()*0.5);
	guiLoad();
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
	for(float y = GAME_HEIGHT*0.75;y<GAME_HEIGHT-ButtonNS::HEIGHT;y+=ButtonNS::HEIGHT+10)
		for(float x = GAME_WIDTH*0.8;x<GAME_WIDTH-ButtonNS::WIDTH;x+=ButtonNS::WIDTH+10)
			spawnButton(VECTOR2(x,y));
}

void SootNSickle::updateScreen()
{
	if(screenLoc.x<0)screenLoc.x=0;
	if(screenLoc.y<0)screenLoc.y=0;
	if(screenLoc.x+GAME_WIDTH>worldSizes[currentState].x)screenLoc.x=worldSizes[currentState].x-GAME_WIDTH;
	if(screenLoc.y+GAME_HEIGHT>worldSizes[currentState].y)screenLoc.y=worldSizes[currentState].y-GAME_HEIGHT;
}


Button * SootNSickle::spawnButton(VECTOR2 loc)
{
	for(int i = 0; i < MAX_BUTTONS; i++)
	{
		if(!buttons[i].getActive())
		{
			buttons[i].create(loc);
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



void SootNSickle::spawnParticleCloud(VECTOR2 loc, COLOR_ARGB c)
{
	float dir,spd;
	VECTOR2 v(1,0);
	for(int i = 0; i < NUM_PARTICLES_IN_CLOUD_EFFECT; i++)
	{
		dir = rand01()*2*PI;
		spd = rand01()*particleNS::CLOUD_VEL;
		spawnParticle(loc,rotateVector(v,dir)*spd,c);
	}
}

void SootNSickle::spawnParticleCone(VECTOR2 loc,float dir, COLOR_ARGB c)
{
	float currentdir,spd;
	VECTOR2 v(1,0);
	for(int i = 0; i < NUM_PARTICLES_IN_CONE_EFFECT; i++)
	{
		currentdir = rand01()*PI/4-PI/8+dir;
		spd = (rand01()/2+0.5)*particleNS::CONE_VEL;
		spawnParticle(loc,rotateVector(v,currentdir)*spd,c);
	}
}



void SootNSickle::deactivateAll()
{
	for(int i = 0 ; i < MAX_PARTICLES; i++)
		particles[i].setActive(false);
	for(int i = 0 ; i < MAX_BUTTONS; i++)
		buttons[i].setActive(false);
}

void SootNSickle::onBaseDeath()
{
	
}