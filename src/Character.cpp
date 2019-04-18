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
Character::Character(Sprite* _sprite, POINT _position, POINT _velocity, int _healthPoint, int _speed) {
	this->sprite = _sprite;
	this->position = _position;
	this->speed = _speed;
	this->healthPoint = _healthPoint;
	this->velocity = _velocity;
}

Character::~Character()
{
}


//-----------------------------------------------------------------
// Character General Methods
//-----------------------------------------------------------------
