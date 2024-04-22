#ifndef COMPLEXPLANE_H
#define COMPLEXPLANE_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include<vector>
#include<complex>

using namespace std;

//global constants
const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;


enum State {
	CALCULATING,
	DISPLAYING
};
class ComplexPlane : public Drawable
{
public:
	ComplexPlane(int _pixelWidth, int _pixelHeight);									  //also looks complete?, nice
	void draw(RenderTarget& target, RenderStates states) const { target.draw(m_vArray); } //complete
	void updateRender(); //NOT COMPLETE
	void zoomIn(); //complete
	void zoomOut(); //complete
	void setCenter(Vector2i mousePixel);//complete
	void setMouseLocation(Vector2i mousePixel); //complete
	void loadText(Text& text);
	size_t countIterations(Vector2f coord);
	void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);
	Vector2f mapPixelToCoords(Vector2i mousePixel);
private:
	VertexArray m_vArray;
	int pixelWidth;
	int pixelHeight;
	double m_aspectRatio;
	Vector2i m_plane_center;
	Vector2i m_plane_size;
	Vector2i m_mouse_location;
	int m_zoomCount;
	State m_state;

};




#endif
