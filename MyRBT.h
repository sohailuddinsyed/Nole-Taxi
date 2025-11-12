#include "MyHeap.h"
#include <queue>

#define RED false
#define BLACK true
#define L 0
#define R 1

class RBTNode {
public :
    RBTNode *leftChild, *rightChild, *parent;
    HeapNode *heapNode;
    bool color;
    int rideNumber, rideCost, tripDuration;

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

    void insert(RBTNode *p) {
        int rn = p -> rideNumber;

        RBTNode *pp = root;
        treeSize++;

        if(pp == nullptr) {
            root = p;
            p -> color = BLACK;
            p -> parent = nullptr;
            return;
        } 

        while(pp && pp -> rideNumber != -1) {
            p -> parent = pp;
            if(rn > (pp -> rideNumber)) pp = pp -> rightChild;
            else pp = pp -> leftChild;
        }
        pp = p -> parent;
        if(rn < pp -> rideNumber) pp -> leftChild = p;
        else pp -> rightChild = p;

        adjustRBT(p);
    }

    void adjustRBT(RBTNode* p) {
        RBTNode *pp = p -> parent, *gp = pp -> parent;
        if(pp -> color == BLACK) return;

        int X, Y, r;

        X = (gp -> leftChild == pp) ? L : R;
        Y = (pp -> leftChild == p) ? L : R;
        r = (X == L) ? gp -> rightChild -> color : gp -> leftChild -> color;

        cout << X << Y << r << endl;
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
        RBTNode *pp = gp -> leftChild, *p = pp -> leftChild;
        RBTNode *c = pp -> rightChild, *b = p -> rightChild;
        
        pp -> rightChild = gp;
        gp -> leftChild = c;

        pp -> parent = gp -> parent;

        if(gp -> parent != nullptr) {
            if(gp -> parent -> rightChild == gp) gp -> parent -> rightChild = pp;
            else gp -> parent -> leftChild = pp;
        } else root = pp;

        gp -> parent = pp;
    }

    void RRRotation(RBTNode* gp) {
        RBTNode *pp = gp -> rightChild, *p = pp -> rightChild;
        RBTNode *c = pp -> leftChild, *b = p -> leftChild;
        
        pp -> leftChild = gp;
        gp -> rightChild = c;

        pp -> parent = gp -> parent;

        if(gp -> parent != nullptr) {
            if(gp -> parent -> rightChild == gp) gp -> parent -> rightChild = pp;
            else gp -> parent -> leftChild = pp;
        } else root = pp;

        gp -> parent = pp;
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