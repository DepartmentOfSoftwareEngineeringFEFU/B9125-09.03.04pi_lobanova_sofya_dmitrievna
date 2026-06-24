#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

struct Node {
    char name[50];     
    Node* next;        
};

void mypush(Node*& circle, const char* name) {
    Node* newNode = new Node;
    strcpy(newNode->name, name);
    
    if (circle == nullptr) {
        newNode->next = newNode;
        circle = newNode;
    } else {
        Node* temp = circle;
        while (temp->next != circle) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = circle;
    }
}

char* mypop(Node*& circle, Node* toRemove) {
    static char removedName[50];
    strcpy(removedName, toRemove->name);
    
    if (circle == circle->next) {
        delete toRemove;
        circle = nullptr;
    } else {
        Node* prev = circle;
        while (prev->next != toRemove) {
            prev = prev->next;
        }

        prev->next = toRemove->next;
        
        if (circle == toRemove) {
            circle = toRemove->next;
        }
        
        delete toRemove;
    }
    
    return removedName;
}

void printCircle(Node* circle) {
    if (circle == nullptr) {
        cout << "Круг пуст." << endl;
        return;
    }
    
    Node* current = circle;
    cout << "Участники круга: ";
    do {
        cout << current->name;
        current = current->next;
        if (current != circle) cout << " -> ";
    } while (current != circle);
    cout << endl;
}

// Очистка всего кольца
void clearCircle(Node*& circle) {
    while (circle != nullptr) {
        mypop(circle, circle);
    }
}

void fillCircle(Node*& circle, int n) {
    const char* defaultNames[] = {
        "Аня", "Боря", "Витя", "Галя", "Дима",
        "Елена", "Женя", "Зина", "Игорь", "Коля"
    };
    
    for (int i = 0; i < n; i++) {
        if (i < 10) {
            mypush(circle, defaultNames[i]);
        } else {
            char tempName[20];
            sprintf(tempName, "Участник%d", i + 1);
            mypush(circle, tempName);
        }
    }
}

int main() {
    srand(time(nullptr));
    
    Node* circle = nullptr;
    int N, k;
    
    cout << "=== ИГРА-СЧИТАЛОЧКА ===" << endl;
    cout << "Дети стоят в кругу и повторяют считалочку." << endl;
    cout << "Тот, на ком считалочка заканчивается, выходит из круга." << endl;
    cout << "Игра продолжается, пока не останется один победитель!" << endl;
    cout << endl;
    
    // Ввод параметров
    cout << "Введите количество участников N (N > k): ";
    cin >> N;
    
    cout << "Введите количество слов в считалочке k: ";
    cin >> k;
    
    if (N <= k) {
        cout << "Ошибка: N должно быть больше k!" << endl;
        return 1;
    }
    
    fillCircle(circle, N);
    
    cout << endl;
    cout << "Начальный состав:" << endl;
    printCircle(circle);
    cout << endl;
    
    Node* current = circle;  
    int round = 1;
    
    while (circle != nullptr && circle->next != circle) {
        cout << "=== Раунд " << round << " ===" << endl;
        
        for (int i = 1; i < k; i++) {
            current = current->next;
        }

        cout << "Считалочка закончилась на: " << current->name << endl;
  
        Node* nextPlayer = current->next;

        char* eliminated = mypop(circle, current);
        cout << "-> " << eliminated << " покидает круг!" << endl;
        
        current = nextPlayer;        

        if (circle != nullptr) {
            cout << "Остались: ";
            printCircle(circle);
        }
        cout << "Новый ведущий: " << current->name << endl;
        cout << endl;
        
        round++;
        
        // Небольшая задержка для читаемости
        // system("pause"); // можно раскомментировать для пошагового режима
    }
    

    cout << "========================================" << endl;
    cout << "           ИГРА ЗАКОНЧЕНА!" << endl;
    if (circle != nullptr) {
        cout << "🏆 ПОБЕДИТЕЛЬ: " << circle->name << "! 🏆" << endl;
    } else {
        cout << "Что-то пошло не так..." << endl;
    }
    cout << "========================================" << endl;
    
    // Очищаем память
    clearCircle(circle);
    
    return 0;
}