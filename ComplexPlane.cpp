#include "ComplexPlane.h"
#include <sstream>
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
	m_zoomCount++;
	float local_x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float local_y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_plane_size = { local_x, local_y };
	m_state = State::CALCULATING;
}


void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	float local_x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float local_y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_plane_size = { local_x, local_y };
	m_state = State::CALCULATING;
}


void ComplexPlane::setCenter(Vector2i mousePixel)
{
	m_plane_center = { static_cast<int>(mapPixelToCoords(mousePixel).x), static_cast<int>(mapPixelToCoords(mousePixel).y) };
	m_state = State::CALCULATING;
}


void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
	m_mouseLocation = { static_cast<int>(mapPixelToCoords(mousePixel).x), static_cast<int>(mapPixelToCoords(mousePixel).y) };
}


void ComplexPlane::loadText(Text& text) //not sure about the "Cursor should update live as the user moves the mouse.  Center should only update after they click." i think that might just update itself as long as this gets called in main at the right time?
{
	stringstream ss;
	ss << "Mandelbrot Set" << endl << "Center: (" << m_plane_center.x << "," << m_plane_center.y << ")" << endl
		<< "Cursor: " << m_mouseLocation.x << "," << m_mouseLocation.y << ")" << endl << "Left-click to Zoom in" << endl << "Right-click to Zoom out";
	cout << ss.str();
}
void ComplexPlane::updateRender()
{
	if (m_state == State::CALCULATING)
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

size_t ComplexPlane::countIterations(Vector2f coord)
{
	
}
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
		
	for (int i = 0; i < pixelHeight; i++)
	{
		//random color for each row
		Uint8 r, g, b;
		r = rand() % 256;
		g = rand() % 256;
		b = rand() % 256;
		for (int j = 0; j < pixelWidth; j++)
		{
			m_vArray[i * pixelWidth + j].position = { (float)j, (float)i };
			m_vArray[i * pixelWidth + j].color = { r,g,b };
		}
	}
}
Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
	Vector2f MouseLocation;
	MouseLocation.x = (mousePixel.x - 0) / (m_plane_size.x - 0) * (m_plane_size.x) + (m_plane_center.x-m_plane_size.x/2);
	MouseLocation.y = (mousePixel.y - m_plane_size.y) / (0 - m_plane_size.y) * (m_plane_size.y) + (m_plane_center.y - m_plane_size.y/2);
	return MouseLocation;
}
