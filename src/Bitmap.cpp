//-----------------------------------------------------------------
// Bitmap Object
// C++ Source - Bitmap.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Bitmap.h"

//-----------------------------------------------------------------
// Bitmap Constructor(s)/Destructor
//-----------------------------------------------------------------
Bitmap::Bitmap()
	: hBitmap(NULL), width(0), height(0)
{
}

// Create a bitmap from a file
Bitmap::Bitmap(HDC _hDC, LPTSTR _fileName)
	: hBitmap(NULL), width(0), height(0)
{
	Create(_hDC, _fileName);
}

// Create a bitmap from a resource
Bitmap::Bitmap(HDC _hDC, UINT _resID, HINSTANCE _hInstance)
	: hBitmap(NULL), width(0), height(0)
{
	Create(_hDC, _resID, _hInstance);
}

// Create a blank bitmap from scratch
Bitmap::Bitmap(HDC _hDC, int _width, int _height, COLORREF _color)
	: hBitmap(NULL), width(0), height(0)
{
	Create(_hDC, _width, _height, _color);
}

Bitmap::~Bitmap()
{
	Free();
}

//-----------------------------------------------------------------
// Bitmap Helper Methods
//-----------------------------------------------------------------
void Bitmap::Free()
{
	// Delete the bitmap graphics object
	if (hBitmap != NULL)
	{
		DeleteObject(hBitmap);
		hBitmap = NULL;
	}
}

//-----------------------------------------------------------------
// Bitmap General Methods
//-----------------------------------------------------------------
BOOL Bitmap::Create(HDC _hDC, LPTSTR _fileName)
{
	// Free any previous bitmap info
	Free();

	// Open the bitmap file
	HANDLE hFile = CreateFile(_fileName, GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	// Read the bitmap file header
	BITMAPFILEHEADER  bmfHeader;
	DWORD             dwBytesRead;
	BOOL bOK = ReadFile(hFile, &bmfHeader, sizeof(BITMAPFILEHEADER),
		&dwBytesRead, NULL);
	if ((!bOK) || (dwBytesRead != sizeof(BITMAPFILEHEADER)) ||
		(bmfHeader.bfType != 0x4D42))
	{
		CloseHandle(hFile);
		return FALSE;
	}

	BITMAPINFO* pBitmapInfo = (BITMAPINFO*)(new BITMAPINFO_256);
	if (pBitmapInfo != NULL)
	{
		// Read the bitmap info header
		bOK = ReadFile(hFile, pBitmapInfo, sizeof(BITMAPINFOHEADER),
			&dwBytesRead, NULL);
		if ((!bOK) || (dwBytesRead != sizeof(BITMAPINFOHEADER)))
		{
			CloseHandle(hFile);
			Free();
			return FALSE;
		}

		// Store the width and height of the bitmap
		width = (int)pBitmapInfo->bmiHeader.biWidth;
		height = (int)pBitmapInfo->bmiHeader.biHeight;

		// Skip (forward or backward) to the color info, if necessary
		if (pBitmapInfo->bmiHeader.biSize != sizeof(BITMAPINFOHEADER))
			SetFilePointer(hFile, pBitmapInfo->bmiHeader.biSize - sizeof
			(BITMAPINFOHEADER), NULL, FILE_CURRENT);

		// Read the color info
		bOK = ReadFile(hFile, pBitmapInfo->bmiColors,
			pBitmapInfo->bmiHeader.biClrUsed * sizeof(RGBQUAD), &dwBytesRead,
			NULL);

		// Get a handle to the bitmap and copy the image bits
		PBYTE pBitmapBits;
		hBitmap = CreateDIBSection(_hDC, pBitmapInfo, DIB_RGB_COLORS,
			(PVOID*)&pBitmapBits, NULL, 0);
		if ((hBitmap != NULL) && (pBitmapBits != NULL))
		{
			SetFilePointer(hFile, bmfHeader.bfOffBits, NULL, FILE_BEGIN);
			bOK = ReadFile(hFile, pBitmapBits, pBitmapInfo->bmiHeader.biSizeImage,
				&dwBytesRead, NULL);
			if (bOK)
				return TRUE;
		}
	}

	// Something went wrong, so cleanup everything
	Free();
	return FALSE;
}

BOOL Bitmap::Create(HDC _hDC, UINT _resID, HINSTANCE _hInstance)
{
	// Free any previous DIB info
	Free();

	// Find the bitmap resource
	HRSRC hResInfo = FindResource(_hInstance, MAKEINTRESOURCE(_resID), RT_BITMAP);
	if (hResInfo == NULL)
		return FALSE;

	// Load the bitmap resource
	HGLOBAL hMemBitmap = LoadResource(_hInstance, hResInfo);
	if (hMemBitmap == NULL)
		return FALSE;

	// Lock the resource and access the entire bitmap image
	PBYTE pBitmapImage = (BYTE*)LockResource(hMemBitmap);
	if (pBitmapImage == NULL)
	{
		FreeResource(hMemBitmap);
		return FALSE;
	}

	// Store the width and height of the bitmap
	BITMAPINFO* pBitmapInfo = (BITMAPINFO*)pBitmapImage;
	width = (int)pBitmapInfo->bmiHeader.biWidth;
	height = (int)pBitmapInfo->bmiHeader.biHeight;

	// Get a handle to the bitmap and copy the image bits
	PBYTE pBitmapBits;
	hBitmap = CreateDIBSection(_hDC, pBitmapInfo, DIB_RGB_COLORS,
		(PVOID*)&pBitmapBits, NULL, 0);
	if ((hBitmap != NULL) && (pBitmapBits != NULL))
	{
		const PBYTE pTempBits = pBitmapImage + pBitmapInfo->bmiHeader.biSize +
			pBitmapInfo->bmiHeader.biClrUsed * sizeof(RGBQUAD);
		CopyMemory(pBitmapBits, pTempBits, pBitmapInfo->bmiHeader.biSizeImage);

		// Unlock and free the bitmap graphics object
		UnlockResource(hMemBitmap);
		FreeResource(hMemBitmap);
		return TRUE;
	}

	// Something went wrong, so cleanup everything
	UnlockResource(hMemBitmap);
	FreeResource(hMemBitmap);
	Free();
	return FALSE;
}

BOOL Bitmap::Create(HDC _hDC, int _width, int _height, COLORREF _color)
{
	// Create a blank bitmap
	hBitmap = CreateCompatibleBitmap(_hDC, _width, _height);
	if (hBitmap == NULL)
		return FALSE;

	// Set the width and height
	width = _width;
	height = _height;

	// Create a memory device context to draw on the bitmap
	HDC hMemDC = CreateCompatibleDC(_hDC);

	// Create a solid brush to fill the bitmap
	HBRUSH hBrush = CreateSolidBrush(_color);

	// Select the bitmap into the device context
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

	// Fill the bitmap with a solid color
	RECT rcBitmap = { 0, 0, width, height };
	FillRect(hMemDC, &rcBitmap, hBrush);

	// Cleanup
	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
	DeleteObject(hBrush);

	return TRUE;
}

void Bitmap::Draw(HDC _hDC, int _x, int _y, BOOL _isTrans, COLORREF _transColor)
{
	if (hBitmap != NULL)
	{
		// Create a memory device context for the bitmap
		HDC hMemDC = CreateCompatibleDC(_hDC);

		// Select the bitmap into the device context
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

		// Draw the bitmap to the destination device context
		if (_isTrans)
			TransparentBlt(_hDC, _x, _y, GetWidth(), GetHeight(), hMemDC, 0, 0,
				GetWidth(), GetHeight(), _transColor);
		else
			BitBlt(_hDC, _x, _y, GetWidth(), GetHeight(), hMemDC, 0, 0, SRCCOPY);

		// Restore and delete the memory device context
		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}
}

void Bitmap::DrawPart(HDC _hDC, int _x, int _y, int _xPart, int _yPart,
	int _wPart, int _hPart, BOOL _isTrans, COLORREF _transColor)
{
	if (hBitmap != NULL)
	{
		// Create a memory device context for the bitmap
		HDC hMemDC = CreateCompatibleDC(_hDC);

		// Select the bitmap into the device context
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

		// Draw the bitmap to the destination device context
		if (_isTrans)
			TransparentBlt(_hDC, _x, _y, _wPart, _hPart, hMemDC, _xPart, _yPart,
				_wPart, _hPart, _transColor);
		else
			BitBlt(_hDC, _x, _y, _wPart, _hPart, hMemDC, _xPart, _yPart, SRCCOPY);

		// Restore and delete the memory device context
		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}
}
