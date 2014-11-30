// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 4 spacewar.h v1.0

#ifndef _REDSPACE_H             // prevent multiple definitions if this 
#define _REDSPACE_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include <string>
using std::string;
#include <ctime>


#include "Actor.h"
#include "Particle.h"
#include "Button.h"
#include "Controls.h"
#include "Base.h"

namespace SootNSickleNS
{
	const int MAX_AIR_TURRETS = 1000;
	const int MAX_GROUND_TURRETS = 1000;
	const int MAX_GROUND_ENEMIES = 1000;
	const int MAX_AIR_ENEMIES = 1000;
	const int MAX_BUILDINGS = 1000;
	const int MAX_PARTICLES = 10000;
	const int MAX_BUTTONS = 15;

	const int NUM_PARTICLES_IN_CONE_EFFECT = 150;
	const int NUM_PARTICLES_IN_CLOUD_EFFECT = 200;
	

	const float SCREEN_SPEED = 500;

}


using namespace SootNSickleNS;
using namespace utilityNS;

//=============================================================================
// Create game class
//=============================================================================
class SootNSickle : public Game
{
private:

	enum GameState{
		TitleScreen,
		Level1,
		Level2,
		Level3,
		FeelingLucky,
		SIZE //THIS MUST BE THE LAST ELEMENT
	};

	Controls controls;

    // variables
	TextureManager backgroundTex;   
	TextureManager particleTex;
	TextureManager buttonTex;
	TextureManager guiOverlayTex;
	TextureManager baseTex;
	TextureManager healthBarTex;

	Base base;

	TextDX infoText;

	Image background;
	Image guiOverlay;

	Button buttons[MAX_BUTTONS];
	Particle particles[MAX_PARTICLES];
	
	VECTOR2 screenLoc;

	VECTOR2 * worldSizes; //array of sizes per level

	GameState currentState;

	bool paused;


public:
	// Constructor
    SootNSickle();

    // Destructor
    virtual ~SootNSickle();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();


	//places the screen so the selected location is in the middle area (might not center)
	void updateScreen(); 

	Particle* spawnParticle(VECTOR2 loc,VECTOR2 vel, COLOR_ARGB c,float lifespan = particleNS::MAX_LIFETIME,bool reverseFade = false);
	void spawnParticleCloud(VECTOR2 loc, COLOR_ARGB c);
	void spawnParticleCone(VECTOR2 loc, float dir, COLOR_ARGB c);

	Button* spawnButton(VECTOR2 loc);

	void menuLoad();
	void menuUpdate(bool reset = false);
	void menuRender();

	void level1Load();
	void level2Load();
	void level3Load();
	void feelingLuckyLoad();

	void guiLoad();

	void levelsUpdate();
	void levelsRender();


	void deactivateAll();

	VECTOR2 getMouseInWorld(){
		VECTOR2 mouse(input->getMouseX(),input->getMouseY());
		return screenLoc + mouse;
	}

	VECTOR2 getCurrentWorldSize(){return worldSizes[currentState];}

	VECTOR2 getRealEndLoc(VECTOR2 startLoc, VECTOR2 endLoc);

	void onBaseDeath();

};

#endif
