#include "SplayTree.h"
#include "dsexceptions.h"
#include <iostream>
#include <string>

using namespace std;

template <typename Comparable>
SplayTree<Comparable>::SplayTree()
{
    nullNode = new BinaryNode;
    nullNode->left = nullNode->right = nullNode;
    root = nullNode;
}

template <typename Comparable>
SplayTree<Comparable>::SplayTree(const SplayTree &rhs)
{
    nullNode = new BinaryNode;
    nullNode->left = nullNode->right = nullNode;
    root = clone(rhs.root);
}

template <typename Comparable>
SplayTree<Comparable>::SplayTree(SplayTree &&rhs) : root{rhs.root}, nullNode{rhs.nullNode}
{
    rhs.root = nullptr;
    rhs.nullNode = nullptr;
}

template <typename Comparable>
SplayTree<Comparable>::~SplayTree()
{
    makeEmpty();
    delete nullNode;
}

template <typename Comparable>
bool SplayTree<Comparable>::isEmpty() const
{
    return root == nullNode;
}

template <typename Comparable>
void SplayTree<Comparable>::printTree(BinaryNode *t) const
{
    if (t != t->left)
    {
        cout << t->element << "  ";
        printTree(t->left);
        printTree(t->right);
    }
}

template <typename Comparable>
void SplayTree<Comparable>::printTree() const
{
    if (isEmpty())
        cout << "Empty tree" << endl;
    else
        printTree(root);
}

template <typename Comparable>
void SplayTree<Comparable>::makeEmpty()
{
    while (!isEmpty())
    {
        findMax(); // Splay max item to root
        remove(root->element);
    }
}

// If the tree is empty, return false
// otherwise, splay the node with element x or the node that
// is last accessed in the search process to the root
// Check whether the root element is equal x
template <typename Comparable>
bool SplayTree<Comparable>::search(const Comparable &x)
{
    if (isEmpty())
        return false;
    splay(x, root);

    return root->element == x;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Help code
// Make a new node with x:

// BinaryNode *newNode = nullNode;
// newNode = new BinaryNode;
// newNode->left = newNode->right = nullNode;
// newNode->element = x;

// Declare a new node or a new empty tree
// BinaryNode *newNode = nullNode;
// BinaryNode *newTree = nullNode;

///////////////////////////////////////////////////////////////////////////////////////////////
//   Find the smallest item in the tree.
//   Not the most efficient implementation (uses two passes), but has correct amortized behavior.
//   A good alternative is to first call find with parameter smaller than any item in the tree, then call findMin.
//   Return the smallest item or throw UnderflowException if empty.
//   Note: you need to splay the min node to the root
template <typename Comparable>
const Comparable &SplayTree<Comparable>::findMin()
{
    if( isEmpty( ) )
        throw UnderflowException{};
    
    BinaryNode *ptr = root;

    while( ptr->left != nullNode )
        ptr = ptr->left;

    splay( ptr->element, root );
    return ptr->element;
}

// Find the largest item in the tree.
// Not the most efficient implementation (uses two passes), but has correct amortized behavior.
// A good alternative is to first call find with parameter larger than any item in the tree, then call findMax.
// Return the largest item or throw UnderflowException if empty.
// Note: you need to splay the max node to the root
template <typename Comparable>
const Comparable &SplayTree<Comparable>::findMax()
{
    if( isEmpty( ) )
        throw UnderflowException{};

    BinaryNode *ptr = root;

    while( ptr->right != nullNode )
        ptr = ptr->right;

    splay( ptr->element, root );
    return ptr->element;
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
template <typename Comparable>
void SplayTree<Comparable>::rightRotate(BinaryNode *&x)
{
    BinaryNode *y = x->left;
    x->left = y->right;
    y->right = x;
    x=y;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
template <typename Comparable>
void SplayTree<Comparable>::leftRotate(BinaryNode *&x)
{
    BinaryNode *y = x->right;
    x->right = y->left;
    y->left = x;
    x=y;
}

//  Internal method to perform a top-down splay.
//  The last accessed node becomes the new root.
//  The splay tree code depends on the accessed item going to the root.
//  t is the root of the subtree to splay.
template <typename Comparable>
void SplayTree<Comparable>::splay(const Comparable &x, BinaryNode *&t)
{
    BinaryNode *leftTreeMax, *rightTreeMin;
    static BinaryNode header;

    header.left = header.right = nullNode;
    leftTreeMax = rightTreeMin = &header;

    nullNode->element = x;

    for( ; ; )
        if( x < t->element )
        {
            if( x < t->left->element )
                rightRotate( t );
            if( t->left == nullNode )
                break;
            // Link Right 
            rightTreeMin->left = t;
            rightTreeMin = t;
            t = t->left;
        }
        else if( t->element < x )
        {
            if( t->right->element < x )
                leftRotate( t );
            if( t->right == nullNode )
                break;
            // Link Left
            leftTreeMax->right = t;
            leftTreeMax = t;
            t = t->right;
        }
        else
            break;

    leftTreeMax->right = t->left;
    rightTreeMin->left = t->right;
    t->left = header.right;
    t->right = header.left;
}

// Function to insert a new element x in splay tree
template <typename Comparable>
void SplayTree<Comparable>::insert(const Comparable &x)
{
    static BinaryNode *newNode = nullNode;

    if( newNode == nullNode )
        newNode = new BinaryNode;
    newNode->element = x;

    if( root == nullNode )
    {
        newNode->left = newNode->right = nullNode;
        root = newNode;
    }
    else
    {
        splay( x, root );
        if( x < root->element )
        {
            newNode->left = root->left;
            newNode->right = root;
            root->left = nullNode;
            root = newNode;
        }
        else
        if( root->element < x )
        {
            newNode->right = root->right;
            newNode->left = root;
            root->right = nullNode;
            root = newNode;
        }
        else
            return;
    }
    newNode = nullNode;
}

// The remove function for Splay tree, removing a node with element equal to x.
// Note that this function will update the root of Splay Tree after removing/searching the node
template <typename Comparable>
void SplayTree<Comparable>::remove(const Comparable &x)
{
    BinaryNode *newTree;

    // If x is found, it will be at the root
    splay( x, root );
    if( root->element != x )
        return;   // Item not found so do nothing

    if( root->left == nullNode )
        newTree = root->right;
    else
    {
        // Find the maximum in the left subtree, splay it to the root and then attach right child
        newTree = root->left;
        splay( x, newTree );
        newTree->right = root->right;
    }
    delete root;
    root = newTree;
}
