#ifndef wtgraph_hpp
#define wtgraph_hpp

//--------------------------------------------------------------------
//
//  Laboratory 14                                            wtgraph.h
//
//  Class declaration for the adjacency matrix implementation of
//  the Weighted Graph ADT
//
//--------------------------------------------------------------------



const int defMaxGraphSize = 10,      // Default number of vertices
vertexLabelLength = 11,    // Length of a vertex label
infiniteEdgeWt = 9999;   // "Weight" of a missing edge

//--------------------------------------------------------------------

class Vertex
{
public:
    
    char label[vertexLabelLength];   // Vertex label
};

//--------------------------------------------------------------------

class WtGraph
{
public:
    
    // Constructor
    WtGraph(int maxNumber = defMaxGraphSize);
    
    // Destructor
    ~WtGraph();
    
    // Graph manipulation operations
    void insertVertex(Vertex newVertex);             // Insert vertex
    void insertEdge(char *v1, char *v2, int wt);   // Insert edge
    int retrieveVertex(char *v, Vertex &vData) const;
    // Get vertex
    int edgeWeight(char *v1, char *v2, int &wt);
    // Get edge wt.
    void removeVertex(char *v);                       // Remove vertex
    void removeEdge(char *v1, char *v2);            // Remove edge
    void clear();                                    // Clear graph
    
    // Graph status operations
    int empty() const;                            // Graph is empty
    int full() const;                            // Graph is full
    
    // Output the graph structure -- used in testing/debugging
    void showStructure();
    
    // In-lab operation
    void computePaths();
    
private:
    
    // Facilitator functions
    int index(char *v) const;       // Converts vertex label to an index
    
    int& edge(int row, int col);    // Set/get edge weight using adjacency matrix indices
    int& path(int row, int col);
    
    // Data members
    int     maxSize,          // Maximum number of vertices in the graph 그래프의 최대 정점의 개수
    size;             // Actual number of vertices in the graph 그래프의 실제 정점의 개수
    Vertex* vertexList;       // Vertex list 정점 리스트
    int*    adjMatrix;        // Adjacency matrix 인접 행렬
    int*    pathMatrix;       // 경로 행렬
    
};


#endif /* wtgraph_hpp */
