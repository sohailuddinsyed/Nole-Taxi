#include<string>
#include<iostream>

// Forward declaration of the file input parsing operations
void print(RBT *rbt, Heap *heap, int *args, string &output);
void printRange(RBT *rbt, Heap *heap, int *args, string &output);
void insertRide(RBT *rbt, Heap *heap, int* args, string &output);
void getNextRide(RBT *rbt, Heap *heap, string &output);
void cancelRide(RBT *rbt, Heap *heap, int* args, string &output);
void updateTrip(RBT *rbt, Heap *heap, int* args, string &output);
void parseInput(RBT *rbt, Heap *heap, int argc, char **argv, string &output);

// Parses Insert triplets from input
void parseArgs3(int *args, string line) {
    int index = line.find_first_of("(") + 1, len = line.size() - index;
    string argStr = line.substr(index, len - 1);

    int firstComma = argStr.find_first_of(",");
    args[0] = stoi(argStr.substr(0, firstComma));

    int secondComma = argStr.find_last_of(",");
    if(secondComma == string::npos) return;
    args[1] = stoi(argStr.substr(firstComma + 1, secondComma - firstComma));
    args[2] = stoi(argStr.substr(secondComma + 1));
}

// Parses Print triplets from input
void parseArgs2(int *args, string line) {
    int index = line.find_first_of("(") + 1, len = line.size() - index;
    string argStr = line.substr(index, len - 1);

    int firstComma = argStr.find_first_of(",");
    args[0] = stoi(argStr.substr(0, firstComma));
    args[1] = stoi(argStr.substr(firstComma + 1));    
}

// Parses CancelRide triplet from input
void parseArgs1(int *args, string line) {
    int index = line.find_first_of("(") + 1, len = line.size() - index;
    args[0] = stoi(line.substr(index, len - 1)); 
}

// Processes input to parse parameters and call required operations for Nole Taxi
void processOperation(RBT *rbt, Heap *heap, string line, string operationPrefix, string &output) {
    int args[3];
    if(operationPrefix == "Pri") {
        if(line.find(",") != string::npos) {
            parseArgs2(args, line);
            printRange(rbt, heap, args, output);
        } else {
            parseArgs1(args, line);
            print(rbt, heap, args, output);
        }
    } else if(operationPrefix == "Ins") {
        parseArgs3(args, line);
        insertRide(rbt, heap, args, output);
    } else if(operationPrefix == "Upd") {
        parseArgs2(args, line);
        updateTrip(rbt, heap, args, output);
    } else if(operationPrefix == "Can") {
        parseArgs1(args, line);
        cancelRide(rbt, heap, args, output);
    } else if(operationPrefix == "Get") {
        getNextRide(rbt, heap, output);
    }
}