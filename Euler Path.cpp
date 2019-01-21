#include<iostream>
#include <list>

using namespace std;

// A class that represents a graph
class Graph
{
    int n;                                        // Number of vertices
    list<int> *adj;                               // A dynamic array of adjacency lists
    int *temp;

public:

    Graph(int n)
    {
        this->n = n;
        adj = new list<int>[n];
        temp = new int[n];
        for (int i = 0; i < n; i++)
        temp[i] = 0;
    }

    // Insert edges to the graph
    void addEdge(int v, int w)
    {
        adj[v].push_back(w);
        (temp[w])++;
    }

    // Function to do DFS starting from v.
    void DFS(int v, bool visited[]);

   // Method to check if all non-zero degree vertices are connected or not.
    bool isStronglyConnected();

    // Method to check if this graph is Eulerian or not.
    bool isEulerian();

    //Method to get the reverse of a graph - required to check if a graph is strongly connected or not.
    Graph Transpose();
};


void Graph::DFS(int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFS(*i, visited);
}


bool Graph::isStronglyConnected()
{
    // Mark all the vertices as not visited (For first DFS)
    bool visited[n];
    for (int i = 0; i < n; i++)
        visited[i] = false;

    // Find the first vertex with non-zero degree
    int p;
    for (p = 0; p < n; p++)
        if (adj[p].size() > 0)
          break;

    // DFS Traversal
    DFS(p, visited);

     // If DFS traversal doesn't visit all vertices, then return false.
    for (int i = 0; i < n; i++)
        if (adj[i].size() > 0 && visited[i] == false)
              return false;

    // Create a reversed graph
    Graph g = Transpose();

    // Mark all the vertices as not visited (For second DFS)
    for (int i = 0; i < n; i++)
        visited[i] = false;

    // Do DFS for reversed graph starting from first vertex.
    // Staring Vertex must be same starting point of first DFS
    g.DFS(p, visited);

    // If all vertices are not visited in second DFS, then return false
    for (int i = 0; i < n; i++)
        if (adj[i].size() > 0 && visited[i] == false)
             return false;

    return true;
}


bool Graph::isEulerian()
{
    // Check if all non-zero degree vertices are connected
    if (isStronglyConnected() == false)
        return false;

    // Check if in degree and out degree of every vertex is same
    for (int i = 0; i < n; i++)
        if (adj[i].size() != temp[i])
            return false;

    return true;
}


Graph Graph::Transpose()
{
    Graph g(n);
    for (int v = 0; v < n; v++)
    {
        // Recur for all the vertices adjacent to this vertex
        list<int>::iterator i;
        for(i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            g.adj[*i].push_back(v);
            (g.temp[v])++;
        }
    }
    return g;
}

int main()
{
    //NOTE: If there are n vertices, the first node starts from 0

    cout<<" Graph G1 1 is ";
    Graph g1(5);

    g1.addEdge(0,1);
    g1.addEdge(1,4);
    g1.addEdge(1,2);
    g1.addEdge(2,1);
    g1.addEdge(2,4);
    g1.addEdge(4,3);
    g1.addEdge(3,2);
    g1.addEdge(4,0);

    g1.isEulerian()?cout<<"Eulerian.":cout<<"Not Eulerian.";

    cout<<" \n \n Graph G2 is ";
    Graph g2(5);

    g2.addEdge(0, 0);
    g2.addEdge(0, 1);
    g2.addEdge(1, 0);
    g2.addEdge(0, 3);
    g2.addEdge(1, 2);
    g2.addEdge(1, 3);
    g2.addEdge(2, 3);
    g2.addEdge(3, 4);

    (g2.isEulerian())?cout<<"Eulerian.":cout<<"Not Eulerian.";


     cout<<"\n \n Graph G3 is ";
     Graph g3(7);

     g3.addEdge(0,3);
     g3.addEdge(4,1);
     g3.addEdge(3,4);
     g3.addEdge(1,3);
     g3.addEdge(3,5);
     g3.addEdge(5,6);
     g3.addEdge(6,2);
     g3.addEdge(2,0);


     (g3.isEulerian())?cout<<"Eulerian. ":cout<<"Not Eulerian. ";

     cout<<"\n \n";

    return 0;
}
