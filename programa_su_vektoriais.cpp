#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>  // maksimaliai int reikšmei gauti
#include <cstdlib> // atsitiktiniam skaičiam
#include <sstream> // string streamui

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
    string vardas = "Vardas";
    string pavarde = "Pavardė";
    vector<int> pazymiai;
    int egzo_rezas;
    // double rezas_vid; // gal vietoj šių narių palikti tiesiog double'ą grąžinančias apskaičiavimo funkcijas?
    // double rezas_med;
    double rezas_vid() const // dadėtas const reiškia, kad šitas metodas niekaip nepakeis paties objekto (tik read only)
    {
        if (pazymiai.size() == 0)
            return egzo_rezas * 0.6;
        int pazymiu_suma = 0;
        for (auto paz : pazymiai)
            pazymiu_suma += paz;
        double rezas_vid = ((pazymiu_suma * 1.0) / (pazymiai.size() * 1.0)) * 0.4 + (egzo_rezas * 0.6);
        return rezas_vid;
    }
    double rezas_med() const
    {
        if (pazymiai.size() == 0)
            return 0;
        double rezas_med = 0;
        vector<int> visi_pazymiai = pazymiai;
        visi_pazymiai.push_back(egzo_rezas);
        std::sort(visi_pazymiai.begin(), visi_pazymiai.end()); // sort(..) surikiuoja visi_pazymiai vektorių did. tvarka
        int visu_pazymiu_sk = visi_pazymiai.size();
        if (visu_pazymiu_sk % 2 != 0)
            rezas_med = visi_pazymiai[visu_pazymiu_sk / 2];
        else
            rezas_med = (visi_pazymiai[(visu_pazymiu_sk / 2) - 1] + visi_pazymiai[visu_pazymiu_sk / 2]) / 2.0;
        return rezas_med;
    }
};

int studentu_sk = 0; // nustatom čia, kad būtų globalus, visur matomas (reikia jo ir įvesties (studentų skaičiaus sekimui), ir išvesties (lentelės spausdinimui) fjoms)

void generuota_ivestis(vector<Studentas> &grupe);
void misri_ivestis(vector<Studentas> &grupe);
void rank_ivestis(vector<Studentas> &grupe);
void failo_ivestis(string failo_pav, vector<Studentas> &grupe);
void isvestis(vector<Studentas> &grupe);

int main()
{
    for (;;)
    {
        srand(time(0)); // nustatom rand() seedą (visos programos pradžioj)

        int eiga;
        cout << endl
             << "Pasirinkite, ka norite daryti:" << endl
             << "1 - ivesti duomenis is failo" << endl
             << "2 - ivesti duomenis ranka" << endl
             << "3 - ivesti duomenis, pazymius sugeneruoti" << endl
             << "4 - sugeneruoti duomenis" << endl
             << "5 - baigti darba" << endl;
        while (!(cin >> eiga) || (eiga != 1 && eiga != 2 && eiga != 3 && eiga != 4 && eiga != 5))
        {
            cout << "Pasirinkite, ka norite daryti [1/2/3/4]: ";
            cin.clear();
            cin.ignore(MAX_INT, '\n');
        }

        vector<Studentas> grupe;

        const string failo_pav = "kursiokai.txt";

        switch (eiga)
        {
        case 1:
            failo_ivestis(failo_pav, grupe);
            isvestis(grupe);
            studentu_sk = 0;
            break;
        case 2:
            rank_ivestis(grupe);
            isvestis(grupe);
            studentu_sk = 0; // atstatom studentų sk. (globalus kint., taigi reikia tai daryt)
            break;
        case 3:
            misri_ivestis(grupe);
            isvestis(grupe);
            studentu_sk = 0;
            break;
        case 4:
            generuota_ivestis(grupe);
            isvestis(grupe);
            studentu_sk = 0;
            break;
        case 5:
            return 0;
            break;
        }
    }
}

void failo_ivestis(string failo_pav, vector<Studentas> &grupe)
{
    FILE *failo_ptr; // C stiliaus failo rodyklės kintamasis

    vector<string> eilutes; // čia bus laikomos nuskaitytos failo eilutės

    // LAIKO MAT.
    char eil_buferis[250];
    failo_ptr = fopen(failo_pav.c_str(), "r"); // .c_str() tam, kad paverstų C++inį stringą į C'inį stringą (fopen() — C funkcija, dėl to reikia pritaikyt jai))

    if (failo_ptr == NULL)
    {
        // MEST AR PARODYT ERRORĄ, GAL IR SU TEMPLATE KLAIDŲ VALDYMO F-JA
        return;
    }

    while (fgets(eil_buferis, 250, failo_ptr) != NULL)
    {
        eilutes.push_back(eil_buferis);
    }
    fclose(failo_ptr);

    if (eilutes.empty())
    {
        // ERROR?
        return;
    }

    eilutes.erase(eilutes.begin()); // ištrinam pirmą elementą, nes jame — antraštinė eilutė

    for (const auto &eil : eilutes) // su & nesukuriamos eilutės kopijos — veikia greičiau
    {
        std::istringstream srautas(eil); // eilutės įvesties ("skaitymo") srautas

        Studentas A;

        if (!(srautas >> A.vardas >> A.pavarde))
            continue;

        int temp; // laikinas kintamasis pažymių perdavimui
        while (srautas >> temp)
        {
            A.pazymiai.push_back(temp);
        }

        if (A.pazymiai.empty())
            continue;
        A.egzo_rezas = A.pazymiai.back(); // paskutinis elementas — egzamino rezas
        A.pazymiai.pop_back();            // ištrinam egzo rezą iš pažymių vektoriaus

        grupe.push_back(A);
        A.pazymiai.clear();
    }
}

void generuota_ivestis(vector<Studentas> &grupe)
{
    int min_iverciu_sk;
    int reikiamas_studentu_sk;
    cout << "Iveskite, kiek studentai privalo tureti iverciu: ";
    while (!(cin >> min_iverciu_sk) || min_iverciu_sk <= 0)
    {
        cout << "Netinkama ivestis. Iveskite minimalu iverciu skaiciu: ";
        cin.clear();
        cin.ignore(MAX_INT, '\n');
    }
    cout << "Iveskite, kiek norite sugeneruoti studentu: ";
    while (!(cin >> reikiamas_studentu_sk) || reikiamas_studentu_sk <= 0)
    {
        cout << "Netinkama ivestis. Iveskite studentu skaiciu: ";
        cin.clear();
        cin.ignore(MAX_INT, '\n');
    }

    // vardų generavimui
    vector<string> vardai = {"Jonas", "Lina", "Lukas", "Egle", "Marius", "Migle", "Azuolas", "Aiste", "Tomas", "Ieva", "Mindaugas", "Austeja", "Vytautas", "Saule", "Rimvydas", "Gabija", "Povilas", "Lukne", "Audrius", "Ugne"};
    vector<string> vyr_pavardes = {"Butkus", "Zemaitis", "Rimkus", "Simkus", "Mazeika", "Petraitis", "Braziunas", "Sukys", "Simonis", "Bareikis"};
    vector<string> mot_pavardes = {"Butkute", "Zemaityte", "Rimkute", "Simkute", "Mazeikaite", "Petraityte", "Braziunaite", "Sukyte", "Simonyte", "Bareikyte"};

    for (int i = 0; i < reikiamas_studentu_sk; i++)
    {
        Studentas A;

        A.vardas = vardai[rand() % 20];
        if (A.vardas.back() == 's')
            A.pavarde = vyr_pavardes[rand() % 10];
        else
            A.pavarde = mot_pavardes[rand() % 10];

        int iverciu_sk = 0;
        int iverciu_suma = 0;

        for (int i = 0; i < min_iverciu_sk; i++)
        {
            A.pazymiai.push_back(rand() % 11); // sugeneruoti sk. nuo 0 iki 10
            iverciu_suma += A.pazymiai.back();
            iverciu_sk++;
        }
        A.egzo_rezas = rand() % 11; // 0-10

        grupe.push_back(A);
        A.pazymiai.clear(); // apsauga: isvalo pazymiu vektoriu, kad kitam kartojime vektorius butu tuscias
    }
}

void misri_ivestis(vector<Studentas> &grupe)
{
    int min_iverciu_sk;
    cout << "Iveskite, kiek studentai privalo tureti iverciu: ";
    while (!(cin >> min_iverciu_sk) || min_iverciu_sk <= 0)
    {
        cout << "Netinkama ivestis. Iveskite minimalu iverciu skaiciu: ";
        cin.clear();
        cin.ignore(MAX_INT, '\n');
    }

    cout << "Įveskite studentų duomenis." << endl
         << "Kai įvesite visus studentus, įveskite 'x'." << endl;

    for (int i = 0;; i++)
    {
        Studentas A;
        cout << "Iveskite varda ir pavarde: ";
        cin >> A.vardas;
        if (A.vardas == "x")
            break;
        cin >> A.pavarde;

        int iverciu_sk = 0;
        int iverciu_suma = 0;

        for (int i = 0; i < min_iverciu_sk; i++)
        {
            A.pazymiai.push_back(rand() % 11); // sugeneruoti sk. nuo 0 iki 10
            iverciu_suma += A.pazymiai.back();
            iverciu_sk++;
        }
        A.egzo_rezas = rand() % 11;

        grupe.push_back(A);
        A.pazymiai.clear(); // apsauga: isvalo pazymiu vektoriu, kad kitam kartojime vektorius butu tuscias
    }
}

void rank_ivestis(vector<Studentas> &grupe)
{
    int min_iverciu_sk;
    cout << "Iveskite, kiek studentai privalo tureti iverciu: ";
    while (!(cin >> min_iverciu_sk) || min_iverciu_sk <= 0)
    {
        cout << "Netinkama ivestis. Iveskite minimalu iverciu skaiciu: ";
        cin.clear();
        cin.ignore(MAX_INT, '\n');
    }

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

        // int iverciu_sk = 0;
        int iverciu_suma = 0;
        cout << "Iveskite semestro ivercius: (kai suvesite visus semestro ivercius, iveskite 'x')" << endl;
        for (;;) // for loopas be parametrų — begalinis loopas (iš jo išeis tik jeigu vartotojas įves "x")
        {
            int pazymys;
            string ivercio_ivestis;
            cin >> ivercio_ivestis;
            if (ivercio_ivestis == "x")
                break;

            try
            {
                pazymys = std::stoi(ivercio_ivestis); // std::stoi funkcija paverčia string į int.
                if (pazymys < 0 || pazymys > 10)
                    throw "Netinkama ivestis"; // tuščio "throw;" negalima palikt, nes td tsg užlauš programą
                A.pazymiai.push_back(pazymys);
                iverciu_suma += pazymys;
                // iverciu_sk++;
            }
            catch (...) // "..." argumentas sako, kad priimk bet kokią klaidą; šiuo catch bloku valdom dvi klaidas: string>int konvertavimo galimą klaidą IR netinkamą pažymio skaitinę vertę (ne tarp 1 ir 10)
            {
                cout << "Netinkama ivestis. Iveskite pazymi tarp 0 iki 10: ";
            }
        }

        cout << "Iveskite egzamino vertinima: ";
        while (!(cin >> A.egzo_rezas) || A.egzo_rezas < 0 || A.egzo_rezas > 10)
        {
            cout << "Netinkama ivestis. Iveskite pazymi tarp 0 ir 10: ";
            cin.clear();
            cin.ignore(MAX_INT, '\n');
        }
        cin.ignore(MAX_INT, '\n'); // SKIRTA TAM, jeigu būtų įvestas float skaičius: ši komanda ištrins bufery likusią pokablelinę dalį (jinai lieka, kadangi programa pasiima tik sveikąją dalį iš įvesties). To reikia todėl, nes ta likusi bufery dalis po to tampa sekančios įvesties dalim (o to mum nereik)

        if (A.pazymiai.size() < min_iverciu_sk)
        {
            A.pazymiai.resize(min_iverciu_sk, 0); // pridės reikiamą sk. nulių, jeigu pažymių yra mažiau nei jų privalomas minimalus sk.
        }

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

    // dinamiškam lentelės stulpelių pavadinimų pavaizdavimui
    string pasirinktas_galutinis;
    if (galutinio_pasirinkimas == "v")
        pasirinktas_galutinis = "Vid.";

    else if (galutinio_pasirinkimas == "m")
        pasirinktas_galutinis = "Med.";

    // lentelės viršutinės eilutės spausdinimas (joje — stulpelių pavadinimai)
    cout
        << left << setw(20) << "Vardas"
        << left << setw(25) << "Pavarde"
        << left << setw(10) << "Galutinis (" << pasirinktas_galutinis << ")"
        << endl;

    // skiriamosios linijos tarp lentelės viršutinės ir likusiųjų eilučių spausdinimas
    const int LENTELES_PLOTIS = 60;
    for (int i = 0; i < LENTELES_PLOTIS; i++)
        cout << "-";
    cout << endl;

    if (galutinio_pasirinkimas == "v")
    {
        for (const auto &A : grupe)
        {
            cout
                << left << setw(20) << A.vardas
                << left << setw(25) << A.pavarde
                << setw(10) << std::fixed << std::setprecision(2) << A.rezas_vid()
                << endl;
        }
    }
    else if (galutinio_pasirinkimas == "m")
    {
        for (const auto &A : grupe)
        {
            cout
                << left << setw(20) << A.vardas
                << left << setw(25) << A.pavarde
                << setw(10) << std::fixed << std::setprecision(2) << A.rezas_med()
                << endl;
        }
    }
}