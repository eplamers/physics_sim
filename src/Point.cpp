//
// Created by erik on 7/25/22.
//

#include "Point.h"
#include <cmath>
#include <iomanip>
#include <iostream>

//Default Constructor
Point::Point() :
	m_ID { s_id_generator++ }
{
	print();
}

//List initialization constructor
Point::Point(double x, double y, double xd, double yd, double fx, double fy, double mass) :
	m_x { x },
	m_y { y },
	m_xd { xd },
	m_yd { yd },
	m_fx { fx },
	m_fy { fy },
	m_mass { mass }
{
	std::cout << "Point initialized at: ";
	print();
}

//print function
void Point::print()
{
	std::cout << std::fixed;
	std::cout << std::setprecision(2);
	std::cout << "x:" << m_x << ", y:" << m_y << ", x_dot:" << m_xd << ", y_dot:" << m_yd << ", fx:" << m_fx << ", fy:" << m_fy << ", time: " << m_t << "\n";
}

void Point::printWallParam()
{
	std::cout << "x:[" << m_x_llim << ", " << m_x_ulim << "], y:[" << m_y_llim << ", " << m_y_ulim << "]\n";
}

//non-trivial member functions

//apply force and update
Point& Point::applyForce(double fx = 0.0, double fy = 0.0, bool isPrint = 0.0)
{
	// update forces
	m_fx = fx - (m_xd * m_b);
	m_fy = fy - m_g - (m_yd * m_b);

	// update x_axis speed & position
	m_xd += (m_fx / m_mass) * m_dt;
	m_x += m_xd * m_dt;

	// update y_axis speed & position
	m_yd += (m_fy / m_mass) * m_dt;
	m_y += m_yd * m_dt;

	// update time
	m_t += m_dt;

	// update shape parameters if present

	// option call to print
	if (isPrint)
	{
		print();
	}
	return *this;
}

Point& Point::applySwirlingForce()
{
	double origin_x {};
	double origin_y {};
	double R {};
	double Fx {};
	double Fy {};
	double new_x {};
	double new_y {};
	origin_x = (m_x_ulim - m_x_llim) / 2;
	origin_y = (m_y_ulim - m_y_llim) / 2;
	new_x = m_x - origin_x;
	new_y = m_y - origin_y;
	R = sqrt(pow(new_x, 2) + pow(new_y, 2));
	Fx = -R * sin(atan2(new_y, new_x)) - (10 * new_x);
	Fy = R * cos(atan2(new_y, new_x)) - (10 * new_y);
	applyForce(Fx, Fy);
	std::cout << "m_x:" << m_x - origin_x << ", m_y:" << m_y << ", Fx:" << Fx << ", Fy:" << Fy << "\n";
	return *this;
}

void Point::printStr(const std::string& str)
{
	std::cout << str << "\n";
}

//check for collision with containment box
// TODO make more robust
// Reverse when collision is first detected... but don't do anything if collision continues to be detected.
// TODO pass string by reference to make more efficient?
void Point::checkCollision()
{
	bool isColliding { false };

	if ((m_x + m_radius) >= m_x_ulim)
	{
		//bounce off right wall
		if (!isColliding)
		{
			m_xd = -m_xd * m_bounce;
			printStr(m_right_collision);
			isColliding = true;
		}
	}
	else if ((m_x - m_radius) <= m_x_llim)
	{
		// bounce off left wall
		if (!isColliding)
		{
			m_xd = -m_xd * m_bounce;
			printStr(m_left_collision);
			isColliding = true;
		}
	}
	else if ((m_y + m_radius) >= m_y_ulim)
	{
		// bounce off of ceiling
		if (!isColliding)
		{
			m_yd = -m_yd * m_bounce;
			printStr(m_top_collision);
			isColliding = true;
		}
	}
	else if ((m_y - m_radius) <= m_y_llim)
	{
		// bounce off of floor
		if (!isColliding)
		{
			m_yd = -m_yd * m_bounce;
			printStr(m_bottom_collision);
			isColliding = true;
		}
	}
	else
	{
		isColliding = false;
	}
}

void Point::linkWindowAndCircle(sf::RenderWindow& window, sf::CircleShape& circle, bool verbose = 1)
{
	// update window size params
	setWalls(window.getSize().x / m_renderScaling, 0.0, window.getSize().y / m_renderScaling, 0.0);
	// update shape radius and position
	setRadius(circle.getRadius() / m_renderScaling);

	if (verbose)
	{
		printWallParam();
	}
}
