#include "ComplexPlane.h"
#include <sstream>
#include <cmath>
using namespace sf;
using namespace std;

ComplexPlane::ComplexPlane(int _pixelWidth, int _pixelHeight) 
{
	pixelWidth = _pixelWidth; 
	pixelHeight = _pixelHeight;
	m_aspectRatio = pixelHeight / pixelWidth;
	m_plane_center = { 0, 0 };
	m_plane_size = { (BASE_WIDTH), (BASE_HEIGHT * m_aspectRatio)};
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
	m_plane_center = { (mapPixelToCoords(mousePixel).x), (mapPixelToCoords(mousePixel).y) };
	m_state = State::CALCULATING;
}


void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
	m_mouseLocation = { mapPixelToCoords(mousePixel).x, mapPixelToCoords(mousePixel).y };
}


void ComplexPlane::loadText(Text& text) //not sure about the "Cursor should update live as the user moves the mouse.  Center should only update after they click." i think that might just update itself as long as this gets called in main at the right time?
{
	stringstream ss;
	ss << "Mandelbrot Set" << endl << "Center: (" << m_plane_center.x << "," << m_plane_center.y << ")" << endl;
	ss << "Cursor: (" << m_mouseLocation.x << "," << m_mouseLocation.y << ")" << endl;
	ss	<< "Left-click to Zoom in" << endl << "Right-click to Zoom out";

	text.setString(ss.str());
}
void ComplexPlane::updateRender()
{
	if (m_state == State::CALCULATING)
	{
		// j represents x, i represnts y
		for (int i = 0; i < pixelHeight; i++)
		{
			for (int j = 0; j < pixelWidth; j++)
			{
				Vector2i temp = { j, i };
				m_vArray[j + i * pixelWidth].position = { (float)j,(float)i };
				m_mouseLocation = ComplexPlane::mapPixelToCoords(temp);
				size_t bruh = countIterations(m_mouseLocation);
				Uint8 r;
				Uint8 g;
				Uint8 b;
				iterationsToRGB(bruh, r, g, b);
				m_vArray[j + i * pixelWidth].color = { r, g, b };
			}
		}
	}
	m_state = State::DISPLAYING;

}

size_t ComplexPlane::countIterations(sf::Vector2f coord)
{
	int iterations = 0;
	double c = sqrt(pow(coord.x, 2) + pow(coord.y, 2));
	double z_n = 0;
	while (iterations < 64) 
	{
		z_n = z_n*z_n + c;
		// cout << z_n << " " << iterations << " " << c <<  endl;
		if (z_n > 2) { return iterations; break; }
		iterations++;
	}
	return 64;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
		
		//random color for each row
		if (count > 62) {
			r = 0;
			g = 0;
			b = 0;
		}
		else if (count > 55)
		{
			r = 50;
			g = 25;
			b = 255;
		}
		else if (count > 45)
		{
			r = 0;
			g = 150;
			b = 200;
		}
		else if (count > 35)
		{
			r = 14;
			g = 255;
			b = 57;
		}
		else if (count > 25)
		{
			r = 14;
			g = 172;
			b = 180;
		}
		else if (count > 15)
		{
			r = 250;
			b = 25;
			b = 0;
		}
}
Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
	//Vector2f MouseLocation;
	m_mouseLocation.x = (mousePixel.x - 0) / (pixelWidth - 0) * (m_plane_size.x) + (m_plane_center.x-m_plane_size.x/2.0);
	m_mouseLocation.y = (mousePixel.y - pixelHeight) / (0 - pixelHeight) * (m_plane_size.y) + (m_plane_center.y - m_plane_size.y/2.0);
	return m_mouseLocation;
}
