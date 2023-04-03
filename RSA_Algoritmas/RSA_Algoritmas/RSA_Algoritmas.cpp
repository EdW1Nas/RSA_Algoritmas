#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;


bool arPirminis(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}


int euklidoAlg(int a, int b) {
    if (b == 0) {
        return a;
    }
    return euklidoAlg(b, a % b);
}


int randomSkaiciai(int min, int max) {
    return rand() % (max - min + 1) + min;
}


int euklidoIspAlg(int base, int exp, int mod) {
    int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}


void raktai(int p, int q, int& n, int& e, int& d) {
    n = p * q;
    int phi = (p - 1) * (q - 1);
    e = randomSkaiciai(2, phi - 1);
    while (euklidoAlg(e, phi) != 1) {
        e = randomSkaiciai(2, phi - 1);
    }
    d = 0;
    for (int i = 1; i <= phi; i++) {
        if ((i * e) % phi == 1) {
            d = i;
            break;
        }
    }
}


string tekstoSifravimas(string text, int n, int e) {
    string sifruotasTekstas = "";
    for (char c : text) {
        int ASCII = int(c);
        int sifruotasSimbolis = euklidoIspAlg(ASCII, e, n);
        sifruotasTekstas += to_string(sifruotasSimbolis) + " ";
    }
    return sifruotasTekstas;
}


string teksoDesifravimas(string text, int n, int d) {
    string desifruotasTekstas = "";
    string value = "";
    for (char c : text) {
        if (c == ' ') {
            int sifruotasSimbolis = stoi(value);
            int ASCII = euklidoIspAlg(sifruotasSimbolis, d, n);
            desifruotasTekstas += char(ASCII);
            value = "";
        }
        else {
            value += c;
        }
    }
    return desifruotasTekstas;
}

int main() {
    int parinktis;
    cout << "Sifruoti ar Desifruoti: " << endl;
    cout << "1. Sifravimas" << endl;
    cout << "2. Desifravimas" << endl;
    cin >> parinktis;

    int p, q, n, e, d;
    cout << "Iveskite p (Pirminis skaicius): ";
    cin >> p;
    while (!arPirminis(p)) {
        cout << "p turi but pirminis skaicius. Iveskite kita p: ";
        cin >> p;
    }
    cout << "Iveskite q (Pirminis skaicius): ";
    cin >> q;
    while (!arPirminis(q)) {
        cout << "q turi but pirminis skaicius. Iveskite kita q: ";
        cin >> q;
    }

    raktai(p, q, n, e, d);

    int ivedimasParinktis;
    cout << "Irasyti teskta ar gauti teksta is .txt failo \n";
    cout << "1. Ivesti teksta" << endl;
    cout << "2. Gauti teksta is .txt failo" << endl;
    cin >> ivedimasParinktis;

    string tekstas;
    if (ivedimasParinktis == 1) {
        cout << "Iveskite teksta kuri norite sifruoti/desifruoti: ";
        cin.ignore();
        getline(cin, tekstas);
    }
    else {
        string failoPavadinimas;
        cout << "Iveskite .txt failo pavadinima (Su .txt): ";
        cin >> failoPavadinimas;
        ifstream failas(failoPavadinimas);
        getline(failas, tekstas);
        failas.close();
    }

    string result;
    if (parinktis == 1) {
        result = tekstoSifravimas(tekstas, n, e);
    }
    else {
        result = teksoDesifravimas(tekstas, n, d);
    }
    cout << "Rezultatas: ";
    cout << result << endl;

    string passwordFailoPavadinimas;
    cout << "Iveskite .txt failo pavadinima kuriame norite issaugoti slaptazodi(Su .txt): ";
    cin >> passwordFailoPavadinimas;

    ofstream passwordFailas(passwordFailoPavadinimas);
    passwordFailas << n << " " << e << endl; //public raktas
   // passwordFailas << n << " " << d << endl; //private raktas
    passwordFailas.close();

    string resultFailoVardas;
    cout << "Iveskite .txt failo pavadinima kuriame norite rezultata: ";
    cin >> resultFailoVardas;

    ofstream resultFailas(resultFailoVardas);
    resultFailas << result << endl;
    resultFailas.close();

    return 0;
}