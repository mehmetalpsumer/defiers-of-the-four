//-----------------------------------------------------------------
// Robot Captain Object
// C++ Header - R_Captain.h
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
// R_Captain Class
//-----------------------------------------------------------------
class R_Captain:public Robot
{
protected:
public:
	// Constructor(s)/Destructor
	R_Captain(string _name, string _description, Sprite * _sprite, Sprite * _menuSprite, int _healthPoint, int _speed, POINT _mapPosition, int _fireSpeed);
	virtual ~R_Captain();

	// General Methods
	void UseAbility1();
	void UseAbility2();
	void Unbreakable(bool active);
};
