#include <iostream>
#include <fstream>

using namespace std;
struct Node {
    char data;
    Node* next;
};

void mypush(Node*& top, char ch) {
    Node* newNode = new Node;
    newNode->data = ch;
    newNode->next = top;
    top = newNode;
}

char mypop(Node*& top) {
    if (top == nullptr) {
        return '\0';
    }
    char ch = top->data;
    Node* temp = top;
    top = top->next;
    delete temp;
    return ch;
}

bool isEmpty(Node* top) {
    return top == nullptr;
}

// Очистка стека
void clearStack(Node*& top) {
    while (!isEmpty(top)) {
        mypop(top);
    }
}

int main() {
    Node* stack = nullptr; 
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Ошибка чтения из файла" << endl;
        return 1;
    }

    char ch;
    while (inputFile.get(ch)) {
        mypush(stack, ch);
    }
    inputFile.close();

    cout << "Текст в обратном порядке:" << endl;
    while (!isEmpty(stack)) {
        cout << mypop(stack);
    }
    cout << endl;

    clearStack(stack);
    
    return 0;
}