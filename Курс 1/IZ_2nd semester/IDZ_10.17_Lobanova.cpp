#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

void printMenu() {
    cout << "\n===== МЕНЮ =====\n";
    cout << "1. Создать список\n";
    cout << "2. Добавить элемент\n";
    cout << "3. Удалить элемент\n";
    cout << "4. Вывести список\n";
    cout << "5. Удалить все элементы >= M\n";
    cout << "6. Удалить весь список\n";
    cout << "7. Выйти\n";
    cout << "Выберите действие: ";
}

Node* createList(int n) {
    Node* head = nullptr;
    Node* tail = nullptr;
    
    for (int i = 0; i < n; i++) {
        Node* newNode = new Node;
        newNode->data = rand() % 101;
        newNode->next = nullptr;
        newNode->prev = tail;
        
        if (head == nullptr) {
            head = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
    }
    return head;
}

void printList(Node* head) {
    if (head == nullptr) {
        cout << "Список пуст!\n";
        return;
    }
    
    Node* current = head;
    int index = 1;  // Нумерация с 1
    while (current != nullptr) {
        cout << index << ": " << current->data << "\n";
        current = current->next;
        index++;
    }
}

Node* addElement(Node* head) {
    int pos, val;
    cout << "Введите позицию для вставки (1 - в начало, и т.д.): ";
    cin >> pos;
    cout << "Введите значение (0-100): ";
    cin >> val;
    
    if (val < 0 || val > 100) {
        cout << "Ошибка: значение должно быть от 0 до 100\n";
        return head;
    }
    
    if (pos < 1) {
        cout << "Ошибка: позиция должна быть >= 1\n";
        return head;
    }
    
    Node* newNode = new Node;
    newNode->data = val;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    
    // Вставка в начало (позиция 1)
    if (pos == 1) {
        newNode->next = head;
        if (head != nullptr) {
            head->prev = newNode;
        }
        cout << "Элемент добавлен\n";
        return newNode;
    }
    
    // Поиск позиции
    Node* current = head;
    for (int i = 1; i < pos - 1 && current != nullptr; i++) {
        current = current->next;
    }
    
    if (current == nullptr) {
        cout << "Неверная позиция!\n";
        delete newNode;
        return head;
    }
    
    // Вставка в середину или конец
    newNode->next = current->next;
    newNode->prev = current;
    
    if (current->next != nullptr) {
        current->next->prev = newNode;
    }
    current->next = newNode;
    
    cout << "Элемент добавлен\n";
    return head;
}

Node* deleteElement(Node* head) {
    if (head == nullptr) {
        cout << "Список пуст!\n";
        return head;
    }
    
    int pos;
    cout << "Введите позицию элемента для удаления: ";
    cin >> pos;
    
    if (pos < 1) {
        cout << "Ошибка: позиция должна быть >= 1\n";
        return head;
    }
    
    // Удаление первого элемента (позиция 1)
    if (pos == 1) {
        Node* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        delete temp;
        cout << "Элемент удален\n";
        return head;
    }
    
    // Поиск удаляемого элемента
    Node* current = head;
    for (int i = 1; i < pos && current != nullptr; i++) {
        current = current->next;
    }
    
    if (current == nullptr) {
        cout << "Неверная позиция!\n";
        return head;
    }
    
    // Удаление элемента
    current->prev->next = current->next;
    if (current->next != nullptr) {
        current->next->prev = current->prev;
    }
    
    delete current;
    cout << "Элемент удален\n";
    return head;
}

Node* deleteGreaterOrEqual(Node* head, int M) {
    if (head == nullptr) {
        cout << "Список пуст!\n";
        return head;
    }
    
    Node* current = head;
    int count = 0;
    
    while (current != nullptr) {
        Node* nextNode = current->next;
        
        if (current->data >= M) {
            // Если удаляем голову
            if (current->prev == nullptr) {
                head = current->next;
                if (head != nullptr) {
                    head->prev = nullptr;
                }
            } 
            // Если удаляем хвост или середину
            else {
                current->prev->next = current->next;
                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                }
            }
            delete current;
            count++;
        }
        current = nextNode;
    }
    
    cout << "Удалено элементов: " << count << "\n";
    return head;
}

void deleteAll(Node* head) {
    Node* current = head;
    int count = 0;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
        count++;
    }
    cout << "Удален весь список (" << count << " элементов)\n";
}

int main() {
    srand(time(nullptr));
    
    Node* head = nullptr;
    int choice;
    
    do {
        printMenu();
        cin >> choice;
        
        switch(choice) {
            case 1: {
                int n;
                cout << "Введите количество элементов (n >= 2): ";
                cin >> n;
                if (n >= 2) {
                    if (head != nullptr) {
                        cout << "Сначала удалите существующий список!\n";
                    } else {
                        head = createList(n);
                        cout << "Список создан\n";
                    }
                } else {
                    cout << "Ошибка: n должно быть >= 2\n";
                }
                break;
            }
            case 2:
                if (head == nullptr) {
                    cout << "Сначала создайте список (пункт 1)\n";
                } else {
                    head = addElement(head);
                }
                break;
            case 3:
                if (head == nullptr) {
                    cout << "Список пуст\n";
                } else {
                    head = deleteElement(head);
                }
                break;
            case 4:
                if (head == nullptr) {
                    cout << "Список пуст\n";
                } else {
                    printList(head);
                }
                break;
            case 5: {
                if (head == nullptr) {
                    cout << "Список пуст\n";
                } else {
                    int M;
                    cout << "Введите число M: ";
                    cin >> M;
                    head = deleteGreaterOrEqual(head, M);
                }
                break;
            }
            case 6:
                if (head == nullptr) {
                    cout << "Список уже пуст\n";
                } else {
                    deleteAll(head);
                    head = nullptr;
                }
                break;
            case 7:
                if (head != nullptr) {
                    deleteAll(head);
                }
                cout << "До свидания!\n";
                break;
            default:
                cout << "Неверный выбор!\n";
        }
    } while (choice != 7);
    
    return 0;
}