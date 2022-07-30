#include "Platform/Platform.hpp"
#include "Point.h"
#include <chrono>
#include <iostream>
#include <random>
#include <thread>

#define window_x 1200.0f // set SFML window size
#define window_y 1200.0f
#define renderScaling 5.0
#define num_points 4
#define BALLBOUNCE

double render_x { 0.0f };
double render_y { 0.0f };

// declaration
void updateSfmlShape(sf::CircleShape& shape, Point& point);
double randomDouble(double lower_bound, double upper_bound);

void updateSfmlShape(sf::CircleShape& shape, Point& point)
{
	double render_x {};
	double render_y {};
	render_x = point.getX() * renderScaling - shape.getRadius();
	render_y = -point.getY() * renderScaling + window_y - shape.getRadius();
	shape.setPosition(render_x, render_y);
}

int main()
{
	util::Platform platform;

#if defined(_DEBUG)
	std::cout << "Hello World!" << std::endl;
#endif

	// Create SFML window
	sf::RenderWindow window;															   // in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle()); // Use the screenScalingFactor
	window.create(sf::VideoMode(window_x * screenScalingFactor, window_y * screenScalingFactor), "SFML works!");
	platform.setIcon(window.getSystemHandle());

	// create collection of point and shape objects and give them random mass, position, and radii
	Point* points = new Point[num_points];
	sf::CircleShape* shapes = new sf::CircleShape[num_points];
	int i {};

	for (i = 0; i < num_points; i++)

	{
		double rand_radius = (rand() / (double)RAND_MAX) * (20 - 10) + 10;
		double rand_x = (rand() / (double)RAND_MAX) * (0.8 - 0.2) + 0.2;
		double rand_y = (rand() / (double)RAND_MAX) * (0.8 - 0.2) + 0.2;
		double rand_mass = (rand() / (double)RAND_MAX) * (15 - 5) + 5;
		points[i].setMass(rand_mass);
		points[i].setRadius(rand_radius / renderScaling);
		points[i].setCOR(0.8);
		points[i].setWindResistance(0.5);
		points[i].setPosition(rand_x * window_x / renderScaling, rand_y * window_y / renderScaling);
		shapes[i].setFillColor(sf::Color::White);
		shapes[i].setRadius(rand_radius);
		points[i].linkWindowAndCircle(window, shapes[i], true);
		points[i].setGravity(9.8);
	}

	// Create SFML event
	sf::Event event;

	while ((window.isOpen()) && (points[0].getT() < 100))
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

#ifdef BALLBOUNCE

		window.clear();
		for (i = 0; i < num_points; i++)
		{
			points[i].applySwirlingForce().checkCollision();
			//points[i].applyForce(0.0, 0.0, false).checkCollision();
			updateSfmlShape(shapes[i], points[i]);
			window.draw(shapes[i]);
		}
		window.display();

		// let the physics enginer set this time
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
#endif
	}
	window.close();

	return 0;
}

/*
How I want this program to flow
- SFML window is created with a specific window size
- I choose the number of circles to simulate, with RNG mass and radius
- SFML shapes are generated for each circle, and is linked to each respective point instance
- Each point instance is linked to the SFML window
-
*/