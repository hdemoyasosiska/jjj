#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <unordered_map>

struct UniversityRecord {
    int specializationCode;
    std::string universityName;
};


struct TableEntry {
    int key;
    long long offset; // Смещение записи в файле
};
std::unordered_map<int, TableEntry> table;

void buildTableFromFile(const char* filename) {
    // Откройте файл для чтения
    std::ifstream inputFile(filename, std::ios::binary);

    if (!inputFile.is_open()) {
        std::cerr << "Failed to open file for reading." << std::endl;
        return;
    }

    // Считывайте записи и добавляйте их в таблицу
    int key;
    long long offset = 0;

    while (inputFile.read(reinterpret_cast<char*>(&key), sizeof(int))) {
        TableEntry entry;
        entry.key = key;
        entry.offset = offset;

        table[key] = entry;

        // Переместитесь к следующей записи
        offset = inputFile.tellg();
    }

    inputFile.close();
}

long long findRecordOffset(int key) {
    if (table.find(key) != table.end()) {
        return table[key].offset;
    } else {
        return -1; // Если запись с таким ключом не найдена
    }
}


UniversityRecord readRecordFromFile(const char* filename, long long offset) {
    std::ifstream inputFile(filename, std::ios::binary);

    if (!inputFile.is_open()) {
        std::cerr << "Failed to open file for reading." << std::endl;
        return UniversityRecord(); // Вернуть пустую запись или бросить исключение
    }

    // Переместиться к указанному смещению
    inputFile.seekg(offset);

    // Считать запись
    UniversityRecord record;
    inputFile.read(reinterpret_cast<char*>(&record), sizeof(UniversityRecord));

    inputFile.close();

    return record;
}

bool compareRecords(const UniversityRecord& record1, const UniversityRecord& record2) {
    return record1.specializationCode < record2.specializationCode;
}

int binarySearch(const std::vector<UniversityRecord>& records, int key) {
    int left = 0;
    int right = records.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (records[mid].specializationCode == key) {
            return mid;
        } else if (records[mid].specializationCode < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

int main() {
    int task;
    std::cout << "Task: ";
    std::cin >> task;
    switch (task) {
        case 1: {
            std::vector<UniversityRecord> records;

            for (int i = 0; i < 10; ++i) {
                UniversityRecord record;
                record.specializationCode = rand() % 1000;
                std::cout << record.specializationCode << "\n";
                record.universityName = "University " + std::to_string(i);
                records.push_back(record);
            }

            std::sort(records.begin(), records.end(), compareRecords);

            std::ofstream outputFile("university_records.dat", std::ios::binary);
            for (const UniversityRecord &record: records) {
                outputFile.write(reinterpret_cast<const char *>(&record), sizeof(UniversityRecord));
            }
            outputFile.close();

            int keyToSearch;
            std::cout << "Enter key\n";
            std::cin >> keyToSearch;
            int resultIndex = binarySearch(records, keyToSearch);

            if (resultIndex != -1) {
                std::cout << "Record found: " << records[resultIndex].universityName << std::endl;
            } else {
                std::cout << "Record not found." << std::endl;
            }
            break;
        }
        case 2:{
            int sz;
            std::cout << "Size of file: ";
            std::cin >> sz;
            std::vector<UniversityRecord> rrecords;

            for (int i = 0; i < sz; ++i) {
                UniversityRecord record;
                record.specializationCode = rand() % 1000;
                //std::cout << record.specializationCode << "\n";
                record.universityName = "University " + std::to_string(i);
                rrecords.push_back(record);
            }

            std::sort(rrecords.begin(), rrecords.end(), compareRecords);

            std::ofstream outputFile("university_records.dat", std::ios::binary);
            for (const UniversityRecord &record: rrecords) {
                outputFile.write(reinterpret_cast<const char *>(&record), sizeof(UniversityRecord));
            }
            outputFile.close();

            std::ifstream inputFile("university_records.dat",   std::ios::binary);

            if (!inputFile) {
                std::cerr << "Failed to open file for reading." << std::endl;
                return 1;
            }

            std::vector<UniversityRecord> records;
            UniversityRecord record;

            // Reading records from the binary file
            while (inputFile.read(reinterpret_cast<char*>(&record), sizeof(UniversityRecord))) {
                records.push_back(record);
            }

            inputFile.close();

            // Key to search for (replace with the key you want to find)
            int keyToSearch = 42;

            auto startTime = std::chrono::high_resolution_clock::now();

            // Linear search
            bool found = false;
            for (const UniversityRecord& r : records) {
                if (r.specializationCode == keyToSearch) {
                    found = true;
                    std::cout << "Record found: " << r.universityName << std::endl;
                    break;
                }
            }

            auto endTime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

            if (!found) {
                std::cout << "Record not found." << std::endl;
            }

            std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
            break;
        }
        case 3:{
            int sz;
            std::cout << "Size of file: ";
            std::cin >> sz;
            std::vector<UniversityRecord> rrecords;

            for (int i = 0; i < sz; ++i) {
                UniversityRecord record;
                record.specializationCode = rand() % 1000;
                //std::cout << record.specializationCode << "\n";
                record.universityName = "University " + std::to_string(i);
                rrecords.push_back(record);
            }

            std::sort(rrecords.begin(), rrecords.end(), compareRecords);

            std::ofstream outputFile("university_records.dat", std::ios::binary);
            for (const UniversityRecord &record: rrecords) {
                outputFile.write(reinterpret_cast<const char *>(&record), sizeof(UniversityRecord));
            }
            outputFile.close();

            buildTableFromFile("university_records.dat");

            // Измерьте время выполнения поиска для каждого размера файла
            auto start = std::chrono::high_resolution_clock::now();
            long long offset = findRecordOffset(42); // Замените some_key на ключ, который вы ищете
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            std::cout <<offset;
            // Выведите время выполнения в миллисекундах
            std::cout << "Search time: " << duration.count() << " microseconds" << std::endl;

            return 0;

            break;
        }
    }


    return 0;
}
