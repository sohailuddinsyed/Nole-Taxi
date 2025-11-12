#include <fstream>
#include <string>

#include "MyRBT.h"

void insertRide(int* args) {
    cout << args[1];
}

void parseArgs(int *args, string line) {
    int index = line.find_first_of("(") + 1, len = line.size() - index;
    string argStr = line.substr(index, len - 1);

    int firstComma = argStr.find_first_of(",");
    args[0] = stoi(argStr.substr(0, firstComma));

    int secondComma = argStr.find_last_of(",");
    if(secondComma == string::npos) return;
    args[1] = stoi(argStr.substr(firstComma + 1, secondComma - firstComma));    
}

void parseInput(int argc, char **argv) {
    fstream newfile;
    newfile.open(argv[1], ios::in);
    if(newfile.is_open()){
        string line;
        while(getline(newfile, line)){ 
            string operation = line.substr(0, 3);
            int args[3];
            if(operation == "Ins") {
                parseArgs(args, line);
                insertRide(args);
            } 
        }
        newfile.close();
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


    rnode = new RBTNode(nullptr, nullptr, nullptr, nullptr, RED, 2, 300, 10);
    hnode = new HeapNode(nullptr, 1024, 300, 10);
    rbt -> insert(rnode);
    heap -> push(hnode);
    rnode -> heapNode = hnode;
    hnode -> rbtNode = rnode;

    // heap -> getTopNode();
    // cout << heap -> getSize() << endl;


    rnode = new RBTNode(nullptr, nullptr, nullptr, nullptr, RED, 1, 200, 10);
    hnode = new HeapNode(nullptr, 1022, 200, 10);
    rbt -> insert(rnode);
    heap -> push(hnode);
    rnode -> heapNode = hnode;
    hnode -> rbtNode = rnode;

        rnode = new RBTNode(nullptr, nullptr, nullptr, nullptr, RED, 4, 200, 10);
    hnode = new HeapNode(nullptr, 1022, 200, 10);
    rbt -> insert(rnode);
    heap -> push(hnode);
    rnode -> heapNode = hnode;
    hnode -> rbtNode = rnode;

        rnode = new RBTNode(nullptr, nullptr, nullptr, nullptr, RED, 5, 200, 10);
    hnode = new HeapNode(nullptr, 1022, 200, 10);
    rbt -> insert(rnode);
    heap -> push(hnode);
    rnode -> heapNode = hnode;
    hnode -> rbtNode = rnode;

        rnode = new RBTNode(nullptr, nullptr, nullptr, nullptr, RED, 9, 200, 10);
    hnode = new HeapNode(nullptr, 1022, 200, 10);
    rbt -> insert(rnode);
    heap -> push(hnode);
    rnode -> heapNode = hnode;
    hnode -> rbtNode = rnode;

        rnode = new RBTNode(nullptr, nullptr, nullptr, nullptr, RED, 3, 200, 10);
    hnode = new HeapNode(nullptr, 1022, 200, 10);
    rbt -> insert(rnode);
    heap -> push(hnode);
    rnode -> heapNode = hnode;
    hnode -> rbtNode = rnode;

    //     rnode = new RBTNode(nullptr, nullptr, nullptr, nullptr, RED, 6, 200, 10);
    // hnode = new HeapNode(nullptr, 1022, 200, 10);
    // rbt -> insert(rnode);
    // heap -> push(hnode);
    // rnode -> heapNode = hnode;
    // hnode -> rbtNode = rnode;

    //     rnode = new RBTNode(nullptr, nullptr, nullptr, nullptr, RED, 7, 200, 10);
    // hnode = new HeapNode(nullptr, 1022, 200, 10);
    // rbt -> insert(rnode);
    // heap -> push(hnode);
    // rnode -> heapNode = hnode;
    // hnode -> rbtNode = rnode;


    // heap -> getTopNode();
    // cout << heap -> getSize() << endl;


    // rnode = heap -> top() -> rbtNode;

    // rbt -> printTree();
    // cout << endl;

    // rnode = new RBTNode(nullptr, nullptr, nullptr, nullptr, RED, 1022, 100, 10);
    // hnode = new HeapNode(nullptr, 1025, 100, 10);
    // rbt -> insert(rnode);
    // heap -> push(hnode);
    // rnode -> heapNode = hnode;
    // hnode -> rbtNode = rnode;

    // rnode = new RBTNode(nullptr, nullptr, nullptr, nullptr, RED, 1019, 99, 10);
    // hnode = new HeapNode(nullptr, 1026, 99, 10);
    // rbt -> insert(rnode);
    // heap -> push(hnode);
    // rnode -> heapNode = hnode;
    // hnode -> rbtNode = rnode;

    
    // rnode = new RBTNode(nullptr, nullptr, nullptr, nullptr, RED, 1020, 98, 10);
    // hnode = new HeapNode(nullptr, 1020, 98, 10);
    // rbt -> insert(rnode);
    // heap -> push(hnode);
    // rnode -> heapNode = hnode;
    // hnode -> rbtNode = rnode;

    rbt -> printTree();
    // cout << heap -> getSize() << endl;
    cout << rbt -> treeSize << endl;
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