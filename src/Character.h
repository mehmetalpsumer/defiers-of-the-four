//-----------------------------------------------------------------
// Bitmap Object
// C++ Header - Character.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include "Sprite.h"

//-----------------------------------------------------------------
// Character Class
//-----------------------------------------------------------------
class Character {
	protected:
		// Member Variables
		Sprite *sprite;
		POINT position;
		POINT velocity;
		int healthPoint;
		int speed;
	public:
		// Constructor(s)/Destructor
		Character();
		Character(Sprite *sprite, POINT position, POINT velocity, int healthPoint, int speed);
		virtual ~Character();

		// General methods
		void Move();
		void Fire(POINT target);

		// Getters and setters
		Sprite* GetSprite();
		int GetSpeed();
};
