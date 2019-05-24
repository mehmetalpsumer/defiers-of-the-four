//-----------------------------------------------------------------
// Demon Boss Object
// C++ Header - DemonBoss1.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include <string>
#include <time.h>
#include "Demon.h"

//-----------------------------------------------------------------
// R_Captain Class
//-----------------------------------------------------------------
class DemonBoss :public Demon
{
protected:
public:
	// Constructor(s)/Destructor
	DemonBoss(Sprite * _sprite, POINT _mapPosition);
	virtual ~DemonBoss();
};
