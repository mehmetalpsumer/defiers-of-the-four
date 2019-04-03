//-----------------------------------------------------------------
// Bitmap Object
// C++ Header - R_RoboCap.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include "Character.h"

//-----------------------------------------------------------------
// Custom Data Types
//-----------------------------------------------------------------
enum allyStatus {
	Alive,
	Wounded,
	Dead
};

//-----------------------------------------------------------------
// R_RoboCap Class
//-----------------------------------------------------------------
class R_RoboCap:public Character
{
protected:
	// Member Variables
	char *name;
	allyStatus status;
	int *cooldowns;

	// Helper Methods
	void Free();

public:
	// Constructor(s)/Destructor
	R_RoboCap(Sprite *sprite, POINT position, POINT velocity, int healthPoint, int speed, char name[20], int cooldowns[2]);
	virtual ~R_RoboCap();

	// General Methods

};
