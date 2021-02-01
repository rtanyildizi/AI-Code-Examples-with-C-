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
    std::queue<int> frontier;

    Graph()
    {
        for (int i = 0; i < NODES; i++)
        {
            for (int j = 0; j < NODES; j++)
            {
                adjMatrix[i][j] = 0;
            }
        }
        for (int j = 0; j < NODES; j++)
        {
            cameFrom[j] = -1;
        }
    }

    void bfs(int start_node, int goal_node)
    {
        resetVisited();
        frontier.push(start_node);
        std::cout << start_node << "->";
        visited[start_node] = 1;

        while (!frontier.empty())
        {
            int node = frontier.front();
            frontier.pop();
            for (int j = 0; j < NODES; j++)
            {
                int isSucc = adjMatrix[node][j];
                if (visited[j] != 1 && isSucc == 1)
                {
                    std::cout << j << "->";
                    cameFrom[j] = node;

                    if (j == goal_node)
                    {
                        std::cout << "#" << std::endl;
                        printShortest(j);
                        return;
                    }

                    frontier.push(j);
                    visited[j] = 1;
                }
            }
        }
        std::cout << "X" << std::endl;

        std::cout << "Goal node bulunamadi." << std::endl;
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

        std::cout << node << " # " << std::endl;
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
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 6);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 6);
    g.addEdge(6, 6);
    g.print();

    std::cout << "BFS Traversal" << std::endl;
    g.bfs(0, 6);
    return 0;
}
