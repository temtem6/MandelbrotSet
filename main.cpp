#include "ComplexPlane.h"

using namespace std;
using namespace sf;
int main()
{
	int pixelWidth = sf::VideoMode::getDesktopMode().width;
	int pixelHeight = sf::VideoMode::getDesktopMode().height;
	VideoMode vm(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	RenderWindow window(vm, "Mandelbrot Set", Style::Default);

	View view;
	view.setSize(pixelWidth, pixelHeight);
	view.setCenter(pixelWidth / 2, pixelHeight / 2);
	window.setView(view);

	ComplexPlane complex(pixelWidth, pixelHeight);
	Text text;
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "Unable to upload file" << std::endl;
	}
	text.setFont(font);
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::Yellow);
	text.setStyle(sf::Text::Bold);
	
	while (window.isOpen())
	{

		/*
		****************************************
		Handle the players input
		****************************************
		*/

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					Vector2i mousepixel = { event.mouseButton.x, event.mouseButton.y };
					complex.zoomIn();
					complex.setCenter(mousepixel);
				}
				else 
				{
					Vector2i mousepixel = { event.mouseButton.x, event.mouseButton.y };
					complex.zoomOut();
					complex.setCenter(mousepixel);
				}
			}
			/*else if (event.MouseMoved) {
				
				complex.setCenter();
				{{{{{	FINISH THIS FUNCTION }}}}}
			}*/
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		/*
		****************************************
		Update the scene
		****************************************
		*/
		complex.updateRender();

		complex.loadText(text);
		/*
		****************************************
		Draw the scene
		****************************************
		*/

		window.clear();
		window.draw(complex);
		window.draw(text);
		window.display();
	}

	return 0;
}

