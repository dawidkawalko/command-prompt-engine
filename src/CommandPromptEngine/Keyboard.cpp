#include "Keyboard.hpp"
#include <Windows.h>

Keyboard::Keyboard()
	: Keyboard(0, 255) // Full ASCII range
{

}

Keyboard::Keyboard(const int asciiStart, const int asciiEnd)
	: m_asciiStart(asciiStart), m_asciiEnd(asciiEnd)
{

}

void Keyboard::getUserInput()
{
	for (int keyCode = m_asciiStart; keyCode <= m_asciiEnd; ++keyCode)
	{
		auto& keyState = m_keys[keyCode];

		if (GetAsyncKeyState(keyCode) & 0x8000)
		{
			if (keyState == KeyState::PRESSED)
			{
				keyState = KeyState::HELD;
			}

			if (keyState != KeyState::HELD)
			{
				keyState = KeyState::PRESSED;
			}
		}
		else
		{
			if (keyState == KeyState::RELEASED)
			{
				keyState = KeyState::UNSET;
			}

			if (keyState == KeyState::HELD)
			{
				keyState = KeyState::RELEASED;
			}
		}
	}
}

bool Keyboard::wasPressed(const int keyCode) const
{
	return m_keys.at(keyCode) == KeyState::PRESSED;
}

bool Keyboard::wasReleased(const int keyCode) const
{
	return m_keys.at(keyCode) == KeyState::RELEASED;
}

bool Keyboard::isHeld(const int keyCode) const
{
	return m_keys.at(keyCode) == KeyState::HELD;
}
