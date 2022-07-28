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

	// option call to print
	if (isPrint)
	{
		print();
	}
	return *this;
}

//check for collision with containment box
// TODO make more robust
void Point::checkCollision()
{
	if ((m_x + m_radius) >= m_x_ulim)
	{
		//bounce off right wall
		m_xd = -m_xd * m_bounce;
		std::cout << "bounced off right wall!\n";
	}
	else if ((m_x - m_radius) <= m_x_llim)
	{
		// bounce off left wall
		m_xd = -m_xd * m_bounce;
		std::cout << "bounced off left wall!\n";
	}
	else if ((m_y + m_radius) >= m_y_ulim)
	{
		// bounce off of ceiling
		m_yd = -m_yd * m_bounce;
		std::cout << "bounced off ceiling!\n";
	}
	else if ((m_y - m_radius) <= m_y_llim)
	{
		// bounce off of floor
		m_yd = -m_yd * m_bounce;
		std::cout << "bounced off floor!\n";
	}
}