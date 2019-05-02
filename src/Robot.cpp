//-----------------------------------------------------------------
// Robot Object
// C++ Source - Robot.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Robot.h"

//-----------------------------------------------------------------
// Robot Constructor(s)/Destructor
//-----------------------------------------------------------------
Robot::Robot(std::string _name, std::string _description, Sprite* _sprite, int _healthPoint, int _speed, POINT _mapPosition, ControlStatus _controlStatus, int _cooldown1, int _cooldown2, bool _menuHover)
	:Character(_name, _description, _sprite, _healthPoint, _speed, _mapPosition) 
{
	name = _name;
	description = _description;
	sprite = _sprite;
	speed = _speed;
	healthPoint = _healthPoint;
	maxHealthPoint = _healthPoint;
	mapPosition = _mapPosition;
	controlStatus = _controlStatus;
	cooldown1 = _cooldown1;
	cooldown2 = _cooldown2;

}

Robot::~Robot()
{
}


//-----------------------------------------------------------------
// Robot General Methods
//-----------------------------------------------------------------
