#include "MyHeap.h"
#include <queue>

#define RED 0
#define BLACK 1

#define L 0
#define R 1

class RBTNode {
public :
    RBTNode *leftChild, *rightChild, *parent;
    HeapNode *heapNode;
    bool color;
    int rideNumber, rideCost, tripDuration;

    // Initializes external nodes
    RBTNode() {
        this -> leftChild = nullptr;
        this -> rightChild = nullptr;
        this -> parent = nullptr;
        this -> heapNode = nullptr;
        this -> color = BLACK;
        this -> rideNumber = -1;
        this -> rideCost = -1;
        this -> tripDuration = -1;
    }

    // Initializes non-external RBT nodes
    RBTNode(RBTNode *leftChild, RBTNode *rightChild, RBTNode *parent, HeapNode* heapNode,
    bool color, int rideNumber, int rideCost, int tripDuration) {
        this -> leftChild = leftChild != nullptr ?
            leftChild : new RBTNode();
        this -> rightChild = rightChild != nullptr ?
            rightChild : new RBTNode();
        this -> parent = parent;
        this -> heapNode = heapNode;
        this -> color = color;
        this -> rideNumber = rideNumber;
        this -> rideCost = rideCost;
        this -> tripDuration = tripDuration;
    }

    // Initializes non-external RBT nodes from an existing node
    RBTNode(RBTNode *node) {
        this -> leftChild = node -> leftChild != nullptr ?
            node -> leftChild : new RBTNode();
        this -> rightChild = node -> rightChild != nullptr ?
            node -> rightChild : new RBTNode();
        this -> parent = node -> parent;
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
    int treeSize;

    RBT() {
        root = nullptr;
        treeSize = 0;
    }

    RBT(RBTNode *rbtNode) {
        root = rbtNode;
        treeSize = 1;
    }

    bool isExternalNode(RBTNode* node) {
        return node -> rideNumber == -1;
    }

    RBTNode* findNode(int key, RBTNode* node) {
        if(!node || isExternalNode(node)) return nullptr;

        int currentRideNumber = node -> rideNumber;
        if(key == currentRideNumber) return node;

        if(key > currentRideNumber) return findNode(key, node -> rightChild);
        return findNode(key, node -> leftChild);
    }

    RBTNode* findParent(int key, RBTNode* node) {
        if(!node) return node;
        if(key > (node -> rideNumber)) {
            if(isExternalNode(node -> rightChild)) return node;
            node = node -> rightChild;
        } else {
            if(isExternalNode(node -> leftChild)) return node;
            node = node -> leftChild;
        }
        return findParent(key, node);
    }

    void insert(RBTNode *p) {
        int rn = p -> rideNumber;
        treeSize++;

        RBTNode *pp = findParent(rn, root);

        if(pp == nullptr) {
            root = p;
            p -> color = BLACK;
            return;
        } 

        p -> parent = pp;
        if(rn < pp -> rideNumber) pp -> leftChild = p;
        else pp -> rightChild = p;

        adjustRBT(p);
    }

    void deleteNode(int rideNumber) {
        RBTNode *p = findNode(rideNumber, root);
        if(!p) return;

        bool color = p -> color;
        if(color == RED) {
            delete p;
        }
        treeSize--;
    }

    // Rebalances and maint
    void adjustRBT(RBTNode* p) {
        RBTNode *pp = p -> parent, *gp = pp -> parent;
        if(pp -> color == BLACK) return;

        int X, Y, r;

        X = (gp -> leftChild == pp) ? L : R;
        Y = (pp -> leftChild == p) ? L : R;
        r = (X == L) ? gp -> rightChild -> color : gp -> leftChild -> color;

        if(r == RED) {
            XYr(p);
            return;
        }

        if(X == L && Y == L) {
            LLRotation(gp);
            pp -> color = BLACK;
            gp -> color = RED;  
        } else if(X == R && Y == R) {
            RRRotation(gp);
            pp -> color = BLACK;
            gp -> color = RED;  
        } else if(X == L && Y == R) {
            LRRotation(pp, gp);
            p -> color = BLACK;
            gp -> color = RED;  
        } else {
            RLRotation(pp, gp);
            p -> color = BLACK;
            gp -> color = RED; 
        }
        
    }

    void XYr(RBTNode* p) {
        if(p == root) {
            p -> color = BLACK;
            return;
        }

        RBTNode *pp = p -> parent;
        if(p -> color == BLACK || pp -> color == BLACK) return;
        
        int X = (pp -> parent -> leftChild == pp) ? L : R;
        RBTNode *gp = pp -> parent, *d = (X == L) ? 
            gp -> rightChild : gp -> leftChild;

        d -> color = BLACK;
        pp -> color = BLACK;
        gp -> color = RED;

        XYr(gp);
    }

    void LLRotation(RBTNode* gp) {
        RBTNode *ggp = gp -> parent, *pp = gp -> leftChild, *p = pp -> leftChild;
        RBTNode *c = pp -> rightChild;
        
        pp -> rightChild = gp;
        gp -> leftChild = c;

        pp -> parent = ggp;
        gp -> parent = pp;

        if(!ggp) {
            root = pp;
            return;
        }

        if(ggp -> rightChild == gp) ggp -> rightChild = pp;
        else ggp -> leftChild = pp;       
    }

    void RRRotation(RBTNode* gp) {
        RBTNode *ggp = gp -> parent, *pp = gp -> rightChild, *p = pp -> rightChild;
        RBTNode *c = pp -> leftChild, *b = p -> leftChild;
        
        pp -> leftChild = gp;
        gp -> rightChild = c;

        pp -> parent = ggp;
        gp -> parent = pp;

        if(!ggp) {
            root = pp;
            return;
        }

        if(ggp -> leftChild == gp) ggp -> leftChild = pp;
        else ggp -> rightChild = pp; 
    }

    void LRRotation(RBTNode* pp, RBTNode *gp) {
        RRRotation(pp);
        LLRotation(gp);
    }

    void RLRotation(RBTNode* pp, RBTNode *gp) {
        LLRotation(pp);
        RRRotation(gp);
    }

    void printTree() {
        queue<RBTNode*> q;
        q.push(root);

        while(!q.empty()) {
            int size = q.size();
            while(size) {
                RBTNode *node = q.front();
                q.pop();
                char color = node -> color ? 'b' : 'r';

                if(node -> rideNumber >= 0) 
                    cout << color << "-" << node -> rideNumber << "\t";
                if(node -> leftChild) q.push(node -> leftChild);
                if(node -> rightChild) q.push(node -> rightChild);
                size--;
            }
            cout << endl;
        }
    }

};