#include "ComplexPlane.h"
#include <sstream>
#include <cmath>
#include <complex>
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
	m_pixel_size.x = _pixelWidth;
	m_pixel_size.y = _pixelHeight;
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
				sf::Vector2f crispy = ComplexPlane::mapPixelToCoords(temp);
				size_t bruh = countIterations(crispy);
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
	double re = coord.x;
	double im = coord.y;
	complex<double> c (re, im);
	complex<double> z(0, 0);
	while (iterations < MAX_ITER && abs(z) < 2) 
	{
		z = z*z + c;
		// cout << z_n << " " << iterations << " " << c <<  endl;
		//if (abs(z) > 2) { return iterations; break; }
		iterations++;
	}
	return iterations;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
		
		//random color for each row
		if (count == MAX_ITER) {
			r = 0;
			g = 0;
			b = 0;
		}
		else if (count > 50)
		{
			r = 170;
			g = 50;
			b = 255;
		}
		else if (count > 40)
		{
			r = 0;
			g = 150;
			b = 200;
		}
		else if (count > 30)
		{
			r = 14;
			g = 255;
			b = 57;
		}
		else if (count > 20)
		{
			r = 14;
			g = 172;
			b = 180;
		}
		else if (count > 10)
		{
			r = 255;
			g = 100;
			b = 150;
		}
}
Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
	Vector2f MouseLocation;
	MouseLocation.x = (mousePixel.x - 0) / (m_pixel_size.x - 0) * (m_plane_size.x) + (m_plane_center.x-m_plane_size.x/2.0);
	MouseLocation.y = (mousePixel.y - m_pixel_size.y) / (0 - m_pixel_size.y) * (m_plane_size.y) + (m_plane_center.y - m_plane_size.y/2.0);
	return MouseLocation;
}
