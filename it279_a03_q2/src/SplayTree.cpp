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
    nullNode->value = 0;
    root = nullNode;
}

template <typename Comparable>
SplayTree<Comparable>::SplayTree(const SplayTree &rhs)
{
    nullNode = new BinaryNode;
    nullNode->left = nullNode->right = nullNode;
    nullNode->value = 0;
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

template <typename Comparable>
void SplayTree<Comparable>::printTree(BinaryNode *t) const
{
    if (t != t->left)
    {
        cout << "(" << t->element << "," << t->value << ")  ";
        printTree(t->left);
        printTree(t->right);
    }
}

// If the tree is empty, return false
// otherwise, splay the node with element x or the node that
// is last accessed in the search process to the root
// Check whether the root element is equal x
// In the case of a successful search, splaying
// should occur from the found node up to the root. If search fails, splaying should start at the last
// node visited before the failure is detected.
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
// newNode->value = 1;

// Declare a new node or a new empty tree
// BinaryNode *newNode = nullNode;
// BinaryNode *newTree = nullNode;

///////////////////////////////////////////////////////////////////////////////////////////////
// Copy and paste you developed methods in q1 for the following five methods
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

///////////////////////////////////////////////////////////////////////////////////////////////
// Copy and paste you developed methods in q1, update the following two methods
///////////////////////////////////////////////////////////////////////////////////////////////

// In the method insert(const Comparable &x), if there is no node in the tree with the
// element == x, this node should be inserted and the value field should be set to 1, and theSize
// will increase 1. Splaying should occur starting at the inserted node. If there is already a node in
// the tree with the element == x, the value field of that node is incremented by 1 and splaying
// occurs as for a successful search. 

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
        theSize = 1;
        newNode->value = 1;
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
            root->value = 1;
            theSize++;
        }
        else
        if( root->element < x )
        {
            newNode->right = root->right;
            newNode->left = root;
            root->right = nullNode;
            root = newNode;
            root->value = 1;
            theSize++;
        }
        else
        {
            root->value++;
            return;
        }
            
    }
    newNode = nullNode;
}

// In the method remove(const Comparable &x), if there is no node with element == x, the
// value 0 is returned and splaying proceed is the same as the remove method in q1 (you don’t
// need to update your code). If the node with element == x is in the tree, theSize will decrease 1,
// the node’s value field is returned, the node is deleted and the splaying process is the same as
// q1. 

// The remove function for Splay tree, removing a node with element equal to x.
// Note that this function will update the root of Splay Tree after removing/searching the node
template <typename Comparable>
int SplayTree<Comparable>::remove(const Comparable &x)
{
     BinaryNode *newTree;
     int val;

    // If x is found, it will be at the root
    splay( x, root );
    if( root->element != x )
        return 0;   // Item not found so do nothing
    if(root->element == x)
    {
        theSize--;
    }

    if( root->left == nullNode )
    {
        newTree = root->right;
        val = root->value;

    }
    else
    {
        // Find the maximum in the left subtree, splay it to the root and then attach right child
        newTree = root->left;
        splay( x, newTree );
        newTree->right = root->right;
        val = root->value;
    }
    delete root;
    root = newTree;
    return val;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Complete the size method
///////////////////////////////////////////////////////////////////////////////////////////////
template <typename Comparable>
int SplayTree<Comparable>::size() const
{
    return theSize;
}
