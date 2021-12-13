#include "BST.h"
#include <algorithm>
#include <iostream>
using namespace std;

template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree() : root{nullptr}
{
}

/**
 * Copy constructor
 */
template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree &rhs) : root{nullptr}
{
    root = clone(rhs.root);
}

/**
 * Move constructor
 */
template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(BinarySearchTree &&rhs) : root{rhs.root}
{
    rhs.root = nullptr;
}

/**
 * Internal method to clone subtree.
 */
template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::clone(BinaryNode *t) const
{
    if (t == nullptr)
        return nullptr;
    else
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
};

/**
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable &x, BinaryNode *&t)
{
    if (t == nullptr)
        t = new BinaryNode{x, nullptr, nullptr};
    else if (x < t->element)
        insert(x, t->left);
    else if (t->element < x)
        insert(x, t->right);
    else
        ; // Duplicate; do nothing
}

/**
 * Remove x from the tree. Nothing is done if x is not found.
 */
template <typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable &x)
{
    remove(x, root);
}

/**
 * Find the smallest item in the tree.
 * Throw UnderflowException if empty.
 */
template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::findMin() const
{
    if (isEmpty())
    {
        cout << "\nCannot find the node" << endl;
        throw UnderflowException{};
    }
    return findMin(root);
}
/**
 * Internal method to find the smallest item in a subtree t.
 * Return node containing the smallest item.
 */
template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::findMin(BinaryNode *t) const
{
    if (t == nullptr)
    {
        return nullptr;
    }
    if (t->left == nullptr)
        return t;

    return findMin(t->left);
}

/**
 * Find the largest item in the tree.
 * Throw UnderflowException if empty.
 */
template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::findMax() const
{
    if (isEmpty())
    {
        cout << "\nCannot find the node" << endl;
        throw UnderflowException{};
    }
    return findMax(root);
}

/**
 * Internal method to find the largest item in a subtree t.
 * Return node containing the largest item.
 */
template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::findMax(BinaryNode *t) const
{
    if(t != nullptr)
    while(t->right != nullptr)
        t = t->right;
    return t;
}

/**
 * Insert x into the tree; duplicates are ignored.
 */
template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable &x)
{
    insert(x, root);
}

/**
 * Internal method to remove from a subtree.
 * x is the item to remove.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
template <typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable &x, BinaryNode *&t)
{
    if (t == nullptr)
        return; // Item was not found, nothing to do
    if(x < t->element)
        remove(x, t->left);
    else if(t->element < x)
        remove(x, t->right);
    else if(t->left != nullptr && t->right != nullptr)
    {
        t->element = findMin(t->right)->element;
        remove(t->element, t->right);
    }
    else
    {
        BinaryNode *old = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete old;
    }
}

/**
 * Destructor for the tree
 */
template <typename Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree()
{
    makeEmpty();
}
template <typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty()
{
    makeEmpty(root);
}
/**
 * Internal method to make subtree empty.
 */
template <typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty(BinaryNode *&t)
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
  * Print the tree contents in sorted order.
  */
template <typename Comparable>
void BinarySearchTree<Comparable>::printTree() const
{
    if (isEmpty())
        cout << "Empty tree" << endl;
    else
        printTree(root, cout);
    cout << endl;
};

/**
 * Internal method to print a subtree rooted at t in sorted order.
 */
template <typename Comparable>
void BinarySearchTree<Comparable>::printTree(BinarySearchTree<Comparable>::BinaryNode *t, ostream &out) const
{
    if (t != nullptr)
    {
        cout << t->element << " ";      
		printTree(t->left, out);

        printTree(t->right, out);
    }
}

/**
 * Test if the tree is logically empty.
 * Return true if empty, false otherwise.
 */
template <typename Comparable>
bool BinarySearchTree<Comparable>::isEmpty() const
{
    return root == nullptr;
}

//Add code to implement the functions listed in the header file
// public:
//     BinaryNode *find(const Comparable &x) const
//     BinaryNode *findParent(const Comparable &x) const;
//     BinaryNode *findSuccessor(const Comparable &x) const;   
//     BinaryNode *findPredecessor(const Comparable &x) const;
// private:
//     BinaryNode *find(const Comparable &x, BinaryNode *t) const;
//     BinaryNode *findParent(const Comparable &x, BinaryNode *t) const;

// Find successor
// successor node is the one with the smallest value in the node’s right subtree
template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::findSuccessor(const Comparable &x) const
{
    // finding min(smallest val) of the node right subtree after checking not null, if it is null, then should not have succ
    // works for almost all cases
    if (findMin(find(x)->right) != nullptr){
        return findMin(find(x)->right);
    }
    else{
        return nullptr;
        cout << "\n no successor" << endl;
    }
}

// Find predecessor
// predecessor is largest value in left subtree
template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::findPredecessor(const Comparable &x) const
{
    // finding max(largest val) of left subtree, if null then should not have predecessor
    // works for almost all cases
    if (findMax(find(x)->left) != nullptr){
        return findMax(find(x)->left);
    }
    else{
        return nullptr;
        cout << "\n no predecessor" << endl;
    }
}

// Find
template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::find(const Comparable &x) const
{
    return find(x, root);
}

template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::find(const Comparable &x, BinaryNode *t) const
{
    if(t == nullptr)
        return nullptr;
    else if(x < t->element)
        return find(x, t->left);
    else if(t->element < x)
        return find(x, t->right);
    else
        return t;
}

// Find parent
template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::findParent(const Comparable &x) const
{
    if (isEmpty()){
        cout << "\nCannot find the node" << endl;
    }
    else if (x == root->element){
        cout << "\nNo parent" << endl;
    }
    return findParent(x, root);
}

template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::findParent(const Comparable &x, BinaryNode *t) const
{
    if(t == nullptr){
        return nullptr;
    }
    else if((t->left != nullptr && t->left->element == x) || (t->right != nullptr && t->right->element == x)){
        return t;
    }
    else if(t->element > x){
        return findParent(x, t->left);
    }
    else if(t->element < x){
        return findParent(x, t->right);
    }
    else
        return nullptr;
}
