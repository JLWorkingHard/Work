"""
ECE606, F'22, Assignment 6, Problem 3
Template solution file.
"""

"""
You are not allowed to import anything. You are, however,
allowed to use any built-in Python 3 language feature and
data structures you like. You are allowed to define any subroutines
you like to structure your code as you like.
"""
def prim(g,s):
    INF = 9999999
    N = len(g)
    selected_node = [0]*N
    no_edge = 0
    selected_node[s] = True
    result = []
    G = [[0 for i in range(N)]for j in range(N)]
    i = 0
    while i<N:
        for j in g[i]:
            G[j[0]][i]= j[1]
        i += 1
    while (no_edge < N - 1):        
        minimum = INF
        a = 0
        b = 0
        for m in range(N):
            if selected_node[m]:
                lis = [i for i in range(N)]
                lis.remove(m)
                if m > sum(lis)/N:
                    lis = lis[::-1]
                for n in lis:
                    if ((not selected_node[n]) and G[m][n]):  
                        if minimum > G[m][n]:
                            minimum = G[m][n]
                            a = m
                            b = n
        result.append([a,b])
        selected_node[b] = True
        no_edge += 1
    return result

def hasMST(G, e, f):
    """
    You need to implement this method. See the handout for its specs.
    """
    lise = sorted(e)
    lisf = sorted(f)
    for i in range(len(G)):
        res = prim(G,i)
        flag1 = False
        flag2 = False
        for j in res:
            lis = sorted(j)
            if lise == lis: flag1 = True
            if lisf == lis: flag2 = True
        if flag1 and flag2: return True
    return False