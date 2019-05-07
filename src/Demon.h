//-----------------------------------------------------------------
// Bitmap Object
// C++ Header - Demon.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
using namespace std;
#include <windows.h>
#include <string>
#include <vector>

#include "Sprite.h"
#include "Robot.h"

#ifndef DEMONBASE_H
#define DEMONBASE_H
#endif



class DemonBase;


//-----------------------------------------------------------------
// Custom Data Types
//-----------------------------------------------------------------
typedef vector<vector<int>> Map;


//-----------------------------------------------------------------
// Demon Class
//-----------------------------------------------------------------
class Demon :public Character
{
protected:

	// Member Variables
	int base_number;
	int base_number_that_warned_by_the_helpless_demon;
	vector<Robot*> currentTargets;
	DemonBase* base;

	// Helper Methods
	void Free();

public:
	// Constructor(s)/Destructor
	Demon(std::string _name, std::string _description, Sprite* _sprite, int _healthPoint, int _speed, POINT _mapPosition,
		Demon _robots_in_range[], int _base_number, DemonBase* base,
		int _base_number_that_warned_by_the_helpless_demon, int _fireSpeed, bool _menuHover = false);
	virtual ~Demon();

	// General Methods

	// Accessor Methods
	int GetBaseNumber() { return base_number; };
	void SetBaseNumber(int __base_number) { base_number = __base_number; };
	int GetBaseNumberThatWarnedByTheHelplessDemon() { return base_number_that_warned_by_the_helpless_demon; };
	void SetBaseNumberThatWarnedByTheHelplessDemon(int __base_number_that_warned_by_the_helpless_demon) { base_number_that_warned_by_the_helpless_demon = __base_number_that_warned_by_the_helpless_demon; };

	vector<Robot*> GetCurrentTargets() { return currentTargets; };
	void SetCurrentTargets(vector<Robot*> _currentTargets) { currentTargets = _currentTargets; };

	DemonBase* GetBase() { return base; };
	void SetBase(DemonBase* _base) { base = _base; };

	vector<Robot> FindTheClosestRobot(Demon demon, vector<Robot> robots_around_the_demon);
	int EuclideanDistance(Demon* demon, Robot* robot, DemonBase* demonBase);
	void AttackByMaintainingTheDistance(Demon* demon, Map currentmap, Robot* robot);
	void Situations(Demon* demon, Robot* robot, Map currentmap, vector<DemonBase*> demonBaseArray);
	void seekTheRobots(Demon* demon, Map currentmap);
	void WarnTheBaseDemons(Demon* demon, Map currentmap, DemonBase* base);
	void Chase(Demon* demon, Robot* robot);
	void Evade(Demon* demon, Robot* robot);
	void Attack(Demon* demon, Robot* robot);
	Robot* FindTheClosestRobot(Demon* demon, vector<Robot*> robots_around_the_demon);
	DemonBase* FindTheClosestBase(Demon* demon, int _pEnemyBase_c, vector<DemonBase*> demonBaseArray);
	void RestrictForTheBaseBoundaries(Demon* demon);
};