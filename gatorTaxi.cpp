#include "MyRBT.h"

int main() {
    RBT *rbt = new RBT();
    rbt -> insert(new RBTNode(nullptr, nullptr, 1, 1024, 300, 10));
    rbt -> heap -> getTopNode();

    rbt -> insert(new RBTNode(nullptr, nullptr, 1, 1022, 200, 10));
    rbt -> heap -> getTopNode();
    cout << rbt -> heap -> getSize() << endl;
    cout << rbt -> root -> leftChild -> rideNumber << endl;
    // cout << root -> heap -> top() -> rbtNode -> color;
}


/*
    Heap tests
    --------------------------------------------------
    // heap -> push(new HeapNode(nullptr, 10,11,12));
    // heap -> push(new HeapNode(nullptr, 20,9,12));
    // heap -> push(new HeapNode(nullptr, 30,9,9));
    // heap -> getTopNode();
    // cout << heap -> getSize() << endl;

    // heap -> pop();

    // heap -> getTopNode();
    // cout << heap -> getSize() << endl;
*/