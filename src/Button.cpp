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
	hDC = _hDC;
	text = _text;
	x = _x;
	y = _y;
	width = BTN_WIDTH;
	height = BTN_HEIGHT;
	hover = false;
	

	RECT bounds = {x, y, x + width,  y + height };

	bgBitmapDefault = new Bitmap(hDC, width, height, CR_BG);
	bgBitmapHover = new Bitmap(hDC, width, height, CR_BGHOVER);
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
	DrawText(_hDC, text, -1, &bounds, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

}
