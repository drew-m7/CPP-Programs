#include <iostream>
#include "BST.h"
#include "BST.cpp"
#include "flags.h"

using namespace std;

// // Test program
int main()
{
    cout << "Question 01: " << endl;
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

    if (TEST0)
    {
        // Uncomment the code for testing
        cout << "Test0: " << endl;
        cout << "The built binary search tree (BST) is (preorder traversal):" << endl;
        t.printTree();
    }

    if (TEST1)
    {
        // Uncomment the code for testing
        cout << "Test1: " << endl;
        cout << "The built binary search tree (BST) is (preorder traversal):" << endl;
        t.printTree();
        cout << "The parent of " << 50 << " is " << t.findParent(50)->element << endl;
    }

    if (TEST2)
    {
        // Uncomment the code for testing
        cout << "Test2: " << endl;
        cout << "The built binary search tree (BST) is (preorder traversal):" << endl;
        t.printTree();
        cout << "The max vaule of the BST is: " << t.findMax()->element << endl;
        cout << "The min vaule of the BST is: " << t.findMin()->element << endl;

        cout << "The successor of " << 30 << " is " << t.findSuccessor(30)->element << endl;
        cout << "The predecessor of " << 30 << " is " << t.findPredecessor(30)->element << endl;
        cout << "The parent of " << 30 << " is " << t.findParent(30)->element << endl;
        cout << "The successor of " << 70 << " is " << t.findSuccessor(70)->element << endl;
        cout << "The predecessor of " << 70 << " is " << t.findPredecessor(70)->element << endl;
        cout << "The parent of " << 70 << " is " << t.findParent(70)->element << endl;
        cout << "The successor of " << 85 << " is " << t.findSuccessor(85)->element << endl;
        cout << "The predecessor of " << 85 << " is " << t.findPredecessor(85)->element << endl;
        cout << "The parent of " << 85 << " is " << t.findParent(85)->element << endl;
    }

    if (TEST3)
    {
        // Uncomment the code for testing
        cout << "Test3: " << endl;
        t.remove(30);
        cout << "The updated tree is (preorder traversal):" << endl;
        t.printTree();

        cout << "The successor of " << 35 << " is " << t.findSuccessor(35)->element << endl;
        cout << "The predecessor of " << 35 << " is " << t.findPredecessor(35)->element << endl;
        cout << "The parent of " << 35 << " is " << t.findParent(35)->element << endl;
        cout << "The successor of " << 40 << " is " << t.findSuccessor(40)->element << endl;
        cout << "The predecessor of " << 40 << " is " << t.findPredecessor(40)->element << endl;
        cout << "The parent of " << 40 << " is " << t.findParent(40)->element << endl;

        cout << "The max vaule of the BST is: " << t.findMax()->element << endl;
        cout << "The min vaule of the BST is: " << t.findMin()->element << endl;
    }

    if (TEST4)
    {
        // Uncomment the code for testing
        cout << "Test4: " << endl;
        t.remove(10);
        t.remove(85);
        cout << "The updated tree is (preorder traversal):" << endl;
        t.printTree();
        cout << "The max vaule of the BST is: " << t.findMax()->element << endl;
        cout << "The min vaule of the BST is: " << t.findMin()->element << endl;
    }

    return 0;
}
