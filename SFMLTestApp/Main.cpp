#include <sfml\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <math.h>

using namespace sf;

class Bullet {
public:
	CircleShape shape;
	Vector2f currVelocity;
	float maxSpeed;

	Bullet(float radius = 5.f)
		: currVelocity(0.f, 0.f), maxSpeed(15.f)
	{
		this->shape.setRadius(radius);
		this->shape.setFillColor(Color::Red);
	}
};

int main() {
	float windowWidth = 800.f;
	float windowHeigth = 600.f;
	float playerRadius = 25.f;

	Vector2f playerCenter;
	Vector2f mousePositionWindow;
	Vector2f aimDirection;
	Vector2f aimDirectionNormalise;

	RenderWindow window(sf::VideoMode(windowWidth, windowHeigth), "Shooter Game");
	window.setFramerateLimit(60);

	CircleShape player(playerRadius);
	player.setPosition((windowWidth/2) - playerRadius, (windowHeigth / 2) - playerRadius);
	player.setFillColor(Color::Magenta);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		playerCenter = Vector2f(player.getPosition().x + player.getRadius(), player.getPosition().y + player.getRadius());
		

		if (Keyboard::isKeyPressed(Keyboard::Left))
			player.move(-10.f, 0.f);
		if (Keyboard::isKeyPressed(Keyboard::Right))
			player.move(10.f, 0.f);
		if (Keyboard::isKeyPressed(Keyboard::Down))
			player.move(0.f, 10.f);
		if (Keyboard::isKeyPressed(Keyboard::Up))
			player.move(0.f, -10.f);



		window.clear();
		window.draw(player);
		window.display();
	}

	return 0;
}