#include <iostream>
#include <queue>
#include <stack>
#define NODES 10

class Graph
{
public:
    int adjMatrix[NODES][NODES];
    int visited[NODES];
    int cameFrom[NODES];

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
        }
    }

    bool dfs(int start_node, int goal_node)
    {
        int node = start_node;
        visited[node] = 1;
        std::cout << node << "->";

        for (int j = 0; j < NODES; j++)
        {
            const int is_scc = adjMatrix[node][j];

            if (is_scc == 1 && visited[j] != 1)
            {
                cameFrom[j] = node;
                visited[j] = 1;
                if (j == goal_node)
                {
                    std::cout << j << "->#" << std::endl;
                    printShortest(j);
                    return true;
                }
                if (dfs(j, goal_node))
                    return true;
            }
        }
        return false;
    }

    void printShortest(int node)
    {
        std::cout << "Shortest path: " << std::endl;
        std::stack<int> cf;
        int c = cameFrom[node];

        while (c != -1)
        {
            cf.push(c);
            c = cameFrom[c];
        }

        while (!cf.empty())
        {
            std::cout << cf.top() << "->";
            cf.pop();
        }

        std::cout << node << "->#" << std::endl;
    }

    void addEdge(int i, int j)
    {
        adjMatrix[i][j] = 1;
        adjMatrix[j][i] = 1;
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

    void print()
    {
        for (int i = 0; i < NODES; i++)
        {
            for (int j = 0; j < NODES; j++)
            {
                std::cout << adjMatrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

int main(int argc, char *argv[])
{
    Graph g = Graph();
    g.addDirectedEdge(0, 1);
    g.addDirectedEdge(0, 2);
    g.addDirectedEdge(1, 3);
    g.addDirectedEdge(1, 6);
    g.addDirectedEdge(2, 3);
    g.addDirectedEdge(2, 4);
    g.addDirectedEdge(3, 4);
    g.addDirectedEdge(3, 5);
    g.addDirectedEdge(4, 6);
    g.addDirectedEdge(6, 6);
    g.print();

    if (!g.dfs(0, 6))
    {
        std::cout << "X" << std::endl;
        std::cout << "Goal node bulunamadi" << std::endl;
    }
    return 0;
}
