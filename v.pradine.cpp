#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
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
    double rez_vid;
    double rez_med;
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
        int iverciu_sk, iverciu_suma = 0;
        cin >> iverciu_sk;

        // cout << "Iveskite semestro ivercius: " << endl;
        for (int j = 0; j < iverciu_sk; j++)
        {
            int pazymys;
            cout << "Iveskite " << j + 1 << "-aji pazymi is " << iverciu_sk << ": ";
            cin >> pazymys;
            A.paz.push_back(pazymys);
            iverciu_suma += pazymys;
        }

        cout << "Iveskite egzamino vertinima: ";
        cin >> A.egz;

        // vidurkio apsk.
        A.rez_vid = (iverciu_suma * 1.0) / (iverciu_sk * 1.0) * 0.4 + (A.egz * 0.6);

        // medianos apsk.
        vector<int> visi_paz = A.paz;
        visi_paz.push_back(A.egz);
        std::sort(visi_paz.begin(), visi_paz.end());
        int visu_paz_sk = visi_paz.size();
        if (visu_paz_sk % 2 != 0)
            A.rez_med = visi_paz[visu_paz_sk / 2];
        else
            A.rez_med = (visi_paz[(visu_paz_sk / 2) - 1] + visi_paz[visu_paz_sk / 2]) / 2.0;

        grupe.push_back(A);
        A.paz.clear(); // apsauga: isvalo pazymiu vektoriu, kad kitam kartojime vektorius butu tuscias
    }
}

void isvestis(vector<Studentas> &grupe)
{
    char galutinio_pasirinkimas;
    bool ar_ivestas_tinkamas_galutinio_tipas = false;
    do
    {
        cout << "Ar norite rasti galutini vidurki ar galutine mediana?" << endl
             << "Jeigu vidurki, iveskite: v" << endl
             << "Jeigu mediana, iveskite: m" << endl;
        cin >> galutinio_pasirinkimas;
        if (galutinio_pasirinkimas == 'v' || galutinio_pasirinkimas == 'm')
            ar_ivestas_tinkamas_galutinio_tipas = true;
    } while (ar_ivestas_tinkamas_galutinio_tipas == false);

    string pasirinktas_galutinis;
    if (galutinio_pasirinkimas == 'v')
        pasirinktas_galutinis = "Vid.";
    else if (galutinio_pasirinkimas == 'm')
        pasirinktas_galutinis = "Med.";

    // lentelės viršutinės eilutės spausdinimas
    cout
        << left << setw(15) << "Vardas"
        << left << setw(20) << "Pavarde"
        << left << setw(10) << "Galutinis (" << pasirinktas_galutinis << ")"
        << endl;

    // skiriamosios linijos tarp lentelės viršutinės ir likusiųjų eilučių spausdinimas
    const int LENTELES_PLOTIS = 45;
    for (int i = 0; i < LENTELES_PLOTIS; i++)
        cout << "-";
    cout << endl;

    if (galutinio_pasirinkimas == 'v')
    {
        for (const auto &A : grupe) // su &, const apsaugo nuo pakeitimo (jo nenorim)
        {
            cout
                << left << setw(15) << A.vardas
                << left << setw(20) << A.pavarde
                << setw(10) << std::fixed << std::setprecision(2) << A.rez_vid
                << endl;
        }
    }
    else if (galutinio_pasirinkimas == 'm')
    {
        for (const auto &A : grupe) // su &, const apsaugo nuo pakeitimo (jo nenorim)
        {
            cout
                << left << setw(15) << A.vardas
                << left << setw(20) << A.pavarde
                << setw(10) << std::fixed << std::setprecision(2) << A.rez_med
                << endl;
        }
    }
}