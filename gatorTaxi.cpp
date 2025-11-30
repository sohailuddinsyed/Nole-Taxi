#include <fstream>
#include<vector>

#include "MyRBT.h"
#include "stringUtils.h"

// Print node operation
void print(RBT *rbt, Heap *heap, int *args, string &output) {
    int valueToPrint = args[0];
    RBTNode *node = rbt -> findNode(valueToPrint, rbt -> root);
    if(node) node -> heapNode -> printHeapNode(output);
    else output += "(0,0,0)\n";
}
 // Print range
void printRange(RBT *rbt, Heap *heap, int *args, string &output) {
    int r1 = args[0], r2 = args[1];
    output += rbt -> range(r1, r2);
}

// Inserts a new ride in RBT and Min-Heap
void insertRide(RBT *rbt, Heap *heap, int* args, string &output) {
    RBTNode* rnode = new RBTNode(nullptr, nullptr, nullptr, nullptr, RED, args[0], args[1], args[2]);
    HeapNode* hnode = new HeapNode(nullptr, args[0], args[1], args[2]);

    // Creates a link between RBT and Min-Heap nodes
    rnode -> heapNode = hnode;
    hnode -> rbtNode = rnode;

    if(rbt -> findNode(rnode -> rideNumber, rbt -> root)) {
        output += "Duplicate RideNumber\n";
        return;
    }
    rbt -> insert(rnode);
    heap -> push(hnode);
}

// Gets the min-cost ride and deletes it from RBT and Min-Heap
void getNextRide(RBT *rbt, Heap *heap, string &output) {
    if(heap -> back == 0) {
        output += "No active ride requests\n";
        return;
    }
    // Pops the min node form Min-Heap first
    HeapNode* deletedHeapNode = heap -> pop();
    if(!deletedHeapNode) {
        output += "No active ride requests\n";
        return;
    }
    deletedHeapNode -> printHeapNode(output);
    rbt -> deleteNode(deletedHeapNode -> rbtNode -> rideNumber);
}

// Deletes a ride from RBT and Min-Heap.
void cancelRide(RBT *rbt, Heap *heap, int* args, string &output) {
    HeapNode* deletedHeapNode = rbt -> deleteNode(args[0]);
    if(!deletedHeapNode) return;
    heap -> remove(deletedHeapNode);
}

// Updates an exisiting trip in RBT and Min-Heap
void updateTrip(RBT *rbt, Heap *heap, int* args, string &output) {
    int newTD = args[1];
    RBTNode* node = rbt -> findNode(args[0], rbt -> root);
    if(node) {
        int existingTD = node -> tripDuration;
        // Case 1 : New trip Duration is less than existing duration
        // Only updates in Min-Heap
        if(newTD <= existingTD) {
            node -> tripDuration = newTD;
            heap -> update(node -> heapNode , node -> rideCost, newTD);
        } 
        // Case 2 : New trip Duration is more than existing duration but under
        // twice of exisitng duration
        // PErforms cancelRide followed by insertRide
        else if(existingTD < newTD && newTD <= 2 * existingTD) {
            cancelRide(rbt, heap, args, output);
            args[1] = node -> rideCost + 10;
            args[2] = newTD;
            insertRide(rbt, heap, args, output);
        }
        // Case 3 : New trip duration is more than exisiting duration 
        // Performs cancelRide
        else if(newTD > 2 * existingTD) {
            cancelRide(rbt, heap, args, output);
        }
    }
}

// Utility function to parse the input from a file
void parseInput(RBT *rbt, Heap *heap, int argc, char **argv) {
    fstream inputFile;
    inputFile.open(argv[1], ios::in);
    string output;

    ofstream MyFile("output_file.txt");
    if(inputFile.is_open()) {
        string fileLine;

        while(getline(inputFile, fileLine)){ 
            string operationPrefix = fileLine.substr(0, 3);
            processOperation(rbt, heap, fileLine, operationPrefix, output);
            if(output.find("Duplicate RideNumber") == -1) 
                MyFile << output;
            if(output.find("Duplicate RideNumber") != -1) {
                MyFile << "Duplicate RideNumber";
                inputFile.close();
                MyFile.close();
                return;
            }
            output = "";
        }
        inputFile.close();
    }

    MyFile << output;
    MyFile.close();
}

int main(int argc, char **argv) {
    // RBT and Min-Heap object pointers used for performing all operations
    RBT *rbt = new RBT();
    Heap *heap = new Heap();

    if(argc >= 2) {
        parseInput(rbt, heap, argc, argv);
        return 0;
    } 
}