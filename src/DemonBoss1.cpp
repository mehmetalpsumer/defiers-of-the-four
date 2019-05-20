//-----------------------------------------------------------------
// Demon Boss 1 Object
// C++ Source - DemonBoss1.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "DemonBoss1.h"

//-----------------------------------------------------------------
// DemonBoss1 Constructor(s)/Destructor
//-----------------------------------------------------------------

DemonBoss1::DemonBoss1(Sprite * _sprite, POINT _mapPosition):Demon(_sprite, _mapPosition, NULL)
{
	demonType = D_BOSS1;
	stats.armor = 10;
	stats.health = stats.maxHealth = 1000;

	CharacterStats pStats;
	pStats.fireDelay = 7;
	pStats.fireSpeed = 10;
	pStats.health = pStats.maxHealth = 200;
	pStats.speed = 0;
	pStats.armor = 7;
	stats = baseStats = pStats;
	fireDirection = { stats.fireSpeed, 0 };
}

DemonBoss1::~DemonBoss1()
{
}
