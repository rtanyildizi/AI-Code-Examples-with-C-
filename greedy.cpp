#include <iostream>
#include <queue>
#include <stack>
#define NODES 10

using namespace std;

typedef pair<int, int> node;

class Graph
{
public:
    int adjMatrix[NODES][NODES];
    int heuristics[NODES];
    int visited[NODES];
    int cameFrom[NODES];

    priority_queue<node, vector<node>, greater<node>> frontier;

    Graph()
    {
        for (int i = 0; i < NODES; i++)
        {
            for (int j = 0; j < NODES; j++)
            {
                adjMatrix[i][j] = 0;
            }
        }
        for (int i = 0; i < NODES; i++)
        {
            cameFrom[i] = -1;
            visited[i] = 0;
            heuristics[i] = 0;
        }
    }

    void greedy(int start_node, int goal_node)
    {
        auto node = makeNode(start_node);
        frontier.push(node);

        visited[start_node] = 1;

        while (!frontier.empty())
        {
            auto node = frontier.top();
            frontier.pop();
            cout << node.second << "[" << node.first << "]"
                 << "->";

            for (int j = 0; j < NODES; j++)
            {
                const int is_scc = adjMatrix[node.second][j];
                if (is_scc == 1 && visited[j] != 1)
                {
                    if (j == goal_node || heuristics[j] == 0)
                    {
                        cout << j << "[" << heuristics[j] << "]"
                             << "->#" << endl;
                        return;
                    }
                    visited[j] = 1;
                    frontier.push(makeNode(j));
                }
            }
        }
        cout << "#" << endl;
        cout << "Goal node bulunamadi" << endl;
    }

    void addDirectedEdge(int i, int j)
    {
        adjMatrix[i][j] = 1;
    }

    void resetVisited()
    {
        for (int i = 0; i < NODES; i++)
        {
            visited[i] = 0;
        }
    }

    void changeHeuristic(int node, int h)
    {
        heuristics[node] = h;
    }

    node makeNode(int node)
    {
        return make_pair(heuristics[node], node);
    }

    void print()
    {
        for (int i = 0; i < NODES; i++)
        {
            for (int j = 0; j < NODES; j++)
            {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};

int main(int argc, char *argv[])
{
    Graph g = Graph();

    g.addDirectedEdge(0, 1);
    g.addDirectedEdge(0, 5);
    g.addDirectedEdge(1, 2);
    g.addDirectedEdge(1, 4);
    g.addDirectedEdge(2, 3);
    g.addDirectedEdge(2, 6);
    g.addDirectedEdge(3, 4);
    g.addDirectedEdge(5, 2);
    g.addDirectedEdge(5, 6);
    g.addDirectedEdge(6, 4);

    g.changeHeuristic(0, 7);
    g.changeHeuristic(1, 9);
    g.changeHeuristic(2, 4);
    g.changeHeuristic(3, 2);
    g.changeHeuristic(4, 0);
    g.changeHeuristic(5, 5);
    g.changeHeuristic(5, 5);
    g.changeHeuristic(6, 3);

    g.print();
    g.greedy(0, 4);
    return 0;
}
