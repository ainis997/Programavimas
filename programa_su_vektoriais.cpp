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

// kad būtų trumpiau
const auto MAX_INT = std::numeric_limits<int>::max();

struct Studentas
{
    string vardas, pavarde;
    vector<int> pazymiai;
    int egzo_rezas;
    double rezas_vid;
    double rezas_med;
};

void ivestis(vector<Studentas> &grupe);
void isvestis(vector<Studentas> &grupe);

int main()
{
    vector<Studentas> grupe;
    ivestis(grupe);
    isvestis(grupe);

    // pritaikymas terminalui: tinkama programos pabaiga (kad vartotojas spėtų pamatyti išvestį)
    cin.ignore(); // išvalo įvesties buferį (atmintį); be jo — programos langas iš karto išsijungia
    cout << endl
         << "Programos pabaiga. Spauskite ENTER..." << endl;
    cin.get(); // lauks kol vartotojas paspaus enter
}

void ivestis(vector<Studentas> &grupe)
{
    for (int i = 0;; i++)
    {
        if (i > 0)
        {
            string arDarVestiStudenta;
            cout << "Ar norite suvesti dar vieno studento duomenis?" << endl;
            while (arDarVestiStudenta != "n" && arDarVestiStudenta != "t")
            {
                cout << "Jeigu taip, iveskite 't'. Jeigu ne, iveskite 'n'." << endl;
                cin >> arDarVestiStudenta;
            }
            if (arDarVestiStudenta == "n")
                break;
        }

        Studentas A;
        cout << "Iveskite varda ir pavarde: ";
        cin >> A.vardas >> A.pavarde;

        cout << "Iveskite semestro ivercius: (kai suvesite visus semestro ivercius, iveskite 'x')" << endl;
        int iverciu_sk = 0;
        int iverciu_suma = 0;
        for (;;)
        {
            int pazymys;
            string ivercio_ivestis;
            cin >> ivercio_ivestis;
            if (ivercio_ivestis == "x")
                break;
            try
            {
                pazymys = std::stoi(ivercio_ivestis);
                if (pazymys < 1 || pazymys > 10)
                    throw "Netinkama ivestis"; // tuscio "throw;" negalima palikt, nes td tsg užlauš programą
                A.pazymiai.push_back(pazymys);
                iverciu_sk++;
                iverciu_suma += pazymys;
            }
            catch (...)
            { // "..." argumentas sako, kad priimk bet kokią klaidą
                cout << "Netinkama ivestis. Iveskite pazymi nuo 1 iki 10: ";
            }
        }

        cout << "Iveskite egzamino vertinima: ";
        while (!(cin >> A.egzo_rezas) || A.egzo_rezas < 1 || A.egzo_rezas > 10)
        {
            cout << "Netinkama ivestis. Iveskite pazymi tarp 1 ir 10: ";
            cin.clear();
            cin.ignore(MAX_INT, '\n');
        }

        // vidurkio apsk.
        A.rezas_vid = (iverciu_suma * 1.0) / (iverciu_sk * 1.0) * 0.4 + (A.egzo_rezas * 0.6);

        // medianos apsk.
        vector<int> visi_pazymiai = A.pazymiai;
        visi_pazymiai.push_back(A.egzo_rezas);
        std::sort(visi_pazymiai.begin(), visi_pazymiai.end()); // sort(..) surikiuoja visi_pazymiai vektorių did. tvarka
        int visu_pazymiu_sk = visi_pazymiai.size();
        if (visu_pazymiu_sk % 2 != 0)
            A.rezas_med = visi_pazymiai[visu_pazymiu_sk / 2];
        else
            A.rezas_med = (visi_pazymiai[(visu_pazymiu_sk / 2) - 1] + visi_pazymiai[visu_pazymiu_sk / 2]) / 2.0;

        grupe.push_back(A);
        A.pazymiai.clear(); // apsauga: isvalo pazymiu vektoriu, kad kitam kartojime vektorius butu tuscias
    }
}

void isvestis(vector<Studentas> &grupe)
{
    string galutinio_pasirinkimas;
    bool ar_ivestas_tinkamas_galutinio_tipas = false;
    while (ar_ivestas_tinkamas_galutinio_tipas == false)
    {
        cout << "Ar norite rasti galutini vidurki ar galutine mediana?" << endl
             << "Jeigu vidurki, iveskite 'v'. Jeigu mediana, iveskite 'm'. " << endl;
        cin >> galutinio_pasirinkimas;
        if (galutinio_pasirinkimas == "v" || galutinio_pasirinkimas == "m")
            ar_ivestas_tinkamas_galutinio_tipas = true;
    }

    string pasirinktas_galutinis;
    if (galutinio_pasirinkimas == "v")
        pasirinktas_galutinis = "Vid.";
    else if (galutinio_pasirinkimas == "m")
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

    if (galutinio_pasirinkimas == "v")
    {
        for (const auto &A : grupe) // su &, const apsaugo nuo pakeitimo (jo nenorim)
        {
            cout
                << left << setw(15) << A.vardas
                << left << setw(20) << A.pavarde
                << setw(10) << std::fixed << std::setprecision(2) << A.rezas_vid
                << endl;
        }
    }
    else if (galutinio_pasirinkimas == "m")
    {
        for (const auto &A : grupe) // su &, const apsaugo nuo pakeitimo (jo nenorim)
        {
            cout
                << left << setw(15) << A.vardas
                << left << setw(20) << A.pavarde
                << setw(10) << std::fixed << std::setprecision(2) << A.rezas_med
                << endl;
        }
    }
}