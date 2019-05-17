//-----------------------------------------------------------------
// R_Captain Object
// C++ Source - R_Captain.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "R_Captain.h"

//-----------------------------------------------------------------
// R_Captain Constructor(s)/Destructor
//-----------------------------------------------------------------

R_Captain::R_Captain(std::string _name, std::string _description, Sprite * _sprite, Sprite * _menuSprite, int _healthPoint, int _speed, POINT _mapPosition, int _fireSpeed)
	:Robot(_name, _description, _sprite, _menuSprite, _healthPoint, _speed, _mapPosition, _fireSpeed, CS_AI, false)
{
	name = { "Captain" };
	description = { "Leads the robots to battle by boosting their stats.\nAbility 1: Passive. Boosts armor and max health of the allies by 20%."};
	robotType = R_CAPTAIN;
}

R_Captain::~R_Captain()
{
}


//-----------------------------------------------------------------
// Character General Methods
//-----------------------------------------------------------------
