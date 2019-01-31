#ifndef __Keyboard__
#define __Keyboard__

#include <map>

/**
* Class responsible for keyboard input management.
*/
class Keyboard
{
public:
	/**
	* Default constructor.
	*/
	Keyboard();

	/**
	* Constructor.
	*
	* @param asciiStart Beginning of the key scan range.
	* @param asciiEnd End of the key scan range.
	*/
	Keyboard(const int asciiStart, const int asciiEnd);

	/**
	* Set the key states accordingly.
	* Scans key codes in range [m_asciiStart, m_asciiEnd].
	*/
	void getUserInput();

	/**
	* Check if a key was just pressed.
	*
	* @param keyCode ASCII key value.
	* @param bool True if pressed.
	*/
	bool wasPressed(const int keyCode) const;

	/**
	* Check if a key was just released.
	*
	* @param keyCode ASCII key value.
	* @param bool True if released.
	*/
	bool wasReleased(const int keyCode) const;

	/**
	* Check if a key is being held down.
	*
	* @param keyCode ASCII key value.
	* @param bool True if beign held down.
	*/
	bool isHeld(const int keyCode) const;

private:
	int m_asciiStart;
	int m_asciiEnd;

	enum KeyState { UNSET, PRESSED, RELEASED, HELD };
	std::map<int, KeyState> m_keys;
};

#endif // define __Keyboard__
