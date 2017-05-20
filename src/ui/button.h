#pragma once

#include "../common.h"
#include "../rectangle.h"
#include "../graphics/graphics.h"

class Button {
public:
	Button(int x, int y, int texID);

	enum class State { UNSELECTED, SELECTED };

	inline int getTexID() const { return m_texID; }
	inline State getState() const { return m_state; }
	inline void setState(State newState) { m_state = newState; }
	inline bool isValid() const { return (m_rectangle.getW() != 0 && m_rectangle.getH() != 0); }
	inline Rectangle& getRect() { return m_rectangle; }

private:
	Rectangle m_rectangle;
	State m_state = State::UNSELECTED;
	int m_texID;

	friend void Graphics::Main::renderButton(Button*);
};

