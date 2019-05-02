//-----------------------------------------------------------------
// Character Object
// C++ Header - Character.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include <string>
#include "Sprite.h"

//-----------------------------------------------------------------
// Character Class
//-----------------------------------------------------------------
class Character {
	protected:
		// Member Variables
		std::string name;
		std::string description;
		Sprite *sprite;
		int healthPoint;
		int maxHealthPoint;
		int speed;
		POINT mapPosition;
	public:
		// Constructor(s)/Destructor
		Character(std::string _name, std::string _description, Sprite* _sprite, int _healthPoint, int _speed, POINT _mapPosition);
		virtual ~Character();

		// General methods
		inline void TakeHit(int _damage) { healthPoint -= _damage; };
		inline void Heal(int _healAmount) { 
			healthPoint += _healAmount;

			if (healthPoint > maxHealthPoint) {
				healthPoint = maxHealthPoint;
			}
		}

		// Accessor methods
		std::string GetName() { return name; };
		std::string GetDescription() { return description; };
		Sprite* GetSprite() { return sprite; };
		int GetHealthPoint() { return healthPoint; };
		int GetSpeed() { return speed; };
		POINT GetMapPosition() { return mapPosition; };
};
