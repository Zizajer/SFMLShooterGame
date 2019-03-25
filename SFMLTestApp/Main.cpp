#include <sfml\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <iostream>
#include <cstdlib>
#include <map>
#include <ctime>
#include <math.h>
#include <vector>

using namespace sf;
using namespace std;

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

class Enemy {
public:
	RectangleShape shape;
	Enemy() {
		this->shape.setFillColor(Color::White);
		this->shape.setSize(Vector2f(50.f, 50.f));
	}
};

int main() {
	srand(time(NULL));
	float windowWidth = 800.f;
	float windowHeigth = 600.f;
	float playerRadius = 25.f;

	Vector2f playerCenter;
	Vector2f mousePositionWindow;
	Vector2f aimDirection;
	Vector2f aimDirectionNormalise;

	float spawnMaxTime = 80;
	float spawnTime = spawnMaxTime;

	RenderWindow window(sf::VideoMode(windowWidth, windowHeigth), "Shooter Game");
	window.setFramerateLimit(60);

	CircleShape player(playerRadius);
	player.setPosition((windowWidth/2) - playerRadius, (windowHeigth / 2) - playerRadius);
	player.setFillColor(Color::Magenta);

	Bullet bullet;
	vector<Bullet> bullets;

	Enemy enemy;
	vector<Enemy> enemies;


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
			{
				bullets.erase(bullets.begin() + i);
			}
			else {
				for(size_t j = 0 ; j < enemies.size(); j++)
					if (bullets[i].shape.getGlobalBounds().intersects(enemies[j].shape.getGlobalBounds())) {
						bullets.erase(bullets.begin() + i);
						enemies.erase(enemies.begin() + j);
					}
			}
		}

		float xCoordinateDifference = (((rand() % 400) - 200));
		float yCoordinateDifference = (((rand() % 400) - 200));

		if (50 > xCoordinateDifference < -50)
			xCoordinateDifference = 50;

		if (50 > yCoordinateDifference < -50)
			yCoordinateDifference = 50;

		if (spawnTime >= spawnMaxTime) {
			Enemy enemy;
			enemy.shape.setPosition(playerCenter.x + xCoordinateDifference, playerCenter.y + yCoordinateDifference);
			enemies.push_back(enemy);
			spawnTime = 0;
		}
		else {
			spawnTime++;
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

		for (size_t i = 0; i < enemies.size(); i++) {
			window.draw(enemies[i].shape);
		}

		window.display();

		
	}

	return 0;
}