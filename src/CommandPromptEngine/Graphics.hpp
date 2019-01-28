#ifndef __Graphics__
#define __Graphics__

#include <Windows.h>

/**
* Class responsible for controlling the console buffer.
*/
class Graphics
{
public:
	/**
	* Default constructor.
	*/
	Graphics();

	/**
	* Default destructor.
	*/
	~Graphics();

	/**
	* Set the console screen buffer size.
	*
	* @param width Number of cells in a row.
	* @param height Number of cells in a column.
	* @return bool True on success.
	*/
	bool setBufferSize(const int width, const int height);

	/**
	* Get the console screen buffer for displaying.
	*
	* @return CHAR_INFO* Pointer to the buffer array. Values are immutable.
	*/
	const CHAR_INFO* getBuffer() const;

	/**
	* Get the console screen buffer size.
	*
	* @return COORD Size as coordinates.
	*/
	COORD getBufferSize() const;

private:
	int m_bufferWidth;
	int m_bufferHeight;
	CHAR_INFO* m_consoleBuffer;
};

#endif // define __Graphics__
