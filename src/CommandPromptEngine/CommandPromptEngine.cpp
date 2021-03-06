#include "CommandPromptEngine.hpp"
#include <chrono>

CommandPromptEngine::CommandPromptEngine()
	: m_screenWidth(0), m_screenHeight(0), m_isRunning(false),
	  m_consoleOutHandle(INVALID_HANDLE_VALUE), m_consoleRectangle { 0, 0 }
{

}

CommandPromptEngine::~CommandPromptEngine()
{

}

bool CommandPromptEngine::setSize(const int width, const int height, const int fontWidth, const int fontHeight)
{
	// Check if the provided size is correct
	if (width <= 0 || height <= 0 || fontWidth <= 0 || fontHeight <= 0)
	{
		return false;
	}

	m_screenWidth = width;
	m_screenHeight = height;

	// Get the console output handle
	m_consoleOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (m_consoleOutHandle == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	// Set the console size to 1x1 initially
	m_consoleRectangle = { 0, 0, 1, 1 };
	if (!SetConsoleWindowInfo(m_consoleOutHandle, true, &m_consoleRectangle))
	{
		return false;
	}

	// Set the console screen buffer size
	COORD screenBufferSize = { short(m_screenWidth), short(m_screenHeight) };
	if (!SetConsoleScreenBufferSize(m_consoleOutHandle, screenBufferSize))
	{
		return false;
	}

	// Set the active console screen buffer
	if (!SetConsoleActiveScreenBuffer(m_consoleOutHandle))
	{
		return false;
	}

	// Set the font
	CONSOLE_FONT_INFOEX fontInfo;
	fontInfo.cbSize = sizeof(fontInfo);
	fontInfo.nFont = 0;
	fontInfo.dwFontSize.X = fontWidth;
	fontInfo.dwFontSize.Y = fontHeight;
	fontInfo.FontFamily = FF_DONTCARE;
	fontInfo.FontWeight = FW_NORMAL;
	wcscpy_s(fontInfo.FaceName, L"Consolas");

	if (!SetCurrentConsoleFontEx(m_consoleOutHandle, false, &fontInfo))
	{
		return false;
	}

	// Set the actual console size
	m_consoleRectangle = { 0, 0, short(m_screenWidth) - 1, short(m_screenHeight) - 1 };
	if (!SetConsoleWindowInfo(m_consoleOutHandle, true, &m_consoleRectangle))
	{
		return false;
	}

	m_graphics.setBufferSize(m_screenWidth, m_screenHeight);

	return true;
}

void CommandPromptEngine::start()
{
	// Call user startup method
	m_isRunning = userStartup();

	auto previousTime = std::chrono::system_clock::now();
	auto currentTime = std::chrono::system_clock::now();

	while (m_isRunning)
	{
		// Calculate delta time
		previousTime = currentTime;
		currentTime = std::chrono::system_clock::now();

		auto timeDifference = currentTime - previousTime;
		double deltaTime = timeDifference.count();

		// Get keyboard input
		m_keyboard.getUserInput();

		// Clear the buffer
		for (int x = 0; x < m_screenWidth; ++x)
		{
			for (int y = 0; y < m_screenHeight; ++y)
			{
				fill(x, y, 0x00);
			}
		}

		// Call user update method
		m_isRunning = userUpdate(deltaTime);

		// Draw
		WriteConsoleOutput(m_consoleOutHandle, m_graphics.getBuffer(), m_graphics.getBufferSize(), { 0, 0 }, &m_consoleRectangle);
	}
}

bool CommandPromptEngine::keyPressed(const int keyCode) const
{
	return m_keyboard.wasPressed(keyCode);
}

bool CommandPromptEngine::keyReleased(const int keyCode) const
{
	return m_keyboard.wasReleased(keyCode);
}

bool CommandPromptEngine::keyHeld(const int keyCode) const
{
	return m_keyboard.isHeld(keyCode);
}

void CommandPromptEngine::fill(const int x, const int y, const int color)
{
	m_graphics.fillColor(x, y, color);
}
