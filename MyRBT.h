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
        this -> rideNumber = 0;
        this -> rideCost = 0;
        this -> tripDuration = 0;
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

    // Copies node's RBT pointers to the calling node
    void copyRBTPointers(RBTNode *node) {
        this -> leftChild = node -> leftChild;
        this -> rightChild = node -> rightChild;
        this -> parent = node -> parent;
        this -> color = node -> color;
    }
};

class RBT {
public:
    // Root node of the RBT
    RBTNode *root;

    // Initializes an empty RBT
    RBT() {
        root = nullptr;
    }

    // Checks if a node is an external node
    bool isExternalNode(RBTNode* node) {
        return node -> rideNumber == 0 && node -> tripDuration == 0 && node -> rideCost == 0;
    }

    // Finds the RBT node with the key and returns a pointer
    RBTNode* findNode(int key, RBTNode* node) {
        if(!node || isExternalNode(node)) return nullptr;

        int currentRideNumber = node -> rideNumber;
        if(key == currentRideNumber) return node;

        if(key > currentRideNumber) return findNode(key, node -> rightChild);
        return findNode(key, node -> leftChild);
    }

    // Finds the parent of the RBT node
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

    // Find the common ancestor
    RBTNode *findCommonAncestor(int r1, int r2, RBTNode *root) {
        if(!root || isExternalNode(root)) return root;
        if(root -> rideNumber < r1) return findCommonAncestor(r1, r2, root -> rightChild);
        if(root -> rideNumber > r2) return findCommonAncestor(r1, r2, root -> leftChild);
        return root;
    }

    // Returns the string triplets with rideNumbers in [r1,r2]
    string range(int r1, int r2) {
        RBTNode *ancestor = findCommonAncestor(r1, r2, root);
        if(!ancestor) return "(0,0,0)\n";

        string output;
        if(!isExternalNode(ancestor))
            printInorder(r1, r2, output, ancestor);
        else output += "(" + to_string(ancestor -> rideNumber) + "," + to_string(ancestor -> rideCost) + ","
            + to_string(ancestor -> tripDuration) + ")," ;

        return output.substr(0, output.length() - 1) + "\n";
    }

    // Prints the indorder traversal from node
    void printInorder(int r1, int r2, string &output, RBTNode* node) {
        int rn = node -> rideNumber;
        if(isExternalNode(node)) return;

        printInorder(r1, r2, output, node -> leftChild);
        if(rn >= r1 && rn <= r2)
        output += "(" + to_string(node -> rideNumber) + "," + to_string(node -> rideCost) + ","
            + to_string(node -> tripDuration) + "),";
        printInorder(r1, r2, output, node -> rightChild);
    }

    // Returns the relationship between parent and child a L or R
    int getChildType(RBTNode* pp, RBTNode* p) {
        if(pp -> rightChild == p) return R;
        return L;
    }

    // Returns the node with max rideNumber under the subtree p
    RBTNode* getMaxNode(RBTNode *p, RBTNode *currMax) {
        if(isExternalNode(p)) return currMax;
        else {
            return getMaxNode(p -> rightChild, p);
        }
    }
    
    // Inserts an RBT node into the tree
    void insert(RBTNode *p) {
        int rn = p -> rideNumber;

        RBTNode *pp = findParent(rn, root);
        if(pp == nullptr) {
            root = p;
            p -> color = BLACK;
            return;
        } 
        p -> parent = pp;
        if(rn < pp -> rideNumber) pp -> leftChild = p;
        else pp -> rightChild = p;

        // Fix imbalances
        adjustRBT(p);
    }

    // Checks and fixes all insert imbalances
    void adjustRBT(RBTNode* p) {
        if(!p || !p -> parent || !p -> parent -> parent) return;

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

        // RBT insert imbalances LLb, RRb, LRb and RLb
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

    // Fixes XYr imbalance
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

        if(gp == root) gp -> color = BLACK;

        // Shifts p, pp and gp 2-levels up
        adjustRBT(gp);
    }

    // Performs LL Rotation on the node
    void LLRotation(RBTNode* gp) {
        RBTNode *ggp = gp -> parent, *pp = gp -> leftChild, *p = pp -> leftChild;
        RBTNode *c = pp -> rightChild;

        pp -> rightChild = gp;
        gp -> leftChild = c;
        c -> parent = gp;

        pp -> parent = ggp;
        gp -> parent = pp;

        if(!ggp) {
            root = pp;
            return;
        }

        if(ggp -> rightChild == gp) ggp -> rightChild = pp;
        else ggp -> leftChild = pp; 
    }

    // Performs RR Rotation on the node
    void RRRotation(RBTNode* gp) {
        RBTNode *ggp = gp -> parent, *pp = gp -> rightChild, *p = pp -> rightChild;
        RBTNode *c = pp -> leftChild, *b = p -> leftChild;
        
        pp -> leftChild = gp;
        gp -> rightChild = c;
        c -> parent = gp;

        pp -> parent = ggp;
        gp -> parent = pp;

        if(!ggp) {
            root = pp;
            return;
        }

        if(ggp -> leftChild == gp) ggp -> leftChild = pp;
        else ggp -> rightChild = pp; 
    }

    // Performs an LR Rotation
    void LRRotation(RBTNode* pp, RBTNode *gp) {
        RRRotation(pp);
        LLRotation(gp);
    }

    // Performs and RL Rotation
    void RLRotation(RBTNode* pp, RBTNode *gp) {
        LLRotation(pp);
        RRRotation(gp);
    }

    // Deletes an RBT node
    HeapNode* deleteNode(int rideNumber) {
        RBTNode *p = findNode(rideNumber, root);
        if(!p) return nullptr;

        RBTNode *pp = p -> parent, *lc = p -> leftChild, *rc = p -> rightChild, *y;
        int pColor = p -> color;
        int noOfChildren = isExternalNode(lc) && isExternalNode(rc) ? 0 : 
                            !isExternalNode(lc) && !isExternalNode(rc) ? 2 : 1;

        // Deletes node with degree 0 from RBT
        if(noOfChildren == 0) {
            RBTNode *extNode = p -> rightChild;
            if(p == root) {
                root = nullptr;
                return p -> heapNode;
            } else {
                if(getChildType(pp, p) == R) pp -> rightChild = extNode;
                else pp -> leftChild = extNode;
                y = extNode;
            }
        } 
        // Deletes node with degree 1 from RBT
        else if(noOfChildren == 1) {
            RBTNode *lc = p -> leftChild, *rc = p -> rightChild;
            if(p == root) {
                root = isExternalNode(lc) ? rc : lc;
                root -> parent = nullptr;
                return p -> heapNode;
            } else {
                if(getChildType(pp, p) == R) {
                    if(!isExternalNode(lc)) pp -> rightChild = lc;
                    else pp -> rightChild = rc;
                } else {
                    if(!isExternalNode(lc)) pp -> leftChild = lc;
                    else pp -> leftChild = rc;
                }
            }
            y = isExternalNode(lc) ? rc : lc;
        } 
        // Deletes node with degree 2 from RBT
        else {
            // Finds the node with max rideNumber from LST
            RBTNode *LSTMaxNode = getMaxNode(p -> leftChild, p);
            if(LSTMaxNode != p -> leftChild) {
                LSTMaxNode -> parent -> rightChild = LSTMaxNode -> leftChild;

                y = LSTMaxNode -> parent -> rightChild;
                y -> parent = LSTMaxNode -> parent;

                pColor = LSTMaxNode -> color;

                LSTMaxNode -> copyRBTPointers(p);
                LSTMaxNode -> leftChild -> parent = LSTMaxNode;
                LSTMaxNode -> rightChild -> parent = LSTMaxNode;

                if(p == root) root = LSTMaxNode;
                else {
                    if(getChildType(LSTMaxNode -> parent, p)) 
                        LSTMaxNode -> parent -> rightChild = LSTMaxNode;
                    else LSTMaxNode -> parent -> leftChild = LSTMaxNode;
                }
                pp = y -> parent;
            } else {
                LSTMaxNode -> parent -> leftChild = LSTMaxNode -> leftChild;
                y = LSTMaxNode -> parent -> leftChild;

                pColor = LSTMaxNode -> color;

                LSTMaxNode -> copyRBTPointers(p);
                LSTMaxNode -> leftChild = y;
                LSTMaxNode -> leftChild -> parent = LSTMaxNode;
                LSTMaxNode -> rightChild -> parent = LSTMaxNode;

                if(p == root) root = LSTMaxNode;
                else {
                    if(getChildType(LSTMaxNode -> parent, p)) LSTMaxNode -> parent -> rightChild = LSTMaxNode;
                    else LSTMaxNode -> parent -> leftChild = LSTMaxNode;
                }
                pp = LSTMaxNode;
            }
        }

        y -> parent = pp;
        if(y == root || y -> color == RED) {
            y -> color = BLACK;
            return p -> heapNode;
        }
        
        // Fix imbalances if a black node is deleted
        if(pColor == BLACK) {
            adjustRBTAfterDelete(y, pp);
        }
        return p -> heapNode;
    }

    // Adjust RBT after delete
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

        // Fixes RB0, RB1, RB2, RR0, RR1, RR2 and
        // LB0, LB1, LB2, LR0, LR1, LR2 imbalances
        if(X == R && c == BLACK && n == 0) {
            RB0(y, py);
        } else if(X == R && c == BLACK && n == 1) { 
            RB1Cases(y, py, a);
        } else if(X == R && c == BLACK && n == 2) { 
            RB2(y, py);
        } else if(X == R && c == RED) { 
            RRCases(py);
        } else if(X == L && c == BLACK && n == 0) { 
            LB0(y, py);
        } else if(X == L && c == BLACK && n == 1) {
            LB1Cases(y, py, b);
        } else if(X == L && c == BLACK && n == 2) {
            LB2(y, py);
        } else if(X == L && c == RED) {
            LRCases(py);
        }
    }

    // Fixes the RB0 imbalance
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
        adjustRBTAfterDelete(py, py -> parent);
    }

    // Fixes the LB0 imbalance
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
        adjustRBTAfterDelete(py, py -> parent);
    }

    // Determines the RB1 imbalance
    void RB1Cases(RBTNode *y, RBTNode *py, RBTNode *a) {
        if(a -> color == RED) RB11(y, py);
        else RB12(y, py);
    }

    // Determines the LB1 imbalance
    void LB1Cases(RBTNode *y, RBTNode *py, RBTNode *b) {
        if(b -> color == RED) LB12(y, py);
        else LB11(y, py);
    }

    // Fixes RB11 imbalance
    void RB11(RBTNode *y, RBTNode *py) {
        RBTNode *v = py -> leftChild, *a = v -> leftChild;
        a -> color = BLACK;
        v -> color = py -> color ;
        py -> color = BLACK;
        LLRotation(py);
    }

    // Fixes LB11 imbalance
    void LB11(RBTNode *y, RBTNode *py) {
        RBTNode *v = py -> rightChild, *b = v -> leftChild;
        b -> color = BLACK;
        v -> color = BLACK ;
        py -> color = BLACK;
        RLRotation(v, py);
    }

    // Fixes RB12 imbalance
    void RB12(RBTNode *y, RBTNode *py) {
        RBTNode *v = py -> leftChild, *w = v -> rightChild;
        w -> color = py -> color ;
        py -> color = BLACK;
        LRRotation(v, py);
    }

    // Fixes LB12 imbalance
    void LB12(RBTNode *y, RBTNode *py) {
        RBTNode *v = py -> rightChild, *a = v -> rightChild;
        a -> color = BLACK;
        v -> color = BLACK;
        RRRotation(py);
    }

    // Fixes RB2 imbalance
    void RB2(RBTNode *y, RBTNode *py) {
        RBTNode* w = py -> leftChild -> rightChild;
        w -> color = py -> color;
        py -> color = BLACK;
        LRRotation(py -> leftChild, py);
    }
    
    // Fixes LB2 imbalance
    void LB2(RBTNode *y, RBTNode *py) {
        RBTNode* a = py -> rightChild -> leftChild;
        a -> color = py -> color;
        py -> color = BLACK;
        RLRotation(py -> rightChild, py);
    }

    // Checks for thr type of RR imbalance
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

    // Checks for thr type of LL imbalance
    void LRCases(RBTNode *py) {
        RBTNode *v = py -> rightChild, *a = v -> leftChild;
        RBTNode *b = a -> leftChild, *c = a -> rightChild;
        int n = c -> color == RED ? (b -> color == RED ? 2 : 1) : b -> color == RED ? 1 : 0;

        if(n == 0) {
            LR0(py, v, a);
        } else if(n == 1) {
            if(c -> color == RED) LR11(v, py, c);
            else LR12(py, v, a, b);
        } else {
            LR2(py, v, a, b);
        }
    }

    // Fixes RR0 imbalance
    void RR0(RBTNode *py, RBTNode *v, RBTNode *b) {
        LLRotation(py);
        v -> color = BLACK;
        b -> color = RED;
    }
    // Fixes LR0 imbalance
    void LR0(RBTNode *py, RBTNode *v, RBTNode *a) {
        RRRotation(py);
        v -> color = BLACK;
        a -> color = RED;
    }

    // Fixes RR11 imbalance
    void RR11(RBTNode *y, RBTNode *py, RBTNode *b) {
        LRRotation(y, py);
        b -> color = BLACK;
    }

    // Fixes LR11 imbalance
    void LR11(RBTNode *v, RBTNode *py, RBTNode *c) {
        RLRotation(v, py);
        c -> color = BLACK;
    }

    // Fixes RR12 imbalance
    void RR12(RBTNode *py, RBTNode *v, RBTNode *w, RBTNode *x) {
        RRRotation(w);
        LRRotation(v, py);
        x -> color = BLACK;
    }

    // Fixes LR12 imbalance
    void LR12(RBTNode *py, RBTNode *v, RBTNode *w, RBTNode *b) {
        LLRotation(w);
        RLRotation(v, py);
        b -> color = BLACK;
    }

    // Fixes RR2 imbalance
    void RR2(RBTNode *py, RBTNode *v, RBTNode *w, RBTNode *x) {
        RRRotation(w);
        LRRotation(v, py);
        x -> color = BLACK;
    }

    // Fixes LR2 imbalance
    void LR2(RBTNode *py, RBTNode *v, RBTNode *w, RBTNode *b) {
        LLRotation(w);
        RLRotation(v, py);
        b -> color = BLACK;
    }
};