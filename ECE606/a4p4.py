"""
ECE606, F'22, Assignment 4, Problem 4
Template solution file.
"""

"""
You are not allowed to import anything. You are, however,
allowed to use any built-in Python 3 language feature and
data structures you like. You are allowed to define any subroutines
you like to structure your code as you like.
"""

def dijkstra(graph,source, dest):
    vertices = list(range(len(graph)))
    dist = {vertex: float('inf') for vertex in vertices}
    previous = {vertex: None for vertex in vertices}
    num_path = {vertex: 0 for vertex in vertices}
    dist[source] = 0
    num_path[source] = 1
    q = vertices.copy()
    neighbours = {vertex: [] for vertex in vertices}
    for u in range(len(graph)):
        for edge_info in graph[u]:
            neighbours[u].append(edge_info)

    while q:
        u = min(q, key=lambda vertex: dist[vertex])
        q.remove(u)
        if dist[u] == float('inf') or u == dest:
            break
        for edge_info in neighbours[u]:
            alt = dist[u] + edge_info[1]
            if alt < dist[edge_info[0]]:                                  # Relax (u,v,a)
                dist[edge_info[0]] = alt
                previous[edge_info[0]] = u
                num_path[edge_info[0]] = num_path[u]
            elif alt == dist[edge_info[0]]:
                num_path[edge_info[0]] += 1
    return num_path[dest]
def atLeastTwoSP(G, u, v):
    """
    You need to implement this method. See the handout for its specs.
    """
    result = dijkstra(G,u,v)
    if result == 1 or result== 0:
        return False
    else: return True