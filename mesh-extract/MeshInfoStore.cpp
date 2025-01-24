#include "MeshInfoStore.h"
#include <sstream>

void MeshInfoStore::addVertex(Vertex a)
{
	vertexStore.push_back(a);
}

void MeshInfoStore::addVertex(double x, double y, double z)
{
	vertexStore.push_back(Vertex(x, y, z));
}

void MeshInfoStore::addVertex(double u, double v , double x , double y, double z)
{
	Vertex newVertex(x, y, z);
	newVertex.setUVs(u, v);
	vertexStore.push_back(newVertex);
}

void MeshInfoStore::addFace(Face a)
{
	faceStore.push_back(a);
}

void MeshInfoStore::addFace(std::vector<Vertex> a)
{
	faceStore.push_back(Face(a));
}

void MeshInfoStore::addFace(std::vector<Vertex> a, Vertex b)
{
	Face newFace(a);
	newFace.setNormal(b);
	faceStore.push_back(newFace);
}

void MeshInfoStore::addFace(std::vector<Vertex> a, double b, double c, double d)
{
	Face newFace(a);
	newFace.setNormal(b, c, d);
	faceStore.push_back(newFace);
}

void MeshInfoStore::setVertices(std::vector<Vertex> a)
{
	vertexStore = a;
}

void MeshInfoStore::setFaces(std::vector<Face> a)
{
	faceStore = a;
}

Vertex MeshInfoStore::getVertex(int a)
{
	return vertexStore[a];
}

Face MeshInfoStore::getFace(int a)
{
	return faceStore[a];
}

std::vector<Vertex> MeshInfoStore::getVertices()
{
	return vertexStore;
}

std::vector<Face> MeshInfoStore::getFaces()
{
	return faceStore;
}

std::string MeshInfoStore::displayVertices()
{
	std::string output = "";

	for (unsigned int i = 0; i < vertexStore.size(); i++)
	{

		std::ostringstream strs;
		strs << "Vertex " << i << ": (" << vertexStore[i].getX() << ", " << vertexStore[i].getY() << ", " << vertexStore[i].getZ() << ")\n";
		output += strs.str();

	}

	return output;
}

std::string MeshInfoStore::displayFaces()
{
	std::string output = "";

	for (unsigned int i = 0; i < faceStore.size(); i++)
	{

		std::ostringstream strs;
		strs << " Face " << i << ": ";
		
		for (unsigned int j = 0; j < getFace(i).getVertices().size(); j++)
		{
			strs << "(" << faceStore[i].getVertex(j).getX() << ", " << faceStore[i].getVertex(j).getY() << ", " << faceStore[i].getVertex(j).getZ() << ") ";
		}

		strs << "\n";
		output += strs.str();

	}

	return output;
}

std::string MeshInfoStore::displayNormals()
{
	std::string output = "";

	for (unsigned int i = 0; i < faceStore.size(); i++)
	{

		std::ostringstream strs;
		strs << " Face " << i << ": (" << faceStore[i].getNormal().getX() << ", " << faceStore[i].getNormal().getY() << ", " << faceStore[i].getNormal().getZ() << ")\n";
		output += strs.str();

	}

	return output;
}

std::string MeshInfoStore::displayUVs()
{
	std::string output = "";

	for (unsigned int i = 0; i < vertexStore.size(); i++)
	{

		std::ostringstream strs;
		strs << "Vertex " << i << ": (" << vertexStore[i].getU() << ", " << vertexStore[i].getV() << ")\n";
		output += strs.str();

	}

	return output;
}

MeshInfoStore::MeshInfoStore()
{
}

MeshInfoStore::~MeshInfoStore()
{
}