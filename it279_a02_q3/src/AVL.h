#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
using namespace std;

template <typename Comparable>
class AvlTree
{
private:
    struct AvlNode
    {
        Comparable element;
        AvlNode *left;
        AvlNode *right;
        int height;

        AvlNode(const Comparable &ele, AvlNode *lt, AvlNode *rt, int h = 0)
            : element{ele}, left{lt}, right{rt}, height{h} {}

        AvlNode(Comparable &&ele, AvlNode *lt, AvlNode *rt, int h = 0)
            : element{std::move(ele)}, left{lt}, right{rt}, height{h} {}
    };

public:
    AvlTree();
    AvlTree(const AvlTree &rhs);
    AvlTree(AvlTree &&rhs);
    ~AvlTree();

    /**
     * Deep copy.
     */
    AvlTree &operator=(const AvlTree &rhs)
    {
        AvlTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    /**
     * Move.
     */
    AvlTree &operator=(AvlTree &&rhs)
    {
        std::swap(root, rhs.root);

        return *this;
    }

    AvlNode *findMin() const;
    AvlNode *findMax() const;

    bool isEmpty() const;
    void printTree() const;
    void makeEmpty();

    void insert(const Comparable &x);
    void remove(const Comparable &x);

private:
    AvlNode *root;

    void insert(const Comparable &x, AvlNode *&t);
    void remove(const Comparable &x, AvlNode *&t);

    void balance(AvlNode *&t);
    void makeEmpty(AvlNode *&t);
    void printTree(AvlNode *t) const;

    AvlNode *findMin(AvlNode *t) const;
    AvlNode *findMax(AvlNode *t) const;

    AvlNode *clone(AvlNode *t) const;
    int height(AvlNode *t) const;
    int max(int lhs, int rhs) const;
    int getBalance(AvlNode *N);

    void rightRotate(AvlNode *&y);
    void leftRotate(AvlNode *&x);
};
#endif