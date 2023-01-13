#include <vector>
#include <queue>
class Spfa{
    public:
        unsigned m_vex;
        void putin(std::vector<std::vector<unsigned> > &adj, unsigned src, unsigned dest);
        bool BFS(std::vector<std::vector<unsigned> > adj, unsigned src, unsigned dest, unsigned v,unsigned pred[], unsigned dist[]);
        void putout(std::vector<std::vector<unsigned> > adj, unsigned s,unsigned dest, unsigned v);
        void resize(std::vector<std::vector<unsigned> > &adj, unsigned v);    
};
