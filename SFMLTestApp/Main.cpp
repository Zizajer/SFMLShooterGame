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
	Color color;

	Bullet(Color color , float radius = 5.f)
		: currVelocity(0.f, 0.f), maxSpeed(15.f)
	{
		this->shape.setRadius(radius);
		this->shape.setFillColor(color);
	}
};

class Enemy {
public:
	RectangleShape shape;
	float lastShooted;
	Enemy() : lastShooted(0.f) {
		this->shape.setFillColor(Color::White);
		this->shape.setSize(Vector2f(50.f, 50.f));
	}
};


Vector2f getNormalisedVector(Vector2f vector) {
	return vector / sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

int main() {
	srand(time(NULL));
	float windowWidth = 800.f;
	float windowHeigth = 600.f;
	float playerRadius = 25.f;

	Vector2f playerCenter;
	Vector2f mousePositionWindow;
	Vector2f aimDirection;
	Vector2f enemyAimDirection;

	float spawnMaxTime = 80;
	float spawnTime = spawnMaxTime;

	RenderWindow window(sf::VideoMode(windowWidth, windowHeigth), "Shooter Game");
	window.setFramerateLimit(60);

	CircleShape player(playerRadius);
	player.setPosition((windowWidth/2) - playerRadius, (windowHeigth / 2) - playerRadius);
	player.setFillColor(Color::Magenta);

	Bullet enemyBullet(Color::White);
	Bullet playerBullet(Color::Magenta);
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

		if (Mouse::isButtonPressed(Mouse::Left)) {
			playerBullet.shape.setPosition(playerCenter);
			playerBullet.currVelocity = getNormalisedVector(aimDirection) * playerBullet.maxSpeed;
			bullets.push_back(Bullet(playerBullet));
		}

		for (size_t i = 0; i < enemies.size(); i++) {
			if (enemies[i].lastShooted == 20) {
				enemyBullet.shape.setPosition(enemies[i].shape.getPosition());
				enemyAimDirection = playerCenter - enemies[i].shape.getPosition();
				enemyBullet.currVelocity = getNormalisedVector(enemyAimDirection) * enemyBullet.maxSpeed;
				bullets.push_back(Bullet(enemyBullet));
				enemies[i].lastShooted == 0;
			}
			else
				enemies[i].lastShooted++;
		}

		for (size_t i = 0; i < bullets.size(); i++) {
			bullets[i].shape.move(bullets[i].currVelocity);

			if (bullets[i].shape.getPosition().x < 0 || bullets[i].shape.getPosition().x > window.getSize().x
				|| bullets[i].shape.getPosition().y < 0 || bullets[i].shape.getPosition().y > window.getSize().y)
			{
				bullets.erase(bullets.begin() + i);
			}
			else {
				for (size_t j = 0; j < enemies.size(); j++) {
					if (bullets[i].shape.getGlobalBounds().intersects(enemies[j].shape.getGlobalBounds())) {
						bullets.erase(bullets.begin() + i);
						enemies.erase(enemies.begin() + j);
					}
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