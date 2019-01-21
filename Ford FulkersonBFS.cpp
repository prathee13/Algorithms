#include <iostream>
#include <string.h>
#include <queue>

using namespace std;

// Number of vertices in given graph
#define N 7

// Function to know if a path exists from source to sink and then to save the path
bool bfs(int residualGraph[N][N], int s, int t, int parent[])
{
    // An array to keep track of all vertices.
    bool visited[N];
    memset(visited, 0, sizeof(visited));

    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    // Standard BFS Loop
    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v=0; v<N; v++)
        {
            if (visited[v]==false && residualGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    //When sink is reached.
    if (visited[t] == true)
        return true;
    else
        return false;
}

// Ford Fulkerson Algorithm
int fordFulkerson(int graph[N][N], int s, int t)
{
    int u, v;

    // Create a residual graph with capacities of original graph.
    int residualGraph[N][N];
    for (u = 0; u < N; u++)
        for (v = 0; v < N; v++)
             residualGraph[u][v] = graph[u][v];

    int parent[N];  //Array to store path

    int max_flow = 0;

    // Augment the flow while there is path from source to sink
    while (bfs(residualGraph, s, t, parent))
    {

        int path_flow = INT_MAX;
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, residualGraph[u][v]);
        }

        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            residualGraph[u][v] -= path_flow;
            residualGraph[v][u] += path_flow;
        }

        // Summation of flow
        max_flow += path_flow;
    }

    // Return the overall flow
    return max_flow;
}


int main()
{
    int graph[N][N] = { {0, 7, 6, 5, 0, 0, 0},
                        {0, 0, 0, 1, 2, 0, 0},
                        {0, 0, 0, 3, 0, 9, 0},
                        {0, 0, 0, 0, 5, 3, 0},
                        {0, 0, 0, 0, 0, 0, 6},
                        {0, 0, 0, 0, 0, 0, 8},
                        {0, 0, 0, 0, 0, 0, 0}
                      };

    cout << "The maximum possible flow using BFS is " << fordFulkerson(graph, 0, 6);

    return 0;
}
