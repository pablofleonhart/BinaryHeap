#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <cmath>

using namespace std;
# define INF 0x3f3f3f3f

class Heap
{
    int n, k;
    vector<int> weights;
    vector<int> vertexes;
    set< pair<int, int> > idx;

public:
    Heap( int k );

    bool isEmpty();

    void printWeights();

    void insert( int weight, int vertex );

    pair<int, int> deleteMin();

    void heapifyDown( int index );

    void heapifyUp( int index );
};

Heap::Heap( int k )
{
    n = 0;
    this->k = k;
}

bool Heap::isEmpty()
{
    return n == 0;
}

void Heap::printWeights()
{
    cout << "Built Heap:" << endl;
    for ( int i = 0; i < n; i++ )
        cout << weights[ i ] << "(" << vertexes[ i ] << ") ";

    cout << endl;
}

void Heap::heapifyDown( int index )
{
    vector<int> child;

    child.push_back( 0 );
    for ( int i = 1; i <= k; i++ )
    {
        child.push_back( ( ( k * index + i ) < n ) ? ( k * index + i ) : -1 );
    }

    int min_child = -1, min_child_index;

    for ( int i = 1; i <= k; i++ )
    {
        if ( child[ i ] != -1 && ( weights[ child[ i ] ] < min_child || min_child == -1 ) )
        {
            min_child_index = child[ i ];
            min_child = weights[ child[ i ] ];
        }
    }

    if ( min_child != -1 )
    {
        if ( weights[ index ] > weights[ min_child_index ] )
        {
            swap( weights[ index ], weights[ min_child_index ] );
            swap( vertexes[ index ], vertexes[ min_child_index ] );
        }

        index = min_child_index;
        heapifyDown( index );
    }
}

void Heap::heapifyUp( int index )
{
    if ( index > 0 )
    {
        int parent = floor( ( index - 1 ) / k );

        if ( weights[ index ] < weights[ parent ] )
        {
            swap( weights[ index ], weights[ parent ] );
            swap( vertexes[ index ], vertexes[ parent ] );
            heapifyUp( parent );
        }
    }
}

void Heap::insert( int weight, int vertex )
{
    weights.push_back( weight );
    vertexes.push_back( vertex );

    n++;

    heapifyUp( n - 1 ); 
}

pair<int, int> Heap::deleteMin()
{
    int minWeight = weights[ 0 ];
    int minVertex = vertexes[ 0 ];

    weights[ 0 ] = weights[ n - 1 ];
    weights.pop_back();

    vertexes[ 0 ] = vertexes[ n - 1 ];
    vertexes.pop_back();

    n--;

    if ( weights[ 0 ] > minWeight )
    {
        heapifyDown( 0 );
    }
    else
    {
        heapifyUp( n );
    }

    return make_pair( minWeight, minVertex );
}
 
// iPair ==>  Integer Pair
typedef pair<int, int> iPair;
 
// This class represents a directed graph using
// adjacency list representation
class Graph
{
    int V;    // No. of vertices
 
    // In a weighted graph, we need to store vertex
    // and weight pair for every edge
    list< pair<int, int> > *adj;
 
public:
    Graph(int V);  // Constructor
 
    // function to add an edge to graph
    void addEdge(int u, int v, int w);
 
    // prints shortest path from s
    void shortestPath(int src, Heap heap );
};
 
// Allocates memory for adjacency list
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<iPair> [V];
}
 
void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}
 
// Prints shortest paths from src to all other vertices
void Graph::shortestPath(int src, Heap heap )
{
    // Create a priority queue to store vertices that
    // are being preprocessed. This is weird syntax in C++.
    // Refer below link for details of this syntax
    // http://geeksquiz.com/implement-min-heap-using-stl/
    //priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
 
    // Create a vector for distances and initialize all
    // distances as infinite (INF)
    vector<int> dist(V, INF);
 
    // Insert source itself in priority queue and initialize
    // its distance as 0.
    //pq.push(make_pair(0, src));
    heap.insert( 0, src );
    dist[src] = 0;
 
    /* Looping till priority queue becomes empty (or all
      distances are not finalized) */
    while ( !heap.isEmpty() )
    {
        // The first vertex in pair is the minimum distance
        // vertex, extract it from priority queue.
        // vertex label is stored in second of pair (it
        // has to be done this way to keep the vertices
        // sorted distance (distance must be first item
        // in pair)
        //int u = pq.top().second;
        int u = heap.deleteMin().second;
        //pq.pop();
 
        // 'i' is used to get all adjacent vertices of a vertex
        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            // Get vertex label and weight of current adjacent
            // of u.
            int v = (*i).first;
            int weight = (*i).second;
 
            //  If there is shorted path to v through u.
            if (dist[v] > dist[u] + weight)
            {
                // Updating distance of v
                dist[v] = dist[u] + weight;
                heap.insert( dist[ v ], v );
                //pq.push(make_pair(dist[v], v));
            }
        }
    }
 
    // Print shortest distances stored in dist[]
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}
 
// Driver program to test methods of graph class
int main()
{
    // create the graph given in above fugure
    int V = 9;
    Graph g(V);
    Heap heap( 4 );
 
    //  making above shown graph
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);
 
    g.shortestPath(0, heap);
 
    return 0;
}