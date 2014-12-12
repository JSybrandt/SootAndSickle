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

#include<Windows.h>

#include<fstream>
#include <stack> 

#include "Actor.h"
#include "Particle.h"
#include "Button.h"
#include "Controls.h"
#include "Base.h"
#include "PowerSupply.h"
#include "PowerField.h"
#include "MineralPatch.h"
#include "Extractor.h"
#include "Turret.h"
#include "AATurret.h"
#include "Zombie.h"
#include "ZombieBat.h"
#include "Factory.h"
#include "House.h"
#include "AirField.h"
#include "WPManager.h"
#include "ZombieSpawner.h"

namespace SootNSickleNS
{
	const int MAX_AIR_TURRETS = 100;
	const int MAX_GROUND_TURRETS = 100;
	const int MAX_GROUND_ENEMIES = 1000;
	const int MAX_AIR_ENEMIES = 1000;
	const int MAX_POWER_SUPPLIES = 100;
	const int MAX_EXTRACTORS = 100;
	const int MAX_MINERALS = 100;
	const int MAX_FACTORIES = 100;
	const int MAX_HOUSES = 100;
	const int MAX_AIR_FIELDS = 100;
	const int MAX_PARTICLES = 10000;
	const int MAX_BUTTONS = 10;

	const int NUM_PARTICLES_IN_CONE_EFFECT = 150;
	const int NUM_PARTICLES_IN_CLOUD_EFFECT = 200;
	

	const float SCREEN_SPEED = 500;

	const float CURSOR_HEIGHT = 50;

	const float POWER_SUPPLY_COST = 10;
	const float GROUND_TURRET_COST = 50;
	const float AIR_TURRET_COST = 75;
	const float EXTRACTOR_COST = 25;
	const float FACTORY_COST = 100;
	const float HOUSE_COST = 80;
	const float AIR_FIELD_COST = 150;

	const float SELL_BACK_RATE = 0.8;

	const int MAIN_MENU_OPTION_COUNT = 4;

	const int NUM_TUTORIAL_IMAGES = 3;

	const float AUDIO_INTRO_TIME = 17.5;

	const float SHOW_TEXT_TIME = 2.5;
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
		TitleScreen = 0,
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
	TextureManager iconTex;
	TextureManager cursorTex;
	TextureManager powerFieldTex;
	TextureManager powerSupplyTex;
	TextureManager extractorTex;
	TextureManager mineralTex;
	TextureManager turretgTex;
	TextureManager turretaTex;
	TextureManager standTex;
	TextureManager factoryTex;
	TextureManager houseTex;
	TextureManager airFieldTex;
	TextureManager zombieTex;
	TextureManager zombieBatTex;
	TextureManager mainMenuBackgroundTex;
	TextureManager mainMenuButtonTex;
	TextureManager transportShipTex;
	TextureManager logoTex;
	TextureManager gameOverTex;

	Base base;

	TextDX infoText;
	TextDX buildingText;
	TextDX levelText; 

	Image background;
	Image guiOverlay;
	Image cursor;
	Image logo;
	Image gameOver;

	bool showGameOverScreen;

	Image tutorial;

	Image mainMenuBackground;
	Image mainMenuOptions[MAIN_MENU_OPTION_COUNT];

	Button buttons[MAX_BUTTONS];
	Particle particles[MAX_PARTICLES];
	PowerSupply powerSupplies[MAX_POWER_SUPPLIES];
	Extractor extractors[MAX_EXTRACTORS];
	MineralPatch minerals[MAX_MINERALS];
	Turret turrets[MAX_GROUND_TURRETS];
	AATurret aaturrets[MAX_AIR_TURRETS];
	Zombie zombies[MAX_GROUND_ENEMIES];
	ZombieBat zombieBats[MAX_AIR_ENEMIES];
	Factory factories[MAX_FACTORIES];
	House houses[MAX_HOUSES];
	AirField airFields[MAX_AIR_FIELDS];
	WPManager path1;
	WPManager path2;
	WPManager path3;
	ZombieSpawner zs1;
	ZombieSpawner zs2;
	ZombieSpawner zs3;

	VECTOR2 screenLoc;

	VECTOR2 * worldSizes; //array of sizes per level

	GameState currentState;

	bool paused;

	void raiseAllButtons();

	int cursorSelection;

	float mineralLevel;
	int population;
	int idlePopulation;
	int capacity;

	void attemptToSellBuilding();
	void attemptToUpgradeBuilding();
	void attemptToTogglePower();

	int tutorialSelection;
	bool showTutorial;
	
	float audioIntroCountdown;
	float playingIntro;

	float levelTextCooldown;
	string levelString;

	bool showIcon;
	float levelTimer;

	

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
	void spawnParticleCloud(VECTOR2 loc, COLOR_ARGB c, int n = NUM_PARTICLES_IN_CLOUD_EFFECT);
	void spawnParticleCone(VECTOR2 loc, float dir, COLOR_ARGB c, int n = NUM_PARTICLES_IN_CONE_EFFECT);

	Button* spawnButton(VECTOR2 loc,ButtonNS::ButtonType t);
	PowerSupply* spawnPowerSupply(VECTOR2 loc);
	Extractor* spawnExtractor(VECTOR2 loc);
	MineralPatch* spawnMinerals(VECTOR2 loc, float ammount);
	Turret* spawnTurret(VECTOR2 loc);
	Turret* spawnAATurret(VECTOR2 loc);
	Factory* spawnFactory(VECTOR2 loc);
	House* spawnHouse(VECTOR2 loc);
	AirField* spawnAirField(VECTOR2 loc);
	Zombie* spawnZombie(VECTOR2 loc);
	ZombieBat* spawnZombieBat(VECTOR2 loc);

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

	void resetZombies();
	void healBuildings();
	void deactivateAll();

	VECTOR2 getMouseInWorld(){
		VECTOR2 mouse(input->getMouseX(),input->getMouseY());
		return screenLoc + mouse;
	}

	VECTOR2 getCurrentWorldSize(){return worldSizes[currentState];}

	VECTOR2 getRealEndLoc(VECTOR2 startLoc, VECTOR2 endLoc);

	void onBaseDeath();

	void buttonOnClick(Button* caller);

	void checkClick();

	bool isBuildingLocationLegal(Actor* newBuilding);

	void refreshPower();

	bool wasClickedLastFrame;

	MineralPatch* findMineableMinerals(Extractor * caller);

	void addMinerals(float n){mineralLevel+=n; mineralsMined +=n;}


	void addPopulation(int n){n = min(n,capacity-population);idlePopulation+=n;population+=n;}
	void removePopulation(int n){population-=n;}
	int getIdlePop(){return idlePopulation;}
	void addIdlePop(int n){n=min(n,population-idlePopulation);idlePopulation +=n;}
	void removeIdlePop(int n){idlePopulation -=n;}

	float upgradePoints;

	float mineralsMined;
	int enemeiesKilled;
	int buildingsDestroyed;
	float secondsSurvived;
	bool victory;

	float MaxMineralsMined;
	int MaxEnemeiesKilled;
	int MaxBuildingsDestroyed;
	float MaxSecondsSurvived;
	int MaxScore;

	void updateMaxes();

	int getScore(){return mineralsMined/2+5*enemeiesKilled-3*buildingsDestroyed+secondsSurvived;}


	bool cheatNoDeath;
	bool cheatMoreDamage;
	bool cheatBigMoney;

	float cheatCooldown;
	string cheatText;
};

#endif
