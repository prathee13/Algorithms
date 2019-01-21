#include<bits/stdc++.h>
#include<iostream>

using namespace std;

//Structure for one edge.
struct Edge
{
    int vertex, flow, capacity, rev ;
};

//
class Graph
{
    int V;
    int *level ; // stores level of a node
    vector< Edge > *adj;
public :
    Graph(int V)
    {
        adj = new vector<Edge>[V];
        this->V = V;
        level = new int[V];
    }


    void addEdge(int u, int v, int C)
    {
        // Forward edge : 0 flow and C capacity
        Edge a{v, 0, C, adj[v].size()};

        // Back edge : 0 flow and 0 capacity
        Edge b{u, 0, 0, adj[u].size()};

        adj[u].push_back(a);
        adj[v].push_back(b); // reverse edge
    }

    bool BFS(int s, int t);
    int sendFlow(int s, int flow, int t, int ptr[]);
    int DinicMaxflow(int s, int t);
};

// Finds if more flow can be sent from s to t.
// Also assigns levels to nodes.
bool Graph::BFS(int s, int t)
{
    for (int i = 0 ; i < V ; i++)
        level[i] = -1;

    level[s] = 0;

    list< int > q;
    q.push_back(s);

    vector<Edge>::iterator i ;
    while (!q.empty())
    {
        int u = q.front();
        q.pop_front();
        for (i = adj[u].begin(); i != adj[u].end(); i++)
        {
            Edge &e = *i;
            if (level[e.vertex] < 0  && e.flow < e.capacity)
            {
                level[e.vertex] = level[u] + 1;

                q.push_back(e.vertex);
            }
        }
    }

    return level[t] < 0 ? false : true ;
}

int Graph::sendFlow(int u, int flow, int t, int start[])
{
    // Sink reached
    if (u == t)
        return flow;

    // Traverse all adjacent edges one -by - one.
    for (  ; start[u] < adj[u].size(); start[u]++)
    {
        // Pick next edge from adjacency list of u
        Edge &e = adj[u][start[u]];

        if (level[e.vertex] == level[u]+1 && e.flow < e.capacity)
        {
            // find minimum flow from u to t
            int curr_flow = min(flow, e.capacity - e.flow);

            int temp_flow = sendFlow(e.vertex, curr_flow, t, start);

            // flow is greater than zero
            if (temp_flow > 0)
            {
                // add flow  to current edge
                e.flow += temp_flow;

                // subtract flow from reverse edge
                // of current edge
                adj[e.vertex][e.rev].flow -= temp_flow;
                return temp_flow;
            }
        }
    }

    return 0;
}

// Returns maximum flow in graph
int Graph::DinicMaxflow(int s, int t)
{
    // Corner case
    if (s == t)
        return -1;

    int total = 0;  // Initialize result

    // Augment the flow while there is path
    // from source to sink
    while (BFS(s, t) == true)
    {
        // store how many edges are visited
        // from V { 0 to V }
        int *start = new int[V+1];

        // while flow is not zero in graph from S to D
        while (int flow = sendFlow(s, INT_MAX, t, start))

            // Add path flow to overall flow
            total += flow;
    }

    // return maximum flow
    return total;
}

// Driver program to test above functions
int main()
{
    Graph g(7);
    g.addEdge(0, 1, 7);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 1);
    g.addEdge(1, 4, 2);
    g.addEdge(2, 3, 3);
    g.addEdge(2, 5, 9);
    g.addEdge(3, 4, 5);
    g.addEdge(3, 6, 3);
    g.addEdge(4, 6, 6);
    g.addEdge(5, 6, 8);


    cout << "The maximum possible flow using Algorithm of Dinic is " << g.DinicMaxflow(0, 6);
    return 0;
}
