#include <iostream>
#include <list>
#define INF 0xf
#include "spfa.h"
void Spfa::resize(std::vector<std::vector<unsigned> > &adj, unsigned v)
{
    adj.resize(v);
}
void Spfa::putin(std::vector<std::vector<unsigned> > &adj, unsigned src, unsigned dest)
{
    adj[src-1].push_back(dest);
    adj[dest-1].push_back(src);
}

bool Spfa::BFS(std::vector<std::vector<unsigned> > adj, unsigned src, unsigned dest, unsigned v,
         unsigned pred[], unsigned dist[])
{
    std::list<unsigned> queue;
    bool visited[v];
    for (unsigned i = 0; i < v; i++) {
        visited[i] = false;
        dist[i] = INF;
        pred[i] = 0;
    }
    visited[src-1] = true;
    dist[src-1] = 0;
    queue.push_back(src);
    while (!queue.empty()) {
        unsigned u = queue.front();
        queue.pop_front();
        for (unsigned i = 0; i < adj[u-1].size(); i++) {
            if (visited[adj[u-1][i]-1] == false) {
                visited[adj[u-1][i]-1] = true;
                dist[adj[u-1][i]-1] = dist[u-1] + 1;
                pred[adj[u-1][i]-1] = u;
                queue.push_back(adj[u-1][i]);
                if (adj[u-1][i] == dest)
                    return true;
            }
        }
    }
 
    return false;
}
void Spfa::putout(std::vector<std::vector<unsigned> > adj, unsigned s, unsigned dest, unsigned v)
{
    unsigned pred[v], dist[v];
 
    if (BFS(adj, s, dest, v, pred, dist) == false) {
        std::cerr << "Error: from child_a2, given source and destination" << " are not connected" << std::endl;
        return;
    }
    std::vector<unsigned> path;
    unsigned crawl = dest;
    path.push_back(crawl);
    
    while (pred[crawl-1] != 0) {
        path.push_back(pred[crawl-1]);
        crawl = pred[crawl-1];
    }
    if (path.size() > 1)
    {
        for (int i = path.size() - 1; i > 0; i--)
        std::cout << path[i] << "-";
	    std::cout << path[0] << std::endl;
    }
}
