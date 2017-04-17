#include<bits/stdc++.h>
using namespace std;

void restoreDown( int arr[], int ver[], int len, int index, int k )
{
	int child[k+1];

	while (1)
	{
		for ( int i = 1; i <= k; i++ )
			child[i] = ( ( k * index + i ) < len ) ? ( k * index + i ) : 100000;

		int max_child = 100000, max_child_index;

		for ( int i = 1; i <= k; i++ )
		{
			if ( child[i] != 100000 && arr[child[i]] < max_child )
			{
				max_child_index = child[i];
				max_child = arr[child[i]];
			}
		}

		if ( max_child == 100000 )
			break;

		if ( arr[index] > arr[max_child_index] )
		{
			swap( arr[index], arr[max_child_index] );
			swap( ver[index], ver[max_child_index] );
		}

		index = max_child_index;
	}
}

void restoreUp( int arr[], int ver[], int index, int k )
{
	int parent = (index-1)/k;

	while ( parent >= 0 )
	{
		if ( arr[index] < arr[parent] )
		{
			swap( arr[index], arr[parent] );
			swap( ver[index], ver[parent] );
			index = parent;
			parent = ( index -1 )/k;
		}

		else
			break;
	}
}

void buildHeap( int arr[], int ver[], int n, int k )
{
	for ( int i = (n-1)/k; i >= 0; i-- )
		restoreDown( arr, ver, n, i, k );
}

void insert( int arr[], int ver[], int* n, int k, int elem, int weight )
{
	arr[*n] = weight;
	ver[*n] = elem;

	*n = *n+1;

	restoreUp( arr, ver, *n-1, k );
}

int getMin( int arr[], int ver[], int* n, int k )
{
	int min = arr[0];

	arr[0] = arr[*n-1];
	ver[0] = ver[*n-1];

	*n = *n-1;

	restoreDown( arr, ver, *n, 0, k );

	return min;
}

int main()
{
	const int capacity = 20;
	int arr[ capacity ] = { 10, 18, 11, 15, 12, 14, 13, 99, 60, 1, 2, 70, 56, 33 };
	int ver[ capacity ] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
	int n = 14;
	int k = 3;

	buildHeap( arr, ver, n, k );

	printf( "Built Heap : \n" );
	for ( int i = 0; i < n; i++ )
		printf( "%d ", arr[i] );

	int element = 8;
	insert( arr, ver, &n, k, 15, element );

	printf( "\n\nHeap after insertion of %d: \n", element );
	for ( int i = 0; i < n; i++ )
		printf( "%d ", arr[i] );

	printf( "\n\nExtracted min is %d", getMin( arr, ver, &n, k ) );
	printf( "\n\nExtracted min is %d", getMin( arr, ver, &n, k ) );
	printf( "\n\nExtracted min is %d", getMin( arr, ver, &n, k ) );
	printf( "\n\nExtracted min is %d", getMin( arr, ver, &n, k ) );

	printf( "\n\nHeap after extract min: \n" );
	for ( int i = 0; i < n; i++ )
	{
		printf( "(%d)%d ", ver[i], arr[i] );
	}

	return 0;
}
