#include <maya/MSimple.h>
#include <maya/MGlobal.h>
#include <maya/MItSelectionList.h>
#include <maya/MDagPath.h>
#include <maya/MItMeshVertex.h>
#include <maya/MItMeshPolygon.h>
#include <maya/MFnMesh.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MPointArray.h>
#include <math.h>

#include "MeshInfoStore.h"

DeclareSimpleCommand(meshInfoStore, "Faiz Ansari", "1.0");

// ---Declare Methods---
MSelectionList getMeshesInsideRadius(MPoint, MPoint, MStatus);
std::vector<MeshInfoStore> storeMeshData(MSelectionList, MStatus);
void displayMeshData(MeshInfoStore);
void generateMeshFromStore(MeshInfoStore, MStatus);
void polyReduceMesh(int);

// ---Main---
MStatus meshInfoStore::doIt(const MArgList& args)
{
	MStatus stat = MS::kSuccess;

	//Set the Center and Radius of mesh selection area
	MPoint selectionCenter(0.0, 0.0, 0.0, 1.0), selectionRadius(5.0, 5.0, 5.0, 1.0);

	// Select all meshes inside the selection area
	MSelectionList meshList = getMeshesInsideRadius(selectionCenter, selectionRadius, stat);

	// Store the data of each selected mesh in a vector
	std::vector<MeshInfoStore> meshDataStore = storeMeshData(meshList, stat);
	
	// Iterate over vector of stored mesh data
	for (unsigned int i = 0; i < meshDataStore.size(); i++) {

		// Output the data of the current mesh
		MGlobal::displayInfo(("OBJECT: " + std::to_string(i) + ": \n").c_str());
		displayMeshData(meshDataStore[i]);

		// Recreate the current mesh using its stored data
		generateMeshFromStore(meshDataStore[i], stat);

		// PolyReduce the current mesh
		polyReduceMesh(i+1);
	}

	return MS::kSuccess;
}

// ---Method Definitions---

//  Selects all meshes within a spherical area with a specified center and radius
MSelectionList getMeshesInsideRadius(MPoint centerPoint, MPoint radiusPoint, MStatus stat)
{

	MSelectionList meshListAll, meshListInside;
	MDagPath dagPath;
	MObject component;
	MPoint pt;

	double polyReduceDistance = sqrt(pow((radiusPoint[0] - centerPoint[0]), 2) +
		pow((radiusPoint[1] - centerPoint[1]), 2) +
		pow((radiusPoint[2] - centerPoint[2]), 2));

	MGlobal::executeCommand("select -all;");
	MGlobal::getActiveSelectionList(meshListAll);

	MItSelectionList preIter(meshListAll);
	for (; !preIter.isDone(); preIter.next())
	{
		preIter.getDagPath(dagPath, component);
		MItMeshVertex vertIter(dagPath, component, &stat);
		if (stat == MS::kSuccess)
		{
			for (; !vertIter.isDone(); vertIter.next())
			{
				pt = vertIter.position(MSpace::kWorld);

				double distance = sqrt(pow((pt[0] - centerPoint[0]), 2) +
					pow((pt[1] - centerPoint[1]), 2) +
					pow((pt[2] - centerPoint[2]), 2));

				if (distance <= polyReduceDistance)
				{
					meshListInside.add(dagPath, component);
					break;
				}
			}
		}

	}

	return meshListInside;

}

//  Gets Vertices, Faces, Normals, and UV's of each object in a list of selected objects
//  Each object's data is stored as a separate element in a vector to keep objects distinct
std::vector<MeshInfoStore> storeMeshData(MSelectionList selection, MStatus stat)
{
	
	std::vector<MeshInfoStore> meshDataList;
	MDagPath dagPath;
	MObject component;
	MPoint pt;
	int vertCount, vertIndex, polyCount, polyIndex;

	MItSelectionList iter(selection);
	for (; !iter.isDone(); iter.next())
	{
		MeshInfoStore store;

		iter.getDagPath(dagPath, component);

		MItMeshVertex vertIter(dagPath, component, &stat);
		if (stat == MS::kSuccess)
		{
			float2 vUV;

			for (; !vertIter.isDone(); vertIter.next())
			{
				bool hasUV = false;

				pt = vertIter.position(MSpace::kWorld);
				stat = vertIter.getUV(vUV);

				if (stat)
				{
					hasUV = true;
					store.addVertex(vUV[0], vUV[1], pt.x, pt.y, pt.z);
				}
				else
				{
					store.addVertex(pt.x, pt.y, pt.z);
				}

			}
		}

		MItMeshPolygon polyIter(dagPath, component, &stat);
		if (stat == MS::kSuccess)
		{
			MVector fNormal;

			for (; !polyIter.isDone(); polyIter.next())
			{
				polyIndex = polyIter.index();
				vertCount = polyIter.polygonVertexCount();
				polyIter.getNormal(fNormal);

				Face newFace = Face();

				for (int i = 0; i < vertCount; i++)
				{
					pt = polyIter.point(i, MSpace::kWorld);
					newFace.addVertex(pt.x, pt.y, pt.z);
				}

				newFace.setNormal(fNormal.x, fNormal.y, fNormal.z);
				store.addFace(newFace);
			}
		}

		meshDataList.push_back(store);
	}

	return meshDataList;
}

// Output the stored data of a mesh
void displayMeshData(MeshInfoStore store)
{
		MGlobal::displayInfo(("Vertices:\n" + store.displayVertices()).c_str());
		MGlobal::displayInfo(("Faces:\n" + store.displayFaces()).c_str());
		MGlobal::displayInfo(("Normals:\n" + store.displayNormals()).c_str());
		MGlobal::displayInfo(("UV's:\n" + store.displayUVs()).c_str());
}
// Creates an object in the 3D space using the stored data of a mesh
void generateMeshFromStore(MeshInfoStore store, MStatus stat)
{
		MFnMesh meshFn;
		MPointArray newVerts;
		MIntArray newPolyCounts, newPolyConnects;
		MFloatArray newUVals, newVVals;
		MObject objTransform;
		MPoint pt;

		for (unsigned int i = 0; i < store.getVertices().size(); i++)
		{
			newVerts.append(store.getVertex(i).getX() + 5, store.getVertex(i).getY(), store.getVertex(i).getZ(), 1.0);
			newUVals.append(store.getVertex(i).getU());
			newVVals.append(store.getVertex(i).getV());
		}

		for (unsigned int i = 0; i < store.getFaces().size(); i++)
		{
			newPolyCounts.append(store.getFace(i).getVertices().size());

			for (unsigned int j = 0; j < newPolyCounts[i]; j++)
			{
				pt.x = store.getFace(i).getVertex(j).getX() + 5;
				pt.y = store.getFace(i).getVertex(j).getY();
				pt.z = store.getFace(i).getVertex(j).getZ();
				pt.w = 1.0;

				int index = std::distance(newVerts.begin(), std::find(newVerts.begin(), newVerts.end(), pt));
				newPolyConnects.append(index);

			}
		}

		objTransform = meshFn.create(store.getVertices().size(),
			store.getFaces().size(),
			newVerts,
			newPolyCounts,
			newPolyConnects,
			newUVals,
			newVVals,
			MObject::kNullObj,
			&stat);
		if (!stat)
			stat.perror("Unable to create mesh");

		meshFn.updateSurface();
}

// Run PolyReduce command via MEL on an object in an iterating list
void polyReduceMesh(int i)
{
	MGlobal::executeCommand(("select -r polySurface" + std::to_string(i) + ";").c_str());
	MGlobal::executeCommand("polyReduce -ver 1 -trm 2 -tct 4;");
	MGlobal::executeCommand(("rename polySurface" + std::to_string(i) + " polySurface" + std::to_string(i) + "_UEproxy;").c_str());
}
