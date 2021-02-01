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
    int visited[NODES];
    int heuristics[NODES];

    priority_queue<node, vector<node>, greater<node>> frontier;

    Graph()
    {
        for (int i = 0; i < NODES; i++)
        {
            for (int j = 0; j < NODES; j++)
            {
                adjMatrix[i][j] = -1;
            }
        }
        for (int i = 0; i < NODES; i++)
        {
            visited[i] = -1;
            heuristics[i] = -1;
        }
    }

    void astar(int start_node, int goal_node)
    {
        const int cost = 0 + heuristics[start_node];
        auto node = make_pair(cost, start_node);
        frontier.push(node);
        visited[start_node] = 0;

        while (!frontier.empty())
        {
            node = frontier.top();
            frontier.pop();
            cout << node.second << "[" << node.first << "], ";

            if (node.second == goal_node)
            {
                cout << "#" << endl;
                return;
            }

            for (int j = 0; j < NODES; j++)
            {
                const int is_scc = adjMatrix[node.second][j];
                const int pathToNode = is_scc + visited[node.second];

                if (is_scc > -1)
                {
                    if (visited[j] == -1 || visited[j] > pathToNode)
                    {
                        frontier.push(make_pair(pathToNode + heuristics[j], j));
                        visited[j] = pathToNode;
                    }
                }
            }
        }

        cout << "x" << endl
             << "Goal node bulunamadi" << endl;
    }

    void changeHeuristic(int node, int h)
    {
        heuristics[node] = h;
    }

    void addDirectedEdge(int i, int j, int w)
    {
        adjMatrix[i][j] = w;
    }

    void resetVisited()
    {
        for (int i = 0; i < NODES; i++)
        {
            visited[i] = -1;
        }
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

    g.addDirectedEdge(0, 1, 3);
    g.addDirectedEdge(0, 5, 2);
    g.addDirectedEdge(1, 2, 5);
    g.addDirectedEdge(1, 4, 10);
    g.addDirectedEdge(2, 3, 2);
    g.addDirectedEdge(2, 6, 1);
    g.addDirectedEdge(3, 4, 4);
    g.addDirectedEdge(5, 2, 1);
    g.addDirectedEdge(5, 6, 4);
    g.addDirectedEdge(6, 4, 3);

    g.changeHeuristic(0, 7);
    g.changeHeuristic(1, 9);
    g.changeHeuristic(2, 4);
    g.changeHeuristic(3, 2);
    g.changeHeuristic(4, 0);
    g.changeHeuristic(5, 5);
    g.changeHeuristic(5, 5);
    g.changeHeuristic(6, 3);

    g.print();

    g.astar(0, 4);
    return 0;
}
