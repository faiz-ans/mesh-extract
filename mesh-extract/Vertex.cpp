#include "Vertex.h"

void Vertex::setU(double a)
{
	u = a;
}

void Vertex::setV(double a)
{
	v = a;
}

void Vertex::setX(double a)
{
	x = a;
}

void Vertex::setY(double b)
{
	y = b;
}

void Vertex::setZ(double c)
{
	z = c;
}

void Vertex::setCoords(double a, double b, double c)
{
	setX(a);
	setY(b);
	setZ(c);
}

void Vertex::setUVs(double a, double b)
{
	setU(a);
	setV(b);
}

double Vertex::getU()
{
	return u;
}

double Vertex::getV()
{
	return v;
}

double Vertex::getX()
{
	return x;
}

double Vertex::getY()
{
	return y;
}

double Vertex::getZ()
{
	return z;
}

Vertex::Vertex() : u(0), v(0), x(0), y(0), z(0)
{
}

Vertex::Vertex(double a, double b, double c) : u(0), v(0)
{
	setCoords(a, b, c);
}

Vertex::~Vertex()
{
}