//-----------------------------------------------------------------
// Portal Object
// C++ Header - Portal.h
//-----------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Sprite.h"

//-----------------------------------------------------------------
// Portal Class
//-----------------------------------------------------------------
class Portal : public Sprite
{
public:
	// Constructor(s)/Destructor
	Portal(Bitmap* _bitmap);
	virtual ~Portal();
	bool isReady;

};
