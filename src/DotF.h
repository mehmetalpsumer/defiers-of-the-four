//-----------------------------------------------------------------
// Fore 2 Application
// C++ Header - Fore.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include "Resource.h"
#include "GameEngine.h"
#include "Bitmap.h"
#include "Sprite.h"
#include <queue> 
typedef vector< vector<int>> game_object_positions;
typedef std::vector<game_object_positions> game_objects_positions;
typedef vector< vector<int>> map;

//-----------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------
HINSTANCE   _hInstance;
GameEngine* _pGame;
HDC         _hOffscreenDC;
HBITMAP     _hOffscreenBitmap;
Bitmap*     _pWallBitmap;
Sprite*     _pWalls[100];
Bitmap*     _pEnemyBaseBitmap;

map CreateMap(bool _fLevel);
queue <POINT> pathFinding(POINT targetposition, POINT startingposition, map currentmap, bool first_map);
int number_of_enemyCenter;
Sprite*     _pEnemyBase[20];
Sprite*     _robot[2];
Bitmap* _robotbmp;
map  maps[8];