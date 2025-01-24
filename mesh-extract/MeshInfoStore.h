#pragma once
#ifndef MESHINFOSTORE_H
#define MESHINFOSTORE_H
#include <string>
#include <vector>
#include "Vertex.h"
#include "Face.h"

class MeshInfoStore
{
public:
	void addVertex(Vertex);
	void addVertex(double, double, double);
	void addVertex(double, double, double, double, double);
	void addFace(Face);
	void addFace(std::vector<Vertex>);
	void addFace(std::vector<Vertex>, Vertex);
	void addFace(std::vector<Vertex>, double, double, double);
	void setVertices(std::vector<Vertex>);
	void setFaces(std::vector<Face>);
	Vertex getVertex(int);
	Face getFace(int);
	std::vector<Vertex> getVertices();
	std::vector<Face> getFaces();
	std::string displayVertices();
	std::string displayFaces();
	std::string displayNormals();
	std::string displayUVs();
	MeshInfoStore();
	~MeshInfoStore();
	//void addFace(std::vector<double>);

private:
	std::vector<Vertex> vertexStore;
	std::vector<Face> faceStore;
};

#endif // MESHINFOSTORE_H