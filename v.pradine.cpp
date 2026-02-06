#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

// su šitais nereiks visur std:: dadėt
using std::cin;
using std::cout;
using std::endl;
using std::left;
using std::right;
using std::setw;
using std::string;
using std::vector;

struct Studentas
{
    string vardas, pavarde;
    vector<int> paz;
    int egz;
    double rez;
};

void ivestis(vector<Studentas> &grupe);
void isvestis(vector<Studentas> &grupe);

int main()
{
    vector<Studentas> grupe;
    ivestis(grupe);
    isvestis(grupe);
}

void ivestis(vector<Studentas> &grupe)
{
    for (int i = 0; i < 2; i++)
    {
        Studentas A;
        cout << "Iveskite varda ir pavarde: ";
        cin >> A.vardas >> A.pavarde;
        cout << "Kiek bus semestro iverciu? ";
        int iverciuSk, iverciuSuma = 0;
        cin >> iverciuSk;
        cout << "Iveskite semestro ivercius: " << endl;
        for (int j = 0; j < iverciuSk; j++)
        {
            int pazymys;
            cout << "Iveskite " << j + 1 << "-aji pazymi is " << iverciuSk << ": ";
            cin >> pazymys;
            A.paz.push_back(pazymys);
            iverciuSuma += pazymys;
        }
        cout << "Iveskite egzamino vertinima: ";
        cin >> A.egz;
        A.rez = (iverciuSuma * 1.0) / (iverciuSk * 1.0) * 0.4 + (A.egz * 0.6);
        grupe.push_back(A);
        A.paz.clear(); // apsauga: isvalo pazymiu vektoriu, kad kitam kartojime vektorius butu tuscias
    }
}

void isvestis(vector<Studentas> &grupe)
{
    cout << left << setw(10) << "Vardas" << left << setw(20) << "Pavarde" << setw(10) << "Galutinis (Vid.)" << endl;
    for (const auto &A : grupe) // su &, const apsaugo nuo pakeitimo (jo nenorim)
    {
        cout << left << setw(10) << A.vardas << left << setw(20) << A.pavarde << setw(10) << A.rez << endl;
    }
}