//-----------------------------------------------------------------
// Character Object
// C++ Source - Character.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Character.h"

//-----------------------------------------------------------------
// Character Constructor(s)/Destructor
//-----------------------------------------------------------------
Character::Character(std::string _name, std::string _description, Sprite* _sprite, Sprite* _menuSprite, 
	int _healthPoint, int _speed, POINT _mapPosition, int _fireSpeed) {
	name = _name;
	description = _description;
	sprite = _sprite;
	menuSprite = _menuSprite;
	speed = _speed;
	healthPoint = _healthPoint;
	maxHealthPoint = _healthPoint;
	mapPosition = _mapPosition;
	fireSpeed = _fireSpeed;
	fireDirection = { fireSpeed, 0 };
	fireDelay = 7;
	curFireDelay = 0;

	task = AT_IDLE;
	ready = true;
}

Character::~Character()
{
}


//-----------------------------------------------------------------
// Character General Methods
//-----------------------------------------------------------------
