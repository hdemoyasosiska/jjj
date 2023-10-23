#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;
std::vector<int> computePrefixFunction(const std::string& substr) {
    int m = substr.length();
    std::vector<int> pi(m, 0);  // Инициализируем префикс-функцию нулями

    int j = 0;
    for (int i = 1; i < m; i++) {
        while (j > 0 && substr[i] != substr[j]) {
            j = pi[j - 1];
        }

        if (substr[i] == substr[j]) {
            j++;
        }

        pi[i] = j;
    }

    return pi;
}

// Функция для определения минимальной длины исходной строки
int findMinOriginalLength(const std::string& substring) {
    std::vector<int> prefix_function = computePrefixFunction(substring);
    for (int i = 0; i < prefix_function.size(); i++) {
        if (i != 0) {
            std::cout << ", ";
        }
        std::cout << prefix_function[i];
    }
    int max_match_length = prefix_function.back(); // Длина совпадения с суффиксом

    int m = substring.length();
    int min_length = m - max_match_length; // Минимальная длина исходной строки

    return min_length;
}
int main() {
    system("chcp 65001");
    cout << "task ";
    int task;
    cin >> task;
    switch (task) {
        case 1: {
            string sentence;
            cin.clear();
            cin.ignore();
            cout << "Введите предложение: ";
            getline(cin, sentence);


            istringstream iss(sentence);
            string word;
            vector<string> words;

            while (iss >> word) {
                // Удаляем знаки препинания
                word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
                words.push_back(word);
            }

            if (words.empty()) {
                cout << "Предложение не содержит слов." << endl;
                return 1;
            }


            string lastWord = words.back();
            transform(lastWord.begin(), lastWord.end(), lastWord.begin(), ::tolower);

            int countEqual = 0;
            int countGreater = 0;

            for (int i = 0; i < words.size(); i++) {
                string &word = words[i];
                string lowercaseWord = word;
                transform(lowercaseWord.begin(), lowercaseWord.end(), lowercaseWord.begin(), ::tolower);

                if (lowercaseWord == lastWord && i != words.size() - 1) {
                    countEqual++;
                } else if (lowercaseWord > lastWord) {
                    countGreater++;
                }
            }
            cout << "last - " << lastWord;
            cout << "Количество слов равных последнему слову: " << countEqual << endl;
            cout << "Количество слов больших последнего слова: " << countGreater << endl;

            break;
            //Indoor cats generally live from 12-18 years of age, Many may live to be in their early 20s- The oldest reported cat,
            // an- amazing 38 years old. Outdoor cats; generally live shorter
            // lives due to being more likely to be involved in traumas such as motor vehicle accidents or dog attacks.
        }
        case 2:
            std::string substring;
            std::cout << "Enter the substring: ";
            std::cin >> substring;

            int minOriginalLength = findMinOriginalLength(substring);
            std::cout << "Minimum original length of the string: " << minOriginalLength << std::endl;

            return 0;


    }
    }

