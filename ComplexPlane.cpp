#include "ComplexPlane.h"

using namespace sf;
using namespace std;

ComplexPlane::ComplexPlane(int _pixelWidth, int _pixelHeight) 
{
	pixelWidth = _pixelWidth; 
	pixelHeight = _pixelHeight;
	m_aspectRatio = _pixelHeight / _pixelWidth;
	m_plane_center = { 0, 0 };
	m_plane_size = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
	m_zoomCount = 0;
	m_state = State::CALCULATING;
	m_vArray.setPrimitiveType(Points);
	m_vArray.resize(_pixelWidth * _pixelHeight);
}


void ComplexPlane::zoomIn()
{

}


void ComplexPlane::zoomOut()
{

}


void ComplexPlane::setCenter(Vector2i mousePixel)
{

}


void ComplexPlane::setMouse(Vector2i mousePixel)
{

}


void ComplexPlane::loadText(Text& text)
{

}


void ComplexPlane::updateRender()
{
	if (m_state == CALCULATING)
	{
		// j represents x, i represnts y
		for (int i = 0; i < pixelHeight; i++)
		{
			for (int j = 0; j < pixelHeight; j++)
			{
				m_vArray[j + i * pixelWidth].position = { (float)j,(float)i };

			}
		}
	}

}
