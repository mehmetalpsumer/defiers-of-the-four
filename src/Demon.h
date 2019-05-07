//-----------------------------------------------------------------
// Bitmap Object
// C++ Header - Demon.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include <string>
#include "Character.h"
#include "DotF.h"

#ifndef DEMONBASE_H
#define DEMONBASE_H
#endif

#include "DemonBase.h"

class DemonBase;


//-----------------------------------------------------------------
// Custom Data Types
//-----------------------------------------------------------------
enum ControlStatus {
	AI
};


int x_bound_of_view_field = 6;
int y_bound_of_view_field = 6;

int x_bound_of_attack_field = 4;
int y_bound_of_attack_field = 4;

Bitmap* _demonBitmap;
Sprite* _demon;


//-----------------------------------------------------------------
// Demon Class
//-----------------------------------------------------------------
class Demon :public Character
{
protected:

	// Member Variables
	ControlStatus controlStatus;
	bool menuHover;
	int base_number;
	int base_number_that_warned_by_the_helpless_demon;
	vector<Robot*> currentTargets;
	DemonBase* base;

	// Helper Methods
	void Free();

public:
	// Constructor(s)/Destructor
	Demon(std::string _name, std::string _description, Sprite* _sprite, int _healthPoint, int _speed, POINT _mapPosition,
		ControlStatus _controlStatus, Demon _robots_in_range[], int _base_number, DemonBase* base,
		int _base_number_that_warned_by_the_helpless_demon, bool _menuHover = false);
	virtual ~Demon();

	// General Methods

	// Accessor Methods
	void SetMenuHover(bool _hover) { menuHover = _hover; };
	bool GetMenuHover() { return menuHover; };
	int GetBaseNumber() { return base_number; };
	void SetBaseNumber(int __base_number) {  base_number = __base_number; };
	int GetBaseNumberThatWarnedByTheHelplessDemon() { return base_number_that_warned_by_the_helpless_demon; };
	void SetBaseNumberThatWarnedByTheHelplessDemon(int __base_number_that_warned_by_the_helpless_demon) { base_number_that_warned_by_the_helpless_demon = __base_number_that_warned_by_the_helpless_demon; };

	vector<Robot*> GetCurrentTargets() { return currentTargets; };
	void SetCurrentTargets(vector<Robot*> _currentTargets) { currentTargets = _currentTargets; };

	DemonBase* GetBase() { return base; };
	void SetBase(DemonBase* _base) { base = _base; };

	vector<Robot> FindTheClosestRobot(Demon demon, vector<Robot> robots_around_the_demon);
};
