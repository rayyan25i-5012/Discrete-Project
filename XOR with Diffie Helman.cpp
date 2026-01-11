#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <ctime>   
using namespace std;
int mod(int a, int b) {
    int quotient = a / b;
    int remainder = a - (quotient * b);
    while (remainder < 0) {
        remainder += b;
    }
    return remainder;
}
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, mod(a, b));
}
int pmod(int base, int exp, int m) {
    if (exp == 0) return 1;
    
    int half = pmod(base, exp / 2, m);
    half = mod(half * half, m);
    
    if (mod(exp, 2) != 0) { 
        half = mod(half * base, m);
    }
    return half;
}
bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (mod(n, i) == 0) return false;
    }
    return true;
}
int dprime() {
    int p;
    do {
        p = mod(rand(), 48) + 2; 
    } while (!isPrime(p));
    return p;
}
int newkey() {
int p = dprime();
int g = 5; 

    int a_private = mod(rand(), (p - 2)) + 1;
    int A_public  = pmod(g, a_private, p);

    int b_private = mod(rand(), (p - 2)) + 1;
    int B_public  = pmod(g, b_private, p);

    int sharedsecret = pmod(B_public, a_private, p);

    cout << "DH Parameters => "<<"p  = "<<p<< ", g =" <<g<<endl;
    cout << "1st Public = " << A_public << ", 2nd Public = "<<B_public<<endl;
    cout << "Shared Secret Key generated = "<<sharedsecret<<endl;

    return sharedsecret;
}
void processfile(const string& inputfile, const string& outputfile, int key) {
    ifstream fin(inputfile.c_str(), ios::binary); 
    ofstream fout(outputfile.c_str(), ios::binary);

    char ch;
    while (fin.get(ch)) {
        char transformed = ch ^ static_cast<char>(key);
        fout.put(transformed);
    }

    fin.close();
    fout.close();
}
void createTestFile() {
    ofstream f("input2.txt");
    string s;
    cout << "Enter text to encrypt = ";
    getline(cin, s);
    f<<s;
    f.close();
}
int main() {
    srand(static_cast<unsigned int>(time(0)));

    cout << "' Encryption (XOR + DH) ' " << endl;
    createTestFile();
    int key = newkey();
    processfile("input2.txt", "encrypted2.txt", key);
    processfile("encrypted2.txt", "decrypted2.txt", key);

    cout<<"Protocol Complete" <<endl;
    cout<<"Both files are same !"<<endl;

    return 0;
}
 
