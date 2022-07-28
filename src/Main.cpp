#include "Platform/Platform.hpp"
#include "Point.h"
#include <chrono>
#include <iostream>
#include <thread>
#define window_x 2000.0f
#define window_y 1000.0f
#define radius 20.0f
#define renderScaling 20.0
#define BALLBOUNCE

double render_x { 0.0f };
double render_y { 0.0f };

int main()
{
	util::Platform platform;

#if defined(_DEBUG)
	std::cout << "Hello World!" << std::endl;
#endif

	sf::RenderWindow window;
	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());
	// Use the screenScalingFactor
	window.create(sf::VideoMode(window_x * screenScalingFactor, window_y * screenScalingFactor), "SFML works!");
	platform.setIcon(window.getSystemHandle());

	sf::CircleShape shape(radius);
	shape.setFillColor(sf::Color::White);

	sf::Event event;

	Point ball { 30.0, 30.0, 10.0, 15.0, 0.0, 0.0, 1.0 };
	ball.setGravity(9.8);
	ball.setWindResistance(0.0);
	ball.setCOR(0.98);
	ball.setDt(0.01);
	ball.setRadius(radius / renderScaling);
	ball.setWalls((window_x / renderScaling), 0.0, (window_y / renderScaling), 0.0);
	ball.printWallParam();
	render_x = ball.getX() * renderScaling - radius;
	render_y = -ball.getY() * renderScaling + window_y - radius;
	// use window to set ball radius, and window frame limits

	shape.setPosition(render_x, render_y);

	std::cout << window.getSize().x << "\n";

	while ((window.isOpen()) && (ball.getT() < 100))
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

#ifdef BALLBOUNCE

		ball.applyForce(0.0, 0.0, true).checkCollision();
		render_x = ball.getX() * renderScaling - radius;
		render_y = -ball.getY() * renderScaling + window_y - radius;
		shape.setPosition(render_x, render_y);

		window.clear();
		window.draw(shape);
		window.display();

		std::this_thread::sleep_for(std::chrono::milliseconds(1));

#endif
	}
	window.close();

	return 0;
}
