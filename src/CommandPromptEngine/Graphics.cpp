#include "Graphics.hpp"

Graphics::Graphics()
	: m_consoleBuffer(nullptr)
{

}

Graphics::~Graphics()
{
	// Memory cleanup
	if (m_consoleBuffer)
	{
		delete[] m_consoleBuffer;
	}
}

bool Graphics::setBufferSize(const int width, const int height)
{
	if (width <= 0 || height <= 0)
	{
		return false;
	}

	m_bufferWidth = width;
	m_bufferHeight = height;

	// Allocate the buffer memory
	m_consoleBuffer = new CHAR_INFO[m_bufferWidth * m_bufferHeight]();

	return true;
}

const CHAR_INFO* Graphics::getBuffer() const
{
	return m_consoleBuffer;
}

COORD Graphics::getBufferSize() const
{
	return { short(m_bufferWidth), short(m_bufferHeight) };
}
