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
// Custom Data Types
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// R_Wololo Class
//-----------------------------------------------------------------
class R_Wololo :public Robot
{
protected:

	// Member Variables


	// Helper Methods
	void Free();

public:
	// Constructor(s)/Destructor
	R_Wololo(std::string _name, std::string _description, Sprite * _sprite, Sprite * _menuSprite, int _healthPoint, int _speed, POINT _mapPosition, int _fireSpeed);
	virtual ~R_Wololo();

	// General Methods
	void UseAbility1();
	void UseAbility2(vector<Robot*> robots);
};