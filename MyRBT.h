#include "MyHeap.h"
#define RED false
#define BLACK true

class RBTNode {
public :
    RBTNode *leftChild, *rightChild;
    HeapNode *heapNode;
    bool color;
    int rideNumber, rideCost, tripDuration;

    RBTNode() {}

    RBTNode(RBTNode *leftChild, RBTNode *rightChild, HeapNode* heapNode,
    bool color, int rideNumber, int rideCost, int tripDuration) {
        this -> leftChild = leftChild;
        this -> rightChild = rightChild;
        this -> heapNode = heapNode;
        this -> color = color;
        this -> rideNumber = rideNumber;
        this -> rideCost = rideCost;
        this -> tripDuration = tripDuration;
    }
    RBTNode(RBTNode *node) {
        this -> leftChild = node -> leftChild;
        this -> rightChild = node -> rightChild;
        this -> heapNode = node -> heapNode;
        this -> color = node -> color;
        this -> rideNumber = node -> rideNumber;
        this -> rideCost = node -> rideCost;
        this -> tripDuration = node -> tripDuration;
    }
};

class RBT {
public:
    RBTNode *root;

    RBT() {
        root = nullptr;
    }

    RBT(RBTNode *rbtNode) {
        root = rbtNode;
    }

    RBTNode** findParent(int rideNumber, RBTNode **parent, RBTNode *root) {
        if(!root) return parent;

        if(rideNumber < root -> rideNumber) 
            return findParent(rideNumber, &root, root -> leftChild);
        return findParent(rideNumber, &root, root -> rightChild);
    }

    void insert(RBTNode *node) {
        int rn = node -> rideNumber, 
            rc = node -> rideCost,
            td = node -> tripDuration;

        RBTNode **parent = findParent(rn, &node, root);
        if((*parent) == node) {
            root = node;
        } else {
            if(rn > (*parent) -> rideNumber) (*parent) -> rightChild = node;
            else (*parent) -> leftChild = node;
        }
    }

    void LLRotation(){}
    void RRRotation () {}
    void LRRotation() {}
    void RLRotation() {}
};