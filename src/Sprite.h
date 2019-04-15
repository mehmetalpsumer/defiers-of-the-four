//-----------------------------------------------------------------
// Sprite Object
// C++ Header - Sprite.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include "Bitmap.h"

//-----------------------------------------------------------------
// Custom Data Types
//-----------------------------------------------------------------
typedef WORD        SPRITEACTION;
const SPRITEACTION  SA_NONE = 0x0000L,
SA_KILL = 0x0001L;

typedef WORD        BOUNDSACTION;
const BOUNDSACTION  BA_STOP = 0,
BA_WRAP = 1,
BA_BOUNCE = 2,
BA_DIE = 3;

//-----------------------------------------------------------------
// Sprite Class
//-----------------------------------------------------------------
class Sprite
{
protected:
	// Member Variables
	Bitmap*       bitmap;
	int			  numFrames, curFrame;
	int			  frameDelay, frameTrigger;
	RECT          position, collisionRect;
	POINT         velocity;
	int           zOrder;
	RECT          bounds;
	BOUNDSACTION  boundsAction;
	BOOL          isHidden;

	// Helper Methods
	void UpdateFrame();
	virtual void  CalcCollisionRect();

public:
	// Constructor(s)/Destructor
	Sprite(Bitmap* _bitmap);
	Sprite(Bitmap* _bitmap, RECT& _bounds,
		BOUNDSACTION _boundsAction = BA_STOP);
	Sprite(Bitmap* _bitmap, POINT _position, POINT _velocity, int _zOrder,
		RECT& _bounds, BOUNDSACTION _boundsAction = BA_STOP);
	virtual ~Sprite();

	// General Methods
	virtual SPRITEACTION  Update();
	void                  Draw(HDC _hDC);
	BOOL                  IsPointInside(int _x, int _y);
	BOOL                  TestCollision(Sprite* _testSprite);

	// Accessor Methods
	Bitmap* GetBitmap() { return bitmap; };
	void	SetNumFrames(int _numFrames);
	void	SetFrameDelay(int _frameDelay);
	RECT&   GetPosition() { return position; };
	void    SetPosition(int _x, int _y);
	void    SetPosition(POINT _position);
	void    SetPosition(RECT& _position);
	void    OffsetPosition(int _x, int _y);
	RECT&   GetCollision() { return collisionRect; };
	POINT   GetVelocity() { return velocity; };
	void    SetVelocity(int _x, int _y);
	void    SetVelocity(POINT _velocity);
	BOOL    GetZOrder() { return zOrder; };
	void    SetZOrder(int _zOrder) { zOrder = _zOrder; };
	void    SetBounds(RECT& _bounds) { CopyRect(&bounds, &_bounds); };
	void    SetBoundsAction(BOUNDSACTION ba) { boundsAction = ba; };
	BOOL    IsHidden() { return isHidden; };
	void    SetHidden(BOOL _isHidden) { isHidden = _isHidden; };
	int     GetWidth() { return bitmap->GetWidth(); };
	int     GetHeight() { return bitmap->GetHeight(); };
};

//-----------------------------------------------------------------
// Sprite Inline Helper Methods
//-----------------------------------------------------------------
inline void Sprite::UpdateFrame() {
	if ((frameDelay >= 0) && (--frameTrigger <= 0)) {
		// Reset the frame trigger;
		frameTrigger = frameDelay;

		// Increment the frame
		if (++curFrame >= numFrames) {
			curFrame = 0;
		}
	}
}

inline void Sprite::CalcCollisionRect() {
	int iXShrink = (position.left - position.right) / 12;
	int iYShrink = (position.top - position.bottom) / 12;
	CopyRect(&collisionRect, &position);
	InflateRect(&collisionRect, iXShrink, iYShrink);
}

//-----------------------------------------------------------------
// Sprite Inline General Methods
//-----------------------------------------------------------------
inline BOOL Sprite::TestCollision(Sprite* _testSprite) {
	RECT& rcTest = _testSprite->GetCollision();
	return collisionRect.left <= rcTest.right &&
		rcTest.left <= collisionRect.right &&
		collisionRect.top <= rcTest.bottom &&
		rcTest.top <= collisionRect.bottom;
}

inline BOOL Sprite::IsPointInside(int _x, int _y) {
	POINT ptPoint;
	ptPoint.x = _x;
	ptPoint.y = _y;
	return PtInRect(&position, ptPoint);
}

//-----------------------------------------------------------------
// Sprite Inline Accessor Methods
//-----------------------------------------------------------------
inline void Sprite::SetNumFrames(int _numFrames) {
	// Set the number of frames
	numFrames = _numFrames;

	// Recalculate the position
	RECT rect = GetPosition();
	rect.right = rect.left + ((rect.right - rect.left) / numFrames);
	SetPosition(rect);
}

inline void Sprite::SetPosition(int _x, int _y) {
	OffsetRect(&position, _x - position.left, _y - position.top);
	CalcCollisionRect();
}

inline void Sprite::SetPosition(POINT _position) {
	OffsetRect(&position, _position.x - position.left,
		_position.y - position.top);
	CalcCollisionRect();
}

inline void Sprite::SetPosition(RECT& _rcPosition) {
	CopyRect(&collisionRect, &_rcPosition);
	CalcCollisionRect();
}

inline void Sprite::OffsetPosition(int _x, int _y) {
	OffsetRect(&position, _x, _y);
	CalcCollisionRect();
}

inline void Sprite::SetVelocity(int _x, int _y) {
	velocity.x = _x;
	velocity.y = _y;
}

inline void Sprite::SetVelocity(POINT _velocity) {
	velocity.x = _velocity.x;
	velocity.y = _velocity.y;
}
