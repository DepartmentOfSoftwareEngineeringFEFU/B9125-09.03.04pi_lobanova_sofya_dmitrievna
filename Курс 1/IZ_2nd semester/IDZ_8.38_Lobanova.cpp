#include <iostream>
#include <string>
#include <climits>
#include <fstream>
#include <sstream>

using namespace std;

struct Student {
    string surname; 
    int form;       //1-11
    char formLetter; //А, Б, В и тд.
    string gender;   //Муж или Жен
    int height;      //в см
    int weight;      //в кг
};

int main() {
    const int MAX_STUDENTS = 1000;
    Student students[MAX_STUDENTS];
    int n = 0; 
    
    ifstream file("basa.txt");
    
    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл basa.txt" << endl;
        cout << "Программа завершена с ошибкой." << endl;
    } else {
        // Проверка чтения количества учеников
        string firstLine;
        if (!getline(file, firstLine)) {
            cout << "Ошибка: не удалось прочитать количество учеников из файла!" << endl;
            cout << "Программа завершена с ошибкой." << endl;
            file.close();
        } else {
            stringstream ss(firstLine);
            if (!(ss >> n)) {
                cout << "Ошибка: не удалось преобразовать количество учеников!" << endl;
                cout << "Программа завершена с ошибкой." << endl;
                file.close();
            } else {
                if (n > MAX_STUDENTS || n <= 0) {
                    cout << "Некорректное количество учеников в файле!" << endl;
                    cout << "Программа завершена с ошибкой." << endl;
                    file.close();
                } else {
                    // Чтение данных об учениках из файла с проверкой
                    int successfullyRead = 0;
                    bool errorOccurred = false;
                    
                    for (int i = 0; i < n; i++) {
                        string line;
                        if (!getline(file, line)) {
                            cout << "ОШИБКА: Не удалось прочитать строку для ученика #" << i + 1 << endl;
                            cout << "Проверьте формат файла!" << endl;
                            errorOccurred = true;
                            break;
                        }
                        
                        // Пропускаем пустые строки
                        if (line.empty()) {
                            i--;
                            continue;
                        }
                        
                        stringstream ssLine(line);
                        if (!(ssLine >> students[i].surname >> students[i].form >> students[i].formLetter 
                                  >> students[i].gender >> students[i].height >> students[i].weight)) {
                            cout << "ОШИБКА: Не удалось разобрать данные для ученика #" << i + 1 << endl;
                            cout << "Проверьте формат файла!" << endl;
                            errorOccurred = true;
                            break;
                        }
                        
                        // Дополнительная проверка корректности данных
                        if (students[i].form < 1 || students[i].form > 11) {
                            cout << "ОШИБКА: Некорректный номер класса (" << students[i].form 
                                 << ") у ученика " << students[i].surname << endl;
                            errorOccurred = true;
                            break;
                        }
                        
                        if (students[i].gender != "Муж" && students[i].gender != "Жен") {
                            cout << "ОШИБКА: Некорректный пол (" << students[i].gender 
                                 << ") у ученика " << students[i].surname << endl;
                            errorOccurred = true;
                            break;
                        }
                        
                        if (students[i].height <= 0 || students[i].height > 250) {
                            cout << "ОШИБКА: Некорректный рост (" << students[i].height 
                                 << " см) у ученика " << students[i].surname << endl;
                            errorOccurred = true;
                            break;
                        }
                        
                        if (students[i].weight <= 0 || students[i].weight > 200) {
                            cout << "ОШИБКА: Некорректный вес (" << students[i].weight 
                                 << " кг) у ученика " << students[i].surname << endl;
                            errorOccurred = true;
                            break;
                        }
                        
                        successfullyRead++;
                    }
                    
                    file.close(); // Закрытие файла
                    
                    if (!errorOccurred) {
                        cout << "Данные успешно загружены из файла basa.txt" << endl;
                        cout << "Количество учеников: " << successfullyRead << endl;
                        
                        // Вывод загруженных данных для контроля
                        cout << "\nЗагруженные данные:" << endl;
                        for (int i = 0; i < successfullyRead; i++) {
                            cout << students[i].surname << " " << students[i].form << students[i].formLetter 
                                 << " " << students[i].gender << " " << students[i].height << "см " 
                                 << students[i].weight << "кг" << endl;
                        }
                        
                        cout << "\n=== Задание 1: Рост в параллелях ===" << endl;
                        
                        for (int form = 1; form <= 11; form++) {
                            int maxHeight = -1;
                            int minHeight = INT_MAX;
                            bool found = false; 

                            for (int i = 0; i < successfullyRead; i++) {
                                if (students[i].form == form) {
                                    found = true;
                                    if (students[i].height > maxHeight) {
                                        maxHeight = students[i].height;
                                    }
                                    if (students[i].height < minHeight) {
                                        minHeight = students[i].height;
                                    }
                                }
                            }
                            
                            if (found) {
                                cout << form << " класс: самый высокий = " << maxHeight 
                                     << " см, самый низкий = " << minHeight << " см" << endl;
                            } else {
                                cout << form << " класс: нет учеников" << endl;
                            }
                        }

                        cout << "\n=== Задание 2: Девочки с весом > 60 кг ===" << endl;
                        
                        int totalGirls = 0;
                        int beautifulGirls = 0; 
                        
                        for (int i = 0; i < successfullyRead; i++) {
                            if (students[i].gender == "Жен") {
                                totalGirls++;
                                if (students[i].weight > 60) {
                                    beautifulGirls++;
                                }
                            }
                        }
                        
                        if (totalGirls > 0) {
                            double percentage = (beautifulGirls * 100.0) / totalGirls;
                            cout << "Всего девочек: " << totalGirls << endl;
                            cout << "Девочек с весом > 60 кг: " << beautifulGirls << endl;
                            cout << "Процент: " << percentage << "%" << endl;
                        } else {
                            cout << "В базе нет девочек" << endl;
                        }
                        
                        cout << "ДЕВОЧКИ С ЛЮБЫМ ВЕСОМ ПРЕКРАСНЫ!!" << endl;
                        
                        cout << "\n=== Задание 3: Ученики 10-11 классов с ИМТ 20-25 ===" << endl;
                        
                        int IMT_10_11 = 0; 
                        
                        for (int i = 0; i < successfullyRead; i++) {
                            if (students[i].form == 10 || students[i].form == 11) {
                                double heightInMeters = students[i].height / 100.0; 
                                double imt = students[i].weight / (heightInMeters * heightInMeters);
                                
                                if (imt >= 20 && imt <= 25) {
                                    IMT_10_11++;
                                    cout << students[i].surname << " (" << students[i].form << students[i].formLetter 
                                         << "): ИМТ = " << imt << endl;
                                }
                            }
                        }
                        
                        cout << "\nВсего учеников 10-11 классов с ИМТ 20-25: " << IMT_10_11 << endl;
                    } else {
                        cout << "\nПрограмма завершена из-за ошибок в данных." << endl;
                    }
                }
            }
        }
    }
    
    cout << "\nПрограмма завершена." << endl;
    return 0;
}