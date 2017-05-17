#ifndef HOLLOWHEAP
#define HOLLOWHEAP

#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;

class Node;
class Item;
class HollowHeap;

vector<unsigned> hollowNodes;
Node *fullNodes[ 100000000 ];
Item *items[ 100000000 ];

vector<unsigned> links;
vector<unsigned> times;
unsigned inserts, updates, deletes;

class Item
{
public:
    Node *node;
    unsigned value;

    Item( unsigned v );
};

Item::Item( unsigned v )
{
    value = v;
}

class Node
{
public:
    Item *item;
    Node *nextSibling;
    Node *firstChild;
    Node *extraParent;
    unsigned rank;
    unsigned key;

    Node();
};

Node::Node()
{
    firstChild  = NULL;
    nextSibling = NULL;
    extraParent = NULL;
    rank = 0;
}

class HollowHeap
{
public:
	int lks;
    Node *root;

    HollowHeap();
    bool isEmpty();
    void printNodes();
    Item *findMin();
    void insert( unsigned key, unsigned vertex );
    void meld( Node *node );
    Node *makeNode( unsigned key, Item *e );
    Node *link( Node *v, Node *w );
    void addChild( Node *v, Node *w );
    Node *decreaseKey( unsigned vertex, unsigned key );
    unsigned deleteMin();
    unsigned deleteNode( Item *e );
};

HollowHeap::HollowHeap()
{
    root = NULL;
}

bool HollowHeap::isEmpty()
{
	return root == NULL;
}

void HollowHeap::printNodes()
{
	cout << endl << "##### HollowHeap #####" << endl;
    Node *aux;

    for ( int i = 0; i < 13; i++ )
    {
        if ( items[ i ] != NULL && items[ i ]->node != NULL )
        {
            cout << items[ i ]->node->key << " child: ";
            
            if ( items[ i ]->node->firstChild != NULL )
            {          
            	cout << items[ i ]->node->firstChild->key;
            }
            
            cout << " ## siblings: ";

            aux = items[ i ]->node->nextSibling;

            while ( aux != NULL )
            {
            	cout << aux->key << " ";
            	aux = aux->nextSibling;
            }

            cout << endl;
        }
    }
}

Item *HollowHeap::findMin()
{
    if ( root == NULL )
    {
        return NULL;
    }

    else
    {
        return root->item;
    }
}

void HollowHeap::insert( unsigned key, unsigned vertex )
{
    lks = 0;
    inserts++;
    Item *e = new Item( vertex );

    Node *node = makeNode( key, e );

    if ( root == NULL )
    {
        root = node;
    }
    else
    {
        meld( node );
    }

    
    unsigned index = log2( vertex );
	links[ index ] += lks;
}

void HollowHeap::meld( Node *node )
{
    if ( node == NULL )
    {
        //return root;
    }

    if ( root == NULL )
    {
        //return node;
    }

    link( node, root );
}

Node *HollowHeap::makeNode( unsigned key, Item *e )
{
    Node *node = new Node();
    node->item = e;
    node->key = key;
    e->node = node;

    items[ e->value ] = e;

    return node;
}

Node *HollowHeap::link( Node *v, Node *w )
{
	lks++;
    if ( v->key >= w->key )
    {
        addChild( v, w );
        return w;
    }
    else
    {
        addChild( w, v );
        return v;
    }
}

void HollowHeap::addChild( Node *v, Node *w )
{
    if ( v == root )
    {
        root = w;
    }

    v->nextSibling = w->firstChild;
    w->firstChild = v;
}

Node *HollowHeap::decreaseKey( unsigned vertex, unsigned key )
{
	Item *e = items[ vertex ];

	if ( e == NULL )
	{
		return NULL;
	}

    Node *u = e->node;

    if ( u == NULL )
    {
        return NULL;
    }

    else
    {
        updates++;

        if ( u == root )
        {
            u->key = key;
            return root;
        }

        Node *v = makeNode( key, e );
        u->item = NULL;

        if ( u->rank > 2 )
        {
            v->rank = u->rank - 2;
        }

        if ( key > root->key )
        {
            v->firstChild = u;
            u->extraParent = v;
        }
        else
        {
            u->extraParent = NULL;
        }

        return link( v, root );
    }
}

unsigned HollowHeap::deleteMin()
{
    return deleteNode( findMin() );
}

unsigned HollowHeap::deleteNode( Item *e )
{
    if ( e != NULL )
    {
    	deletes++;
        unsigned value = e->value;       

        e->node->item = NULL;
        e->node->extraParent = NULL;
        e->node = NULL;

        if ( root->item == NULL )
        {
            unsigned maxRank = 0;
            root->nextSibling = NULL;

            while ( root != NULL )
            {                
                Node *w = root->firstChild;
                Node *x = root;
                Node *u;

                root = root->nextSibling;

                while ( w != NULL )
                {
                    u = w;
                    w = w->nextSibling;

                    if ( u->item == NULL )
                    {
                        if ( u->extraParent == NULL )
                        {
                            u->nextSibling = root;
                            root = u;
                        }

                        else
                        {
                            if ( u->extraParent == x )
                            {
                                w = NULL;
                            }

                            else
                            {
                                u->nextSibling = NULL;
                            }

                            u->extraParent = NULL;
                        }
                    }

                    else
                    {
                        while ( fullNodes[ u->rank ] != NULL )
                        {
                            u = link( u, fullNodes[ u->rank ] );
                            fullNodes[ u->rank ] = NULL;

                            u->rank++;
                        }

                        fullNodes[ u->rank ] = u;

                        if ( u->rank > maxRank )
                        {
                            maxRank = u->rank;
                        }
                    }
                }

                delete( x );
            }

            for ( unsigned i = 0; i <= maxRank; i++ )
            {
                if ( fullNodes[ i ] != NULL )
                {
                    if ( root == NULL )
                    {
                        root = fullNodes[ i ];
                    }

                    else
                    {
                        root = link( root, fullNodes[ i ] );
                    }

                    fullNodes[ i ] = NULL;
                }
            }
        }        

        return value;
    }

    else
    {
        return 0;
    }
}

#endif
