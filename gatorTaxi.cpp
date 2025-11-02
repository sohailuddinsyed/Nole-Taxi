#include "MyRBT.h"

int main() {
    RBT *root = new RBT(new RBTNode(nullptr, nullptr, 1, 1024, 300, 10));
    root -> heap -> getTopNode();
    cout << root -> heap -> getSize() << endl;
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