#include <vector>
#include <iostream>
using namespace std;
/*------------------------------------------------------------------------- 
    Vertex Details
    graph  - Index of the vertex's component
    block  - List of indices of blocks that vertex belongs to
    impact - The impact of the vertex (to be calculated)
  -------------------------------------------------------------------------*/
struct vertex
{
    int graph;
    vector<int> block;
    int impact;
    vert()
    {
        impact = -1;
    }
};
/*-------------------------------------------------------------------------
    Edge Details
    u - Parent vertex
    v - Child vertex
  -------------------------------------------------------------------------*/
struct edge
{
    int u, v;
    edge(ll _u, ll _v)
    {
        u = _u;
        v = _v;
    }
};
/*-------------------------------------------------------------------------
    Block Details
    size        - Number of nodes contained by the block
    cutVertices - List of cut vertices of the block
    graph       - Index of the block's component
  -------------------------------------------------------------------------*/
struct block
{
    int size;
    vector<int> cutVertices;
    int graph;
    block(ll _s)
    {
        size = _s;
    }
};

