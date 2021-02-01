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
        }
    }

    void ucs(int start_node, int goal_node)
    {
        auto node = make_pair(0, start_node);
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
                        frontier.push(make_pair(pathToNode, j));
                        visited[j] = pathToNode;
                    }
                }
            }
        }

        cout << "x" << endl
             << "Goal node bulunamadi" << endl;
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

    g.addDirectedEdge(0, 1, 99);
    g.addDirectedEdge(0, 2, 80);
    g.addDirectedEdge(1, 4, 211);
    g.addDirectedEdge(2, 3, 97);
    g.addDirectedEdge(3, 4, 101);

    g.print();

    g.ucs(0, 7);
    return 0;
}
