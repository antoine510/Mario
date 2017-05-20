#include "button.h"

Button::Button(int x, int y, int texID) :
	m_rectangle(x, y, 0, 0, FRAME_SCREEN),
	m_texID(texID) {}

