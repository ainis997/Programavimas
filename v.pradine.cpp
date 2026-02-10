#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits> // maksimaliai int reikšmei gauti

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
        cout << "Įveskite vardą ir pavardę: ";
        cin >> A.vardas >> A.pavarde;

        int iverciu_sk, iverciu_suma = 0;
        cout << "Kiek bus semestro įverčių? ";
        while (!(cin >> iverciu_sk))
        {
            cout << "Netinkama įvestis. Įveskite tinkamą skaičių: ";
            cin.clear();                                       // išvalo errorus, atsiradusius dėl netinkamos įvesties
            cin.ignore(std::numeric_limits<int>::max(), '\n'); // iš atminties išsitrina anksčiau įrašytą įvestį (ištrina maksimaliai std::numeric_limits<int>::max() simbolių; trina iki kol aptinka simbolį '\n')
        }

        // cout << "Iveskite semestro ivercius: " << endl;
        for (int j = 0; j < iverciu_sk; j++)
        {
            cout << "Įveskite " << j + 1 << "-ąjį pažymį iš " << iverciu_sk << ": ";
            int pazymys;
            while (!(cin >> pazymys) || pazymys < 1 || pazymys > 10)
            {
                cout << "Netinkama įvestis. Įveskite pažymį tarp 1 ir 10: ";
                cin.clear();
                cin.ignore(std::numeric_limits<int>::max(), '\n');
            }

            A.paz.push_back(pazymys);
            iverciu_suma += pazymys;
        }

        cout << "Įveskite egzamino vertinimą: ";
        while (!(cin >> A.egz) || A.egz < 1 || A.egz > 10)
        {
            cout << "Netinkama įvestis. Įveskite pažymį tarp 1 ir 10: ";
            cin.clear();
            cin.ignore(std::numeric_limits<int>::max(), '\n');
        }
        /*do
        {
            cout << "Iveskite egzamino vertinima: ";
            cin >> A.egz;
        } while (A.egz < 1 || A.egz > 10);*/

        // vidurkio apsk.
        A.rez_vid = (iverciu_suma * 1.0) / (iverciu_sk * 1.0) * 0.4 + (A.egz * 0.6);

        // medianos apsk.
        vector<int> visi_paz = A.paz;
        visi_paz.push_back(A.egz);
        std::sort(visi_paz.begin(), visi_paz.end()); // sort(..) surikiuoja visi_paz vektorių did. tvarka
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
    while (ar_ivestas_tinkamas_galutinio_tipas == false)
    {
        cout << "Ar norite rasti galutinį vidurkį ar galutinę medianą?" << endl
             << "Jeigu vidurkį, įveskite: v" << endl
             << "Jeigu medianą, įveskite: m" << endl;
        cin >> galutinio_pasirinkimas;
        if (galutinio_pasirinkimas == 'v' || galutinio_pasirinkimas == 'm')
            ar_ivestas_tinkamas_galutinio_tipas = true;
    }

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
    const int LENTELES_PLOTIS = 50;
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