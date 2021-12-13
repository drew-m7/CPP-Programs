#include "SplayTree.h"
#include "flags.h"
#include "SplayTree.cpp"
#include <iostream>

using namespace std;

// Testing program
int main()
{
    int val;
    cout << "Assignment 03, Question 02 (Drew): " << endl;
    SplayTree<int> t;

    if (TEST0)
    {
        // Uncomment the code for testing
        cout << "Test0: " << endl;
        t.insert(50);
        t.insert(30);
        t.insert(20);
        t.insert(30);
        t.insert(40);
        t.insert(10);
        t.insert(10);
        t.insert(10);
        t.insert(5);
        t.insert(45);
        t.insert(20);
        t.insert(48);

        cout << "The built splay tree is (preorder traversal):" << endl;
        t.printTree();
        cout << endl;

        val = t.remove(20);
        cout << "The value of the removed node is: " << val << endl;
        cout << "The updated splay tree is (preorder traversal):" << endl;
        t.printTree();
        cout << endl;

        t.search(26);
        cout << "The updated splay tree is (preorder traversal):" << endl;
        t.printTree();
        cout << endl;

        t.search(45);
        cout << "The updated splay tree is (preorder traversal):" << endl;
        t.printTree();
        cout << endl;
        cout << "The number of nodes in the splay tree: " << t.size() << endl;
    }

    if (TEST1)
    {
        // Uncomment the code for testing
        cout << "Test1: " << endl;
        t.insert(50);
        t.insert(40);
        t.insert(35);
        t.insert(40);
        t.insert(10);
        t.insert(15);
        t.insert(45);
        t.insert(48);
        t.insert(5);

        cout << "The built splay tree is (preorder traversal):" << endl;
        t.printTree();
        cout << endl;

        val = t.remove(35);
        cout << "The value of the removed node is: " << val << endl;
        cout << "The updated splay tree is (preorder traversal):" << endl;
        t.printTree();
        cout << endl;

        t.search(10);
        cout << "The updated splay tree is (preorder traversal):" << endl;
        t.printTree();
        cout << endl;

        val = t.remove(35);
        cout << "The value of the removed node is: " << val << endl;
        cout << "The updated splay tree is (preorder traversal):" << endl;
        t.printTree();
        cout << endl;
        cout << "The number of nodes in the splay tree: " << t.size() << endl;
    }

    if (TEST2)
    {
        // Uncomment the code for testing
        cout << "Test2: " << endl;
        t.insert(60);
        t.insert(50);
        t.insert(85);
        t.insert(80);
        t.insert(55);
        t.insert(58);
        t.insert(65);
        t.insert(55);
        t.insert(75);
        t.insert(80);
        t.insert(85);
        t.insert(55);
        t.insert(62);

        cout << "The built splay tree is (preorder traversal):" << endl;
        t.printTree();
        cout << endl;

        val = t.remove(80);
        cout << "The value of the removed node is: " << val << endl;
        cout << "The updated splay tree is (preorder traversal):" << endl;
        t.printTree();
        cout << endl;

        t.search(10);
        t.search(75);
        t.search(59);
        cout << "The updated splay tree is (preorder traversal):" << endl;
        t.printTree();
        cout << endl;
        cout << "The number of nodes in the splay tree: " << t.size() << endl;
    }

    return 0;
}
