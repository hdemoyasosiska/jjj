#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include <bitset>
#include <iostream>
#include <fstream>
#include <time.h>
#include <ctime>
#include <random>

using namespace std;
mt19937 gen(time(0));
uniform_int_distribution<>id(0, 1000000);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "nomer";
    int nomer;
    cin >> nomer;
    switch (nomer) {


    case 1: {

        unsigned char x = 230;
        //cin >> x;
        unsigned char mmaska = 1; //1=00000001 – 8-разрядная маска
        x = x & (~(mmaska << 4));
        cout << "x with 5 bit in 0 = " << +x << endl;

        x = 5;
        //cin >> x;
        x = x | (mmaska << 6);
        cout << "x with 7 bit in 1 = " << +x << endl;

        //Битовые операции
        unsigned int X = 25;
        const int n = sizeof(int) * 8; //=32 - количество разрядов в числе типа int
        unsigned maska = (1 << n - 1); //1 в старшем бите 32-разрядной сетки
        cout << "start: " << bitset<n>(maska) << endl;
        cout << "result: ";
        for (int i = 1; i <= n; i++) //32 раза - по количеству разрядов:
        {
            cout << ((X & maska) >> (n - i));
            maska = maska >> 1; //смещение 1 в маске на разряд вправо
        }
        cout << endl;
    }
          break;
    case 2: {
        int chisla[8];
        unsigned char mask;
        int l;
        int n = 0;
        for (int i = 0; i <= 7; i++) {
            cin >> l;
            if (l < 8 && l >= 0) {
                chisla[i] = l;
                n++;
            }
            else break;
        }
        unsigned char spisok = 0;
        for (int i = 0; i < n; i++) {
            spisok = spisok | (1 << chisla[i]);

        }
        cout << "curr list " << bitset<8>(spisok) << endl;
        for (int i = 0; i <= 7; i++) {
            if (bitset<8>(spisok)[i] == 1) {
                cout << i << ' ';
            }
        }
    }
          break;
    case 3: {
        int chisla[64];
        fill(chisla, chisla + 64, -1);
        unsigned long long mask;
        int l;
        int n = 0;
        for (int i = 0; i <= 63; i++) {
            cin >> l;
            if (l < 64 && l >= 0) {
                chisla[i] = l;
                n++;
            }
            else break;
        }
        unsigned long long spisok = 0;

        for (int i = 0; i < n; i++) {
            spisok = spisok | (1 << chisla[i]);
        }
        cout << "curr list " << bitset<64>(spisok) << endl;
        for (int i = 0; i < 64; i++) {
            if (bitset<64>(spisok)[i] == 1) {
                cout << i << ' ';
            }
        }
    }
    break;
    case 4: {
        unsigned char chisla[64];
        unsigned char mask[8] = { 0 }; // Инициализируем массив mask нулями
        int l;
        int n = 0;

        for (int i = 0; i <= 63; i++) {
            cin >> l;
            if (l < 64 && l >= 0) {
                chisla[i] = l;
                n++;
            }
            else {
                break;
            }
        }

        for (int i = 0; i < n; i++) {
            int byteIndex = chisla[i] / 8; // Находим индекс байта
            int bitIndex = chisla[i] % 8; // Находим индекс бита в байте
            mask[byteIndex] |= (1 << bitIndex); // Устанавливаем бит в соответствующем байте массива mask
        }

        cout << "curr list ";
        for (int i = 0; i < 8; i++) {
            cout << bitset<8>(mask[i]) << " ";
        }
        cout << endl;

        cout << "Bits : ";
        for (int i = 0; i < 64; i++) {
            int byteIndex = i / 8;
            int bitIndex = i % 8;
            if ((mask[byteIndex] & (1 << bitIndex)) != 0) {
                cout << i << ' ';
            }
        }

    }
    break;
    case 5: {
        vector<unsigned char> mask(1048576, 0); // Инициализируем массив mask нулями
        int l;
        int n = 0;

        ifstream inputFile("unique_numbers.txt");
        int number;
        clock_t begin = clock();
        while (inputFile >> number) {
            int byteIndex = number / 8; // Находим индекс байта
            int bitIndex = number % 8; // Находим индекс бита в байте
            mask[byteIndex] |= (1 << bitIndex); // Устанавливаем бит в соответствующем байте массива mask

        }
        inputFile.close();



        ofstream outputFile("sorted_numbers.txt");

        for (int i = 0; i < 1048576; i++) {
            int byteIndex = i / 8;
            int bitIndex = i % 8;
            if ((mask[byteIndex] & (1 << bitIndex)) != 0) {
                outputFile << i << "\n";
            }
        }
        outputFile.close();
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        cout << "\nTime: " << time_spent;


        size_t sizeOfMask = sizeof(mask);

        std::cout << "RAM of mask: " << sizeOfMask << " byte" << std::endl;
    }
    break;
    }
    system("pause");
    return 0;
}
