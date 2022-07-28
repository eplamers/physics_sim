//
// Created by erik on 7/25/22.
//
// TODO update this class to work with pointers
// TODO update this class to work with const reference pointers for getter functions
// TODO update this class to recognize collisions with other instances of the same class
// TODO update this class to accept an SFML window so that it can place the objects inside it
// TODO organize all the point state info into a compound data type or whatever seems proper

#ifndef HELLOWORLD_POINT_H
#define HELLOWORLD_POINT_H

#include <iostream>

class Point
{
private:
	static inline int s_id_generator { 1 }; // point object ID generator
	int m_ID {};							// point object ID
	double m_x { 0.0 };
	double m_y { 0.0 };
	double m_xd { 0.0 };
	double m_yd { 0.0 };
	double m_fx { 0.0 };
	double m_fy { 0.0 };
	double m_mass { 1.0 };
	double m_dt { 0.05 };
	double m_g { 0.0 }; // gravity defaulted to 0.0
	double m_b { 0.0 }; // air resistance defaulted to 0.0
	double m_t { 0.0 }; // time
	double m_radius { 0.5 };
	double m_x_ulim { 20 };
	double m_x_llim { -20 };
	double m_y_ulim { 20 };
	double m_y_llim { -20 };
	double m_bounce { 0.8 };

public:
	//constructor declaration
	Point(double x, double y, double xd, double yd, double fx, double fy, double mass);
	Point();

	//destructor declaration

	//setters & getters & other trivial functions
	void setDt(double dt)
	{
		m_dt = dt;
	};
	void setMass(double mass)
	{
		m_mass = mass;
	};
	void setGravity(double g)
	{
		m_g = g;
	};
	void setWindResistance(double b)
	{
		m_b = b;
	};
	void setRadius(double radius)
	{
		m_radius = radius;
	}
	void setWalls(double x_ulim, double x_llim, double y_ulim, double y_llim)
	{
		m_x_ulim = x_ulim;
		m_x_llim = x_llim;
		m_y_ulim = y_ulim;
		m_y_llim = y_llim;
	}
	void setCOR(double cor)
	{
		//TODO make sure in range 0-1
		m_bounce = cor;
	}

	const double& getX()
	{
		return m_x;
	}
	const double& getY()
	{
		return m_y;
	}
	const double& getT()
	{
		return m_t;
	}

	void print();
	void printWallParam();

	//non-trivial member functions
	Point& applyForce(double fx, double fy, bool print); // this allows me to return a pointer to the class instance for chaining member function calls
	void setState(double x, double y, double xd, double yd, double fx, double fy, double mass);
	void checkCollision();
	//
};

#endif //HELLOWORLD_POINT_H
