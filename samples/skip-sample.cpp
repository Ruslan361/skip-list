#include "skip.h"
#include <iostream>
// Example usage
int main() {
    SkipList<int> skipList;
    skipList.insert(3);
    skipList.insert(6);
    skipList.insert(1);
    skipList.insert(9);
    skipList.print();

    cout << "Search for 6: " << (skipList.search(6) ? "Found" : "Not Found") << endl;
    cout << "Search for 5: " << (skipList.search(5) ? "Found" : "Not Found") << endl;
}