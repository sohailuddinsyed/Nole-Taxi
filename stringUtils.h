#include<string>
#include<iostream>

// Forward declaration of the operations
void print(int *args);
void printRange(int *args);
void insertRide(int* args);
void getNextRide();
void cancelRide(int* args);
void updateTrip(int* args);


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

void parseArgs2(int *args, string line) {
    int index = line.find_first_of("(") + 1, len = line.size() - index;
    string argStr = line.substr(index, len - 1);

    int firstComma = argStr.find_first_of(",");
    args[0] = stoi(argStr.substr(0, firstComma));
    args[1] = stoi(argStr.substr(firstComma + 1));    
}

void parseArgs1(int *args, string line) {
    int index = line.find_first_of("(") + 1, len = line.size() - index;
    args[0] = stoi(line.substr(index, len - 1)); 
}

// Processes input to parse parameters and call required operation functions
void processOperation(string line, string operationPrefix) {
    int args[3];
    if(operationPrefix == "Pri") {
        if(line.find(",") != string::npos) {
            parseArgs2(args, line);
            printRange(args);
        } else {
            parseArgs1(args, line);
            print(args);
        }
    } else if(operationPrefix == "Ins") {
        parseArgs3(args, line);
        insertRide(args);
    } else if(operationPrefix == "Upd") {
        parseArgs2(args, line);
        updateTrip(args);
    } else if(operationPrefix == "Can") {
        parseArgs1(args, line);
        cancelRide(args);
    } else if(operationPrefix == "Get") {
        getNextRide();
    }
}