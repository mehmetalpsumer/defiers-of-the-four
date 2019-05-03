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
#ifndef SPRITE_H
#define SPRITE_H
#endif // !SPRITE_H

class Sprite;

//-----------------------------------------------------------------
// Character Class
//-----------------------------------------------------------------
class Character {
	protected:
		// Member Variables
		std::string name;
		std::string description;
		Sprite* sprite;
		Sprite* menuSprite;
		int healthPoint;
		int maxHealthPoint;
		int speed;
		POINT mapPosition;
	public:
		// Constructor(s)/Destructor
		Character(std::string _name, std::string _description, Sprite* _sprite, Sprite *_menuSprite, int _healthPoint, int _speed, POINT _mapPosition);
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
		Sprite* GetMenuSprite() { return menuSprite; };
		int GetHealthPoint() { return healthPoint; };
		int GetSpeed() { return speed; };
		POINT GetMapPosition() { return mapPosition; };
};
