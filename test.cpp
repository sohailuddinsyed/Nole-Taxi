#include<iostream>

using namespace std;

void addToStr(string &s) {
    s += "Test";
}

void doOperation(string &s) {
    addToStr(s);
}

int main() {
    string s;
    doOperation(s);
    cout << s;
}