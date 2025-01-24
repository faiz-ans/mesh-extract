#pragma once
#ifndef FACE_H
#define FACE_H
#include <vector>
#include "Vertex.h"

class Face
{
public:
	void setVertices(std::vector<Vertex>);
	void setNormal(Vertex);
	void setNormal(double, double, double);
	void addVertex(Vertex);
	void addVertex(double, double, double);
	std::vector<Vertex> getVertices();
	Vertex getVertex(int);
	Vertex getNormal();
	Face();
	Face(std::vector<Vertex>);
	~Face();

private:
	std::vector<Vertex> vertices;
	Vertex normal;
};

#endif // FACE_H 