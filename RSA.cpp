#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

long modPow(long base, long exp, long mod){
    long result = 1;
    base = base % mod;

    while(exp > 0){
        if(exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp / 2;
        base = (base * base) % mod;
    }
    return result;
}

bool isPrime(int n){
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

int randomprime(){
    while(true){
        int num = rand() % 100 + 50;  
        if (isPrime(num)) return num;
    }
}

long gcd(long a, long b){
    while (b != 0){
        long temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

long modinverse(long e, long phi){
    for (long d = 1; d < phi; d++)
        if ((e * d) % phi == 1)
            return d;
    return -1;
}

int main(){
srand(time(NULL));
int p = randomprime();
int q = randomprime();
    
while (q == p) q = randomprime();

long long n = p * q;
long long phi = (p - 1) * (q - 1);
long long e = 3;
    
while (gcd(e, phi) != 1) e++;

long long d = modinverse(e, phi);

cout<<"\n\t'Generated RSA Keys ' ";
cout<<"\nPublic Key (e, n) = (" << e << ", " << n << ")";
cout<<"\nPrivate Key (d, n) = (" << d << ", " << n << ")\n";

string message;
cout<<"\nEnter message to encrypt = ";
getline(cin, message);

long encrypted[500];
ofstream inputfile("input3.txt");
inputfile << message;
inputfile.close();

ofstream encryptfile("encrypted3.txt");
for (int i = 0; i < message.length(); i++){
	encrypted[i] = modPow((int)message[i], e, n);
        encryptfile << encrypted[i] << " ";}
    encryptfile.close();

ofstream decryptfile("decrypted3.txt");
for (int i = 0; i < message.length(); i++){
        long dec_char = modPow(encrypted[i], d, n);
        decryptfile << (char)dec_char;}
    decryptfile.close();

cout<<"Protocol Complete\nBoth files match!"<<endl;
return 0;
}

