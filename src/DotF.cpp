//-----------------------------------------------------------------
// Defiers of the Four Application
// C++ Source - DotF.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "DotF.h"


//-----------------------------------------------------------------
// Game Engine Functions
//-----------------------------------------------------------------
BOOL GameInitialize(HINSTANCE hInstance)
{
	// Create the game engine
	_pGame = new GameEngine(hInstance, (LPTSTR) TEXT("Defiers of the Four"),
		(LPTSTR) TEXT("Defiers of the Four"), (WORD) IDI_DOTF, (WORD) IDI_DOTF_SM, 1024, 768);
	if (_pGame == NULL)
		return FALSE;

	// Set the frame rate
	_pGame->SetFrameRate(30);

	// Store the instance handle
	_hInstance = hInstance;

	// Configure game variables
	characters = new Character*[4];

	return TRUE;
}

void GameStart(HWND hWindow)
{
	// Seed the random number generator
	srand(GetTickCount());

	// Create the offscreen device context and bitmap
	_hOffscreenDC = CreateCompatibleDC(GetDC(hWindow));
	_hOffscreenBitmap = CreateCompatibleBitmap(GetDC(hWindow),
		_pGame->GetWidth(), _pGame->GetHeight());
	SelectObject(_hOffscreenDC, _hOffscreenBitmap);

	// Create and load the bitmaps
	HDC hDC = GetDC(hWindow);

	// Load characters
	POINT p;
	p.x = 0;
	p.y = 0;

	Bitmap *bmSheep = new Bitmap(hDC, IDB_SHEEP, _hInstance);
	RECT rcBounds = { 0, 0, 600, 400 };
	Sprite *spr = new Sprite(bmSheep, rcBounds, BA_WRAP);
	spr->SetPosition(500, 300);
	_pGame->AddSprite(spr);
	int cooldowns[2] = { 1, 5 };
	char name[20] = "RoboCap";
	characters[0] = new R_RoboCap(spr, p, p, 100, 5, name, cooldowns);
}

void GameEnd()
{
	// Cleanup the offscreen device context and bitmap
	DeleteObject(_hOffscreenBitmap);
	DeleteDC(_hOffscreenDC);

	// Cleanup the sprites
	_pGame->CleanupSprites();

	// Cleanup the game engine
	delete _pGame;
}

void GameActivate(HWND hWindow)
{
}

void GameDeactivate(HWND hWindow)
{
}

void GamePaint(HDC hDC)
{
	// Draw the background


	// Draw the sprites
	_pGame->DrawSprites(hDC);
}

void GameCycle()
{
	// Update the sprites
	_pGame->UpdateSprites();

	// Obtain a device context for repainting the game
	HWND  hWindow = _pGame->GetWindow();
	HDC   hDC = GetDC(hWindow);

	// Paint the game to the offscreen device context
	GamePaint(_hOffscreenDC);

	// Blit the offscreen bitmap to the game screen
	BitBlt(hDC, 0, 0, _pGame->GetWidth(), _pGame->GetHeight(),
		_hOffscreenDC, 0, 0, SRCCOPY);

	// Cleanup
	ReleaseDC(hWindow, hDC);
}

void HandleKeys()
{
	POINT speed;
	speed.x = 0;
	speed.y = 0;

	if (GetAsyncKeyState('W') < 0) {
		speed.y = -characters[0]->GetSpeed();
	}
	else if (GetAsyncKeyState('S') < 0) {
		speed.y = characters[0]->GetSpeed();
	}

	if (GetAsyncKeyState('D') < 0) {
		speed.x = characters[0]->GetSpeed();
	}
	else if (GetAsyncKeyState('A') < 0) {
		speed.x = -characters[0]->GetSpeed();
	}
	
	POINT normalizedSpeed = NormalizeSpeed(speed.x, speed.y);
	
	characters[0]->GetSprite()->SetVelocity(normalizedSpeed.x, normalizedSpeed.y);
}

POINT NormalizeSpeed(int x, int y) {
	POINT normalizedSpeed;
	normalizedSpeed.x = x;
	normalizedSpeed.y = y;

	if (x != 0 && y != 0) {
		int newVelocity = ceil(sqrt((pow(x, 2) + pow(y, 2))));
		normalizedSpeed.x = newVelocity;
		normalizedSpeed.y = newVelocity;
	}

	return normalizedSpeed;
}

void MouseButtonDown(int x, int y, BOOL bLeft)
{

}

void MouseButtonUp(int x, int y, BOOL bLeft)
{
}

void MouseMove(int x, int y)
{

}

void HandleJoystick(JOYSTATE jsJoystickState)
{
}

BOOL SpriteCollision(Sprite* pSpriteHitter, Sprite* pSpriteHittee)
{
	// Swap the sprite velocities so that they appear to bounce
	POINT ptSwapVelocity = pSpriteHitter->GetVelocity();
	pSpriteHitter->SetVelocity(pSpriteHittee->GetVelocity());
	pSpriteHittee->SetVelocity(ptSwapVelocity);
	return TRUE;
}
