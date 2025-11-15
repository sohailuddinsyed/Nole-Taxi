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

    int getTreeSize(RBTNode *root) {
        if(!isExternalNode(root)) 
            return getTreeSize(root -> leftChild) + getTreeSize(root -> rightChild) + 1;
        return 0;
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

    RBTNode *findCommonAncestor(int r1, int r2, RBTNode *root) {
        if(root -> rideNumber < r1) return findCommonAncestor(r1, r2, root -> rightChild);
        if(root -> rideNumber > r2) return findCommonAncestor(r1, r2, root -> leftChild);
        return root;
    }

    void range(int r1, int r2) {
        RBTNode *n1 = findNode(r1, root), *n2 = findNode(r2, root);
        RBTNode *ancestor = findCommonAncestor(r1, r2, root);
        printInorder(r1, r2, ancestor);
        cout << endl;
    }

    void printInorder(int r1, int r2, RBTNode* node) {
        int rn = node -> rideNumber;
        if(rn < r1 || rn > r2 || isExternalNode(node)) return;

        printInorder(r1, r2, node -> leftChild);
        cout << "(" << node -> rideNumber << "," << node -> rideCost << "," << node -> tripDuration << ")" << ",";
        printInorder(r1, r2, node -> rightChild);
    }

    int getChildType(RBTNode* pp, RBTNode* p) {
        if(pp -> rightChild == p) return R;
        return L;
    }

    RBTNode* getMaxNode(RBTNode *p, RBTNode *currMax) {
        if(isExternalNode(p)) return currMax;
        else return getMaxNode(p -> rightChild, p);
    }

    void deleteNode(int rideNumber) {
        RBTNode *p = findNode(rideNumber, root);
        if(!p) return;

        RBTNode *pp = p -> parent, *lc = p -> leftChild, *rc = p -> rightChild, *y;
        int noOfChildren = isExternalNode(lc) && isExternalNode(rc) ? 0 : 
                            !isExternalNode(lc) && !isExternalNode(rc) ? 2 : 1;

        if(noOfChildren == 0) {
            // Ext node is root
            RBTNode *extNode = p -> rightChild;
            if(p == root) {
                root = extNode;
            } else {
                if(getChildType(pp, p) == R) pp -> rightChild = extNode;
                else pp -> leftChild = extNode;
            }
            y = extNode;
        } else if(noOfChildren == 1) {
            RBTNode *lc = p -> leftChild, *rc = p -> rightChild;
            if(p == root) {
                root = isExternalNode(lc) ? rc : lc;
            } else {
                if(!isExternalNode(rc) && getChildType(pp, p) == R) {
                    pp -> rightChild = rc;
                } else if(!isExternalNode(lc) && getChildType(pp, p) == R) {
                    pp -> rightChild = lc;
                } else if(!isExternalNode(rc)) pp -> leftChild = rc;
                else pp -> leftChild = rc;
            }
            y = isExternalNode(lc) ? rc : lc;
        } else {
            RBTNode *LSTMaxNode = getMaxNode(p -> leftChild, p);
            cout << LSTMaxNode -> rideNumber << endl;
            LSTMaxNode -> leftChild -> parent = LSTMaxNode -> parent;
            if(LSTMaxNode != p -> leftChild) {
                LSTMaxNode -> parent -> rightChild = LSTMaxNode -> leftChild;
                y = LSTMaxNode -> parent -> rightChild;
            } else {
                LSTMaxNode -> parent -> rightChild = LSTMaxNode -> leftChild;
                y = LSTMaxNode -> parent -> rightChild;
            }
            p -> rideNumber = LSTMaxNode -> rideNumber;
        }


        bool colorOfDeletedNode = p -> color;
        if(colorOfDeletedNode == RED) {
            // y -> color = RED;
        } else {
            adjustRBTAfterDelete(y, pp);
        }
        treeSize--;
    }

    void adjustRBTAfterDelete(RBTNode *y, RBTNode* py) {
        if(y == root) {
            y -> color = BLACK;
            return;
        }

        RBTNode *v = (getChildType(py, y) == L) ? py -> rightChild : py -> leftChild;
        if(isExternalNode(v)) {
            if(!isExternalNode(y))
                y -> color = RED;
            return;
        }
        RBTNode *a = v -> leftChild, *b = v -> rightChild;
        int X = getChildType(py, y), c = v -> color, 
        n = a -> color == RED ? (b -> color == RED ? 2 : 1) : b -> color == RED ? 1 : 0;

        //cases
        if(X == R && c == BLACK && n == 0) {
            cout << "RB0 case" << endl;
            RB0(y, py);
        } else if(X == R && c == BLACK && n == 1) {
            RB1Cases(y, py, a);
        } else if(X == R && c == BLACK && n == 2) {
            RB2(y, py);
        } else if(X == R && c == RED) {
            RRCases(py);
        }

        if(X == L && c == BLACK && n == 0) {
            cout << "LB0 case" << endl;
            LB0(y, py);
        } else if(X == L && c == BLACK && n == 1) {
            LB1Cases(y, py, a);
        } else if(X == L && c == BLACK && n == 2) {
            LB2(y, py);
        } else if(X == L && c == RED) {
            LRCases(py);
        }
    }

    void RB0(RBTNode *y, RBTNode *py) {
        if(y == root) {
            y -> color = BLACK;
            return;
        }
        RBTNode *v = py -> leftChild;

        if(py -> color == BLACK) {
            v -> color = RED;
        } else {
            py -> color = BLACK;
            v -> color = RED;
            return;
        }
        RB0(py, py -> parent);
    }

    void RB1Cases(RBTNode *y, RBTNode *py, RBTNode *a) {
        if(a == RED) {
            cout << "RB11 case" << endl;
            RB11(y, py);
        } else {
            cout << "RB12 case" << endl;
            RB12(y, py);
        }
    }

    void RB11(RBTNode *y, RBTNode *py) {
        RBTNode* a = py -> leftChild -> leftChild;
        a -> color = BLACK;
        LLRotation(py);
    }

    void RB12(RBTNode *y, RBTNode *py) {
        RBTNode* w = py -> leftChild -> rightChild;
        w -> color = BLACK;
        LRRotation(py -> leftChild, py);
    }

    void RB2(RBTNode *y, RBTNode *py) {
        RBTNode* w = py -> leftChild -> rightChild;
        w -> color = BLACK;
        LRRotation(py -> leftChild, py);
    }

    void RRCases(RBTNode *py) {
        RBTNode *v = py -> leftChild, *w = v -> rightChild;
        RBTNode *b = w -> leftChild, *c = w -> rightChild;
        int n = c -> color == RED ? (b -> color == RED ? 2 : 1) : b -> color == RED ? 1 : 0;

        if(n == 0) {
            RR0(py, v, w);
        } else if(n == 1) {
            if(b -> color == RED) RR11(v, py, b);
            else RR12(py, v, w, c);
        } else {
            RR2(py, v, w, c);
        }
    }

    void RR0(RBTNode *py, RBTNode *v, RBTNode *w) {
        LLRotation(py);
        v -> color = BLACK;
        w -> color = RED;
    }

    void RR11(RBTNode *y, RBTNode *py, RBTNode *b) {
        LRRotation(y, py);
        b -> color = BLACK;
    }

    void RR12(RBTNode *py, RBTNode *v, RBTNode *w, RBTNode *c) {
        RRRotation(w);
        LRRotation(v, py);
        c -> color = BLACK;
    }

    void RR2(RBTNode *py, RBTNode *v, RBTNode *w, RBTNode *c) {
        RRRotation(w);
        LRRotation(v, py);
        c -> color = BLACK;
    }

    void LB0(RBTNode *y, RBTNode *py) {
        if(y == root) {
            y -> color = BLACK;
            return;
        }
        RBTNode *v = py -> rightChild;

        if(py -> color == BLACK) {
            v -> color = RED;
        } else {
            py -> color = BLACK;
            v -> color = RED;
            return;
        }
        RB0(py, py -> parent);
    }

    void LB1Cases(RBTNode *y, RBTNode *py, RBTNode *a) {
        if(a == RED) {
            cout << "LB11 case" << endl;
            LB11(y, py);
        } else {
            cout << "LB12 case" << endl;
            LB12(y, py);
        }
    }

    void LB11(RBTNode *y, RBTNode *py) {
        RBTNode* a = py -> rightChild -> leftChild;
        a -> color = BLACK;
        RRRotation(py);
    }

    void LB12(RBTNode *y, RBTNode *py) {
        RBTNode* w = py -> rightChild -> rightChild;
        w -> color = BLACK;
        RLRotation(py -> rightChild, py);
    }

    void LB2(RBTNode *y, RBTNode *py) {
        RBTNode* w = py -> rightChild -> rightChild;
        w -> color = BLACK;
        RLRotation(py -> rightChild, py);
    }

    void LRCases(RBTNode *py) {
        RBTNode *v = py -> rightChild, *w = v -> leftChild;
        RBTNode *b = w -> leftChild, *c = w -> rightChild;
        int n = c -> color == RED ? (b -> color == RED ? 2 : 1) : b -> color == RED ? 1 : 0;

        if(n == 0) {
            LR0(py, v, w);
        } else if(n == 1) {
            if(b -> color == RED) LR11(v, py, b);
            else LR12(py, v, w, c);
        } else {
            LR2(py, v, w, c);
        }
    }

    void LR0(RBTNode *py, RBTNode *v, RBTNode *w) {
        RRRotation(py);
        v -> color = BLACK;
        w -> color = RED;
    }

    void LR11(RBTNode *v, RBTNode *py, RBTNode *b) {
        RLRotation(v, py);
        b -> color = BLACK;
    }

    void LR12(RBTNode *py, RBTNode *v, RBTNode *w, RBTNode *c) {
        LLRotation(w);
        RLRotation(v, py);
        c -> color = BLACK;
    }

    void LR2(RBTNode *py, RBTNode *v, RBTNode *w, RBTNode *c) {
        LLRotation(w);
        RLRotation(v, py);
        c -> color = BLACK;
    }

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

        pp -> parent = ggp;   
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

        pp -> parent = ggp;
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