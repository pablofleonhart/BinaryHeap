#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <cmath>
#include <chrono>

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

    void update( unsigned index, unsigned weight );

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

void Heap::update( unsigned index, unsigned weight )
{
    if ( index > 0 && index < n )
    {
        unsigned curWeight = weights[ index ];
        weights[ index ] = weight;

        if ( curWeight < weight )
        {
            heapifyDown( index );
        }
        else
        {
            heapifyUp( index );
        }
    }
}

pair<int, int> Heap::deleteMin()
{
    int minWeight = weights[ 0 ];
    int minVertex = vertexes[ 0 ];

    //cout << minWeight << endl;

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

typedef pair<int, int> iPair;
 
class Graph
{
    int V;
 
    list< pair<int, int> > *adj;
 
public:
    Graph( int V );
 
    void addEdge( int u, int v, int w );
 
    void shortestPath( int from, int to, Heap heap );
};
 
Graph::Graph( int V )
{
    this->V = V;
    adj = new list<iPair> [ V ];
}
 
void Graph::addEdge( int u, int v, int w )
{
    adj[ u ].push_back( make_pair( v, w ) );
    //adj[ v ].push_back( make_pair( u, w ) );
}
 
void Graph::shortestPath( int from, int to, Heap heap )
{
    vector<int> dist( V, INF );
 
    heap.insert( 0, from );
    dist[ from ] = 0;
    int u, v = -1, weight = -1, stop = 0, get = 0;
 
    while ( !heap.isEmpty() && stop == 0 )
    {
        //heap.printWeights();
        u = heap.deleteMin().second;

        list< pair<int, int> >::iterator i;
        for ( i = adj[ u ].begin(); i != adj[ u ].end(); ++i )
        {
            v = ( *i ).first;
            weight = ( *i ).second;
 
            if ( u == to )
            {
                get = 1;
            }

            if ( dist[ v ] > dist[ u ] + weight )
            {
                dist[ v ] = dist[ u ] + weight;
                heap.insert( dist[ v ], v );
            }

            //cout << "u " << u << " -> " << v << " v " << dist[ v ] << endl;
        }

        if ( to != 0 && get == 1 )
        {
            stop = 1;
            break;
        }
    }

    if ( get == 0 )
    {
        cout << "inf" << endl;
    }
    else
    {
        cout << dist[u] << endl;
    }
}

int main( int argc, char *argv[] )
{
    int from = atoi( argv[ 1 ] );
    int to = atoi( argv[ 2 ] );

    string line = "";

    while ( line.substr( 0, 4 ) != "p sp" )
    {
        getline( cin, line );
    }
 
    stringstream pref( line );
    unsigned n, m;
    string ac;
    pref >> ac >> ac >> n >> m;

    Graph g( n + 1 );

    unsigned i = 0;
    while ( i < m )
    {
        getline( cin, line );

        if ( line.substr( 0, 2 ) == "a " )
        {
            stringstream arc( line );
            cout << line << endl;
            unsigned u, v, w;
            arc >> ac >> u >> v >> w;
            g.addEdge( u, v, w );
            i++;
        }
    }

    cout << "Graph built" << endl;
    
    Heap heap( 4 );

    g.shortestPath( from, to, heap );
 
    return 0;
}
