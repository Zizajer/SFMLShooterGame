#include <sfml\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <math.h>
#include <vector>

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

	Bullet bullet;
	std::vector<Bullet> bullets;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		playerCenter = Vector2f(player.getPosition().x + player.getRadius(), player.getPosition().y + player.getRadius());
		mousePositionWindow = Vector2f(Mouse::getPosition(window));
		aimDirection = mousePositionWindow - playerCenter;
		aimDirectionNormalise = aimDirection / sqrt(pow(aimDirection.x, 2) + pow(aimDirection.y, 2));

		if (Mouse::isButtonPressed(Mouse::Left)) {
			bullet.shape.setPosition(playerCenter);
			bullet.currVelocity = aimDirectionNormalise * bullet.maxSpeed;
			bullets.push_back(Bullet(bullet));
		}

		for (size_t i = 0; i < bullets.size(); i++) {
			bullets[i].shape.move(bullets[i].currVelocity);

			if (bullets[i].shape.getPosition().x < 0 || bullets[i].shape.getPosition().x > window.getSize().x
				|| bullets[i].shape.getPosition().y < 0 || bullets[i].shape.getPosition().y > window.getSize().y)
				bullets.erase(bullets.begin());
		}


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

		for (size_t i = 0; i < bullets.size(); i++) {
			window.draw(bullets[i].shape);
		}
		window.display();

		
	}

	return 0;
}