#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H
#include <iostream>

template <typename Comparable>
class SplayTree
{
private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode() : left{nullptr}, right{nullptr} {}
        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt)
            : element{theElement}, left{lt}, right{rt} {}
    };

    BinaryNode *root;
    BinaryNode *nullNode;

    void printTree(BinaryNode *t) const;
    BinaryNode *clone(BinaryNode *t) const;

    // You will complete these three methods
    void splay(const Comparable &x, BinaryNode *&t);
    void rightRotate(BinaryNode *&x);
    void leftRotate(BinaryNode *&x);

public:
    SplayTree();
    SplayTree(const SplayTree &rhs);
    SplayTree(SplayTree &&rhs);
    ~SplayTree();

    // Deep copy.
    SplayTree &operator=(const SplayTree &rhs)
    {
        SplayTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }
    // Move.
    SplayTree &operator=(SplayTree &&rhs)
    {
        std::swap(root, rhs.root);
        std::swap(nullNode, rhs.nullNode);
        return *this;
    }
    bool isEmpty() const;
    void makeEmpty();
    void printTree() const;
    bool search(const Comparable &x);

    // You will complete these four methods
    const Comparable &findMin();
    const Comparable &findMax();
    void insert(const Comparable &x);
    void remove(const Comparable &x);
};

#endif