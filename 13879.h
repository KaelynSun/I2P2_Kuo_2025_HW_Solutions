#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include <limits>

using std::pair;
using std::vector;
using std::numeric_limits;

class graph
{
protected:
    int n;

private:
    vector<vector<int> > adjacent_lists;

public:
    graph(int _n, vector<pair<int, int> > edges) : n(_n), adjacent_lists(_n)
    {
#if __cplusplus >= 201703L
        for (auto [a, b] : edges)
        {
#else
        for (vector<pair<int, int> >::iterator itr = edges.begin(); itr != edges.end(); itr++)
        {
            int a = itr->first, b = itr->second;
#endif
            adjacent_lists[a].push_back(b);
            adjacent_lists[b].push_back(a);
        }
    }

    vector<int> bfs(int) const; // Perform BFS traversal on a graph.
};

class tree : public graph
{
public:
    tree(int n, vector<pair<int, int> > edges) : graph(n, edges) {}
    int diameter() const; // Find the diameter by BFS traversal.
};

#endif // FUNCTION_H

////////////////////////////////////////////////////////////////////////////////
//                              Separate Line!!!                              //
////////////////////////////////////////////////////////////////////////////////

/**
 *
 * It's recommended that you should implement the 3 member functions in a different file.
 *
 * If you edit `function.h` directly, don't paste the codes above.
 *
 */

// Starter codes are provided below. Uncomment them and begin coding!



vector<int> graph::bfs(int source) const
{
    // TODO: Perform BFS traversal on a graph.

    vector <int> distance(n, -1);
    //this means that all the n nodes have not been traversed
    vector <int> queue;

    distance[source] = 0; //set the source node to be 0, meaning they have been travelled
    queue.push_back(source);

    for(size_t i = 0; i < queue.size(); i++){
        int currentNode = queue[i];
        for(int neighbor : adjacent_lists[currentNode]){
            if(distance[neighbor] == -1){
                //if that node's neighbor has not been travelled:
                distance[neighbor] = distance[currentNode] + 1;
                queue.push_back(neighbor);
            }
        }
    }

    return distance;
}

int tree::diameter() const
{
    // TODO: Find the diameter by BFS traversal.
    if (n == 0) return 0;

    vector<int> distance = bfs(0);
    int farthest = 0;
    for(int i = 1; i < n; i++){
        if(distance[i] > distance[farthest]){
            farthest = i;
        }
    }

    distance = bfs(farthest);
    int maxDistance = 0;
    for(int d : distance){
        if(d > maxDistance){
            maxDistance = d;
        }
    }

    return maxDistance;
}

