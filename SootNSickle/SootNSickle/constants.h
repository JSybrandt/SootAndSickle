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
const char BACKGROUND_IMAGE[] = "pictures\\background.png";
const char PARTICLE_IMAGE[] = "pictures\\particle.png";
const char BUTTON_IMAGE[] = "pictures\\button.png";
const char GUI_OVERLAY_IMAGE[] = "pictures\\guiOverlay.png";
const char BASE_IMAGE[] = "pictures\\base.png";
const char HEALTH_BAR_IMAGE[] = "pictures\\healthBar.png";


//Sound Locations
const char WAVE_BANK[] = "audio\\Win\\Wave Bank.xwb";
const char SOUND_BANK[] = "audio\\win\\Sound Bank.xsb";
const char XGS_FILE[]   = "audio\\Win\\AudioProject.xgs";

//Cue Names
const char SC_LAUNCH[] = "launch"; //MUST be exactly the same as cue name


// window
const char CLASS_NAME[] = "Soot & Sickle";
const char GAME_TITLE[] = "Soot & Sickle";
const bool FULLSCREEN = false;              // windowed or fullscreen DO NOT RUN FULLSCREEN IN DEBUG MODE
const UINT GAME_WIDTH =  1280;               // width of screen in pixels
const UINT GAME_HEIGHT = 800;               // height of screen in pixels

//Turret Cells
const int  TURRET_COL = 3;
const int  TURRET_WIDTH = 64;
const int  TURRET_HEIGHT = 64;
const float TURRET_DELAY = 0.15f;
const int  BASE_WIDTH = 128;
const int  BASE_HEIGHT = 128;

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