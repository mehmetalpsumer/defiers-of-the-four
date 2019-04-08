//-----------------------------------------------------------------
// Game Engine Object
// C++ Source - GameEngine.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "GameEngine.h"

//-----------------------------------------------------------------
// Static Variable Initialization
//-----------------------------------------------------------------
GameEngine *GameEngine::gameEngine = NULL;

//-----------------------------------------------------------------
// Windows Functions
//-----------------------------------------------------------------
int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance,
	PSTR _cmdLine, int _cmdShow)
{
	MSG         msg;
	static int  iTickTrigger = 0;
	int         iTickCount;

	if (GameInitialize(_hInstance))
	{
		// Initialize the game engine
		if (!GameEngine::GetEngine()->Initialize(_cmdShow))
			return FALSE;

		// Enter the main message loop
		while (TRUE)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				// Process the message
				if (msg.message == WM_QUIT)
					break;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				// Make sure the game engine isn't sleeping
				if (!GameEngine::GetEngine()->GetSleep())
				{
					// Check the tick count to see if a game cycle has elapsed
					iTickCount = GetTickCount();
					if (iTickCount > iTickTrigger)
					{
						iTickTrigger = iTickCount +
							GameEngine::GetEngine()->GetFrameDelay();
						HandleKeys();
						GameEngine::GetEngine()->CheckJoystick();
						GameCycle();
					}
				}
			}
		}
		return (int)msg.wParam;
	}

	// End the game
	GameEnd();

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND _hWindow, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{
	// Route all Windows messages to the game engine
	return GameEngine::GetEngine()->HandleEvent(_hWindow, _msg, _wParam, _lParam);
}


//-----------------------------------------------------------------
// GameEngine Constructor(s)/Destructor
//-----------------------------------------------------------------
GameEngine::GameEngine(HINSTANCE _hInstance, LPTSTR _windowClass,
	LPTSTR _title, WORD _icon, WORD _smallIcon, int _width, int _height)
{
	// Set the member variables for the game engine
	gameEngine = this;
	hInstance = _hInstance;
	hWindow = NULL;
	if (lstrlen(_windowClass) > 0)
		lstrcpy(windowClass, _windowClass);
	if (lstrlen(_title) > 0)
		lstrcpy(title, _title);
	icon = _icon;
	smallIcon = _smallIcon;
	width = _width;
	height = _height;
	frameDelay = 50;   // 20 FPS default
	sleep = TRUE;
	joystickID = 0;
	sprites.reserve(50);
}

GameEngine::~GameEngine()
{
}

//-----------------------------------------------------------------
// Game Engine General Methods
//-----------------------------------------------------------------
BOOL GameEngine::Initialize(int _cmdShow)
{
	WNDCLASSEX    wndclass;

	// Create the window class for the main window
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance,
		MAKEINTRESOURCE(GetIcon()));
	wndclass.hIconSm = LoadIcon(hInstance,
		MAKEINTRESOURCE(GetSmallIcon()));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = windowClass;

	// Register the window class
	if (!RegisterClassEx(&wndclass))
		return FALSE;

	// Calculate the window size and position based upon the game size
	int iWindowWidth = width + GetSystemMetrics(SM_CXFIXEDFRAME) * 2,
		iWindowHeight = height + GetSystemMetrics(SM_CYFIXEDFRAME) * 2 +
		GetSystemMetrics(SM_CYCAPTION);
	if (wndclass.lpszMenuName != NULL)
		iWindowHeight += GetSystemMetrics(SM_CYMENU);
	int iXWindowPos = (GetSystemMetrics(SM_CXSCREEN) - iWindowWidth) / 2,
		iYWindowPos = (GetSystemMetrics(SM_CYSCREEN) - iWindowHeight) / 2;

	// Create the window
	hWindow = CreateWindow(windowClass, title, WS_POPUPWINDOW |
		WS_CAPTION | WS_MINIMIZEBOX, iXWindowPos, iYWindowPos, iWindowWidth,
		iWindowHeight, NULL, NULL, hInstance, NULL);
	if (!hWindow)
		return FALSE;

	// Show and update the window
	ShowWindow(hWindow, _cmdShow);
	UpdateWindow(hWindow);

	return TRUE;
}

LRESULT GameEngine::HandleEvent(HWND _hWindow, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{
	// Route Windows messages to game engine member functions
	switch (_msg)
	{
	case WM_CREATE:
		// Set the game window and start the game
		SetWindow(_hWindow);
		GameStart(_hWindow);
		return 0;

	case WM_ACTIVATE:
		// Activate/deactivate the game and update the Sleep status
		if (_wParam != WA_INACTIVE)
		{
			GameActivate(_hWindow);
			SetSleep(FALSE);
		}
		else
		{
			GameDeactivate(_hWindow);
			SetSleep(TRUE);
		}
		return 0;

	case WM_PAINT:
		HDC         hDC;
		PAINTSTRUCT ps;
		hDC = BeginPaint(_hWindow, &ps);

		// Paint the game
		GamePaint(hDC);

		EndPaint(_hWindow, &ps);
		return 0;

	case WM_LBUTTONDOWN:
		// Handle left mouse button press
		MouseButtonDown(LOWORD(_lParam), HIWORD(_lParam), TRUE);
		return 0;

	case WM_LBUTTONUP:
		// Handle left mouse button release
		MouseButtonUp(LOWORD(_lParam), HIWORD(_lParam), TRUE);
		return 0;

	case WM_RBUTTONDOWN:
		// Handle right mouse button press
		MouseButtonDown(LOWORD(_lParam), HIWORD(_lParam), FALSE);
		return 0;

	case WM_RBUTTONUP:
		// Handle right mouse button release
		MouseButtonUp(LOWORD(_lParam), HIWORD(_lParam), FALSE);
		return 0;

	case WM_MOUSEMOVE:
		// Handle mouse movement
		MouseMove(LOWORD(_lParam), HIWORD(_lParam));
		return 0;

	case WM_DESTROY:
		// End the game and exit the application
		GameEnd();
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(_hWindow, _msg, _wParam, _lParam);
}

void GameEngine::ErrorQuit(LPTSTR _errorMsg)
{
	MessageBox(GetWindow(), _errorMsg, TEXT("Critical Error"), MB_OK | MB_ICONERROR);
	PostQuitMessage(0);
}

BOOL GameEngine::InitJoystick()
{
	// Make sure joystick driver is present
	UINT uiNumJoysticks;
	if ((uiNumJoysticks = joyGetNumDevs()) == 0)
		return FALSE;

	// Make sure the joystick is attached
	JOYINFO jiInfo;
	if (joyGetPos(JOYSTICKID1, &jiInfo) != JOYERR_UNPLUGGED)
		joystickID = JOYSTICKID1;
	else
		return FALSE;

	// Calculate the trip values
	JOYCAPS jcCaps;
	joyGetDevCaps(joystickID, &jcCaps, sizeof(JOYCAPS));
	DWORD dwXCenter = ((DWORD)jcCaps.wXmin + jcCaps.wXmax) / 2;
	DWORD dwYCenter = ((DWORD)jcCaps.wYmin + jcCaps.wYmax) / 2;
	joystickTrip.left = (jcCaps.wXmin + (WORD)dwXCenter) / 2;
	joystickTrip.right = (jcCaps.wXmax + (WORD)dwXCenter) / 2;
	joystickTrip.top = (jcCaps.wYmin + (WORD)dwYCenter) / 2;
	joystickTrip.bottom = (jcCaps.wYmax + (WORD)dwYCenter) / 2;

	return TRUE;
}

void GameEngine::CaptureJoystick()
{
	// Capture the joystick
	if (joystickID == JOYSTICKID1)
		joySetCapture(hWindow, joystickID, NULL, TRUE);
}

void GameEngine::ReleaseJoystick()
{
	// Release the joystick
	if (joystickID == JOYSTICKID1)
		joyReleaseCapture(joystickID);
}

void GameEngine::CheckJoystick()
{
	if (joystickID == JOYSTICKID1)
	{
		JOYINFO jiInfo;
		JOYSTATE jsJoystickState = 0;
		if (joyGetPos(joystickID, &jiInfo) == JOYERR_NOERROR)
		{
			// Check horizontal movement
			if (jiInfo.wXpos < (WORD)joystickTrip.left)
				jsJoystickState |= JOY_LEFT;
			else if (jiInfo.wXpos > (WORD)joystickTrip.right)
				jsJoystickState |= JOY_RIGHT;

			// Check vertical movement
			if (jiInfo.wYpos < (WORD)joystickTrip.top)
				jsJoystickState |= JOY_UP;
			else if (jiInfo.wYpos > (WORD)joystickTrip.bottom)
				jsJoystickState |= JOY_DOWN;

			// Check buttons
			if (jiInfo.wButtons & JOY_BUTTON1)
				jsJoystickState |= JOY_FIRE1;
			if (jiInfo.wButtons & JOY_BUTTON2)
				jsJoystickState |= JOY_FIRE2;
		}

		// Allow the game to handle the joystick
		HandleJoystick(jsJoystickState);
	}
}

void GameEngine::AddSprite(Sprite* _sprite)
{
	// Add a sprite to the sprite vector
	if (_sprite != NULL)
	{
		// See if there are sprites already in the sprite vector
		if (sprites.size() > 0)
		{
			// Find a spot in the sprite vector to insert the sprite by its z-order
			vector<Sprite*>::iterator siSprite;
			for (siSprite = sprites.begin(); siSprite != sprites.end(); siSprite++)
				if (_sprite->GetZOrder() < (*siSprite)->GetZOrder())
				{
					// Insert the sprite into the sprite vector
					sprites.insert(siSprite, _sprite);
					return;
				}
		}

		// The sprite's z-order is highest, so add it to the end of the vector
		sprites.push_back(_sprite);
	}
}

void GameEngine::DrawSprites(HDC _hDC)
{
	// Draw the sprites in the sprite vector
	vector<Sprite*>::iterator siSprite;
	for (siSprite = sprites.begin(); siSprite != sprites.end(); siSprite++) {
		printf("This is to do");
		(*siSprite)->Draw(_hDC);
	}
}

void GameEngine::UpdateSprites()
{
	// Update the sprites in the sprite vector
	RECT          rcOldSpritePos;
	SPRITEACTION  saSpriteAction;
	vector<Sprite*>::iterator siSprite;
	for (siSprite = sprites.begin(); siSprite != sprites.end(); siSprite++)
	{
		// Save the old sprite position in case we need to restore it
		rcOldSpritePos = (*siSprite)->GetPosition();

		// Update the sprite
		saSpriteAction = (*siSprite)->Update();

		// Handle the SA_KILL sprite action
		if (saSpriteAction & SA_KILL)
		{
			delete (*siSprite);
			sprites.erase(siSprite);
			siSprite--;
			continue;
		}

		// See if the sprite collided with any others
		if (CheckSpriteCollision(*siSprite))
			// Restore the old sprite position
			(*siSprite)->SetPosition(rcOldSpritePos);
	}
}

//-----------------------------------------------------------------
// Game Engine Helper Methods
//-----------------------------------------------------------------
BOOL GameEngine::CheckSpriteCollision(Sprite* _testSprite)
{
	// See if the sprite has collided with any other sprites
	vector<Sprite*>::iterator siSprite;
	for (siSprite = sprites.begin(); siSprite != sprites.end(); siSprite++)
	{
		// Make sure not to check for collision with itself
		if (_testSprite == (*siSprite))
			continue;

		// Test the collision
		if (_testSprite->TestCollision(*siSprite))
			// Collision detected
			return SpriteCollision((*siSprite), _testSprite);
	}

	// No collision
	return FALSE;
}

void GameEngine::CleanupSprites()
{
	Sprite* sprt2;
	// Delete and remove the sprites in the sprite vector
	vector<Sprite*>::iterator siSprite;
	for (siSprite = sprites.begin(); siSprite != sprites.end(); siSprite++)
	{
		delete (*siSprite);
		//m_vSprites.erase(siSprite);
		//siSprite--;
	}
}

Sprite* GameEngine::IsPointInSprite(int _x, int _y)
{
	// See if the point is in a sprite in the sprite vector
	vector<Sprite*>::reverse_iterator siSprite;
	for (siSprite = sprites.rbegin(); siSprite != sprites.rend(); siSprite++)
		if (!(*siSprite)->IsHidden() && (*siSprite)->IsPointInside(_x, _y))
			return (*siSprite);

	// The point is not in a sprite
	return NULL;
}
