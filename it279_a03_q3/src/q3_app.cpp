#include "SplayTree.h"
#include "flags.h"
#include "SplayTree.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <map>
#include <algorithm>
using namespace std;

// Testing program
int main()
{
    cout << "\nAssignment 03, Question 03 (Drew): " << endl;

    // part a
    SplayTree<string> t;

    string line;
    ifstream myfile ("enroll.txt");
    if (myfile.is_open())
    {
    while ( getline (myfile,line) )
    {
      t.insert(line);
    }
    myfile.close();
    }
    else cout << "Unable to open file"; 

    cout << "The built splay tree: " << endl;
    t.printTree();
    cout << endl;
    
    // part b
    cout << endl;
    cout << "The queried students (sorted by number of courses taken in descending order): " << endl;
    list<pair<int, string>> li;
    string lineqry;
    ifstream myfileqry ("query.txt");
    if (myfileqry.is_open())
    {
    while ( getline (myfileqry,lineqry) )
    {
      li.push_back(make_pair(t.remove(lineqry), lineqry));
    }
    myfileqry.close();
    }
    li.sort();
    li.reverse();
    for (auto const &l: li)
    {
        cout << "(" << l.second << ", " << l.first << ") ";
    }
    cout << endl;

    // part c
    cout << endl;
    cout << "The queried students (sorted by student number in ascending order): " << endl;
    map<string, int> map1;

    for (auto const &l: li) 
    {
        map1.insert(make_pair(l.second, l.first));
    }
    li.sort();
    for (auto const &l: map1) 
    {
        cout << "(" << l.first << ", " << l.second << ") ";
    }
    cout << endl;

    // part d
    cout << endl;
    cout << "The updated splay tree: " << endl;
    t.printTree();
    cout << endl;

    return 0;
}
