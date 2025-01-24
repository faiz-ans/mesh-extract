#include "Face.h"

void Face::setVertices(std::vector<Vertex> a)
{
	vertices = a;
}

void Face::addVertex(Vertex a)
{
	vertices.push_back(a);
}

void Face::addVertex(double a, double b, double c)
{
	vertices.push_back(Vertex(a, b, c));
}

std::vector<Vertex> Face::getVertices()
{
	return vertices;
}

Vertex Face::getVertex(int a)
{
	return vertices[a];
}

void Face::setNormal(Vertex a)
{
	normal = a;
}

void Face::setNormal(double a, double b, double c)
{
	normal = Vertex(a, b , c);
}

Vertex Face::getNormal()
{
	return normal;
}

Face::Face() : normal()
{
}

Face::Face(std::vector<Vertex> a) : normal()
{
	setVertices(a);
}

Face::~Face()
{
}