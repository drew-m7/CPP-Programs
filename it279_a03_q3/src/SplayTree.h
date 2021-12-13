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
        int value;

        BinaryNode() : left{nullptr}, right{nullptr} {}
        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt)
            : element{theElement}, left{lt}, right{rt} { value = 1; }
    };

    BinaryNode *root;
    BinaryNode *nullNode;
    int theSize;

    void printTree(BinaryNode *t, bool flg) const;
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

    const Comparable &findMin();
    const Comparable &findMax();
    void insert(const Comparable &x);
    int remove(const Comparable &x);
    int size() const;
};

#endif