#include <sfml\Graphics.hpp>

using namespace sf;

int main() {
	float width = 800;
	float heigth = 600;
	float radius = 50;
	RenderWindow window(sf::VideoMode(width, heigth), "Test nr 1 Circle");
	CircleShape shape(radius);
	shape.setPosition((width/2) - radius, (heigth / 2) - radius);
	shape.setFillColor(Color::Green);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}