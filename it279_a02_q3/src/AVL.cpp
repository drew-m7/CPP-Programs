#include "AVL.h"
#include <algorithm>
#include <iostream>
using namespace std;

template <typename Comparable>
AvlTree<Comparable>::AvlTree() : root{nullptr}
{
}

template <typename Comparable>
AvlTree<Comparable>::AvlTree(const AvlTree &rhs) : root{nullptr}
{
    root = clone(rhs.root);
}

template <typename Comparable>
AvlTree<Comparable>::AvlTree(AvlTree &&rhs) : root{rhs.root}
{
    rhs.root = nullptr;
}

template <typename Comparable>
AvlTree<Comparable>::~AvlTree()
{
    makeEmpty();
}

/**
 * Test if the tree is logically empty.
 * Return true if empty, false otherwise.
 */
template <typename Comparable>
bool AvlTree<Comparable>::isEmpty() const
{
    return root == nullptr;
}

/**
 * Print the tree contents in sorted order.
 */
template <typename Comparable>
void AvlTree<Comparable>::printTree() const
{
    if (isEmpty())
        cout << "Empty tree" << endl;
    else
        printTree(root);
}

/**
 * Make the tree logically empty.
 */
template <typename Comparable>
void AvlTree<Comparable>::makeEmpty()
{
    makeEmpty(root);
}

/**
 * Internal method to make subtree empty.
 */
template <typename Comparable>
void AvlTree<Comparable>::makeEmpty(AvlTree<Comparable>::AvlNode *&t)
{
    if (t != nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

/**
 * Internal method to print a subtree rooted at t in sorted order.
 */
template <typename Comparable>
void AvlTree<Comparable>::printTree(AvlNode *t) const
{
    if (t != nullptr)
    {
        cout << t->element << "  ";
        printTree(t->left);
        printTree(t->right);
    }
}

/**
 * Internal method to clone subtree.
 */
template <typename Comparable>
typename AvlTree<Comparable>::AvlNode *AvlTree<Comparable>::clone(AvlNode *t) const
{
    if (t == nullptr)
        return nullptr;
    else
        return new AvlNode{t->element, clone(t->left), clone(t->right), t->height};
}
// Avl manipulations
/**
 * Return the height of node t or -1 if nullptr.
 */
template <typename Comparable>
int AvlTree<Comparable>::height(AvlNode *t) const
{
    return t == nullptr ? -1 : t->height;
}

template <typename Comparable>
int AvlTree<Comparable>::max(int lhs, int rhs) const
{
    return lhs > rhs ? lhs : rhs;
}

// Get Balance factor of node N
template <typename Comparable>
int AvlTree<Comparable>::getBalance(AvlNode *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// a)	(10 pts) Complete findMax and findMin methods (both public and private). 
// b)	(15 pts) Complete rightRotate method
// c)	(15 pts) Complete leftRotate method
// d)	(40 pts) Complete balance method, must have the function of outputting each of the four cases to handle unbalance and the node that is used as root to rotate. For example:

// left left case: rightRotate (50)
// left left case: rightRotate (20)
// left right case: leftRotate (40), rightRotate(50)

// right left case: rightRotate (50), leftRotate(45)

// e)	(10 pts) Complete insert method 
// f)	(10 pts) Complete remove method

// Insert
template <typename Comparable>
void AvlTree<Comparable>::insert(const Comparable &x){
    insert(x, root);
}

template <typename Comparable>
void AvlTree<Comparable>::insert(const Comparable &x, AvlNode *&t){
    if (t == nullptr){
        t = new AvlNode(x, nullptr, nullptr);
    }
    else if (x < t->element){
        insert(x, t->left);
    }
    else if (x > t->element){
        insert(x, t->right);
    }
    balance(t);
    t->height = max(height(t->left), height(t->right)) + 1;
}

// Remove
template <typename Comparable>
void AvlTree<Comparable>::remove(const Comparable &x){
    remove(x, root);
}

template <typename Comparable>
void AvlTree<Comparable>::remove(const Comparable &x, AvlNode *&t){
    if (t == nullptr){
        return;
    }
    else if (x < t->element){
        remove(x, t->left);
    }
    else if (x > t->element){
        remove(x, t->right);
    }
    else if(t->left != nullptr && t->right != nullptr)
    {
        t->element = findMin(t->right)->element;
        remove(t->element, t->right);
    }
    else
    {
        AvlNode *old = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete old;
    }
    balance(t);
}

// Find min
template <typename Comparable>
typename AvlTree<Comparable>::AvlNode *AvlTree<Comparable>::findMin() const{
    if (isEmpty()){
        cout << "\nCan't find node" << endl;
        throw UnderflowException{};
    }
    return findMin(root);
}

template <typename Comparable>
typename AvlTree<Comparable>::AvlNode *AvlTree<Comparable>::findMin(AvlNode *t) const{
    if (t == nullptr){
        return nullptr;
    }
    else if (t->left == nullptr){
        return t;
    }
    return findMin(t->left);
}

// Find max
template <typename Comparable>
typename AvlTree<Comparable>::AvlNode *AvlTree<Comparable>::findMax() const{
    if (isEmpty()){
        cout << "\nCan't find node" << endl;
        throw UnderflowException{};
    }
    return findMax(root);
}

template <typename Comparable>
typename AvlTree<Comparable>::AvlNode *AvlTree<Comparable>::findMax(AvlNode *t) const{
    if (t == nullptr){
        return nullptr;
    }
    else if (t->right == nullptr){
        return t;
    }
    return findMax(t->right);
}

// Right rotate
template <typename Comparable>
void AvlTree<Comparable>::rightRotate(AvlNode *&y){
    AvlNode *x = y->left;
    AvlNode *SubTree2 = x->right;
    x->right = y;
    y->left = SubTree2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    y=x;
}

// Left rotate
template <typename Comparable>
void AvlTree<Comparable>::leftRotate(AvlNode *&x){
    AvlNode *y = x->right;
    AvlNode *SubTree2 = y->left;
    y->left = x;
    x->right = SubTree2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    x=y;
}

// Balance
template <typename Comparable>
void AvlTree<Comparable>::balance(AvlNode *&t){
    if(getBalance(t) > 1 && getBalance(t->left) >= 0){
        cout << "left left case:rightRotate(" << t->element << ")" << endl;
        rightRotate(t);
    }
    else if(getBalance(t) < -1 && getBalance(t->right) <= 0){
        cout << "right right case:leftRotate(" << t->element << ")" << endl;
        leftRotate(t);
    }
    else if(getBalance(t) > 1 && getBalance(t->left) < 0){
        cout << "left right case:leftRotate(" << t->left->element << ") ,rightRotate(" << t->element << ")" << endl;
        leftRotate(t->left);
        rightRotate(t);
    }
    else if(getBalance(t) < -1 && getBalance(t->right) > 0){
        cout << "right left case:rightRotate(" << t->right->element << ") ,leftRotate(" << t->element << ")" << endl;
        rightRotate(t->right);
        leftRotate(t);
    }
}






