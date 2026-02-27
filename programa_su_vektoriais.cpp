#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>  // maksimaliai int reikšmei gauti
#include <cstdlib> // atsitiktiniam skaičiam
#include <sstream> // string streamui
#include <chrono>  // laiko fiksavimui
#include <fstream> // failam

// su šitais nereiks visur std:: dadėt
using std::cin;
using std::cout;
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
    int egzo_rezas = 0;
    double rezas_vid = 0; // gal vietoj šių narių palikti tiesiog double'ą grąžinančias apskaičiavimo funkcijas?
    double rezas_med = 0;
    void apsk_vid() // dadėtas const reiškia, kad šitas metodas niekaip nepakeis paties objekto (tik read only)
    {
        if (pazymiai.size() == 0)
            rezas_vid = egzo_rezas * 0.6;
        int pazymiu_suma = 0;
        for (auto paz : pazymiai)
            pazymiu_suma += paz;
        rezas_vid = ((pazymiu_suma * 1.0) / (pazymiai.size() * 1.0)) * 0.4 + (egzo_rezas * 0.6);
    }
    void apsk_med()
    {
        if (pazymiai.size() == 0)
            return;
        vector<int> visi_pazymiai = pazymiai;
        visi_pazymiai.push_back(egzo_rezas);
        std::sort(visi_pazymiai.begin(), visi_pazymiai.end()); // sort(..) surikiuoja visi_pazymiai vektorių did. tvarka
        int visu_pazymiu_sk = visi_pazymiai.size();
        if (visu_pazymiu_sk % 2 != 0)
            rezas_med = visi_pazymiai[visu_pazymiu_sk / 2];
        else
            rezas_med = (visi_pazymiai[(visu_pazymiu_sk / 2) - 1] + visi_pazymiai[visu_pazymiu_sk / 2]) / 2.0;
    }
};

struct Failo_dorojimo_laikai
{
    // std::chrono::duration<double> nuskaitymas;
    std::chrono::duration<double> duomenu_apdorojimas;
    std::chrono::duration<double> duomenu_rikiavimas;
    std::chrono::duration<double> duomenu_isvedimas;
    std::chrono::duration<double> visa_trukme;
};

void generuota_ivestis(vector<Studentas> &grupe);
void misri_ivestis(vector<Studentas> &grupe);
void rank_ivestis(vector<Studentas> &grupe);
void failo_ivestis(string SKAIT_FAILO_PAV, vector<Studentas> &grupe, Failo_dorojimo_laikai &t);
void isvestis(string RAS_FAILO_PAV, vector<Studentas> &grupe, Failo_dorojimo_laikai &t);

bool pagal_varda_did(Studentas &A, Studentas &B);
bool pagal_varda_maz(Studentas &A, Studentas &B);
bool pagal_pavarde_did(Studentas &A, Studentas &B);
bool pagal_pavarde_maz(Studentas &A, Studentas &B);
bool pagal_vidurki_did(Studentas &A, Studentas &B);
bool pagal_vidurki_maz(Studentas &A, Studentas &B);
bool pagal_mediana_did(Studentas &A, Studentas &B);
bool pagal_mediana_maz(Studentas &A, Studentas &B);

int main()
{
    bool ar_failas_jau_apdorotas = false;
    for (;;)
    {
        srand(time(0)); // nustatom rand() seedą (visos programos pradžioj)

        int eiga;
        cout << '\n'
             << "Pasirinkite, ka norite daryti:" << '\n'
             << "1 - ivesti duomenis is failo" << '\n'
             << "2 - ivesti duomenis ranka" << '\n'
             << "3 - ivesti duomenis, pazymius sugeneruoti" << '\n'
             << "4 - sugeneruoti duomenis" << '\n'
             << "5 - baigti darba" << '\n';
        while (!(cin >> eiga) || (eiga != 1 && eiga != 2 && eiga != 3 && eiga != 4 && eiga != 5))
        {
            cout << "Pasirinkite, ka norite daryti [1/2/3/4/5]: ";
            cin.clear();
            cin.ignore(MAX_INT, '\n');
        }

        vector<Studentas> grupe;

        string SKAIT_FAILO_PAV;
        const string RAS_FAILO_PAV = "studentu_isvestis.txt";

        Failo_dorojimo_laikai t;

        switch (eiga)
        {
        case 1:
        {
            // atstatom/nustatom nulin laikus
            t.duomenu_apdorojimas = t.duomenu_rikiavimas = t.duomenu_isvedimas = std::chrono::milliseconds::zero();

            cout << "Iveskite ivesties failo pavadinima:\n";
            cin.ignore(MAX_INT, '\n'); // ištrint įvestį iš buferio, jeigu iš ankstesnės įvesties kažkas jame liko
            std::getline(cin, SKAIT_FAILO_PAV);
            auto pati_pradzia = std::chrono::high_resolution_clock::now();
            failo_ivestis(SKAIT_FAILO_PAV, grupe, t);
            isvestis(RAS_FAILO_PAV, grupe, t);
            auto pati_pab = std::chrono::high_resolution_clock::now();
            t.visa_trukme = pati_pab - pati_pradzia;

            cout << '\n'
                 << "Failo duomenu apdorojimo trukme: " << t.duomenu_apdorojimas.count() << "s" << '\n'
                 << "Failo duomenu surikiavimo trukme: " << t.duomenu_rikiavimas.count() << "s" << '\n'
                 << "Failo duomenu isvedimo trukme: " << t.duomenu_isvedimas.count() << "s" << '\n'
                 << "Visos programos trukme: " << t.visa_trukme.count() << "s" << '\n';
            break;
        }
        case 2:
        {
            rank_ivestis(grupe);
            isvestis(RAS_FAILO_PAV, grupe, t);
            break;
        }
        case 3:
        {
            misri_ivestis(grupe);
            isvestis(RAS_FAILO_PAV, grupe, t);
            break;
        }
        case 4:
        {
            generuota_ivestis(grupe);
            isvestis(RAS_FAILO_PAV, grupe, t);
            break;
        }
        case 5:
        {
            return 0;
            break;
        }
        }
    }
}

void failo_ivestis(string SKAIT_FAILO_PAV, vector<Studentas> &grupe, Failo_dorojimo_laikai &t)
{
    auto pr = std::chrono::high_resolution_clock::now();

    std::ifstream sk_failas(SKAIT_FAILO_PAV); // sukuria įvesties srautą ir atidaro failą
    if (!sk_failas.is_open())
    {
        // MEST AR PARODYT ERRORĄ, GAL IR SU TEMPLATE KLAIDŲ VALDYMO F-JA
        cout << "Ivesties failas nurodytu pavadinimu nerastas." << '\n';
        return;
    }

    string sk_failo_eil;

    while (std::getline(sk_failas, sk_failo_eil))
    {
        std::istringstream srautas(sk_failo_eil); // eilutės įvesties ("skaitymo") srautas

        Studentas A;

        if (!(srautas >> A.vardas >> A.pavarde))
            continue;

        int temp; // laikinas kintamasis pažymių perdavimui
        while (srautas >> temp)
        {
            A.pazymiai.push_back(temp);
        }

        if (A.pazymiai.empty()) // jeigu pažymių vektorius gautųsi tuščias, tai pereit (continue) prie kitos iteracijos
            continue;
        A.egzo_rezas = A.pazymiai.back(); // paskutinis elementas — egzamino rezas
        A.pazymiai.pop_back();            // ištrinam egzo rezą iš pažymių vektoriaus

        A.apsk_vid();
        A.apsk_med();

        grupe.push_back(A);
        A.pazymiai.clear();
    }

    sk_failas.close();
    auto pab = std::chrono::high_resolution_clock::now();
    t.duomenu_apdorojimas = pab - pr;
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

        A.apsk_vid();
        A.apsk_med();

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

    cout << "Įveskite studentų duomenis." << '\n'
         << "Kai įvesite visus studentus, įveskite 'x'." << '\n';

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

        A.apsk_vid();
        A.apsk_med();

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
            cout << "Ar norite suvesti dar vieno studento duomenis?" << '\n';
            while (arDarVestiStudenta != "n" && arDarVestiStudenta != "t")
            {
                cout << "Jeigu taip, iveskite 't'. Jeigu ne, iveskite 'n'." << '\n';
                cin >> arDarVestiStudenta;
            }
            if (arDarVestiStudenta == "n")
                break;
        }

        Studentas A;
        cout << "Iveskite varda ir pavarde: ";
        cin >> A.vardas >> A.pavarde;

        int iverciu_suma = 0;
        cout << "Iveskite semestro ivercius: (kai suvesite visus semestro ivercius, iveskite 'x')" << '\n';
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

        A.apsk_vid();
        A.apsk_med();

        grupe.push_back(A);
        A.pazymiai.clear(); // apsauga: isvalo pazymiu vektoriu, kad kitam kartojime vektorius butu tuscias
    }
}

void isvestis(string RAS_FAILO_PAV, vector<Studentas> &grupe, Failo_dorojimo_laikai &t)
{
    if (grupe.empty())
        return;

    string galutinio_pasirinkimas;
    bool ar_ivestas_tinkamas_galutinio_tipas = false;
    while (ar_ivestas_tinkamas_galutinio_tipas == false)
    {
        cout << "Ar norite rasti galutini vidurki ar galutine mediana?" << '\n'
             << "Jeigu vidurki, iveskite 'v'. Jeigu mediana, iveskite 'm'. " << '\n';
        cin >> galutinio_pasirinkimas;
        if (galutinio_pasirinkimas == "v" || galutinio_pasirinkimas == "m")
            ar_ivestas_tinkamas_galutinio_tipas = true;
    }

    // dinamiškam lentelės stulpelių pavadinimų pavaizdavimui
    string pasirinktas_galutinis;
    if (galutinio_pasirinkimas == "v")
        pasirinktas_galutinis = "Galutinis (Vid.)";

    else if (galutinio_pasirinkimas == "m")
        pasirinktas_galutinis = "Galutinis (Med.)";

    string rus; // rus - rūšiavimo būdas
    cout << "Pasirinkite studentu rusiavimo buda:" << '\n'
         << "'vard' - pagal varda" << '\n'
         << "'pav' - pagal pavarde" << '\n'
         << "'vid' - pagal vidurki" << '\n'
         << "'med' - pagal mediana" << '\n'
         << "'ne' - nerusiuoti" << '\n';
    // bool tinkama_rus_ivestis = rus == "vard" || rus == "pav" || rus == "vid" || rus == "med" || rus == "ne";
    for (;;)
    {
        cin >> rus;
        if (rus == "vard" || rus == "pav" || rus == "vid" || rus == "med" || rus == "ne")
            break;
        cout << "Netinkama ivestis. Galimos ivesti reiksmes: 'vard', 'pav', 'vid', 'med', 'ne': ";
    }

    auto pr = std::chrono::high_resolution_clock::now();
    if (rus != "ne")
    {
        string tvarka;
        cout << "Pasirinkite studentu rusiavimo tvarka:" << '\n'
             << "'d' - didejimo tvarka" << '\n'
             << "'m' - mazejimo tvarka" << '\n';
        for (;;)
        {
            cin >> tvarka;
            if (tvarka == "d" || tvarka == "m")
                break;
            cout << "Netinkama ivestis. Galimos ivesti reiksmes: 'd', 'm': ";
        }

        if (tvarka == "d")
        {
            if (rus == "vard")
                std::sort(grupe.begin(), grupe.end(), pagal_varda_did);
            else if (rus == "pav")
                std::sort(grupe.begin(), grupe.end(), pagal_pavarde_did);
            else if (rus == "vid")
                std::sort(grupe.begin(), grupe.end(), pagal_vidurki_did);
            else if (rus == "med")
                std::sort(grupe.begin(), grupe.end(), pagal_mediana_did);
        }
        else if (tvarka == "m")
        {
            if (rus == "vard")
                std::sort(grupe.begin(), grupe.end(), pagal_varda_maz);
            else if (rus == "pav")
                std::sort(grupe.begin(), grupe.end(), pagal_pavarde_maz);
            else if (rus == "vid")
                std::sort(grupe.begin(), grupe.end(), pagal_vidurki_maz);
            else if (rus == "med")
                std::sort(grupe.begin(), grupe.end(), pagal_mediana_maz);
        }
    }
    auto pab = std::chrono::high_resolution_clock::now();
    t.duomenu_rikiavimas = pab - pr;

    pr = std::chrono::high_resolution_clock::now();

    std::ofstream ras_failas(RAS_FAILO_PAV);

    if (!ras_failas.is_open())
    {
        // MEST AR PARODYT ERRORĄ, GAL IR SU TEMPLATE KLAIDŲ VALDYMO F-JA
        cout << "Nepavyko atidaryti isvesties failo." << '\n';
        return;
    }

    ras_failas
        << left << setw(20) << "Vardas"
        << left << setw(25) << "Pavarde"
        << left << setw(15) << pasirinktas_galutinis
        << '\n';

    // skiriamosios linijos tarp lentelės viršutinės ir likusiųjų eilučių spausdinimas
    const int LENTELES_PLOTIS = 60;
    for (int i = 0; i < LENTELES_PLOTIS; i++)
        ras_failas << "-";
    ras_failas << '\n';

    if (galutinio_pasirinkimas == "v")
    {
        for (const auto &A : grupe)
        {
            ras_failas
                << left << setw(20) << A.vardas
                << left << setw(25) << A.pavarde
                << setw(15) << std::fixed << std::setprecision(2) << A.rezas_vid
                << '\n';
        }
    }
    else if (galutinio_pasirinkimas == "m")
    {
        for (const auto &A : grupe)
        {
            ras_failas
                << left << setw(20) << A.vardas
                << left << setw(25) << A.pavarde
                << setw(15) << std::fixed << std::setprecision(2) << A.rezas_med
                << '\n';
        }
    }
    ras_failas.close();

    pab = std::chrono::high_resolution_clock::now();
    t.duomenu_isvedimas = pab - pr;
}

bool pagal_varda_did(Studentas &A, Studentas &B)
{
    for (char &raide : A.vardas)
        raide = std::tolower(raide);
    for (char &raide : B.vardas)
        raide = std::tolower(raide);
    return A.vardas < B.vardas;
}

bool pagal_varda_maz(Studentas &A, Studentas &B)
{
    for (char &raide : A.vardas)
        raide = std::tolower(raide);
    for (char &raide : B.vardas)
        raide = std::tolower(raide);
    return A.vardas > B.vardas;
}

bool pagal_pavarde_did(Studentas &A, Studentas &B)
{
    for (char &raide : A.pavarde)
        raide = std::tolower(raide);
    for (char &raide : B.pavarde)
        raide = std::tolower(raide);
    return A.pavarde < B.pavarde;
}

bool pagal_pavarde_maz(Studentas &A, Studentas &B)
{
    for (char &raide : A.pavarde)
        raide = std::tolower(raide);
    for (char &raide : B.pavarde)
        raide = std::tolower(raide);
    return A.pavarde > B.pavarde;
}

bool pagal_vidurki_did(Studentas &A, Studentas &B)
{
    return A.rezas_vid < B.rezas_vid;
}

bool pagal_vidurki_maz(Studentas &A, Studentas &B)
{
    return A.rezas_vid > B.rezas_vid;
}

bool pagal_mediana_did(Studentas &A, Studentas &B)
{
    return A.rezas_med < B.rezas_med;
}

bool pagal_mediana_maz(Studentas &A, Studentas &B)
{
    return A.rezas_med > B.rezas_med;
}