#include<iostream>
using namespace std;

class RBTNode;

class HeapNode {
public :
    RBTNode *rbtNode;
    int rideNumber, rideCost, tripDuration;
    HeapNode() {
        rbtNode = nullptr;
    }
    HeapNode(RBTNode *rbtNode, int rideNumber, int rideCost, int tripDuration) {
        this -> rbtNode = rbtNode;
        this -> rideNumber = rideNumber;
        this -> rideCost = rideCost;
        this -> tripDuration = tripDuration;
    }
    void printHeapNode() {
        cout << "(" << this -> rideNumber << ", " << 
        this -> rideCost << ", " << 
        this -> tripDuration << ")" << endl;
    }
};

class Heap {
    int back;
    HeapNode* heap[2000];
public:
    Heap() {
        back = 0;
    }

    int getSize() {
        return back;
    }
    void push(HeapNode *heapNode) {
        heap[back] = heapNode;
        heapifyUp(back);
        back++;
    }
    
    void getTopNode () {
        heap[0] -> printHeapNode();
    }
    
    HeapNode* top () {
        return heap[0];
    }

    void pop() {
        back--;
        heap[0] = heap[back];
        heapifyDown(0);
    }

    void heapifyUp(int index) {
        if(index == 0) return;
        int parent = index % 2 ? (index - 1)/2 : (index - 1)/2;

        int prc = heap[parent] -> rideCost, crc = heap[index] -> rideCost;
        int ptd = heap[parent] -> tripDuration, ctd = heap[index] -> tripDuration;
        if(prc < crc) return;

        if(prc > crc) swap(heap[parent], heap[index]);
        else if(ptd > ctd) swap(heap[parent], heap[index]);
        else return;

        heapifyUp(parent);
    }

    void heapifyDown(int parent) {
        if(parent >= back) return;

        int leftChild = parent * 2 + 1, rightChild = parent * 2 + 2;

        int prc = heap[parent] -> rideCost, 
            lcrc = heap[leftChild] -> rideCost, 
            rcrc = heap[rightChild] -> rideCost;

        int ptd = heap[parent] -> tripDuration, 
            lctd = heap[leftChild] -> tripDuration, 
            rctd = heap[rightChild] -> tripDuration;

        if(prc < lcrc && prc < rcrc) return;

        int childToSwap = rightChild;
        if(prc > lcrc || ptd > lctd) childToSwap = leftChild;
        else if(prc > rcrc || ptd > rctd) childToSwap = rightChild;

        swap(heap[parent], heap[childToSwap]);
        heapifyDown(childToSwap);
    }

    void update() {}
    void remove() {}
};