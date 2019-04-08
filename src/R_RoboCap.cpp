//-----------------------------------------------------------------
// Bitmap Object
// C++ Source - R_RoboCap.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "R_RoboCap.h"

//-----------------------------------------------------------------
// RoboCap Constructor(s)/Destructor
//-----------------------------------------------------------------
R_RoboCap::R_RoboCap(Sprite* _sprite, POINT _position, POINT _velocity, int _healthPoint, int _speed, char _name[20], int _cooldowns[2]): Character(_sprite, _position, _velocity, _healthPoint, _speed) {
	this->sprite = _sprite;
	this->position = _position;
	this->speed = _speed;
	this->healthPoint = _healthPoint;
	this->velocity = _velocity;
	this->name = _name;
	this->cooldowns = _cooldowns;
}

R_RoboCap::~R_RoboCap()
{
}


//-----------------------------------------------------------------
// RoboCap General Methods
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// RoboCap Accessor Methods
//-----------------------------------------------------------------
