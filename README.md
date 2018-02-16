# Cut-Vertex-Algorithm
Implementation and presentation of an algorithm that can identify the impact of cut vertices in O(N + M) time complexity.
Impact is defined as the number of vertices seperated from the largest surviving component when a cut vertex is removed.

### Basic Execution
To execute in linux, simply type the following in terminal: 
```
./findImpact
```
### Input Format
The main algorithm takes inputs in the following format:
```
N M
M1 M2
M3 M4
.
.
.
```
N, M are integers, where N represents number of vertices in the graph, and M the number of edges.   
M1 M2, M3 M4... are the connections between the vertices. M1 and M2 are the indices of the vertices being connected.  
Vertices are 1-indexed.   

```
4 4
1 2
2 3
3 4
4 1
```
The above creates a cycle graph with four vertices.

### Output Format
The output is given in pairs, with each pair being represented as "a b" where 'a' is the index of the vertex, and 'b' is its impact.
Example output for the above graph is:
```
1 0
2 0
3 0
4 0
```

### Visualization
By installing graph-tool (https://git.skewed.de/count0/graph-tool/wikis/installation-instructions) for python, the graph can also be displayed.
The following command can be run in linux to generate the display:
```
./findImpact viz | python visualizer.py
```
