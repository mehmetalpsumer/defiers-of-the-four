//-----------------------------------------------------------------
// Bitmap Object
// C++ Header - Robot.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include <string>
#include "Character.h"

//-----------------------------------------------------------------
// Custom Data Types
//-----------------------------------------------------------------
enum ControlStatus {
	PLAYER_1,
	PLAYER_2,
	AI
};

//Sprite* _robot;

//-----------------------------------------------------------------
// Robot Class
//-----------------------------------------------------------------
class Robot:public Character
{
protected:
	
	// Member Variables
	ControlStatus controlStatus;
	int cooldown1, cooldown2;
	bool menuHover;

	// Helper Methods
	void Free();

public:
	// Constructor(s)/Destructor
	Robot(std::string _name, std::string _description, Sprite* _sprite, int _healthPoint, int _speed, POINT _mapPosition, ControlStatus _controlStatus, int _cooldown1, int _cooldown2, bool _menuHover=false);
	virtual ~Robot();

	// General Methods

	// Accessor Methods
	void SetMenuHover(bool _hover) { menuHover = _hover; };
	bool GetMenuHover() { return menuHover; };

};