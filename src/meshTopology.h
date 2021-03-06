/**
    Copyright (c) 2017 Ryan Porter    
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

#ifndef YANTOR3D_MESH_TOPOLOGY_H
#define YANTOR3D_MESH_TOPOLOGY_H

#include "meshData.h"
#include "polyReorder.h"
#include "topologyPath.h"

#include <queue>
#include <vector>

class MeshTopology
{
public:
                MeshTopology();
                MeshTopology(MDagPath &mesh);
    virtual    ~MeshTopology();

    int&        operator[] (int i) { return vertexPath[i]; }

    bool        isComplete();
    bool        hasVisitedVertex(int i);
    
    int         numberOfEdges() { return meshData.numberOfEdges; }
    int         numberOfFaces() { return meshData.numberOfFaces; }
    int         numberOfVertices() { return meshData.numberOfVertices; }

    void        setMesh(MDagPath &mesh);
    void        reset();

    void        walk(polyReorder::ComponentSelection &startAt);
    void        walkStartingFace(polyReorder::ComponentSelection &startAt);
    void        walkVerticesOnFace(int &faceIndex);
    
    static bool hasSameTopology(MDagPath &a, MDagPath &b);

private:
    int         getFirstVisited(std::vector<int> &components, TopologyPath &path);
    int         getOppositeVertex(int &edgeIndex, int &vertexIndex);
    int         getTraversedEdge(int &prevVertex, int &nextVertex);
    int         getNextVertexSibling(int &lastVertex, int &vertex, int &faceIndex);

private:
    MDagPath            mesh;
    MeshData            meshData;

    int                 shellId = 0;

    TopologyPath        edgePath;
    TopologyPath        facePath;
    TopologyPath        vertexPath;
};

#endif
