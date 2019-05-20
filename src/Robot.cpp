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
Robot::Robot(Sprite* _sprite, Sprite* _menuSprite, POINT _mapPosition):Character(_sprite, _menuSprite, _mapPosition) 
{
	menuHover = false;
	controlStatus = CS_AI;
	isRobot = true;
}

Robot::~Robot()
{
}

//-----------------------------------------------------------------
// Robot General Methods
//-----------------------------------------------------------------
void Robot::Update() {
	int cur = 0;
	
	// Update bitmap
	int velX = sprite->GetVelocity().x;
	int velY = sprite->GetVelocity().y;
	/*if (velY == 0 && velX == 0) {
		sprite->SetNumFrames(1);
		cur = robotType * 5;
		
	}*/
	/*else {
		sprite->SetNumFrames(15);
		if (velY == 0) {
			if (velX > 0) {
				// right d
				cur = 4 + (robotType * 5);
			}
			else {
				// left a
				cur = 2 + (robotType * 5);
			}
		}
		else {
			if (velY > 0) {
				//down s
				cur = 3 + (robotType * 5);
			}
			else {
				//up w
				cur = 1 + robotType * 5;
			}
		}
	}*/
	//sprite->SetBitmap(animationBitmaps[cur]);

	if (controlStatus != CS_AI) return;

	switch (task) {
	case AT_FOLLOW:
		if (target == NULL || path.empty()) return;
		Move();
	case AT_IDLE:
	default:
		return;
	}
}
