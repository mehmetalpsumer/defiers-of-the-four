//-----------------------------------------------------------------
// Bitmap Object
// C++ Header - Robot_Captain.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include "Character.h"

//-----------------------------------------------------------------
// Character Class
//-----------------------------------------------------------------
class Ro
{
protected:
	// Member Variables
	Sprite sprite;
	POINT position;
	POINT speed;
	int healthPoint;
	int velocity;


	// Helper Methods
	void Free();

public:
	// Constructor(s)/Destructor
	Character();
	virtual ~Character();

	void Move();
	void Fire(POINT target);

};
