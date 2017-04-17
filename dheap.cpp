#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <cmath>

using namespace std;

void heapifyDown( int arr[], int len, int index, int k )
{
	int child[ k+1 ];

	for ( int i = 1; i <= k; i++ )
	{
		child[i] = ( ( k * index + i ) < len ) ? ( k * index + i ) : -1;
	}

	int min_child = -1, min_child_index;

	for ( int i = 1; i <= k; i++ )
	{
		if ( child[ i ] != -1 && ( arr[ child[ i ] ] < min_child || min_child == -1 ) )
		{
			min_child_index = child[ i ];
			min_child = arr[ child[ i ] ];
		}
	}

	if ( min_child != -1 )
	{
		if ( arr[ index ] > arr[ min_child_index ] )
		{
			swap( arr[ index ], arr[ min_child_index ] );
		}

		index = min_child_index;
		heapifyDown( arr, len, index, k );
	}
}

void heapifyUp( int arr[], int index, int k )
{
	if ( index > 0 )
	{
		int parent = floor( ( index - 1 ) / k );

		if ( arr[ index ] < arr[ parent ] )
		{
			swap( arr[ index ], arr[ parent ] );
			heapifyUp( arr, parent, k );
		}
	}
}

void insert( int arr[], int* n, int k, int elem )
{
	arr[*n] = elem;

	*n = *n+1;

	heapifyUp( arr, *n-1, k );

	for ( int i = 0; i < *n; i++ )
		printf( "%d ", arr[i] );

	printf( "\n" );
}

int deleteMin( int arr[], int* n, int k )
{
	int min = arr[ 0 ];

	arr[ 0 ] = arr[ *n - 1 ];

	*n = *n - 1;

	if ( arr[ 0 ] > min )
	{
		heapifyDown( arr, *n, 0, k );
	}
	else
	{
		heapifyUp( arr, *n, k );
	}

	return min;
}

int main()
{
	const int capacity = 100;
	int arr[ capacity ];
	int n = 0;
	int k = 4;

	insert( arr, &n, k, 10 );
	insert( arr, &n, k, 18 );
	insert( arr, &n, k, 11 );
	insert( arr, &n, k, 15 );
	insert( arr, &n, k, 12 );
	insert( arr, &n, k, 14 );
	insert( arr, &n, k, 13 );
	insert( arr, &n, k, 99 );
	insert( arr, &n, k, 60 );
	insert( arr, &n, k, 1 );
	insert( arr, &n, k, 2 );
	insert( arr, &n, k, 70 );
	insert( arr, &n, k, 56 );
	insert( arr, &n, k, 33 );

	//buildHeap( arr, n, k );

	printf( "Built Heap : \n" );
	for ( int i = 0; i < n; i++ )
		printf( "%d ", arr[i] );

	int element = 8;
	insert( arr, &n, k, element );

	printf( "\n\nHeap after insertion of %d: \n", element );
	for ( int i = 0; i < n; i++ )
		printf( "%d ", arr[i] );

	printf( "\n\nExtracted max is %d", deleteMin( arr, &n, k ) );
	printf( "\n\nHeap after extract max: \n" );
	for ( int i = 0; i < n; i++ )
		printf( "%d ", arr[i] );
	printf( "\n\nExtracted max is %d", deleteMin( arr, &n, k ) );
	printf( "\n\nHeap after extract max: \n" );
	for ( int i = 0; i < n; i++ )
		printf( "%d ", arr[i] );
	printf( "\n\nExtracted max is %d", deleteMin( arr, &n, k ) );
	printf( "\n\nHeap after extract max: \n" );
	for ( int i = 0; i < n; i++ )
		printf( "%d ", arr[i] );
	printf( "\n\nExtracted max is %d", deleteMin( arr, &n, k ) );
	printf( "\n\nHeap after extract max: \n" );
	for ( int i = 0; i < n; i++ )
		printf( "%d ", arr[i] );

	insert( arr, &n, k, 50 );	
	printf( "\n\nExtracted max is %d", deleteMin( arr, &n, k ) );
	printf( "\n\nHeap after extract max: \n" );
	for ( int i = 0; i < n; i++ )
		printf( "%d ", arr[i] );
	printf( "\n\nExtracted max is %d", deleteMin( arr, &n, k ) );
	printf( "\n\nHeap after extract max: \n" );
	for ( int i = 0; i < n; i++ )
		printf( "%d ", arr[i] );
	printf( "\n\nExtracted max is %d", deleteMin( arr, &n, k ) );

	printf( "\n\nHeap after extract max: \n" );
	for ( int i = 0; i < n; i++ )
		printf( "%d ", arr[i] );

	return 0;
}
