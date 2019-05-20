//-----------------------------------------------------------------
// R_Wololo Object
// C++ Source - R_Wololo.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "R_Wololo.h"

//-----------------------------------------------------------------
// R_Wololo Constructor(s)/Destructor
//-----------------------------------------------------------------
R_Wololo::R_Wololo(Sprite * _sprite, Sprite * _menuSprite, POINT _mapPosition):Robot(_sprite, _menuSprite, _mapPosition)
{
	name = { "Wololo" };
	description = { "Heal other robots." };
	robotType = R_WOLOLO;

	// Set up first ability
	time_t now;
	time(&now);

	// Ability 1
	// Passive Aura. Always active. Boost nearby robots' stats.
	abilities[0].cooldown = 10;
	abilities[0].duration = 0;
	abilities[0].name = { "Heal" };
	abilities[0].ready = true;
	abilities[0].active = false;
	abilities[0].usedTime = time(0);

	// Ability 2
	// Active. Boost self stats for a duration.
	abilities[1].cooldown = 20;
	abilities[1].duration = 0;
	abilities[1].name = { "Heal All" };
	abilities[1].ready = true;
	abilities[1].active = false;
	abilities[1].usedTime = now;

	// Stats
	CharacterStats pStats;
	pStats.fireDelay = 7;
	pStats.fireSpeed = 7;
	pStats.health = pStats.maxHealth = 100;
	pStats.speed = 7;
	pStats.armor = 10;
	pStats.damage = 15;
	stats = baseStats = pStats;
}

R_Wololo::~R_Wololo()
{
}


//-----------------------------------------------------------------
// R_Wololo General Methods
//-----------------------------------------------------------------
void R_Wololo::UseAbility1() {
	if (nearbyRobots.size() == 0) return;

	Robot* target = NULL;
	if (abilities[0].ready) {
		int minHealthPoint = 10000;
		for (auto &robot : nearbyRobots) {
			if (robot->GetHealth() < minHealthPoint) {
				minHealthPoint = robot->GetHealth();
				target = (Robot*)robot;
				break;
			}
		}

		time_t now;
		time(&now);
		target->Heal(25);
		abilities[0].usedTime = now;
		abilities[0].ready = false;
	}

}

void R_Wololo::UseAbility2(vector<Robot*> robots) {
	if (abilities[1].ready == false) return;
	for (auto &robot : robots) {
		robot->Heal(10);
	}
	time(&abilities[1].usedTime);
	abilities[1].ready = false;
}
