/* 
Nama        : Anna Safira Dila
NPM         : 140810200034
Deskripsi   : Shift cipher.cpp 
*/

#include <iostream>
#include <bits/stdc++.h>

int main() {
    char ptext[100];
    int key, pil, panjang;

    std::cout << "Input Plaintext : ";
    std::cin.getline(ptext, 100);

    std::cout << "Input key : ";
    std::cin >> key;

    panjang = strlen(ptext);

    std::cout << "\nPilih metode : \n1. Enkripsi \n2. Dekripsi\n";
    std::cout << "Pilihan : ";
    std::cin >> pil;

    if(pil == 1) {
        char a;
        for(int i = 0; ptext[i] != '\0'; i++) {
            a = ptext[i];

            if(a >= 'a' && a <= 'z') {
                a = (a + key - 97)% 26 + 97;
                ptext[i] = a;
            } else if (a >= 'A' && a <= 'Z') {
                a = (a + key - 65)% 26 + 65;
                ptext[i] = a;
            }
        }
        std::cout << "\nEnkripsi : " << ptext;
    } else if (pil == 2) {
        char a;
        for(int i = 0; ptext[i] != '\0'; i++) {
            a = ptext[i];

            if(a >= 'a' && a <= 'z') {
                a = ((a - key - 97)% 26 + 26)% 26 + 97;
                ptext[i] = a;
            } else if (a >= 'A' && a <= 'Z') {
                a = ((a - key - 65)% 26 + 26)%26 + 65;
                ptext[i] = a;
            }
        }
        std::cout << "\nDekripsi : " << ptext;
    } else {
        std::cout << "Pilihan tidak ada";
    }
}