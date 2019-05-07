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

		POINT fireDirection;
		int	fireSpeed;
		int fireDelay;
		int curFireDelay;


	public:
		// Constructor(s)/Destructor
		Character(std::string _name, std::string _description, Sprite* _sprite, Sprite *_menuSprite, 
			int _healthPoint, int _speed, POINT _mapPosition, int _fireSpeed);
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
		int GetFireSpeed() { return fireSpeed; };
		void SetFireSpeed(int _fs) { fireSpeed = _fs; };
		POINT GetFireDirection() { return fireDirection; };
		void SetFireDirection(POINT _fd) { fireDirection = _fd; };
		int GetCurFireDelay() { return curFireDelay; };
		void SetCurFireDelay(int _d) { curFireDelay = _d; };
		int GetFireDelay() { return fireDelay; };
		POINT GetMapPosition() { return mapPosition; };
		void SetMapPosition(POINT __mapPosition) { mapPosition = __mapPosition; };
};
