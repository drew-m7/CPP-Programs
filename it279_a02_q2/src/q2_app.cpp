#include <iostream>
#include "BST.h"
#include "BST.cpp"
#include "flags.h"

using namespace std;

// // Test program
int main()
{
    BinarySearchTree<int> t;
    t.insert(50);
    t.insert(30);
    t.insert(20);
    t.insert(40);
    t.insert(70);
    t.insert(60);
    t.insert(80);

    t.insert(15);
    t.insert(25);
    t.insert(35);
    t.insert(45);

    t.insert(55);
    t.insert(65);
    t.insert(75);
    t.insert(85);

    cout << "Question 02: " << endl;
    cout << "The built binary search tree (BST) is (preorder traversal):" << endl;
    t.printTree();
    cout << endl;

    t.remove(30);
    cout << "The updated binary search tree (BST) is (preorder traversal):" << endl;
    t.printTree();
    cout << endl;

    t.insert(78);
    t.insert(90);
    t.remove(30);
    t.remove(70);
    cout << "The updated binary search tree (BST) is (preorder traversal):" << endl;
    t.printTree();
    cout << endl;

    t.insert(10);
    t.insert(26);
    t.remove(50);
    t.remove(60);
    cout << "The updated binary search tree (BST) is (preorder traversal):" << endl;
    t.printTree();

    return 0;
}
