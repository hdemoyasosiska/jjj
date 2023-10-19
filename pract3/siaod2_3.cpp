#include <iostream>
#include <string>
const int TABLE_SIZE = 10;

class Student {
public:
    int studentID;
    int group;
    std::string fullName;

    Student() : studentID(0), group(0), fullName("") {}
    Student(int id, int grp, const std::string& name)
            : studentID(id), group(grp), fullName(name) {}
};

class HashTable {
private:
    Student* table[TABLE_SIZE];
    int currentSize;

    int hash(int key) {
        return key % TABLE_SIZE;
    }

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i] = nullptr;
        }
        currentSize = 0;
    }

    void insert(const Student& student) {
        if (currentSize >= TABLE_SIZE) {
            std::cout << "Таблица заполнена. Невозможно добавить больше элементов." << std::endl;
            return;
        }

        int key = student.studentID;
        int index = hash(key);

        while (table[index] != nullptr) {
            index = (index + 1) % TABLE_SIZE;
        }

        table[index] = new Student(student);
        ++currentSize;
    }

    void remove(int key) {
        int index = hash(key);

        while (table[index] != nullptr) {
            if (table[index]->studentID == key) {
                delete table[index];
                table[index] = nullptr;
                --currentSize;
                return;
            }
            index = (index + 1) % TABLE_SIZE;
        }

        std::cout << "Студент с номером зачетной книжки " << key << " не найден." << std::endl;
    }

    Student* search(int key) {
        int index = hash(key);

        while (table[index] != nullptr) {
            if (table[index]->studentID == key) {
                return table[index];
            }
            index = (index + 1) % TABLE_SIZE;
        }

        return nullptr;
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (table[i] != nullptr) {
                std::cout << "Запись " << i << ": " << table[i]->studentID << " - " << table[i]->fullName << std::endl;
            }
        }
    }

    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (table[i] != nullptr) {
                delete table[i];
            }
        }
    }
};

int main() {
    system("chcp 65001");
    HashTable hashTable;

    hashTable.insert(Student(1001, 101, "Иванов Иван"));
    hashTable.insert(Student(1002, 102, "Петров Петр"));
    hashTable.insert(Student(1003, 103, "Сидоров Сидор"));
    hashTable.insert(Student(1004, 104, "Алексеев Алексей"));
    hashTable.insert(Student(1005, 105, "Егоров Егор"));

    while (true) {
        std::cout << "Выберите действие:" << std::endl;
        std::cout << "1. Добавить студента" << std::endl;
        std::cout << "2. Удалить студента" << std::endl;
        std::cout << "3. Найти студента" << std::endl;
        std::cout << "4. Вывести список студентов" << std::endl;
        std::cout << "5. Выйти" << std::endl;

        int choice;
        std::cin >> choice;

        if (choice == 5) {
            break;
        }

        switch (choice) {
            case 1: {
                int id, group;
                std::string name;

                std::cout << "Введите номер зачетной книжки: ";
                std::cin >> id;
                std::cout << "Введите номер группы: ";
                std::cin >> group;
                std::cin.ignore();
                std::cout << "Введите ФИО: ";
                std::getline(std::cin, name);

                Student student(id, group, name);
                hashTable.insert(student);
                break;
            }

            case 2: {
                int id;
                std::cout << "Введите номер зачетной книжки для удаления: ";
                std::cin >> id;
                hashTable.remove(id);
                break;
            }

            case 3: {
                int id;
                std::cout << "Введите номер зачетной книжки для поиска: ";
                std::cin >> id;
                Student* student = hashTable.search(id);
                if (student != nullptr) {
                    std::cout << "Студент найден: " << student->fullName << std::endl;
                } else {
                    std::cout << "Студент не найден." << std::endl;
                }
                break;
            }

            case 4:
                std::cout << "Список студентов:" << std::endl;
                hashTable.display();
                break;

            default:
                std::cout << "Некорректный ввод." << std::endl;
                break;
        }
    }

    return 0;
}
