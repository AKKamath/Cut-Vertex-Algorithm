from graph_tool.all import *
N, M = map(int, raw_input().split())
g = Graph(directed=False)
vImpact = g.new_vertex_property("int")
vlist = g.add_vertex(N)
for i in range(M):
	a, b = map(int, raw_input().split())
	g.add_edge(g.vertex(a - 1), g.vertex(b - 1))
for i in range(N):
	a, b = map(int, raw_input().split())
	vImpact[g.vertex(a - 1)] = b
graph_draw(g, vertex_text=vImpact)
