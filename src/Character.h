//-----------------------------------------------------------------
// Character Object
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
		Character(Sprite* _sprite, POINT _position, POINT _velocity, int _healthPoint, int _speed);
		virtual ~Character();

		// General methods
		void Move();
		void Fire(POINT target);

		// Accessor methods
		Sprite* GetSprite() { return sprite; };
		int GetSpeed() { return speed; };
};
