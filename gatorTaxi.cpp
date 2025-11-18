#include <fstream>

#include "MyRBT.h"
#include "stringUtils.h"

void print(int *args) {
    cout << "print: " << args[0] << endl;
    // range(args[0], args[0]);
}

void printRange(int *args) {
    cout << "printRange: " << args[0] << " " << args[1] << endl;
    // range(args[0], args[1]);
}

void insertRide(int* args) {
    cout << "insert: " << args[0] << " " << args[1] << " " << args[2] << endl;
}

void getNextRide() {
    cout << "getNextRide" << endl;
}

void cancelRide(int* args) {
    cout << "cancelRide: " << args[0] << endl;
}

void updateTrip(int* args) {
    cout<< "updateTrip: " << args[0] << " " << args[1] << endl;
}

void parseInput(int argc, char **argv) {
    fstream inputFile;
    inputFile.open(argv[1], ios::in);

    if(inputFile.is_open()){
        string fileLine;
        while(getline(inputFile, fileLine)){ 
            string operationPrefix = fileLine.substr(0, 3);
            processOperation(fileLine, operationPrefix);
        }
        inputFile.close();
    }
}

int main(int argc, char **argv) {
    if(argc > 1) {
        parseInput(argc, argv);
        return 0;
    }

    RBT *rbt = new RBT();
    Heap *heap = new Heap();
    RBTNode *rnode;
    HeapNode *hnode;

        rnode = new RBTNode(nullptr, nullptr, nullptr, nullptr, RED, 41, 200, 10);
    hnode = new HeapNode(nullptr, 1022, 200, 10);
    rbt -> insert(rnode);
    heap -> push(hnode);
    rnode -> heapNode = hnode;
    hnode -> rbtNode = rnode;
    rbt -> printTree();


        rnode = new RBTNode(nullptr, nullptr, nullptr, nullptr, RED, 38, 200, 10);
    hnode = new HeapNode(nullptr, 1022, 200, 10);
    rbt -> insert(rnode);
    heap -> push(hnode);
    rnode -> heapNode = hnode;
    hnode -> rbtNode = rnode;
    rbt -> printTree();


        rnode = new RBTNode(nullptr, nullptr, nullptr, nullptr, RED, 31, 200, 10);
    hnode = new HeapNode(nullptr, 1022, 200, 10);
    rbt -> insert(rnode);
    heap -> push(hnode);
    rnode -> heapNode = hnode;
    hnode -> rbtNode = rnode;
    rbt -> printTree();


        rnode = new RBTNode(nullptr, nullptr, nullptr, nullptr, RED, 12, 200, 10);
    hnode = new HeapNode(nullptr, 1022, 200, 10);
    rbt -> insert(rnode);
    heap -> push(hnode);
    rnode -> heapNode = hnode;
    hnode -> rbtNode = rnode;
    rbt -> printTree();


        rnode = new RBTNode(nullptr, nullptr, nullptr, nullptr, RED, 19, 200, 10);
    hnode = new HeapNode(nullptr, 1022, 200, 10);
    rbt -> insert(rnode);
    heap -> push(hnode);
    rnode -> heapNode = hnode;
    hnode -> rbtNode = rnode;
    rbt -> printTree();


        rnode = new RBTNode(nullptr, nullptr, nullptr, nullptr, RED, 8, 200, 10);
    hnode = new HeapNode(nullptr, 1022, 200, 10);
    rbt -> insert(rnode);
    heap -> push(hnode);
    rnode -> heapNode = hnode;
    hnode -> rbtNode = rnode;
    rbt -> printTree();

    
    // rnode = new RBTNode(nullptr, nullptr, nullptr, nullptr, RED, 14, 200, 10);
    // hnode = new HeapNode(nullptr, 1022, 200, 10);
    // rbt -> insert(rnode);
    // heap -> push(hnode);
    // rnode -> heapNode = hnode;
    // hnode -> rbtNode = rnode;
    // rbt -> printTree();

    //         rnode = new RBTNode(nullptr, nullptr, nullptr, nullptr, RED, 18, 200, 10);
    // hnode = new HeapNode(nullptr, 1022, 200, 10);
    // rbt -> insert(rnode);
    // heap -> push(hnode);
    // rnode -> heapNode = hnode;
    // hnode -> rbtNode = rnode;
    // rbt -> printTree();

    //         rnode = new RBTNode(nullptr, nullptr, nullptr, nullptr, RED, 16, 200, 10);
    // hnode = new HeapNode(nullptr, 1022, 200, 10);
    // rbt -> insert(rnode);
    // heap -> push(hnode);
    // rnode -> heapNode = hnode;
    // hnode -> rbtNode = rnode;
    // rbt -> printTree();

    //         rnode = new RBTNode(nullptr, nullptr, nullptr, nullptr, RED, 17, 200, 10);
    // hnode = new HeapNode(nullptr, 1022, 200, 10);
    // rbt -> insert(rnode);
    // heap -> push(hnode);
    // rnode -> heapNode = hnode;
    // hnode -> rbtNode = rnode;
    // rbt -> printTree();



    cout << "Tree size:" << rbt -> getTreeSize(rbt -> root) << endl;
    // rbt -> printTree();

    cout << rbt -> range(-10,25);

    // rbt -> deleteNode(4);
    // rbt -> deleteNode(9);

    // cout << "Tree size:" << rbt -> treeSize << endl;
    // rbt -> printTree();

    // rbt -> deleteNode(9);

    // cout << "Tree size:" << rbt -> getTreeSize(rbt -> root) << endl;
    // rbt -> printTree();

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