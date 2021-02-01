#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#define NODES 10

using namespace std;

class Node
{
public:
    int n, g, h, f;
    Node(int n, int g, int h)
    {
        this->n = n;
        this->g = g;
        this->h = h;
        this->f = g + h;
    }
};

class Result
{

public:
    int value;
    bool failure;

    Result(int val, bool fail)
    {
        value = val;
        failure = fail;
    }
};

class Graph
{
public:
    int adjMatrix[NODES][NODES];
    int visited[NODES];
    int heuristics[NODES];

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
            heuristics[i] = -1;
            visited[i] = 0;
        }
        visited[0] = 0;
    }

    Result rbfs(int node, int goal_node, int f_limit)
    {
        vector<Node> successors;

        cout << node << "->";
        if (node == goal_node)
            return Result(f_limit, false);
        auto _node = Node(node, visited[node], heuristics[node]);

        /* Expand successors */
        for (int j = 0; j < NODES; j++)
        {
            const int is_scc = adjMatrix[_node.n][j];
            const int pathToNode = is_scc + visited[_node.n];
            if (is_scc > -1)
            {
                successors.push_back(Node(j, pathToNode, heuristics[j]));
                visited[j] = pathToNode;
            }
        }

        if (successors.size() <= 0)
            return Result(10e5, true);

        for (int i = 0; i < successors.size(); i++)
        {
            Node &current = successors[i];
            current.f = max(current.h + current.g, _node.f);
        }

        while (true)
        {
            /* Sort nodes */
            sort(successors.begin(), successors.end(), [](const Node &lhs, const Node &rhs) {
                return lhs.f < rhs.f;
            });
            Node &best = successors[0];
            if (best.f > f_limit)
                return Result(best.f, true);

            Node alternative = Node(99999, 99999, 99999);

            if (successors.size() > 1)
                alternative = successors[1];

            auto result = rbfs(best.n, goal_node, min(f_limit, alternative.f));
            best.f = result.value;
            if (result.failure != true)
                return result;
        }
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
            visited[i] = 0;
        }
    }

    int min(int a, int b)
    {
        if (a < b)
            return a;
        else
            return b;
    }
    int max(int a, int b)
    {
        if (a > b)
            return a;
        else
            return b;
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

    auto result = g.rbfs(0, 4, 10e5);

    if (result.failure != true)
    {
        cout << "#" << endl;
    }

    return 0;
}
