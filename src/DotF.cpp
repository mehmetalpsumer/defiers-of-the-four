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
BOOL GameInitialize(HINSTANCE _hInstance)
{
	// Create the game engine
	game = new GameEngine(_hInstance, (LPTSTR) TEXT("Defiers of the Four"),
		(LPTSTR) TEXT("Defiers of the Four"), (WORD) IDI_DOTF, (WORD) IDI_DOTF_SM, 1024, 768);
	if (game == NULL)
		return FALSE;

	// Set the frame rate
	game->SetFrameRate(30);

	// Store the instance handle
	hInstance = _hInstance;	

	// Configure game variables
	currentScene = MAIN_MENU;
	playerNum = -1;

	return TRUE;
}

void GameStart(HWND _hWindow)
{
	// Seed the random number generator
	srand(GetTickCount());

	// Create the offscreen device context and bitmap
	offScreenDC = CreateCompatibleDC(GetDC(_hWindow));
	offScreenBitmap = CreateCompatibleBitmap(GetDC(_hWindow),
		game->GetWidth(), game->GetHeight());
	SelectObject(offScreenDC, offScreenBitmap);

	// Device context
	HDC hDC = GetDC(_hWindow);

	// Menu bitmaps and sprites
	bmMenuBackground = new Bitmap(hDC, 1024, 768, RGB(22, 15, 28));
	bmMenuTitle = new Bitmap(hDC, IDB_MENU_TITLE, hInstance);

	/* Main menu buttons */
	btnPlay = new Button(hDC, (LPTSTR) TEXT("Play"), 412, 400);
	mainMenuButtons.push_back(btnPlay);
	btnExit = new Button(hDC, (LPTSTR)TEXT("Exit"), 412, 450);
	mainMenuButtons.push_back(btnExit);
	
	/* Play menu buttons */
	btn1Player = new Button(hDC, (LPTSTR)TEXT("1 Player"), 412, 400);
	playMenuButtons.push_back(btn1Player);
	btn2Player = new Button(hDC, (LPTSTR)TEXT("2 Player"), 412, 450);
	playMenuButtons.push_back(btn2Player);
	btnBackToMain = new Button(hDC, (LPTSTR)TEXT("Back"), 412, 500);
	playMenuButtons.push_back(btnBackToMain);
}

void GameEnd()
{
	// Cleanup the offscreen device context and bitmap
	DeleteObject(offScreenBitmap);
	DeleteDC(offScreenDC);

	// Cleanup the sprites
	game->CleanupSprites();

	// Cleanup the game engine
	delete game;
}

void GameActivate(HWND _hWindow)
{
}

void GameDeactivate(HWND _hWindow)
{
}

void GamePaint(HDC _hDC)
{
	switch (currentScene) {
		case MAIN_MENU:
			bmMenuBackground->Draw(_hDC, 0, 0);
			bmMenuTitle->Draw(_hDC, 280, 200, 1, RGB(255, 0, 255));
			for (auto &Button : mainMenuButtons) {
				Button->Draw(_hDC);
			}
			break;
		case PLAY_MENU:
			bmMenuBackground->Draw(_hDC, 0, 0);
			bmMenuTitle->Draw(_hDC, 280, 200, 1, RGB(255, 0, 255));
			for (auto &Button : playMenuButtons) {
				Button->Draw(_hDC);
			}
			break;
		case SELECT_MENU:
			break;
		case GAME:
			game->DrawSprites(_hDC);
			break;
		case GAME_PAUSE:
			break;
		default:
			break;
	}
}

void GameCycle()
{
	// Update the sprites
	game->UpdateSprites();

	// Obtain a device context for repainting the game
	HWND  hWindow = game->GetWindow();
	HDC   hDC = GetDC(hWindow);

	// Paint the game to the offscreen device context
	GamePaint(offScreenDC);

	// Blit the offscreen bitmap to the game screen
	BitBlt(hDC, 0, 0, game->GetWidth(), game->GetHeight(),
		offScreenDC, 0, 0, SRCCOPY);

	// Cleanup
	ReleaseDC(hWindow, hDC);
}

void HandleKeys()
{
}


void MouseButtonDown(int _x, int _y, BOOL _isLeftClick)
{
	

}

void MouseButtonUp(int _x, int _y, BOOL _isLeftClick)
{
	if (_isLeftClick) {
		HandleMenuButtonClick(_x, _y);
	}
}

void MouseMove(int _x, int _y)
{
	// Hover effect for menu buttons
	HandleMenuButtonHover(_x, _y);
	
}

void HandleJoystick(JOYSTATE _joystickState)
{
}

BOOL SpriteCollision(Sprite* _spriteHitter, Sprite* _spriteHittee)
{
	// Swap the sprite velocities so that they appear to bounce
	POINT ptSwapVelocity = _spriteHitter->GetVelocity();
	_spriteHitter->SetVelocity(_spriteHittee->GetVelocity());
	_spriteHittee->SetVelocity(ptSwapVelocity);
	return TRUE;
}


void HandleMenuButtonClick(int _x, int _y) {
	switch (currentScene) {
	case MAIN_MENU:
		// Play clicked
		if (btnPlay->GetSprite()->IsPointInside(_x, _y)) {
			PlaySound((LPCWSTR)IDW_MENU_CLICK, hInstance, SND_ASYNC | SND_RESOURCE);
			currentScene = PLAY_MENU;
		}

		// Exit clicked
		if (btnExit->GetSprite()->IsPointInside(_x, _y)) {
			PlaySound((LPCWSTR)IDW_MENU_CLICK_BACK, hInstance, SND_ASYNC | SND_RESOURCE);
			GameEnd();
		}
		break;
	case PLAY_MENU:
		// Back to main menu clicked
		if (btnBackToMain->GetSprite()->IsPointInside(_x, _y)) {
			PlaySound((LPCWSTR)IDW_MENU_CLICK_BACK, hInstance, SND_ASYNC | SND_RESOURCE);
			currentScene = MAIN_MENU;
		}

		// 1 - Player selected
		if (btn1Player->GetSprite()->IsPointInside(_x, _y)) {
			PlaySound((LPCWSTR)IDW_MENU_CLICK, hInstance, SND_ASYNC | SND_RESOURCE);
			playerNum = 1;
			currentScene = SELECT_MENU;
		}

		// 2 - Player selected
		if (btn2Player->GetSprite()->IsPointInside(_x, _y)) {
			PlaySound((LPCWSTR)IDW_MENU_CLICK, hInstance, SND_ASYNC | SND_RESOURCE);
			playerNum = 2;
			currentScene = SELECT_MENU;
		}
		break;
	default:
		break;
	}
}

void HandleMenuButtonHover(int _x, int _y) {
	switch (currentScene) {
	case MAIN_MENU:
		for (auto &Button : mainMenuButtons)
		{
			if (Button->GetSprite()->IsPointInside(_x, _y)) {
				Button->SetHover(true);
			}
			else {
				Button->SetHover(false);
			}
		}
		break;
	case PLAY_MENU:
		for (auto &Button : playMenuButtons)
		{
			if (Button->GetSprite()->IsPointInside(_x, _y)) {
				Button->SetHover(true);
			}
			else {
				Button->SetHover(false);
			}
		}
		break;
	default:
		break;
	}
}