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

    void copyHeapNodeExceptData(RBTNode *node) {
        this -> leftChild = node -> leftChild;
        this -> rightChild = node -> rightChild;
        this -> parent = node -> parent;
        this -> color = node -> color;
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
        return node -> rideNumber == 0 && node -> tripDuration == 0 && node -> rideCost == 0;
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
        if(isExternalNode(root)) return root;
        if(root -> rideNumber < r1) return findCommonAncestor(r1, r2, root -> rightChild);
        if(root -> rideNumber > r2) return findCommonAncestor(r1, r2, root -> leftChild);
        return root;
    }

    string range(int r1, int r2) {
        RBTNode *n1 = findNode(r1, root), *n2 = findNode(r2, root);
        RBTNode *ancestor = findCommonAncestor(r1, r2, root);

        string output;
        if(!isExternalNode(ancestor))
            printInorder(r1, r2, output, ancestor);
        else output += "(" + to_string(ancestor -> rideNumber) + "," + to_string(ancestor -> rideCost) + ","
            + to_string(ancestor -> tripDuration) + ")," ;

        return output.substr(0, output.length() - 1) + "\n";
    }

    void printInorder(int r1, int r2, string &output, RBTNode* node) {
        int rn = node -> rideNumber;
        if(isExternalNode(node)) return;

        printInorder(r1, r2, output, node -> leftChild);
        if(rn >= r1 && rn <= r2)
        output += "(" + to_string(node -> rideNumber) + "," + to_string(node -> rideCost) + ","
            + to_string(node -> tripDuration) + "),";
        printInorder(r1, r2, output, node -> rightChild);
    }

    int getChildType(RBTNode* pp, RBTNode* p) {
        if(pp -> rightChild == p) return R;
        return L;
    }

    RBTNode* getMaxNode(RBTNode *p, RBTNode *currMax) {
        if(isExternalNode(p)) return currMax;
        else {
            return getMaxNode(p -> rightChild, p);
        }
    }

    HeapNode* deleteNode(int rideNumber) {
        RBTNode *p = findNode(rideNumber, root);
        if(!p) return nullptr;

        RBTNode *pp = p -> parent, *lc = p -> leftChild, *rc = p -> rightChild, *y;
        int pColor = p -> color;
        int noOfChildren = isExternalNode(lc) && isExternalNode(rc) ? 0 : 
                            !isExternalNode(lc) && !isExternalNode(rc) ? 2 : 1;

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
        } else if(noOfChildren == 1) {
            RBTNode *lc = p -> leftChild, *rc = p -> rightChild;
            if(p == root) {
                root = isExternalNode(lc) ? rc : lc;
                root -> parent = nullptr;
                return p -> heapNode;
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
            cout << "LASTMax :" << LSTMaxNode -> rideNumber << endl;
            if(LSTMaxNode != p -> leftChild) {
                LSTMaxNode -> parent -> rightChild = LSTMaxNode -> leftChild;
                y = LSTMaxNode -> parent -> rightChild;

                pColor = LSTMaxNode -> color;

                LSTMaxNode -> copyHeapNodeExceptData(p);
                LSTMaxNode -> leftChild -> parent = LSTMaxNode;
                LSTMaxNode -> rightChild -> parent = LSTMaxNode;

                if(p == root) root = LSTMaxNode;
                else {
                    if(getChildType(LSTMaxNode -> parent, p)) 
                        LSTMaxNode -> parent -> rightChild = LSTMaxNode;
                    else LSTMaxNode -> parent -> leftChild = LSTMaxNode;
                }
                pp = LSTMaxNode;
            } else {

                // cout << "GP Ptrs :" << pp -> rideNumber << " " << pp -> leftChild -> rideNumber << " " << 
                // pp -> rightChild -> rideNumber << endl;
                // cout << "P Ptrs :" << p -> rideNumber << " " << 
                // p -> parent -> rideNumber << "-" << 
                // getChildType(p -> parent, p) << " " <<
                // p -> leftChild -> rideNumber << " " << 
                // p -> rightChild -> rideNumber << endl;
                // cout << "LSTMaxNode Ptrs :" << LSTMaxNode -> rideNumber << " " << 
                // LSTMaxNode -> parent -> rideNumber << "-" << 
                // getChildType(LSTMaxNode -> parent, LSTMaxNode) << " " <<
                // LSTMaxNode -> leftChild -> rideNumber << " " << 
                // LSTMaxNode -> rightChild -> rideNumber << endl;

                LSTMaxNode -> parent -> leftChild = LSTMaxNode -> leftChild;
                y = LSTMaxNode -> parent -> leftChild;

                cout << "DKKKK : " << LSTMaxNode -> parent -> leftChild -> rideNumber << endl;

                pColor = LSTMaxNode -> color;

                LSTMaxNode -> copyHeapNodeExceptData(p);
                LSTMaxNode -> leftChild = y;
                LSTMaxNode -> leftChild -> parent = LSTMaxNode;
                LSTMaxNode -> rightChild -> parent = LSTMaxNode;

                if(p == root) root = LSTMaxNode;
                else {
                    if(getChildType(LSTMaxNode -> parent, p)) LSTMaxNode -> parent -> rightChild = LSTMaxNode;
                    else LSTMaxNode -> parent -> leftChild = LSTMaxNode;
                }
                // cout << "LSTMaxNode Ptrs :" << LSTMaxNode -> rideNumber << " " << 
                // LSTMaxNode -> parent -> rideNumber << "-" << 
                // getChildType(LSTMaxNode -> parent, LSTMaxNode) << " " <<
                // LSTMaxNode -> leftChild -> rideNumber << " " << 
                // LSTMaxNode -> rightChild -> rideNumber << endl;
                pp = LSTMaxNode;
                // cout << "PP Ptrs :" << pp -> rideNumber << " " << 
                // pp -> parent -> rideNumber << " " <<
                // pp -> leftChild -> rideNumber << " " << 
                // pp -> rightChild -> rideNumber << endl;
                // cout << "GP Ptrs :" << pp -> parent -> rideNumber << " " << pp -> parent -> leftChild -> rideNumber << " " << 
                // pp -> parent -> rightChild -> rideNumber << endl;
            }
        }

        cout << y -> rideNumber << " " << p -> rideNumber << " " << pp -> rideNumber << endl;
        cout << "PP Ptrs :" << pp -> rideNumber << " " << 
                pp -> leftChild -> rideNumber << " " << 
                pp -> rightChild -> rideNumber << endl;

        if(y == root || y -> color == RED) {
            y -> color = BLACK;
            return p -> heapNode;
        }
        y -> parent = pp;


        // cout << "Tree is:" << endl;
        // cout << root -> rideNumber << endl;
        // cout << root -> leftChild -> rideNumber << " " << root -> rightChild -> rideNumber;
        // this -> printTree();
        
        if(pColor == BLACK) {
            adjustRBTAfterDelete(y, pp);
        }
        treeSize--;
        cout << "P:" << p -> rideNumber;
        return p -> heapNode;
    }

    void adjustRBTAfterDelete(RBTNode *y, RBTNode* py) {
        if(y == root) {
            y -> color = BLACK;
            return;
        }
        cout << "Adj RBT" << endl;
        RBTNode *v = (getChildType(py, y) == L) ? py -> rightChild : py -> leftChild;
        if(isExternalNode(v)) {
            if(!isExternalNode(y))
                y -> color = RED;
            return;
        }

        RBTNode *a = v -> leftChild, *b = v -> rightChild;
        int X = getChildType(py, y), c = v -> color, 
        n = a -> color == RED ? (b -> color == RED ? 2 : 1) : b -> color == RED ? 1 : 0;

        cout << "Xcn: " << X << " " << c << " " << n << endl;
        //cases
        
        cout << y -> rideNumber << " " << py -> rideNumber << endl;
        this -> printTree();
        cout << endl;

        if(X == R && c == BLACK && n == 0) {
            cout << "RB0" <<endl;
            RB0(y, py);
        } else if(X == R && c == BLACK && n == 1) { 
            RB1Cases(y, py, a);
        } else if(X == R && c == BLACK && n == 2) { 
            RB2(y, py);
        } else if(X == R && c == RED) { 
            RRCases(py);
        } else if(X == L && c == BLACK && n == 0) { 
            cout << "LB0" <<endl;
            LB0(y, py);
        } else if(X == L && c == BLACK && n == 1) {
            LB1Cases(y, py, b);
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
        adjustRBTAfterDelete(py, py -> parent);
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
        adjustRBTAfterDelete(py, py -> parent);
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

    void LB1Cases(RBTNode *y, RBTNode *py, RBTNode *b) {
        if(b -> color == RED) {
            cout << "LB12 case" << endl;
            LB12(y, py);
        } else {
            cout << "LB11 case" << endl;
            LB11(y, py);
        }
    }

    void RB11(RBTNode *y, RBTNode *py) {
        RBTNode *v = py -> leftChild, *a = v -> leftChild;
        a -> color = BLACK;
        v -> color = py -> color ;
        py -> color = BLACK;
        LLRotation(py);
    }

    void LB11(RBTNode *y, RBTNode *py) {
        RBTNode *v = py -> rightChild, *b = v -> leftChild;
        b -> color = BLACK;
        v -> color = BLACK ;
        py -> color = BLACK;
        RLRotation(v, py);
    }

    void RB12(RBTNode *y, RBTNode *py) {
        RBTNode *v = py -> leftChild, *w = v -> rightChild;
        w -> color = py -> color ;
        py -> color = BLACK;
        LRRotation(v, py);
    }

    void LB12(RBTNode *y, RBTNode *py) {
        RBTNode *v = py -> rightChild, *a = v -> rightChild;
        a -> color = BLACK;
        v -> color = BLACK;
        RRRotation(py);
    }

    void RB2(RBTNode *y, RBTNode *py) {
        RBTNode* w = py -> leftChild -> rightChild;
        w -> color = py -> color;
        py -> color = BLACK;
        LRRotation(py -> leftChild, py);
    }

    void LB2(RBTNode *y, RBTNode *py) {
        RBTNode* a = py -> rightChild -> leftChild;
        a -> color = py -> color;
        py -> color = BLACK;
        RLRotation(py -> rightChild, py);
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
            cout << "LR2";
            LR2(py, v, a, b);
        }
    }

    void RR0(RBTNode *py, RBTNode *v, RBTNode *b) {
        LLRotation(py);
        v -> color = BLACK;
        b -> color = RED;
    }

    void LR0(RBTNode *py, RBTNode *v, RBTNode *a) {
        RRRotation(py);
        v -> color = BLACK;
        a -> color = RED;
    }

    void RR11(RBTNode *y, RBTNode *py, RBTNode *b) {
        LRRotation(y, py);
        b -> color = BLACK;
    }

    void LR11(RBTNode *v, RBTNode *py, RBTNode *c) {
        RLRotation(v, py);
        c -> color = BLACK;
    }
    void RR12(RBTNode *py, RBTNode *v, RBTNode *w, RBTNode *x) {
        RRRotation(w);
        LRRotation(v, py);
        x -> color = BLACK;
    }

    void LR12(RBTNode *py, RBTNode *v, RBTNode *w, RBTNode *b) {
        LLRotation(w);
        RLRotation(v, py);
        b -> color = BLACK;
    }

    void RR2(RBTNode *py, RBTNode *v, RBTNode *w, RBTNode *x) {
        RRRotation(w);
        LRRotation(v, py);
        x -> color = BLACK;
    }

    void LR2(RBTNode *py, RBTNode *v, RBTNode *w, RBTNode *b) {
        LLRotation(w);
        RLRotation(v, py);
        b -> color = BLACK;
    }

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

        if(gp == root) gp -> color = BLACK;
        adjustRBT(gp);
    }

    

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

        cout << "After LL" << endl;
        this -> printTree();  
        cout << gp << endl;
        cout << endl;  
    }

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
        cout << ggp -> leftChild -> rideNumber << endl;
        this -> printTree();
        cout << endl;
    }

    void LRRotation(RBTNode* pp, RBTNode *gp) {
        RRRotation(pp);
        this -> printTree();
        cout << gp -> rideNumber << endl;
        LLRotation(gp);
        cout << gp -> rideNumber << endl;
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

                if(!node) {
                    cout << "Empty tree" << endl;
                    return;
                }
                char color = node -> color ? 'b' : 'r';

                if(node -> rideNumber > 0) 
                    cout << color << "-" << node -> rideNumber << "\t";
                if(!isExternalNode(node -> leftChild)) q.push(node -> leftChild);
                if(!isExternalNode(node -> rightChild)) q.push(node -> rightChild);

                size--;
            }
            cout << endl;
        }
    }
};