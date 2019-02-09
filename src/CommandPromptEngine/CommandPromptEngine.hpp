#ifndef __CommandPromptEngine__
#define __CommandPromptEngine__

#include "Graphics.hpp"
#include "Keyboard.hpp"
#include <Windows.h>

/**
* Main class from which any user code should inherit.
*
* Quick guide:
* > Create a class which inherits from CommandPromptEngine
* > Overwrite the userStartup() and userUpdate() methods
* > Create an instance of your new class
* > Call the start(...) method with
*/
class CommandPromptEngine
{
public:
	/**
	* Default constructor.
	*/
	CommandPromptEngine();

	/**
	* Default destructor. Remember to write your own, if needed.
	*/
	virtual ~CommandPromptEngine();

	/**
	* Set the console parameters.
	*
	* @param width Number of cells in a row.
	* @param height Number of cells in a column.
	* @param fontWidth Width of a single cell.
	* @param fontHeight Height of a single cell.
	* @return bool True on success.
	*/
	bool setSize(const int width, const int height, const int fontWidth, const int fontHeight);

	/**
	* Start the engine.
	*/
	void start();

protected:
	/**
	* Only called once. Use this method for initial setup.
	*
	* @return bool True on success.
	*/
	virtual bool userStartup() = 0;

	/**
	* Called on every game step.
	*
	* @return bool True on success.
	*/
	virtual bool userUpdate() = 0;

	/**
	* Check if a key was pressed.
	*
	* @param keyCode ASCII key value.
	* @return bool True if pressed.
	*/
	bool keyPressed(const int keyCode) const;

	/**
	* Check if a key was released.
	*
	* @param keyCode ASCII key value.
	* @return bool True if released.
	*/
	bool keyReleased(const int keyCode) const;

	/**
	* Check if a key is currently being held.
	*
	* @param keyCode ASCII key value.
	* @return bool True if held.
	*/
	bool keyHeld(const int keyCode) const;

	/**
	* Fill a single cell with a given color.
	*
	* @param x
	* @param y
	* @param color Color code.
	*/
	void fill(const int x, const int y, const int color);

private:
	int m_screenWidth;
	int m_screenHeight;
	bool m_isRunning;

	HANDLE m_consoleOutHandle;
	SMALL_RECT m_consoleRectangle;

	Keyboard m_keyboard;
	Graphics m_graphics;
};

#endif // __CommandPromptEngine__
