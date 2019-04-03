//-----------------------------------------------------------------
// Bitmap Object
// C++ Source - Character.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Character.h"

//-----------------------------------------------------------------
// Character Constructor(s)/Destructor
//-----------------------------------------------------------------
Character::Character() {

}

Character::Character(Sprite *sprite, POINT position, POINT velocity, int healthPoint, int speed) {
	this->sprite = sprite;
	this->position = position;
	this->speed = speed;
	this->healthPoint = healthPoint;
	this->velocity = velocity;
}

Character::~Character()
{
}


//-----------------------------------------------------------------
// Character General Methods
//-----------------------------------------------------------------
Sprite* Character::GetSprite() {
	return sprite;
}

int Character::GetSpeed() {
	return speed;
}