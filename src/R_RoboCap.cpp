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
R_RoboCap::R_RoboCap(Sprite *sprite, POINT position, POINT velocity, int healthPoint, int speed, char name[20], int cooldowns[2]): Character() {
	this->sprite = sprite;
	this->position = position;
	this->speed = speed;
	this->healthPoint = healthPoint;
	this->velocity = velocity;
	this->name = name;
	this->cooldowns = cooldowns;
}

R_RoboCap::~R_RoboCap()
{
}


//-----------------------------------------------------------------
// RoboCap General Methods
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// RoboCap Getters and Setters
//-----------------------------------------------------------------
