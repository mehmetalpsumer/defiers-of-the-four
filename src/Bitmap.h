//-----------------------------------------------------------------
// Bitmap Object
// C++ Header - Bitmap.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>

//-----------------------------------------------------------------
// Custom Data Types
//-----------------------------------------------------------------
struct BITMAPINFO_256
{
	BITMAPINFOHEADER  bmiHeader;
	RGBQUAD           bmiColors[256];
};

//-----------------------------------------------------------------
// Bitmap Class
//-----------------------------------------------------------------
class Bitmap
{
protected:
	// Member Variables
	HBITMAP hBitmap;
	int     width, height;

	// Helper Methods
	void Free();

public:
	// Constructor(s)/Destructor
	Bitmap();
	Bitmap(HDC _hDC, LPTSTR _fileName);
	Bitmap(HDC _hDC, UINT _resID, HINSTANCE _hInstance);
	Bitmap(HDC _hDC, int _width, int _height, COLORREF _color = RGB(0, 0, 0));
	virtual ~Bitmap();

	// General Methods
	BOOL Create(HDC _hDC, LPTSTR _fileName);
	BOOL Create(HDC _hDC, UINT _resID, HINSTANCE _hInstance);
	BOOL Create(HDC _hDC, int _width, int _height, COLORREF _color);
	void Draw(HDC _hDC, int _x, int _y, BOOL _isTrans = FALSE,
		COLORREF _transColor = RGB(255, 0, 255));
	int  GetWidth() { return width; };
	int  GetHeight() { return height; };
};
