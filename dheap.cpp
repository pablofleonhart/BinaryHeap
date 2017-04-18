#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <cmath>

using namespace std;

void heapifyDown( vector<int> &nodes, int len, int index, int k )
{
	vector<int> child;

	child.push_back( 0 );
	for ( int i = 1; i <= k; i++ )
	{
		child.push_back( ( ( k * index + i ) < len ) ? ( k * index + i ) : -1 );
	}

	int min_child = -1, min_child_index;

	for ( int i = 1; i <= k; i++ )
	{
		if ( child[ i ] != -1 && ( nodes[ child[ i ] ] < min_child || min_child == -1 ) )
		{
			min_child_index = child[ i ];
			min_child = nodes[ child[ i ] ];
		}
	}

	if ( min_child != -1 )
	{
		if ( nodes[ index ] > nodes[ min_child_index ] )
		{
			swap( nodes[ index ], nodes[ min_child_index ] );
		}

		index = min_child_index;
		heapifyDown( nodes, len, index, k );
	}
}

void heapifyUp( vector<int> &nodes, int index, int k )
{
	if ( index > 0 )
	{
		int parent = floor( ( index - 1 ) / k );

		if ( nodes[ index ] < nodes[ parent ] )
		{
			swap( nodes[ index ], nodes[ parent ] );
			heapifyUp( nodes, parent, k );
		}
	}
}

void insert( vector<int> &nodes, int* n, int k, int elem )
{
	nodes.push_back( elem );

	*n = *n + 1;

	heapifyUp( nodes, *n - 1, k );	
}

int deleteMin( vector<int> &nodes, int* n, int k )
{
	int min = nodes[ 0 ];

	nodes[ 0 ] = nodes[ *n - 1 ];

	nodes.pop_back();

	*n = *n - 1;

	if ( nodes[ 0 ] > min )
	{
		heapifyDown( nodes, *n, 0, k );
	}
	else
	{
		heapifyUp( nodes, *n, k );
	}

	return min;
}

int main()
{
	vector<int> nodes;
	int n = 0;
	int k = 4;

	insert( nodes, &n, k, 10 );
	insert( nodes, &n, k, 18 );
	insert( nodes, &n, k, 11 );
	insert( nodes, &n, k, 15 );
	insert( nodes, &n, k, 12 );
	insert( nodes, &n, k, 14 );
	insert( nodes, &n, k, 13 );
	insert( nodes, &n, k, 99 );
	insert( nodes, &n, k, 60 );
	insert( nodes, &n, k, 1 );
	insert( nodes, &n, k, 2 );
	insert( nodes, &n, k, 70 );
	insert( nodes, &n, k, 56 );
	insert( nodes, &n, k, 33 );
	insert( nodes, &n, k, 8 );

	printf( "\n\nHeap after insertion of 8: \n" );
	for ( int i = 0; i < n; i++ )
		printf( "%d ", nodes[i] );

	printf( "\n\nExtracted min is %d", deleteMin( nodes, &n, k ) );
	printf( "\n\nHeap after extract min: \n" );
	for ( int i = 0; i < n; i++ )
		printf( "%d ", nodes[i] );

	printf( "\n\nExtracted min is %d", deleteMin( nodes, &n, k ) );
	printf( "\n\nHeap after extract min: \n" );
	for ( int i = 0; i < n; i++ )
		printf( "%d ", nodes[i] );

	insert( nodes, &n, k, 50 );

	printf( "\n\nHeap after insertion of 50: \n" );
	for ( int i = 0; i < n; i++ )
		printf( "%d ", nodes[i] );

	printf( "\n\nExtracted min is %d", deleteMin( nodes, &n, k ) );
	printf( "\n\nHeap after extract min: \n" );
	for ( int i = 0; i < n; i++ )
		printf( "%d ", nodes[i] );

	printf( "\n\nExtracted min is %d", deleteMin( nodes, &n, k ) );
	printf( "\n\nHeap after extract min: \n" );
	for ( int i = 0; i < n; i++ )
		printf( "%d ", nodes[i] );
	
	printf( "\n\nExtracted min is %d", deleteMin( nodes, &n, k ) );
	printf( "\n\nHeap after extract min: \n" );
	for ( int i = 0; i < n; i++ )
		printf( "%d ", nodes[i] );

	printf( "\n\nExtracted min is %d", deleteMin( nodes, &n, k ) );
	printf( "\n\nHeap after extract min: \n" );
	for ( int i = 0; i < n; i++ )
		printf( "%d ", nodes[i] );

	return 0;
}
