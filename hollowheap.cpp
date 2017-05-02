#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;

#define INF 1e8

class Vertex {
public:
    vector<int> n;
    vector<int> w;
    int key;
    int i, prev;

    Vertex() {
        key = INF;
        prev = -1;
    }
};

inline int max( int a, int b )
{
    return a > b ? a : b;
}

template<class Key, class Item>
class Node {
public:
    Key key;
    Item *item;

    Node<Key, Item> *parent, *secondParent;
    Node<Key, Item> *children;
    Node<Key, Item> *next, *prev;
    int num_children;

    int rank;

    Node( Key key, Item *_item );

    bool is_hollow();
};

template<class Key, class Item>
Node<Key, Item>::Node( Key _key, Item *_item )
{
    key = _key;
    item = _item;

    secondParent = parent = NULL;
    prev = next = NULL;
    children = NULL;
    num_children = 0;

    rank = 0;
}

template<class Key, class Item>
bool Node<Key, Item>::is_hollow()
{
    return item == NULL;
}

template<class Key, class Item>
class HollowHeap
{
public:
    int size, maxRank;

    Node<Key, Item> *root;
    map<Item *, Node<Key, Item> *> node_map;
    vector<Node<Key, Item>*> A;

    HollowHeap<Key, Item>();

    Node<Key, Item> *makeHeap();
    Node<Key, Item> *insert( Key k, Item *e );
    Node<Key, Item> *meld( Node<Key, Item> *g );
    Item *findMin();
    Node<Key, Item> *deleteMin();
    Node<Key, Item> *del( Item *item );
    void doRankedLinks( Node<Key, Item> *u );
    void doUnrankedLinks();
    Node<Key, Item> *makeNode( Key k, Item *e );
    Node<Key, Item> *decreaseKey( Key k, Item *item );
    Node<Key, Item> *link( Node<Key, Item> *v, Node<Key, Item> *w );
    void addChild( Node<Key, Item> *v, Node<Key, Item> *w );
};

template<class Key, class Item>
HollowHeap<Key, Item>::HollowHeap()
{
    root = NULL;
    size = 0;
}

template<class Key, class Item>
Node<Key, Item> *HollowHeap<Key, Item>::makeHeap()
{
    return NULL;
}

template<class Key, class Item>
Node<Key, Item> *HollowHeap<Key, Item>::insert( Key k, Item *e )
{
    size++;
    cout << "Inserting.." << k << endl;
    if ( root == NULL )
    {
        root = new Node<Key, Item>( k, e );
        return root;
    }
    else
    {
        return meld( makeNode( k, e ) );
    }
}

template<class Key, class Item>
Node<Key, Item> *HollowHeap<Key, Item>::meld( Node<Key, Item> *g )
{
    if ( g == NULL )
    {
        return root;
    }

    if ( root == NULL )
    {
        return g;
    }

    return link( g, root );
}

template<class Key, class Item>
Item *HollowHeap<Key, Item>::findMin()
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

template<class Key, class Item>
Node<Key, Item> *HollowHeap<Key, Item>::deleteMin()
{
    return del( root->item );
}

template<class Key, class Item>
Node<Key, Item> *HollowHeap<Key, Item>::del( Item *item )
{
    Node<Key, Item> *n = node_map[ item ];
    node_map.erase( node_map.find( item ) );
    size--;

    A.clear();
    A.resize( size );

    cout << n << " " << root << endl;
    if ( n != root )
    {
        return NULL;
    }

    maxRank = 0;

    Node<Key, Item> *cur = root;
    while ( cur != NULL )
    {
        cout << cur->key << endl;
        Node<Key, Item> *w = cur->children;
        Node<Key, Item> *v = cur;
        cur = cur->next;

        while ( w != NULL )
        {
            Node<Key, Item> *u = w;
            w = w->next;

            if ( u->item == NULL )
            {
                if ( u->secondParent == NULL )
                {
                    u->next = cur;
                    cur = u;
                }

                else
                {
                    if ( u->secondParent == v )
                    {
                        w = NULL;
                    }

                    else
                    {
                        u->next = NULL;
                    }

                    u->secondParent = NULL;
                }
            }

            else
            {
                doRankedLinks( u );
            }
        }

        delete v;
    }

    doUnrankedLinks();

    return root;
}

template<class Key, class Item>
void HollowHeap<Key, Item>::doRankedLinks( Node<Key, Item> *u )
{
    while ( A[ u->rank ] != NULL )
    {
        u = link( u, A[ u->rank ] );
        A[ u->rank ] = NULL;
        u->rank = u->rank + 1;
    }

    A[ u->rank ] = u;

    if ( u->rank > maxRank )
    {
        maxRank = u->rank;
    }
}

template<class Key, class Item>
void HollowHeap<Key, Item>::doUnrankedLinks()
{
    for ( int i = 0; i < maxRank; i++ )
    {
        if ( A[ i ] != NULL )
        {
            if ( root == NULL )
            {
                root = A[ i ];
            }

            else
            {
                root = link( root, A[ i ] );
            }

            A[ i ] = NULL;
        }
    }
}

template<class Key, class Item>
Node<Key, Item> *HollowHeap<Key, Item>::makeNode( Key k, Item *e )
{
    Node<Key, Item> *node = new Node<Key, Item>( k, e );
    node->item = e;
    //e->item = node;
    node->children = NULL;
    node->next = NULL;
    node->secondParent = NULL;
    node->key = k;
    node->rank = 0;
    node_map[ e ] = node;
    
    return node;
}

template<class Key, class Item>
Node<Key, Item> *HollowHeap<Key, Item>::decreaseKey( Key k, Item *item )
{
    Node<Key, Item> *u = node_map[ item ];

    if ( u->key <= k )
        return;

    if ( u == root )
    {
        root->key = k;
        return root;
    }

    else
    {
        Node<Key, Item> *v( k, item );
        v->rank = max( 0, u->rank - 2 );
        u->item = NULL;
        node_map[ item ] = v;

        if( root->key < v->key )
        {
            addChild( v, u );
        }
        else
        {
            root = v;        
        }

        return link( v, root );
    }
}

template<class Key, class Item>
Node<Key, Item> *HollowHeap<Key, Item>::link( Node<Key, Item> *v, Node<Key, Item> *w )
{
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

template<class Key, class Item>
void HollowHeap<Key, Item>::addChild( Node<Key, Item> *v, Node<Key, Item> *w )
{
    v->next = w->children;
    w->children = v;
}

void print_graph(Vertex *g, int N, bool no_weight) {
    for(int i = 0; i < N; i++) {
        printf("    ");
        for(int j = 0; j < N; j++) {
            int w = -1;
            for(int k = 0; k < int(g[i].n.size()); k++) {
                if(g[i].n[k] == j) {
                    if(no_weight)
                        w = 88;
                    else
                        w = g[i].w[k];
                }
            }
            if(w > 0)
                printf(" %2d ", w);
            else
                printf(" -- ");
        }
        printf("\n");
    }
}

void dfs(int v, Vertex *g, std::vector<int> &visited) {
    visited[v] = 1;
    for(int i = 0; i < int(g[v].n.size()); i++) {
        if(!visited[g[v].n[i]])
            dfs(g[v].n[i], g, visited);
    }
}

int main()
{
    int N = 5;
    int E = N * sqrt(N);
    Vertex *g = new Vertex[N];

    /*std::set<std::pair<int, int> > edges;

gen_graph:
    edges.clear();
    for(int i = 0; i < N; i++) {
        g[i].n.clear();
        g[i].i = i;
    }
    g[0].key = 0;

    for(int i = 0; i < E; i++) {
        int u = rand() % N, v = rand() % N;
        if(u == v)
            continue;

        if(u > v) {
            int t = u;
            u = v;
            v = t;
        }

        int w = 1 + rand() % 10;

        if(edges.find(std::make_pair(u, v)) != edges.end())
            continue;

        edges.insert(std::make_pair(u, v));

        g[u].n.push_back(v);
        g[v].n.push_back(u);

        g[u].w.push_back(w);
        g[v].w.push_back(w);
    }

    std::vector<int> visited(N, 0);
    dfs(0, g, visited);

    int flag = 1;
    for(int i = 0; i < N; i++) {
        if(visited[i] == 0)
            flag = 0;
    }

    if(!flag) {
        goto gen_graph;
    }*/

    HollowHeap<int, Vertex> hh;
    
    for(int i = 0; i < N; i++)
        hh.insert( i, g+i );

    //print_graph( g, N, true );

    Vertex *u = hh.findMin();
    cout << u->key << endl;
    hh.del(u);
    cout << hh.root->key << endl;

    return 0;
}