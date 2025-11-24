#include <fstream>
#include<vector>

#include "MyRBT.h"
#include "stringUtils.h"

void print(RBT *rbt, Heap *heap, int *args, string &output) {
    cout << "print: " << args[0] << endl;
    output += rbt -> range(args[0], args[0]);
}

void printRange(RBT *rbt, Heap *heap, int *args, string &output) {
    cout << "printRange: " << args[0] << " " << args[1] << endl;
    output += rbt -> range(args[0], args[1]);
}

void insertRide(RBT *rbt, Heap *heap, int* args, string &output) {
    cout << "insert: " << args[0] << " " << args[1] << " " << args[2] << endl;
    RBTNode* rnode = new RBTNode(nullptr, nullptr, nullptr, nullptr, RED, args[0], args[1], args[2]);
    HeapNode* hnode = new HeapNode(nullptr, args[0], args[1], args[2]);

    rnode -> heapNode = hnode;
    hnode -> rbtNode = rnode;

    if(rbt -> findNode(rnode -> rideNumber, rbt -> root)) {
        output += "Duplicate RideNumber\n";
        return;
    }

    rbt -> insert(rnode);
    heap -> push(hnode);

    rbt -> printTree();
    heap -> printHeap();
}

void getNextRide(RBT *rbt, Heap *heap, string &output) {
    cout << "getNextRide" << endl;

    if(heap -> getSize() == 0) {
        output += "No active ride requests\n";
        return;
    }
    HeapNode* deletedHeapNode = heap -> pop();
    deletedHeapNode -> printHeapNode(output);
    // cout << rbt -> root -> rideNumber << endl;
    rbt -> deleteNode(deletedHeapNode -> rbtNode -> rideNumber);

    cout << endl;
    heap -> printHeap();
    rbt -> printTree();
}

void cancelRide(RBT *rbt, Heap *heap, int* args, string &output) {
    cout << "cancelRide: " << args[0] << endl;
    RBTNode* deletedRBTNode = rbt -> deleteNode(args[0]);
    heap -> remove(deletedRBTNode -> heapNode);

    heap -> printHeap();
    rbt -> printTree();
}

void updateTrip(RBT *rbt, Heap *heap, int* args, string &output) {
    int newTD = args[1];
    cout<< "updateTrip: " << args[0] << " " << newTD << endl;
    RBTNode* node = rbt -> findNode(args[0], rbt -> root);
    if(node) {
        int existingTD = node -> tripDuration;
        if(newTD <= existingTD) {
            node -> tripDuration = newTD;
            heap -> update(node -> heapNode , node -> rideCost, newTD);
            heap -> printHeap();
            rbt -> printTree();
        } else if(existingTD < newTD && newTD <= 2 * existingTD) {
            cancelRide(rbt, heap, args, output);
            args[1] = node -> rideCost + 10;
            args[2] = newTD;
            insertRide(rbt, heap, args, output);
        } else if(newTD > 2 * existingTD) {
            cancelRide(rbt, heap, args, output);
        }
    } else cout << "No trip to update" << endl;
}

void parseInput(RBT *rbt, Heap *heap, int argc, char **argv) {
    fstream inputFile;
    inputFile.open(argv[1], ios::in);
    string output;

    if(inputFile.is_open()){
        string fileLine;
        while(getline(inputFile, fileLine)){ 
            string operationPrefix = fileLine.substr(0, 3);
            processOperation(rbt, heap, fileLine, operationPrefix, output);
        }
        inputFile.close();
    }

    ofstream MyFile("output_file.txt");
    MyFile << output;
    MyFile.close();
}

int main(int argc, char **argv) {
    RBT *rbt = new RBT();
    Heap *heap = new Heap();

    if(argc >= 2) {
        parseInput(rbt, heap, argc, argv);
        return 0;
    } else cout << "Insufficient arguments - Please provide input file" << endl;
    return 0;

    RBTNode *rnode;
    HeapNode *hnode;

    // vector<int> input = {41,38,31,12,19,8};

    // for(int val : input) {
    //     rnode = new RBTNode(nullptr, nullptr, nullptr, nullptr, RED, val, 200, 10);
    //     hnode = new HeapNode(nullptr, val, 200, 10);
    //     rbt -> insert(rnode);
    //     heap -> push(hnode);
        // rnode -> heapNode = hnode;
        // hnode -> rbtNode = rnode;

    //     cout << "Inserted " << val << endl;
    //         cout << "Tree size:" << rbt -> getTreeSize(rbt -> root) << endl;
    //     rbt -> printTree();
    // }

    // vector<int> dels = {8,12,19,31,38,41};

    // for(int val : dels) {
    //     rbt -> deleteNode(val);
    //     cout << "Deleted " << val << endl;
    //     cout << "Tree size:" << rbt -> getTreeSize(rbt -> root) << endl;
    //     rbt -> printTree();
    // }

    // cout << rbt -> range(9,100);


    heap -> push(new HeapNode(nullptr, 10,11,12));
    heap -> push(new HeapNode(nullptr, 20,9,12));
    heap -> push(new HeapNode(nullptr, 30,9,9));
    // heap -> getTopNode();
    // cout << heap -> getSize() << endl;


    heap -> push(new HeapNode(nullptr, 20,8,12));
    // heap -> pop();
    // heap -> getTopNode();
    HeapNode *h = new HeapNode(nullptr, 30,9,8);
    heap -> push(h);
    // cout << heap -> getSize() << endl;
    heap -> printHeap();

    heap -> remove(h);
    heap -> printHeap();

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