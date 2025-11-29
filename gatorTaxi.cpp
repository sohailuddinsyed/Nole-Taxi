#include <fstream>
#include<vector>

#include "MyRBT.h"
#include "stringUtils.h"

void print(RBT *rbt, Heap *heap, int *args, string &output) {
    cout << "-----------------------------------------------------------" << endl;
    cout << "print: " << args[0] << endl;
    output += rbt -> range(args[0], args[0]);
    // cout << output << endl;
}

void printRange(RBT *rbt, Heap *heap, int *args, string &output) {
    cout << "-----------------------------------------------------------" << endl;
    cout << "printRange: " << args[0] << " " << args[1] << endl;
    output += rbt -> range(args[0], args[1]);
    // cout << output << endl;
}

void insertRide(RBT *rbt, Heap *heap, int* args, string &output) {
    cout << "-----------------------------------------------------------" << endl;
    cout << "insert: " << args[0] << " " << args[1] << " " << args[2] << endl;
    RBTNode* rnode = new RBTNode(nullptr, nullptr, nullptr, nullptr, RED, args[0], args[1], args[2]);
    HeapNode* hnode = new HeapNode(nullptr, args[0], args[1], args[2]);

    rnode -> heapNode = hnode;
    hnode -> rbtNode = rnode;

    if(rbt -> findNode(rnode -> rideNumber, rbt -> root)) {
        output += "Duplicate RideNumber\n";
        // exit(1);
        return;
    }

    rbt -> insert(rnode);
    heap -> push(hnode);

    rbt -> printTree();
    heap -> printHeap();
}

void getNextRide(RBT *rbt, Heap *heap, string &output) {
    cout << "-----------------------------------------------------------" << endl;
    
    cout << "getNextRide " << heap -> heap[0] -> rideNumber << endl;
    HeapNode* deletedHeapNode = heap -> pop();
    if(!deletedHeapNode) {
        output += "No active ride requests\n";
        return;
    }
    deletedHeapNode -> printHeapNode(output);
    // cout << rbt -> root -> rideNumber << endl;
    rbt -> deleteNode(deletedHeapNode -> rbtNode -> rideNumber);
// 
    cout << endl;
    heap -> printHeap();
    rbt -> printTree();
}

void cancelRide(RBT *rbt, Heap *heap, int* args, string &output) {
    cout << "-----------------------------------------------------------" << endl;
    cout << "cancelRide: " << args[0] << endl;
    HeapNode* deletedHeapNode = rbt -> deleteNode(args[0]);
    if(!deletedHeapNode) {
        cout << "No ride" << endl;
        // output += "\n";
        return;
    }
    heap -> remove(deletedHeapNode);

    heap -> printHeap();
    rbt -> printTree();
    cout << deletedHeapNode -> rideNumber;
    cout << rbt -> root -> rideNumber;
}

void updateTrip(RBT *rbt, Heap *heap, int* args, string &output) {
    cout << "-----------------------------------------------------------" << endl;
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

    if(inputFile.is_open()) {
        string fileLine;
        while(getline(inputFile, fileLine)){ 
            string operationPrefix = fileLine.substr(0, 3);
            processOperation(rbt, heap, fileLine, operationPrefix, output);
            if(output.find_first_of("Duplicate RideNumber") != string::npos) {
                inputFile.close();
                ofstream MyFile("output_file.txt");
    MyFile << output;
    MyFile.close();
    return;
            }
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

    vector<int> input = {7,6};

    for(int val : input) {
        rnode = new RBTNode(nullptr, nullptr, nullptr, nullptr, RED, val, 200, 10);
        hnode = new HeapNode(nullptr, val, 200, 10);
        rbt -> insert(rnode);
        heap -> push(hnode);
        rnode -> heapNode = hnode;
        hnode -> rbtNode = rnode;

        cout << "Inserted " << val << endl;
            cout << "Tree size:" << rbt -> getTreeSize(rbt -> root) << endl;
        rbt -> printTree();
    }

    vector<int> dels = {7};

    for(int val : dels) {
        rbt -> deleteNode(val);
        cout << "Deleted " << val << endl;
        cout << "Tree size:" << rbt -> getTreeSize(rbt -> root) << endl;
        rbt -> printTree();
    }

    // cout << rbt -> range(9,100);


    // heap -> push(new HeapNode(nullptr, 13,70,30));
    // heap -> push(new HeapNode(nullptr, 11,80,210));
    // heap -> push(new HeapNode(nullptr, 30,9,9));
    // // heap -> getTopNode();
    // // cout << heap -> getSize() << endl;


    // heap -> push(new HeapNode(nullptr, 20,8,12));
    // heap -> pop();
    // // heap -> getTopNode();
    // HeapNode *h = new HeapNode(nullptr, 30,9,8);
    // heap -> push(h);
    // // cout << heap -> getSize() << endl;
    // heap -> printHeap();

    // heap -> remove(h);
    // heap -> printHeap();

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