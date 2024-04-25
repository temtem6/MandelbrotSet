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
class ComplexPlane : public sf::Drawable
{
public:
	ComplexPlane(int _pixelWidth, int _pixelHeight);									  //also looks complete?, nice
	void draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(m_vArray); } //complete
	void updateRender(); //NOT COMPLETE
	void zoomIn(); //complete
	void zoomOut(); //complete
	void setCenter(sf::Vector2i mousePixel);//complete
	void setMouseLocation(sf::Vector2i mousePixel); //complete
	void loadText(sf::Text& text);
	size_t countIterations(sf::Vector2f coord);
	void iterationsToRGB(size_t count, sf::Uint8& r, sf::Uint8& g, sf::Uint8& b);
	sf::Vector2f mapPixelToCoords(sf::Vector2i mousePixel); //complete
private:
	sf::VertexArray m_vArray;
	double pixelWidth;
	double pixelHeight;
	float m_aspectRatio;
	sf::Vector2f m_plane_center;
	sf::Vector2f m_plane_size; 
	sf::Vector2f m_mouseLocation;
	int m_zoomCount;
	State m_state;
	sf::Vector2f m_pixel_size;
};




#endif
