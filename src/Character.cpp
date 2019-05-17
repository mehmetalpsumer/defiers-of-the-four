//-----------------------------------------------------------------
// Character Object
// C++ Source - Character.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Character.h"

//-----------------------------------------------------------------
// Character Constructor(s)/Destructor
//-----------------------------------------------------------------
Character::Character(std::string _name, std::string _description, Sprite* _sprite, Sprite* _menuSprite, 
	int _healthPoint, int _speed, POINT _mapPosition, int _fireSpeed) {
	name = _name;
	description = _description;
	sprite = _sprite;
	menuSprite = _menuSprite;
	mapPosition = _mapPosition;
	curFireDelay = 0;
	task = AT_IDLE;
	ready = true;

	CharacterStats pStats;
	pStats.fireDelay = 7;
	pStats.fireSpeed = _fireSpeed;
	pStats.health = pStats.maxHealth = _healthPoint;
	pStats.speed = _speed;
	pStats.armor = 10;
	stats = baseStats = pStats;
	fireDirection = { stats.fireSpeed, 0 };
}

Character::~Character()
{
}


//-----------------------------------------------------------------
// Character General Methods
//-----------------------------------------------------------------
