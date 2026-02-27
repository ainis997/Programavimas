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

#include "ivestis_isvestis.h"
#include "strukturos_konstantos.h"
#include "pagalbines_fjos.h"

// su šitais nereiks visur std:: dadėt
using std::cin;
using std::cout;
using std::left;
using std::right;
using std::setw;
using std::string;
using std::vector;

void failo_ivestis(string SKAIT_FAILO_PAV, vector<Studentas> &grupe, Programos_laikai &t)
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

void rank_ivestis(vector<Studentas> &grupe)
{
    int min_iverciu_sk;
    cout << "Iveskite, kiek studentai privalo tureti iverciu: ";
    natur_skaiciaus_ivestis(min_iverciu_sk, ar_sk_nedidesnis_uz_0);

    for (int i = 0;; i++)
    {
        if (i > 0)
        {
            string arDarVestiStudenta;
            string ivestis;
            cout << "Ar norite suvesti dar vieno studento duomenis?" << '\n'
                 << "t - taip, n - ne\n";
            for (;;)
            {
                std::getline(cin, ivestis);
                if (ivestis == "t" || ivestis == "n")
                {
                    arDarVestiStudenta = ivestis;
                    break;
                }
                cout << "Netinkama ivestis. Iveskite dar karta: ";
            }
            if (arDarVestiStudenta == "n")
                break;
        }

        Studentas A;

        bool ar_ivestis_atsaukiama = false;
        vardo_pavardes_ivestis(A, ar_ivestis_atsaukiama); // false reiškia, kad šioje įvestyje negalima atšaukti studentų duomenų pildymo apskritai

        cout << "Iveskite semestro ivercius: (kai suvesite visus semestro ivercius, iveskite 'x')" << '\n';
        // čia palikti cin, kad būtų lankstesnis įvedimas: gali ir enteriais, ir tarpais atskirt pažymius
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
            }
            catch (...) // "..." argumentas sako, kad priimk bet kokią klaidą; šiuo catch bloku valdom dvi klaidas: string>int konvertavimo galimą klaidą IR netinkamą pažymio skaitinę vertę (ne tarp 1 ir 10)
            {
                cout << "Netinkama ivestis. Iveskite pazymi tarp 0 iki 10: ";
            }
        }

        cout << "Iveskite egzamino vertinima: ";
        natur_skaiciaus_ivestis(A.egzo_rezas, ar_sk_ne_tarp_0_ir_10);
        // while (!(cin >> A.egzo_rezas) || A.egzo_rezas < 0 || A.egzo_rezas > 10)
        // {
        //     cout << "Netinkama ivestis. Iveskite pazymi tarp 0 ir 10: ";
        //     cin.clear();
        //     cin.ignore(MAX_INT, '\n');
        // }
        // cin.ignore(MAX_INT, '\n'); // SKIRTA TAM, jeigu būtų įvestas float skaičius: ši komanda ištrins bufery likusią pokablelinę dalį (jinai lieka, kadangi programa pasiima tik sveikąją dalį iš įvesties). To reikia todėl, nes ta likusi bufery dalis po to tampa sekančios įvesties dalim (o to mum nereik)

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

// ================

void misri_ivestis(vector<Studentas> &grupe)
{
    int min_iverciu_sk = 0;
    string ivestis3;
    cout << "Iveskite, kiek studentai privalo tureti iverciu: ";
    natur_skaiciaus_ivestis(min_iverciu_sk, nullptr); // perduodam kintamojo *referencą*

    cout << "Įveskite studentų duomenis. Kai įvesite visus studentus, įveskite 'x'." << '\n';

    for (int i = 0;; i++)
    {
        Studentas A;

        bool ar_ivestis_atsaukiama = true;                     // true reiškia, kad šioje įvestyje galima atšaukti studentų duomenų pildymo apskritai (jeigu vartotojas įves "x", )
        if (!vardo_pavardes_ivestis(A, ar_ivestis_atsaukiama)) // jeigu f-ja grąžina false, tai reikia nutraukti visą šį loopą
            break;

        for (int i = 0; i < min_iverciu_sk; i++)
        {
            A.pazymiai.push_back(rand() % 11); // sugeneruoti sk. nuo 0 iki 10
        }
        A.egzo_rezas = rand() % 11;

        A.apsk_vid();
        A.apsk_med();

        grupe.push_back(A);
        A.pazymiai.clear(); // apsauga: isvalo pazymiu vektoriu, kad kitam kartojime vektorius butu tuscias
    }
}

void generuota_ivestis(vector<Studentas> &grupe)
{
    int min_iverciu_sk = 0;
    string ivestis1;
    cout << "Iveskite, kiek studentai privalo tureti iverciu: ";
    natur_skaiciaus_ivestis(min_iverciu_sk, ar_sk_nedidesnis_uz_0); // perduodam kintamojo *referencą*

    int reikiamas_studentu_sk = 0;
    string ivestis2;
    cout << "Iveskite, kiek norite sugeneruoti studentu: ";
    natur_skaiciaus_ivestis(reikiamas_studentu_sk, ar_sk_nedidesnis_uz_0); // perduodam kintamojo *referencą*

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

        for (int i = 0; i < min_iverciu_sk; i++)
        {
            A.pazymiai.push_back(rand() % 11); // sugeneruoti sk. nuo 0 iki 10
        }
        A.egzo_rezas = rand() % 11; // 0-10

        A.apsk_vid();
        A.apsk_med();

        grupe.push_back(A);
        A.pazymiai.clear(); // apsauga: isvalo pazymiu vektoriu, kad kitam kartojime vektorius butu tuscias
    }
}

void natur_skaiciaus_ivestis(int &sk, bool (*papild_salygu_fja)(int)) // default reikšmė nullptr, jeigu papildomų sąlygų nustatymo funkcija nebus pateikta iškvietime
{
    string ivestis;

    while (std::getline(cin, ivestis))
    {
        std::istringstream sr(ivestis);
        if (sr >> ivestis)
        {
            try
            {
                string perteklius;
                if (sr >> perteklius) // programa nelūštų be šito (tsg paima pirmą elementą), bet tai tsg aiškumui
                    throw std::runtime_error("Pertekline ivestis.");
                size_t perskaitytu_simboliu_sk;
                sk = std::stoi(ivestis, &perskaitytu_simboliu_sk); // 2-as parametras: tam, kad stoi galėtų kintamajan (pro rodyklę) įrašyt perskaitytų simbolių skaičių
                if (perskaitytu_simboliu_sk != ivestis.length())   // tam, jeigu ivestu pvz. "7t" (pats std::stoi nesugaudo tokių!)
                    throw std::runtime_error("Netinkama ivestis.");
                if (sk <= 0)
                    throw std::runtime_error("Netinkama ivestis.");
                if (papild_salygu_fja != nullptr)
                    if (papild_salygu_fja(sk))
                        throw std::runtime_error("Netinkama ivestis.");
                break; // jeigu viršuj buvo errorų, šio kodo nepasieks; jeigu nebuvo - pasieks
            }
            catch (const std::exception &e)
            {
                cout << "Netinkama ivestis. Iveskite dar karta: ";
            }
        }
    }
}

// grąžina bool: jeigu false, tai po vardo/pavardės įvedimo nebebus tęsiamas apskritai studentų duomenų pildymas (reikia mišrios įvesties f-jai); jeigu true, tai atvirkščiai, nieks nesikeičia
bool vardo_pavardes_ivestis(Studentas &A, bool ar_ivestis_atsaukiama)
{
    cout << "Iveskite varda ir pavarde: ";
    for (;;)
    {
        string vardas_pavarde;
        if (std::getline(cin, vardas_pavarde)) // jeigu sėkmingai nuskaito eilutę, tai ...
        {
            if (vardas_pavarde.empty())
            {
                cout << "Tuscia ivestis. Iveskite dar karta: ";
                continue;
            }
            if (vardas_pavarde == "x" && ar_ivestis_atsaukiama) // sąlyga, reikalinga mišrios įvesties f-jai
            {
                return false;
            }
            std::istringstream sr(vardas_pavarde);
            string vardo_ivestis, pavardes_ivestis;
            string perteklius;
            if (sr >> vardo_ivestis >> pavardes_ivestis) // jeigu sėkmingai nuskaitytos dvi vertės - vardo ir pavardės - tai ...
            {
                if (sr >> perteklius) // jeigu ivesta per daug duomenu
                {
                    cout << "Pertekline ivestis. Iveskite dar karta: ";
                    continue;
                }
                A.vardas = vardo_ivestis;
                A.pavarde = pavardes_ivestis;
                break;
            }
            else
                cout << "Netinkama ivestis. Iveskite dar karta: ";
        }
        else
            cout << "Netinkama ivestis. Iveskite dar karta: ";
    }
    return true;
}

// ===== IŠVESTIS =====

void isvestis(string RAS_FAILO_PAV, vector<Studentas> &grupe, Programos_laikai &t)
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