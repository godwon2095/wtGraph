#include "wtgraph.hpp"
#include <iostream>
#include <limits>

using namespace std;

WtGraph::WtGraph(int maxNumber)
:size(0),
maxSize(maxNumber)
{
    vertexList = new Vertex[maxNumber];
    adjMatrix = new int[infiniteEdgeWt];
    pathMatrix = new int[infiniteEdgeWt];
}

WtGraph::~WtGraph()
{
    delete [] vertexList;
    delete [] adjMatrix;
    delete [] pathMatrix;
}

int WtGraph::index(char *v) const
{
    for (int i = 0; i < vertexLabelLength; i++)
    {
        if (vertexList[i].label[0] == *v)
            return i;
    }
    
    return 12;
}

int& WtGraph::edge(int row, int col)
{
    return adjMatrix[row*size + col];
}

int& WtGraph::path(int row, int col)
{
    return pathMatrix[row*size + col];
}

int WtGraph::edgeWeight(char *v1, char *v2, int &wt)
{
    int row = index(v1);
    int col = index(v2);
    
    if (row == 12 || col == 12)
        return 0;
    else
    {
        wt = adjMatrix[row*size + col];
        return 1;
    }
}


void WtGraph::insertVertex(Vertex newVertex)
{
    if (size == defMaxGraphSize)
        cout << "Graph size if full!!" << endl;
    else if (retrieveVertex(newVertex.label, newVertex) == 1)
        cout << "It is alreay exist vertax" << endl;
    else
    {
        vertexList[size] = newVertex;
        
        size++;
        
        for (int i = 0; i < size; i++)
        {
            edge(size, i) = 0;
            edge(i, size) = 0;
            path(size, i) = 0;
            path(i, size) = 0;
        }
    }
}


void WtGraph::insertEdge(char *v1, char *v2, int wt)
{
    if (index(v1) == 12 || index(v2) == 12)
        cout << "There's somethig wrong input." << endl;
    else
    {
        edge(index(v1), index(v2)) = wt;
        edge(index(v2), index(v1)) = wt;
    }
}


int WtGraph::retrieveVertex(char *v, Vertex &vData) const
{
    for (int i = 0; i < size; i++)
    {
        if (vertexList[i].label[0] == *v)
            return 1;
    }
    return 0;
}


void WtGraph::removeVertex(char *v)
{
    int checkInt(0);
    
    for (int i = 0; i < size; i ++)
        if (vertexList[i].label[0] == *v)
        {
            checkInt = i;
        }
    
    size--;
    
    for (int i = checkInt; i < size; i++)
        vertexList[i] = vertexList[i+1];
}


void WtGraph::removeEdge(char *v1, char *v2)
{
    int row = index(v1);
    int col = index(v2);
    
    if (row == 12 || col == 12)
        cout << "There's somethig wrong input." << endl;
    else
    {
        edge(row, col) = 0;
        edge(col, row) = 0;
    }
}


void WtGraph::clear()
{
    size = 0;
}

int WtGraph::empty() const
{
    if (size == 0)
        return 1;
    else
        return 0;
}

int WtGraph::full() const
{
    if (size == defMaxGraphSize)
        return 1;
    else
        return 0;
}


void WtGraph::computePaths()
{
    for (int i = 0; i < size; i ++)
        for (int j = 0; j < size; j ++)
            path(i, j) = edge(i, j);
    
    for (int m = 0 ; m < size ; m++ )
        for (int j = 0 ; j < size ; j++ )
            for (int k = 0 ; k < size ; k++ )
                if (edge(j,m) != 0 && edge(m, k) != 0)
                {
                    if (path(j, k) == 0 || path(j, k) > edge(j, m) + edge(m, k))
                    {
                        if (j != k)
                        {
                            path(j, k) = edge(j, m) + edge(m, k);
                            path(k, j) = edge(j, m) + edge(m, k);
                        }
                    }
                }
}


void WtGraph::showStructure()
{
    if (size != 0)
    {
        cout << "Vertax list :" << endl;
        for (int i = 0; i < size; i ++)
            cout << i << '\t' << vertexList[i].label[0] << endl;
        cout << endl;
        
        cout << "Edge Matrix :" << endl;
        cout << '\t';
        for (int i = 0; i < size; i ++)
            cout << i << '\t' ;
        cout << endl;
        
        for (int i = 0; i < size; i++)
        {
            cout << i;
            for (int j = 0; j < size; j++)
            {
                if (edge(i, j) == 0)
                    cout << '\t' << "-";
                else
                    cout << '\t' << edge(i, j);
            }
            cout << endl;
        }
        
        cout << "Path Matrix :" << endl;
        cout << '\t';
        for (int i = 0; i < size; i ++)
            cout << i << '\t' ;
        cout << endl;
        
        for (int i = 0; i < size; i++)
        {
            cout << i;
            for (int j = 0; j < size; j++)
            {
                if (path(i, j) == 0)
                    cout << '\t' << "-";
                else
                {
                    cout << '\t' << path(i, j);
                }
            }
            cout << endl;
        }
    }
}
