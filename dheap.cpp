#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <cmath>

using namespace std;

class Heap
{
    int n, k;
    vector<int> weights;
    vector<int> vertexes;
    set< pair<int, int> > idx;

public:
    Heap( int k );

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

int main()
{
	Heap heap( 4 );

	heap.insert( 10, 1 );
	heap.insert( 18, 2 );
	heap.insert( 11, 3 );
	heap.insert( 15, 4 );
	heap.insert( 12, 5 );
	heap.insert( 14, 6 );
	heap.insert( 13, 7 );
	heap.insert( 99, 8 );
	heap.insert( 60, 9 );
	heap.insert( 1, 10 );
	heap.insert( 2, 11 );
	heap.insert( 70, 12 );
	heap.insert( 56, 13 );
	heap.insert( 33, 14 );
	heap.insert( 8, 15 );
	heap.insert( 50, 16 );

	heap.deleteMin();
	heap.printWeights();

	heap.deleteMin();
	heap.printWeights();

	heap.deleteMin();
	heap.printWeights();

	heap.deleteMin();
	heap.printWeights();
	
	heap.deleteMin();
	heap.printWeights();

	heap.deleteMin();
	heap.printWeights();

	return 0;
}
