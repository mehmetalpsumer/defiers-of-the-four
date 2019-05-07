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
Robot::Robot(std::string _name, std::string _description, Sprite* _sprite, Sprite* _menuSprite, int _healthPoint, int _speed, POINT _mapPosition, int _fireSpeed, ControlStatus _controlStatus, int _cooldown1, int _cooldown2, bool _menuHover)
	:Character(_name, _description, _sprite, _menuSprite, _healthPoint, _speed, _mapPosition, _fireSpeed) 
{
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
void Robot::Update() {
	if (controlStatus != AI) return;

	switch (task) {
	case AT_FOLLOW:
		if (target == NULL || path.empty()) return;
		Move();
	case AT_IDLE:
	default:
		return;
	}
}