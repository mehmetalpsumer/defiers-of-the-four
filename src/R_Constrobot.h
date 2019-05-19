//-----------------------------------------------------------------
// R_Wololo Object
// C++ Header - R_Wololo.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include <string>
#include <time.h>

#include "Robot.h"

//-----------------------------------------------------------------
// R_Wololo Class
//-----------------------------------------------------------------
class R_Constrobot :public Robot
{
protected:
public:
	// Constructor(s)/Destructor
	R_Constrobot(string _name, string _description, Sprite * _sprite, Sprite * _menuSprite, int _healthPoint, int _speed, POINT _mapPosition, int _fireSpeed);
	virtual ~R_Constrobot();

	// General Methods
	void UseAbility1();
	void UseAbility2();
};