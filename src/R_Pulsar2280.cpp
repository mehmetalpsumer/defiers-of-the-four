//-----------------------------------------------------------------
// Robot Pulsar2280 Object
// C++ Source - R_Pulsar2280.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "R_Pulsar2280.h"

//-----------------------------------------------------------------
// R_Pulsar2280 Constructor(s)/Destructor
//-----------------------------------------------------------------

R_Pulsar2280::R_Pulsar2280(Sprite * _sprite, Sprite * _menuSprite, POINT _mapPosition)
	:Robot(_sprite, _menuSprite, _mapPosition)
{
	name = { "Pulsar 2280" };
	description = { "Creating portal and becoming invisible" };
	robotType = R_PULSAR2280;
	stats.armor = 8;
	// Set up first ability
	time_t now;
	time(&now);

	// Ability 1
	// Create a portal
	abilities[0].cooldown = 10;
	abilities[0].duration = 0;
	abilities[0].name = { "Portal Time" };
	abilities[0].ready = true;
	abilities[0].active = false;
	abilities[0].usedTime = now;

	// Ability 2
	// Becoming invisible
	abilities[1].cooldown = 20;
	abilities[1].duration = 5;
	abilities[1].name = { "Invisible" };
	abilities[1].ready = true;
	abilities[1].active = false;
	abilities[1].usedTime = now;
	baseStats = stats;

	// Stats
	CharacterStats pStats;
	pStats.fireDelay = 7;
	pStats.fireSpeed = 10;
	pStats.health = pStats.maxHealth = 100;
	pStats.speed = 7;
	pStats.armor = 10;
	pStats.damage = 15;
	stats = baseStats = pStats;
}

R_Pulsar2280::~R_Pulsar2280()
{
}


//-----------------------------------------------------------------
// R_Pulsar2280 General Methods
//-----------------------------------------------------------------
void R_Pulsar2280::UseAbility1() {
	PlaySound((LPCWSTR)IDW_CONSTROBOT_1, hInstance, SND_ASYNC | SND_RESOURCE);
	time(&abilities[0].usedTime);
	abilities[0].ready = false;
	time_t now;
	AddStatusMessage("*Portal!*", time(&now) + 2);
}

void R_Pulsar2280::UseAbility2(Robot* robot) {
	time(&abilities[1].usedTime);
	abilities[1].active = true;
	abilities[1].ready = false;
	time_t now;
	AddStatusMessage("*Invisible!*", time(&now) + 5);
}