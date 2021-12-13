#include <iostream>
#include "AVL.h"
#include "AVL.cpp"
#include "flags.h"

using namespace std;

// Testing program
int main()
{
    cout << "Question 03: " << endl;
    AvlTree<int> t;

    if (TEST0)
    {
        // Uncomment the code for testing
        cout << "Test0: " << endl;
        t.insert(50);
        t.insert(30);
        t.insert(20);
        t.insert(40);
        t.insert(10);
        t.insert(5);
        t.insert(45);
        t.insert(48);

        cout << "The built binary search tree (BST) is (preorder traversal):" << endl;
        t.printTree();
        cout << endl;

        t.remove(40);
        cout << "The built binary search tree (BST) is (preorder traversal):" << endl;
        t.printTree();
        cout << endl;

        cout << "The max vaule of the AVL Tree is: " << t.findMax()->element << endl;
        cout << "The min vaule of the AVL Tree is: " << t.findMin()->element << endl;
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

        cout << "The built binary search tree (BST) is (preorder traversal):" << endl;
        t.printTree();
        cout << endl;

        t.remove(35);
        cout << "The built binary search tree (BST) is (preorder traversal):" << endl;
        t.printTree();
        cout << endl;

        cout << "The max vaule of the AVL Tree is: " << t.findMax()->element << endl;
        cout << "The min vaule of the AVL Tree is: " << t.findMin()->element << endl;
    }

    if (TEST2)
    {
        // Uncomment the code for testing
        cout << "Test2: " << endl;
        t.insert(60);
        t.insert(50);
        t.insert(55);
        t.insert(58);
        t.insert(65);
        t.insert(75);
        t.insert(80);
        t.insert(85);
        t.insert(62);

        cout << "The built binary search tree (BST) is (preorder traversal):" << endl;
        t.printTree();
        cout << endl;

        t.remove(80);
        t.remove(85);
        cout << "The built binary search tree (BST) is (preorder traversal):" << endl;
        t.printTree();
        cout << endl;

        cout << "The max vaule of the AVL Tree is: " << t.findMax()->element << endl;
        cout << "The min vaule of the AVL Tree is: " << t.findMin()->element << endl;
    }

    return 0;
}
