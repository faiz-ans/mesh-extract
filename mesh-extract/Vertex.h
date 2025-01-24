#pragma once
#ifndef VERTEX_H
#define VERTEX_H

class Vertex
{
public:
	void setU(double);
	void setV(double);
	void setX(double);
	void setY(double);
	void setZ(double);
	void setCoords(double, double, double);
	void setUVs(double, double);
	double getU();
	double getV();
	double getX();
	double getY();
	double getZ();
	Vertex();
	Vertex(double, double, double);
	~Vertex();

private:
	double u, v, x, y, z;
};

#endif // VERTEX_H 