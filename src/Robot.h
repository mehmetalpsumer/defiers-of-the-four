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
#include <time.h>
//-----------------------------------------------------------------
// Custom Data Types
//-----------------------------------------------------------------
/*
enum ControlStatus {
	PLAYER_1,
	PLAYER_2,
	AI
};
*/

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
	boolean superpower1avaliable;
	boolean superpower2avaliable;
	time_t superpower1usagetime;
	time_t superpower2usagetime;
	//vector<Demon*> currentTargets;
	// Helper Methods
	void Free();

public:
	// Constructor(s)/Destructor
	Robot(std::string _name, std::string _description, Sprite* _sprite, Sprite* _menuSprite, int _healthPoint, int _speed, POINT _mapPosition, int _fireSpeed, ControlStatus _controlStatus, int _cooldown1, int _cooldown2, bool _menuHover=false);
	virtual ~Robot();

	// General Methods
	void Update();

	// Accessor Methods
	void SetMenuHover(bool _hover) { menuHover = _hover; };
	bool GetMenuHover() { return menuHover; };
	void SetControlStatus(ControlStatus _status) { controlStatus = _status; };
	ControlStatus GetControlStatus() { return controlStatus; };
	void UseSuperPower1(vector<Robot*> robots) { // heal robot that has min heal point
		if (superpower1avaliable)
		{


			Robot *minRobot = NULL;
			int minHealthPoint = 10000;
			for (auto &Robot : robots) {
				if (Robot->getHealPoint() < minHealthPoint) {
					minHealthPoint = Robot->getHealPoint();
					minRobot = Robot;
				}
			}

			minRobot->Heal(10);
			superpower1avaliable = false;
			time(&superpower1usagetime);
		}
	}
	void UseSuperPower2(vector<Robot*> robots) { // heal all robots
		if (superpower2avaliable) {
			for (auto &Robot : robots) {
				Robot->Heal(10);
			}
			superpower2avaliable = false;
			time(&superpower2usagetime);
		}
	}
	void SetSuperPower1Availability(bool _i) { superpower1avaliable = _i; };
	void SetSuperPower2Availability(bool _i) { superpower2avaliable = _i; };
	bool GetSuperPower1Availability() { return superpower1avaliable; };
	bool GetSuperPower2Availability() { return superpower2avaliable; };
	time_t GetSuperPower1UsageTime() { return superpower1usagetime; };
	time_t GetSuperPower2UsageTime() { return superpower2usagetime; };
};