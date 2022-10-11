/* 
Nama        : Anna Safira Dila
Kelas       : B
NPM         : 140810200034
Dekripsi    : Vigenere Cipher Praktikum Kriptografi
*/

#include<bits/stdc++.h>

std::string generateKey(std::string str, std::string key) {
	int x = str.size();

	for (int i = 0; ; i++) {
		if (x == i)
			i = 0;
		if (key.size() == str.size())
			break;
		key.push_back(key[i]);
	}
	return key;
}

std::string cipherText(std::string str, std::string key) {
	std::string cipher_text;

	for (int i = 0; i < str.size(); i++) {
		char x = (str[i] + key[i]) %26;

		x += 'A';

		cipher_text.push_back(x);
	}
	return cipher_text;
}

std::string plainText(std::string cipher_text, std::string key) {
	std::string plain_text;

	for (int i = 0 ; i < cipher_text.size(); i++) {
		char x = (cipher_text[i] - key[i] + 26) %26;

		x += 'A';
		plain_text.push_back(x);
	}
	return plain_text;
}

int main() {
    bool menuActive = true;
    std::string str, keyword;
    int pil;
    
    std::cout << "= VIGENERE CIPHER =" << std::endl;
    std::cout << "Input Text (w/o space) : ";
    std::cin >> str;
    std::cout << "Input key : ";
    std::cin >> keyword;

    std::cout << "\nPilih metode : \n1. Enkripsi \n2. Dekripsi\n";
    std::cout << "Pilihan : ";
    std::cin >> pil;

    if(pil == 1) {
        std::string key = generateKey(str, keyword);
        std::string cipher_text = cipherText(str, key);
        std::cout << "\n Hasil \n";
        std::cout << "Ciphertext : " << cipher_text << "\n";
        std::cout << "Plaintext : " << str;
        return 0;
    } else if (pil == 2) {
        std::string key = generateKey(str, keyword);
        std::string plain_text = plainText(str, key);
        std::cout << "\n Hasil \n";
        std::cout << "Ciphertext : " << str << "\n";
        std::cout << "Plaintext : " << plain_text;
        return 0;
    } else {
        std::cout << "Pilihan tidak ada";
    }
}