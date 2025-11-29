#include<iostream>
#include<math.h>
using namespace std;

class RBTNode;

class HeapNode {
public :
    RBTNode *rbtNode;
    int index, rideNumber, rideCost, tripDuration;
    HeapNode() {
        index = -1;
        rideNumber = 0;
        rideCost = 0;
        tripDuration = 0;
        rbtNode = nullptr;
    }

    HeapNode(RBTNode *rbtNode, int rideNumber, int rideCost, int tripDuration) {
        this -> index = -1;
        this -> rbtNode = rbtNode;
        this -> rideNumber = rideNumber;
        this -> rideCost = rideCost;
        this -> tripDuration = tripDuration;
    }

    void printHeapNode() {
        cout << "(" << this -> index << ", " <<
        this -> rideNumber << ", " << 
        this -> rideCost << ", " << 
        this -> tripDuration << ")";
    }

    void printHeapNode(string &output) {
        output += "(" + to_string(this -> rideNumber) + "," + 
        to_string(this -> rideCost) + "," + 
        to_string(this -> tripDuration) + ")\n";
    }
};

class Heap {
public:
    HeapNode* heap[2000];
    int back;
    Heap() {
        back = 0;
    }

    int getSize() {
        return back;
    }

    void push(HeapNode *heapNode) {
        heap[back] = heapNode;
        heap[back] -> index = back;
        heapifyUp(back);
        back++;
    }

    void getTopNode () {
        heap[0] -> printHeapNode();
    }
    
    HeapNode* top () {
        return heap[0];
    }

    HeapNode* pop() {
        if(back == 0) return nullptr;
        back--;
        cout << back;
        HeapNode *deletedNode = heap[0];
        heap[0] = heap[back];
        heap[0] -> index = 0;
        heapifyDown(0);
        return deletedNode;
    }

    void remove(HeapNode* heapNode) {
        int index = heapNode -> index;

        back--;
        heap[index] = heap[back];
        heap[index] -> index = index;
        heapifyDown(index);
    }

    void heapifyUp(int childIndex) {
        if(childIndex == 0) return ;
        int parent = childIndex % 2 ? (childIndex - 1)/2 : (childIndex - 1)/2;

        int prc = heap[parent] -> rideCost, crc = heap[childIndex] -> rideCost;
        int ptd = heap[parent] -> tripDuration, ctd = heap[childIndex] -> tripDuration;
        
        if(prc < crc) return;

        if(prc > crc) {
            swap(heap[parent] -> index, heap[childIndex] -> index);
            swap(heap[parent], heap[childIndex]);
        } else if(ptd > ctd) {
            swap(heap[parent] -> index, heap[childIndex] -> index);
            swap(heap[parent], heap[childIndex]);
        } else return ;

        heapifyUp(parent);
    }

    void heapifyDown(int parent) {
        int leftChild = parent * 2 + 1, rightChild = parent * 2 + 2;
        if(leftChild >= back && rightChild >= back) return;

        int prc = heap[parent] -> rideCost, 
            lcrc = heap[leftChild] -> rideCost;
        int ptd = heap[parent] -> tripDuration, 
            lctd = heap[leftChild] -> tripDuration;
        int childToSwap = rightChild;

        // If only lc exists
        if(rightChild == back) {
            if(prc > lcrc || (prc == lcrc && ptd > lctd)) 
                childToSwap = leftChild;
        } else {
            int rcrc = heap[rightChild] -> rideCost, 
                rctd = heap[rightChild] -> tripDuration;

            if(prc < lcrc && prc < rcrc) return;

            if(lcrc < rcrc) {
                childToSwap = leftChild;
            } else if(lcrc == rcrc) {
                if(lctd < rctd) childToSwap = leftChild;
                else childToSwap = rightChild;
            } else childToSwap = rightChild;
        }

        if(rightChild == back && childToSwap == rightChild) return;
        
        heap[parent] -> index = childToSwap;
        heap[childToSwap] -> index = parent;

        HeapNode *p = heap[parent];
        heap[parent] = heap[childToSwap];
        heap[childToSwap] = p;

        heapifyDown(childToSwap);
    }

    void update(HeapNode* heapNode, int newRideCost, int newTripDuration) {
        if(newRideCost > heapNode -> rideCost) {
            heapNode -> rideCost = newRideCost;
            heapifyDown(heapNode -> index);
        } else if(newTripDuration <= heapNode -> tripDuration) {
            heapNode -> tripDuration = newTripDuration;
            heapifyUp(heapNode -> index);
        } else if(newTripDuration > heapNode -> tripDuration) {
            heapNode -> tripDuration = newTripDuration;
            heapifyDown(heapNode -> index);
        }
    }


    void printHeap() {
        int level = 0, limit = 0;

        for(int i = 0; i < back; i++) {
            heap[i] -> printHeapNode();
            cout << ", ";
            if(i == limit) {
                limit += pow(2, ++level);
                cout << endl;
            }
        }
        cout << endl;
    }
};