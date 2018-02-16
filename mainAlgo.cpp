#include <vector>
#include <stack>
#include <unordered_set>
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
    vertex()
    {
        impact = 0;
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
    edge(int _u, int _v)
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
    block(int _s)
    {
        size = _s;
    }
};
/*-------------------------------------------------------------------------
    Create the main block diagram using DFS
    u         - Index of vertex currently being traversed
    edges     - Adjacency list of graph
    count     - Used to keep track of DFS timings
    vertNum   - List to keep track of when each vertex was traversed
    parent    - List to maintain which vertex cainted function for which node
    low       - List of smaintest time encountered by each vertex
    edgeStack - Stack keeping track of edges traversed
    v         - List of aint vertices present in graph
    blocks    - List of blocks (to be added to)
    graph     - Index of current component being traversed
  -------------------------------------------------------------------------*/
void createBlocks(int u, vector<vector<int> > &edges, int &count, 
    vector<int> &vertNum, vector<int> &parent, vector<int> &low, 
    stack<edge> &edgeStack, vector<vertex> &v, vector<block> &blocks, int graph)
{
    // Set component of current vertex
    v[u].graph = graph;
    // Increment time and set it for vertex
    ++count;
    vertNum[u] = count;
    // Traverse edges of vertex u
    for(int i = 0; i < edges[u].size(); ++i)
    {
        int w = edges[u][i];
        // Vertex has not yet been traversed
        if(vertNum[w] == 0)
        {
            // Set parent and insert edge into stack
            parent[w] = u;
            edgeStack.push(edge(u, w));
            // Smaintest time encountered so far
            low[w] = vertNum[u];
            // Recurse for vertex w
            createBlocks(w, edges, count, vertNum, parent, low, edgeStack, v, blocks, graph);
            // Vertex traversal did not encounter an ancestor of u
            if(low[w] == vertNum[u])
            {
                // Keep track of vertices added to block
                unordered_set<int> vs;
                int c = 0;
                // Pop from stack until initiainty traversed edge encountered
                while(!edgeStack.empty())
                {
                    edge e = edgeStack.top();
                    edgeStack.pop();
                    // Check if vertices already added to block
                    if(vs.find(e.u) == vs.end())
                    {
                        v[e.u].block.push_back(blocks.size());
                        ++c;
                        vs.emplace(e.u);
                    }
                    if(vs.find(e.v) == vs.end())
                    {
                        v[e.v].block.push_back(blocks.size());
                        ++c;
                        vs.emplace(e.v);
                    }
                    // Finished traversal of edges
                    if(e.u == u && e.v == w)
                        break;
                }
                // Create block and insert details
                blocks.push_back(block(c));
                blocks[blocks.size() - 1].graph = graph;
            }
            // Ancestor of u was encountered
            else if(low[w] < vertNum[u])
            {
                if(low[w] < low[u])
                    low[u] = low[w];
            }
        }
        // Already traversed this vertex
        else
        {
            // See if this vertex is an ancestor of previously traversed vertex
            if(w != parent[u])
            {
                if(vertNum[w] < vertNum[u])
                {
                    edgeStack.push(edge(u, w));
                    if(vertNum[w] < low[u])
                        low[u] = vertNum[w];
                }
            }
        }
    }
}
/*-------------------------------------------------------------------------
    Functions used during the second DFS
    Traversing occurs block -> cut vertex -> block -> ...
    ind       - Index of block/vertex being traversed
    vst       - List of whether a node has been visited
    blocks    - List of blocks
    v         - List of vertices
    graph     - List containing vertex count of each component
    returns the number of vertices traversed so far
  -------------------------------------------------------------------------*/
int vertexDFS(int ind, vector<bool> &vst, vector<block> &blocks, vector<vertex> &v, vector<int> &graph);
int blockDFS(int ind, vector<bool> &vst, vector<block> &blocks, vector<vertex> &v, vector<int> &graph);

int vertexDFS(int ind, vector<bool> &vst, vector<block> &blocks, vector<vertex> &v, vector<int> &graph)
{
    // Keep a count of vertices
    int c = 1;
    // We've visited this vertex
    vst[ind + blocks.size() - 1] = true;
    // Try to identify largest group
    int maxi = 0;
    for(int i = 0; i < v[ind].block.size(); ++i)
    {
        // Visit unvisited blocks
        if(!vst[v[ind].block[i]])
        {
            // Get number of vertices in the block
            int num = blockDFS(v[ind].block[i], vst, blocks, v, graph) - 1;
            maxi = max(num, maxi);
            c += num;
        }
    }
    // Make impact the number of vertices not in largest connected component
    maxi = max(maxi, graph[v[ind].graph] - c);
    v[ind].impact = graph[v[ind].graph] - maxi - 1;
    return c;
}

int blockDFS(int ind, vector<bool> &vst, vector<block> &blocks, vector<vertex> &v, vector<int> &graph)
{
    int c = blocks[ind].size;
    // Mark this block as visited
    vst[ind] = true;
    for(int i = 0; i < blocks[ind].cutVertices.size(); ++i)
    {
        // Visit cut vertices
        if(!vst[blocks.size() + blocks[ind].cutVertices[i] - 1])
        {
            c += vertexDFS(blocks[ind].cutVertices[i], vst, blocks, v, graph) - 1;
        }
    }
    return c;
}

int main(int argc, const char *argv[])
{
    // Input number of edges and vertices
    int N, M;
    cin>>N>>M;
	if(argc > 1 && string(argv[1]) == "viz")
		cout<<N<<" "<<M<<"\n";
    // Create necessary lists
    vector<vector<int> > edges(N + 1);
    vector<vertex> v(N + 1);
    vector<block> blocks;
    vector<int> vertNum(N + 1, 0);
    vector<int> parent(N + 1, 0);
    vector<int> low(N + 1, 0);
    vector<int> graph;
    stack<edge> edgeStack;
    // Input edge details
    for(int i = 0; i < M; ++i)
    {
        int a, b;
        cin>>a>>b;
		if(argc > 1 && string(argv[1]) == "viz")
			cout<<a<<" "<<b<<"\n";
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    
    for(int i = 1; i <= N; ++i)
    {
        // Start DFS on each node
        int count = 0;
        if(vertNum[i] == 0)
        {
            createBlocks(i, edges, count, vertNum, parent, low, edgeStack, v, blocks, graph.size());
            // Create blocks for leftover vertices
            while(!edgeStack.empty())
            {
                edge e = edgeStack.top();
                edgeStack.pop();
                v[e.u].block.push_back(blocks.size());
                v[e.v].block.push_back(blocks.size());
                blocks.push_back(block(2));
                blocks[blocks.size() - 1].graph = graph.size();
            }
            graph.push_back(count);
        }
    }
    // Insert cut vertices into appropriate blocks
    for(int i = 1; i <= N; ++i)
    {
        if(v[i].block.size() > 1)
        {
            for(int j = 0; j < v[i].block.size(); ++j)
            {
                blocks[v[i].block[j]].cutVertices.push_back(i);
            }
        }
    }
    // Perform second DFS
    vector<bool> vst(blocks.size() + N + 1, false);
    for(int i = 0; i < blocks.size(); ++i)
    {
        if(vst[i] == false)
        {
            vst[i] = true;
            blockDFS(i, vst, blocks, v, graph);
        }
    }
    // Output results
    for(int i = 1; i <= N; ++i)
    {
        cout<<i<<" "<<v[i].impact<<"\n";
    }
    return 0;
}
