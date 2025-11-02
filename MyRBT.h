#include "MyHeap.h"
#define RED 0
#define BLACK 1

class RBTNode {
public :
    RBTNode *leftChild, *rightChild;
    HeapNode *heapNode;
    bool color;
    int rideNumber, rideCost, tripDuration;

    RBTNode() {}

    RBTNode(RBTNode *leftChild, RBTNode *rightChild,
    bool color, int rideNumber, int rideCost, int tripDuration) {
        this -> leftChild = leftChild;
        this -> rightChild = rightChild;
        this -> heapNode = new HeapNode(this, rideNumber, rideCost, tripDuration);
        this -> color = color;
        this -> rideNumber = rideNumber;
        this -> rideCost = rideCost;
        this -> tripDuration = tripDuration;
    }
};

class RBT {
public:
    RBTNode *root;
    Heap *heap;

    RBT() {
        root = nullptr;
        heap = new Heap();
    }

    RBT(RBTNode *rbtNode) {
        root = rbtNode;
        heap = new Heap();
        heap -> push(root -> heapNode);
    }

    void insert(RBTNode *node) {
        int rn = node -> rideNumber, rc = node -> rideCost,
            td = node -> tripDuration;
        heap -> push(node -> heapNode);
    }
};