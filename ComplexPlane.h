#ifndef COMPLEXPLANE_H
#define COMPLEXPLANE_H
#include <SFML/Graphics.hpp>
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
	void zoomIn();
	void zoomOut();
	void setCenter(Vector2i mousePixel);
	void setMouseLocation(Vector2i mousePixel);
	void loadText(Text& text);
	void updateRender();
private:
	VertexArray m_vArray;
	int pixelWidth;
	int pixelHeight;
	double m_aspectRatio;
	Vector2i m_plane_center;
	Vector2i m_plane_size;
	int m_zoomCount;
	State m_state;
	Vector2f m_mouseLocation;

};




#endif
