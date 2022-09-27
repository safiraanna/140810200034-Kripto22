/* 
Nama        : Anna Safira Dila
NPM         : 140810200034
Deskripsi   : hillCipher.cpp 
*/

#include<bits/stdc++.h>
 
int key[3][3];
 
int mod26(int x) {
    return x >= 0 ? (x%26) : 26 - (abs(x) % 26); 
}
 
int cariDet(int m[3][3], int n) {
    int det;
    
    if(n == 2) {
        det = m[0][0] * m[1][1] - m[0][1]* m[1][0];
    } else det = 0;
    
    return mod26(det);
}
 
int cariDetInvers(int R , int D = 26) {
    int i = 0;
    int p[100] = {0, 1};
    int q[100] = {0};
 
    while(R != 0) {
        q[i] = D / R;
        int oldD = D;
        D = R;
        R = oldD%R;
        
        if(i > 1) {
            p[i] = mod26(p[i-2] - p[i-1]* q[i-2]);
        }
        
        i++;
    }
    
    if (i == 1) {
        return 1;
    } else {
        return p[i] = mod26(p[i - 2] - p[i-1]* q[i - 2]);
    }
}

int gcd(int m, int n) {
    if (n > m)
        std::swap(m, n);
    
    do {
        int temp = m % n;
        m = n;
        n = temp;
    } while (n != 0);
    
    return m;
}
 
void perkalianMatriks(int a[500][3], int a_baris, int a_kolom,  int b[500][3], int b_baris, int b_kolom, int res[500][3]) {
    for(int i = 0; i < a_baris; i++)
    {
        for(int j = 0; j < b_kolom; j++)
        {
            for(int k = 0; k < b_baris; k++)
            {
                res[i][j] += a[i][k] * b[k][j];
            }
            
            res[i][j] = mod26(res[i][j]);
        }
    }
}

void cariKunci() {
    std::string plaintext, ciphertext;
    int key[2][2], det, detInv, adj[2][2], plaintextInv[2][2], plainMatriks[2][2], cipherMatriks[2][2], counter;
    int p, c;
    int transpose[2][2];
    
    std::cout << "\n(only lowercase input please)\n";
    std::cout << "Masukkan plaintext: ";
    std::cin.ignore();
    std::getline(std::cin, plaintext);
    
    counter = 0;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++){
            p = (plaintext[counter]) - 97;
            plainMatriks[i][j] = p;
            counter++;
        }
    }
    
    std::cout << "\n(only lowercase input please)\n";
    std::cout << "Masukkan ciphertext : ";
    std::getline(std::cin, ciphertext);
    
    counter = 0;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            c = (ciphertext[counter]) - 97;
            cipherMatriks[i][j] = c;
            counter++;
        }
    }
    
    det = (plainMatriks[0][0] * plainMatriks[1][1]) - (plainMatriks[0][1] * plainMatriks[1][0]);
    if(gcd(det, 26) == 1) {
        
        detInv = cariDetInvers(det, 26);
        
        adj[0][0] = plainMatriks[1][1];
        adj[0][1] = (-1) * plainMatriks[0][1];
        adj[1][0] = (-1) * plainMatriks[1][0];
        adj[1][1] = plainMatriks[0][0];
        
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                plaintextInv[i][j] = detInv * adj[i][j];
                
                if(plaintextInv[i][j] < 0) {
                    plaintextInv[i][j] = 26 - (abs(plaintextInv[i][j])%26); 
                } else {
                    plaintextInv[i][j] = plaintextInv[i][j];
                    plaintextInv[i][j] = plaintextInv[i][j] % 26;
                }
            } 
        }
        
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                key [i][j] = 0;
                for(int k = 0; k < 2; k++) {
                    key [i][j] += (plaintextInv[i][k] * cipherMatriks[k][j]);
                }
                
                key [i][j] %= 26;
            }
        }
        
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                transpose[j][i] = key[i][j];
                }
        }
    
        for(int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                std::cout << (transpose[i][j]) << "\t";
            }
            std::cout << std::endl;
        }       
    } else {
        std::cout << "Determinan tidak relatif \n";
        std::cout << "Key tidak ditemukan \n\n";
    }
 
}

void cariInvers(int m[3][3], int n, int m_inverse[3][3] ) {
    int adj[3][3] = {0};
 
    int det = cariDet(m , n);
    int detInverse = cariDetInvers(det);
 
    if(n == 2) {
        adj[0][0] = m[1][1];
        adj[1][1] = m[0][0];
        adj[0][1] = -m[0][1];
        adj[1][0] = -m[1][0];
    }
 
    for(int i = 0; i < n; i++) {
        for(int j=0; j < n; j++) {
            m_inverse[i][j] = mod26(adj[i][j] * detInverse) ;
        }
    }
}
 
std::string encrypt(std::string pt, int n) {
    int P[1000][3] = {0};
    int C[1000][3] = {0};
    int ptIter = 0;
 
    while(pt.length()%n != 0) {
        pt += "x";
    }
    
    int baris = (pt.length())/n;
    for(int i = 0; i < baris; i++) {
        for(int j = 0; j < n; j++) {
            P[i][j] = pt[ptIter++] - 'a';
        }
    }
 
    perkalianMatriks(P, baris, n, key, n, n, C);
 
    std::string ct = "";
    
    for(int i = 0; i < baris; i++) {
        for(int j = 0; j < n; j++) {
            ct += (C[i][j] + 'a');
        }
    }

    return ct;
}
 
std::string decrypt(std::string ct, int n)
{
    int P[500][3] = {0};
    int C[500][3] = {0};
    int ctIter = 0;
 
    int kolom = ct.length()/ n;
 
    for(int i = 0; i < kolom; i++) {
        for(int j = 0; j < n; j++) {
            C[i][j] = ct[ctIter++] - 'a';
        }
    }
 
    int k_inverse[3][3] = {0};

    cariInvers(key, n, k_inverse);
 
    perkalianMatriks(C, kolom, n, k_inverse, n, n, P);
 
    std::string pt = "";
    for(int i = 0; i < kolom; i++) {
        for(int j = 0; j < n; j++) {
            pt += (P[i][j] + 'a');
        }
    }

    return pt;
}
 
int main(void) {
    bool menuActive = true;
    std::string pt, ct;
    int n;
    int pil;
 
    while(menuActive) {
        std::cout << "\n === Hill Cipher ===";
        std::cout << "\nMenu : \n1. Enkripsi \n2. Dekripsi(matriks 2x2) \n3. Cari Kunci(matriks 2x2) \n4. Keluar";
        std::cout << "\nPilihan : "; 
        std::cin >> pil;
        switch(pil) {
            case 1:
                    std::cout << "\n(only lowercase input please)\n";
                    std::cout << "\nInput plaintext : ";
                    std::cin >> pt;
                    
                    std::cout << "Input ordo matriks (bisa matriks 2x2 atau 3x3): ";
                    std::cin >> n ;
 
                    std::cout<<"Input matriks " << std::endl; 
                    for(int i = 0; i < n; i++) {
                        for(int j = 0; j < n; j++) {
                            std::cout << "baris " << j + 1 << " kolom " << i + 1 << " : ";
                            std::cin >> key[i][j];
                        }
                    }
 
                    std::cout << "\nPlaintext  : " << pt << std::endl;
 
                    ct = encrypt(pt, n);
                    
                    std::cout << "Plaintext ter-enkripsi : " << ct << std::endl;
                    break;
            case 2:
                    std::cout << "\n(only lowercase input please)\n";
                    std::cout << "\nInput ciphertext : ";
                    std::cin >> ct;
                    
                    std::cout << "Input ordo matriks (hanya matriks 2x2) : ";
                    std::cin >> n ;

                    std::cout<<"Input matriks : " << std::endl; 
                    for(int i = 0; i < n; i++) {
                        for(int j = 0; j < n; j++) {
                            std::cout << "baris " << j+1 << " kolom " << i+1 << " : ";
                            std::cin >> key[i][j];
                        }
                    }
 
                    std::cout << "\nCiphertext  : " << ct << std::endl;
                    std::cout << "Ciphertext ter-Dekripsi : " << decrypt(ct, n)<< std::endl;
                    break;
            case 3:
                    std::cout << std::endl;
                    
                    cariKunci();
                    break;
            case 4:
                    exit(0);
            default:
                    std::cout << "\nPilihan tidak ada, periksa kembali!" << std::endl;
                    break;
        }
    }
}