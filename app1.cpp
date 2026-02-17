#include <iostream>
using namespace std;

template <class T, int k = 3>
class Aplikacija {
protected:
    T* dani;
    int kapacitet;
    int zauzeto;

public:
    Aplikacija() : kapacitet(k), zauzeto(0) {
        dani = new T[k];
    }

    Aplikacija(T niz[]) : kapacitet(k), zauzeto(k) {
        dani = new T[k];
        for (int i = 0; i < k; i++)
            dani[i] = niz[i];
    }

    void dodaj(const T &x) {
        if (zauzeto == kapacitet)
            prosiri();

        dani[zauzeto++] = x;
    }

    void prosiri() {
        int noviKap = kapacitet + kapacitet / 2;
        T* novi = new T[noviKap];

        for (int i = 0; i < zauzeto; i++)
            novi[i] = dani[i];

        delete[] dani;
        dani = novi;
        kapacitet = noviKap;
    }

    void obrisi(int brEl) {
        try {
            if(brEl < 1 || brEl > zauzeto) 
                throw string("Neispravan broj brisanje prvih X dana iz kolekcije");
    
            T* novi = new T[kapacitet]; 
            int l = 0;
    
            for(int i = brEl; i < zauzeto; i++)
                novi[l++] = dani[i];
    
            delete [] dani;
            dani = novi;
            zauzeto = l;
    
        } catch(const string &e) {
            cout << e << endl;
        }
    }

    int ukupno(int a, int b){
        if(a < 0 || b >= zauzeto || a > b){
            cout << "Nevalidni indeksi za ukupno posetilaca!\n";
            return -1;
        }

        int suma = 0;
        for(int i=a; i<=b; i++)
            suma += dani[i].posetioci();
        return suma;
    }

int* p() { // dva dana sa najmanjom zaradom
    try {
        if (zauzeto < 2)
            throw string("Nema dovoljno dana za pronalazak najmanje zarade");

        int* q = new int[2]; // niz za dva dana
        int min1 = 0;
        int min2 = 1;

        // Postavimo min1 kao dan sa manjom zaradom, min2 veći
        if (dani[min1].zarada() > dani[min2].zarada()) {
            int tmp = min1;
            min1 = min2;
            min2 = tmp;
        }

        // Prolazimo kroz sve ostale dane
        for (int i = 2; i < zauzeto; i++) {
            int z = dani[i].zarada();
            if (z < dani[min1].zarada()) {
                // Novi najmanji dan
                min2 = min1;
                min1 = i;
            } else if (z < dani[min2].zarada()) {
                // Novi drugi najmanji dan
                min2 = i;
            }
        }

        q[0] = min1 + 1; // 1-based indeks
        q[1] = min2 + 1;

        return q;
    } catch (const string &e) {
        cout << e << endl;
        return nullptr;
    }
}


    void prikazi(){
        for(int i=0;i<zauzeto;i++)
            cout << "Dan " << i+1 << ": posetioci=" << dani[i].posetioci() 
                 << ", zarada=" << dani[i].zarada() << endl;
    }

    ~Aplikacija() {
        delete[] dani;
    }
};

class Interaktivni{
    int brPosetioca, cena;
public:
    Interaktivni() : brPosetioca(0), cena(0) {}
    Interaktivni(int brPosetioca, int cena) : brPosetioca(brPosetioca), cena(cena) {}
    int zarada(){ return brPosetioca * cena; }
    int posetioci(){ return brPosetioca; }
};

class IzlozbeniPosetioci{
public:
    int odrasli, decado7, decaispod7;
    IzlozbeniPosetioci() : odrasli(0), decado7(0), decaispod7(0) {}
    IzlozbeniPosetioci(int o, int d7, int d7ispod) : odrasli(o), decado7(d7), decaispod7(d7ispod) {}
};

class Izlozbeni{
    IzlozbeniPosetioci i;
    int cena;
public:
    Izlozbeni() : i(), cena(0) {}
    Izlozbeni(int cena, int o, int d1, int d2) : i(o,d1,d2), cena(cena) {}
    int zarada(){ return i.odrasli*cena + i.decado7*(cena/2); }
    int posetioci(){ return i.odrasli + i.decado7 + i.decaispod7; }
};


int main() {
    cout << "=== Interaktivni sektor ===\n";
    Aplikacija<Interaktivni> inter;
    inter.dodaj(Interaktivni(1200,100));
    inter.dodaj(Interaktivni(1500,100));
    inter.dodaj(Interaktivni(900,100));
    inter.dodaj(Interaktivni(1300,100));
    inter.dodaj(Interaktivni(1100,100));

    inter.prikazi();

    cout << "Ukupno posetilaca od dana 2 do 4: " << inter.ukupno(1,3) << endl;

    int* minDani = inter.p();   // Dobijamo niz sa 2 dana sa najmanjom zaradom
    if(minDani != nullptr) {
        cout << "Dani sa najmanjom zaradom (interaktivni): " 
             << minDani[0] << " i " << minDani[1] << endl;
        delete[] minDani;  // Oslobađamo memoriju
    }

    inter.obrisi(2);
    cout << "--- Nakon brisanja prvih 2 dana ---\n";
    inter.prikazi();

    cout << "\n=== Izložbeni sektor ===\n";
    Aplikacija<Izlozbeni> izloz;
    izloz.dodaj(Izlozbeni(100,100,50,20));
    izloz.dodaj(Izlozbeni(100,120,40,30));
    izloz.dodaj(Izlozbeni(100,80,60,25));
    izloz.dodaj(Izlozbeni(100,110,55,15));
    izloz.dodaj(Izlozbeni(100,90,45,35));

    izloz.prikazi();

    cout << "Ukupno posetilaca od dana 2 do 4: " << izloz.ukupno(1,3) << endl;

    minDani = izloz.p();
    if(minDani != nullptr) {
        cout << "Dani sa najmanjom zaradom (izložbeni): " 
             << minDani[0] << " i " << minDani[1] << endl;
        delete[] minDani;
    }

    izloz.obrisi(2);
    cout << "--- Nakon brisanja prvih 2 dana ---\n";
    izloz.prikazi();

    return 0;
}
