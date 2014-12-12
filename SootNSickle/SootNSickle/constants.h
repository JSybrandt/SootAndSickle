#pragma once

// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 5 constants.h v1.0
#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------
// graphic images
const char BACKGROUND_IMAGE[] = "pictures\\backgroundJ.png";
const char PARTICLE_IMAGE[] = "pictures\\particleJ.png";
const char BUTTON_IMAGE[] = "pictures\\buttonJ.png";
const char GUI_OVERLAY_IMAGE[] = "pictures\\guiOverlayJ.png";
const char BASE_IMAGE[] = "pictures\\baseJ.png";
const char HEALTH_BAR_IMAGE[] = "pictures\\healthBarJ.png";
const char ICON_IMAGE[] = "pictures\\buttonImagesJ.png";
const char CURSOR_IMAGE[] = "pictures\\cursorImagesJ.png";
const char POWER_SUPPLY_IMAGE[] = "pictures\\powerSupplyJ.png";
const char POWER_FIELD_IMAGE[] = "pictures\\powerFieldJ.png";
const char MINERAL_IMAGE[] = "pictures\\mineralsJ.png";
const char EXTRACTOR_IMAGE[] = "pictures\\extractorJ.png";
const char TURRETG_IMAGE[] = "pictures\\turretgC.png";
const char TURRETA_IMAGE[] = "pictures\\turretaC.png";
const char TURRETBASE_IMAGE[] = "pictures\\standC.png";
const char FACTORY_IMAGE[] = "pictures\\factoryJ.png";
const char HOUSE_IMAGE[] = "pictures\\houseJ.png";
const char AIR_FIELD_IMAGE[] = "pictures\\airFieldJ.png";
const char ZOMBIE_IMAGE[] = "pictures\\zombieAniC.png";
const char ZOMBIEBAT_IMAGE[] = "pictures\\batAniC.png";
const char MENU_BACKGROUND_IMAGE[] = "pictures\\menuBackgroundJ.png";
const char MAIN_MENU_BUTTON_IMAGE[] = "pictures\\mainMenuButtonsJ.png";
const char TRANSPORT_SHIP_IMAGE[] = "pictures\\transportShipJ.png";
const char LOGO_IMAGE[] = "pictures\\logoJ.png";
const char GAMEOVER_IMAGE[] = "pictures\\gameOverJ.png";

//Sound Locations
const char WAVE_BANK[] = "audio\\Win\\Wave Bank.xwb";
const char SOUND_BANK[] = "audio\\win\\Sound Bank.xsb";
const char XGS_FILE[]   = "audio\\Win\\AudioProject.xgs";

//Cue Names
const char SC_BUILDING[] = "building";
const char SC_OPENING[] = "ruski start";
const char SC_MAIN_LOOP[] = "ruski main";
const char SC_SELL[] = "cash";
const char SC_UPGRADE[] = "upgrade";
const char SC_POWER_ON[] = "powerOn";
const char SC_BUILDING_COLLAPSE[] = "buildingCollapse";
const char SC_ZOMBIE1[] = "zombie1";
const char SC_ZOMBIEDEATH[] = "zombieDeath";
const char SC_ROCKET[] = "rocket";
const char SC_CANNON[] = "cannon";

// window
const char CLASS_NAME[] = "Soot & Sickle";
const char GAME_TITLE[] = "Soot & Sickle";
const bool FULLSCREEN = false;              // windowed or fullscreen DO NOT RUN FULLSCREEN IN DEBUG MODE
const UINT GAME_WIDTH =  1280;               // width of screen in pixels
const UINT GAME_HEIGHT = 800;               // height of screen in pixels

//Turret Cells
const int  TURRET_COL = 0;
const int  TURRET_WIDTH = 128;
const int  TURRET_HEIGHT = 128;
const float TURRET_DELAY = 0.15f;
const int  BASE_WIDTH = 128;
const int  BASE_HEIGHT = 128;

//Zombie Cells
const int ZOMBIE_COL = 2;
const int ZOMBIE_WIDTH = 128;
const int ZOMBIE_HEIGHT = 128;
const float ZOMBIE_DELAY = 0.15f;

//Zombie Cells
const int BAT_COL = 2;
const int BAT_WIDTH = 128;
const int BAT_HEIGHT = 128;
const float BAT_DELAY = 0.15f;

// game
const double PI = 3.14159265;
const float FRAME_RATE  = 100.0f;               // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
const enum COLLISION_TYPE {NONE, CIRCLE, BOX, ROTATED_BOX};
const enum WEAPON {AIR, GROUND, SPECIAL};

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY      = VK_MENU;     // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;   // Enter key




#endif
