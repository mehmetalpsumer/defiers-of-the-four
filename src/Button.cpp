//-----------------------------------------------------------------
// Button Object
// C++ Source - Button.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Button.h"

//-----------------------------------------------------------------
// Button Constructor(s)/Destructor
//-----------------------------------------------------------------
Button::Button(HDC _hDC, LPTSTR _text, int _x, int _y) {
	text = _text;
	x = _x;
	y = _y;
	width = BTN_WIDTH;
	height = BTN_HEIGHT;
	hover = false;
	

	RECT bounds = {x, y, x + width,  y + height };

	bgBitmapDefault = new Bitmap(_hDC, width, height, CR_BG);
	bgBitmapHover = new Bitmap(_hDC, width, height, CR_BGHOVER);
	btnSprite = new Sprite(bgBitmapHover);
	btnSprite->SetPosition(x, y);
}

Button::~Button() {
}

//-----------------------------------------------------------------
// Button General Methods
//-----------------------------------------------------------------
void Button::Draw(HDC _hDC) {
		
	// Draw background
	if (hover) {
		SetBkColor(_hDC, CR_TXTBGHOVER);
		SetTextColor(_hDC, CR_TXTHOVER);
		bgBitmapHover->Draw(_hDC, x, y);
	} else {
		SetBkColor(_hDC, CR_TXTBG);
		SetTextColor(_hDC, CR_TXT);
		bgBitmapDefault->Draw(_hDC, x, y);
	}

	RECT bounds = { x, y, x + width,  y + height };	

	HFONT hFont;
	hFont = CreateFont(48, 0, 0, 0, 100, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Courier"));
	SelectObject(_hDC, hFont);
	DrawText(_hDC, text, -1, &bounds, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	DeleteObject(hFont);

}
