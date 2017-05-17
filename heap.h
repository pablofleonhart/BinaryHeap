#ifndef HEAP
#define HEAP

#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;

vector<unsigned> swps;
vector<unsigned> ts;
unsigned updateSwps, deleteSwps;


class Heap
{
    int n, k, nswap;
    vector<unsigned> weights;
    vector<unsigned> vertexes;
    set< pair<unsigned, unsigned> > idx;

public:
    Heap( int k );

    void printWeights();

    void insert( unsigned weight, unsigned vertex );

    void update( unsigned index, unsigned weight );

    pair<unsigned, unsigned> deleteMin();

    void heapifyDown( unsigned index );

    void heapifyUp( unsigned index );
};

Heap::Heap( int k )
{
	n = 0;
	this->k = k;
}

void Heap::printWeights()
{
    cout << "Heap:" << endl;
    for ( int i = 0; i < n; i++ )
        cout << weights[ i ] << "(" << vertexes[ i ] << ") ";

    cout << endl;
}

void Heap::heapifyDown( unsigned index )
{
	vector<unsigned> child;

	child.push_back( 0 );
	for ( int i = 1; i <= k; i++ )
	{
		child.push_back( ( ( k * index + i ) < n ) ? ( k * index + i ) : -1 );
	}

	unsigned min_child = -1, min_child_index;

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
			nswap++;
			updateSwps++;
			deleteSwps++;
		}

		index = min_child_index;
		heapifyDown( index );
	}
}

void Heap::heapifyUp( unsigned index )
{
	if ( index > 0 )
	{
		unsigned parent = floor( ( index - 1 ) / k );

		if ( weights[ index ] < weights[ parent ] )
		{
			swap( weights[ index ], weights[ parent ] );
			swap( vertexes[ index ], vertexes[ parent ] );
			nswap++;
			updateSwps++;
			deleteSwps++;
			heapifyUp( parent );
		}
	}
}

void Heap::insert( unsigned weight, unsigned vertex )
{
	nswap = 0;
	weights.push_back( weight );
	vertexes.push_back( vertex );

	n++;

	heapifyUp( n - 1 );	

	unsigned index = log2( vertex );
	swps[ index ] += nswap;
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

pair<unsigned, unsigned> Heap::deleteMin()
{
	unsigned minWeight = weights[ 0 ];
	unsigned minVertex = vertexes[ 0 ];

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

#endif
