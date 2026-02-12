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

// int masyvo_dydis = 10;

struct Studentas
{
    string vardas, pavarde;
    int masyvo_dydis = 5;
    int *pazymiai = new int[masyvo_dydis];
    int egzo_rezas;
    double rezas_vid;
    double rezas_med;
};

void ivestis(Studentas *&grupe, int &studentu_masyvo_dydis);
void isvestis(Studentas *&grupe);

// DEĪKTAN DABBER NI LABBAN ĒNSTAN PŪNKCIJAN
template <typename T>
void padid_masyva(int &dab_dydis, T *&masyvas)
{
    T *naujo_masyvo_rod = new T[dab_dydis * 2];
    std::copy_n(masyvas, dab_dydis, naujo_masyvo_rod); // arba: std::move(..)
    dab_dydis *= 2;
    delete[] masyvas;
    masyvas = naujo_masyvo_rod;
}

int main()
{
    // realiai vos ne visas main turinys turės būti begaliniam loope (jis baigsis tik vartotojui paliepus)
    /*
    string eiga;
    cout << "Pasirinkite, ka norite daryti:" << endl
         << "1 - ivesti duomenis ranka" << endl
         << "2 - ivesti duomenis, pazymius sugeneruoti" << endl
         << "3 - sugeneruoti duomenis" << endl
         << "4 - baigti darba" << endl;
    bool ok_eiga = eiga == "1" || eiga == "2" || eiga == "3" || eiga == "4";
    while (!ok_eiga)
    {
        cin >> eiga;
        if (!ok_eiga)
            cout << "Pasirinkite, ka norite daryti [1/2/3/4]: ";
    }
    switch (std::stoi(eiga))
    {
    case 1:
        //
        break;
    case 2:
        //
        break;
    case 3:
        //
        break;
    case 4:
        //
        break;
    }*/
    int studentu_masyvo_dydis = 5;
    Studentas *grupe = new Studentas[studentu_masyvo_dydis];
    // vector<Studentas> grupe;
    ivestis(grupe, studentu_masyvo_dydis);
    isvestis(grupe);

    delete[] grupe;

    // pritaikymas terminalui: tinkama programos pabaiga (kad vartotojas spėtų pamatyti išvestį)
    cin.ignore(); // išvalo įvesties buferį (atmintį); be jo — programos langas iš karto išsijungia
    cout << endl
         << "Programos pabaiga. Spauskite ENTER..." << endl;
    cin.get(); // lauks kol vartotojas paspaus enter
}

int studentu_sk = 0; // nustatom čia, kad būtų globalus, visur matomas (reikia jo ir išvesties fjai)

void ivestis(Studentas *&grupe, int &studentu_masyvo_dydis)
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

        if (studentu_sk == studentu_masyvo_dydis)
        {
            padid_masyva(studentu_masyvo_dydis, grupe);
        }

        Studentas A;
        cout << "Iveskite varda ir pavarde: ";
        cin >> A.vardas >> A.pavarde;

        int iverciu_sk = 0;
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
                A.pazymiai[iverciu_sk] = pazymys;
                iverciu_suma += pazymys;
                iverciu_sk++;

                // MASYVO PADIDINIMAS (jeigu pasiekiama esama masyvo dydžio riba)
                if (iverciu_sk == A.masyvo_dydis)
                    padid_masyva(A.masyvo_dydis, A.pazymiai);
            }
            catch (...) // "..." argumentas sako, kad priimk bet kokią klaidą; šiuo catch bloku valdom dvi klaidas: string>int konvertavimo galimą klaidą IR netinkamą pažymio skaitinę vertę (ne tarp 1 ir 10)
            {
                cout << "Netinkama ivestis. Iveskite pazymi nuo 1 iki 10: ";
            }
        }

        cout << "Iveskite egzamino vertinima: ";
        while (!(cin >> A.egzo_rezas) || A.egzo_rezas < 0 || A.egzo_rezas > 10)
        {
            cout << "Netinkama ivestis. Iveskite pazymi tarp 1 ir 10: ";
            cin.clear();
            cin.ignore(MAX_INT, '\n');
        }

        // vidurkio apsk.
        if (iverciu_sk < min_iverciu_sk)
            A.rezas_vid = ((iverciu_suma * 1.0) / (min_iverciu_sk * 1.0)) * 0.4 + (A.egzo_rezas * 0.6);
        else
            A.rezas_vid = ((iverciu_suma * 1.0) / (iverciu_sk * 1.0)) * 0.4 + (A.egzo_rezas * 0.6);

        // medianos apsk.
        int *visi_pazymiai;
        // DAR REIKIA PATIKRINT AR ČIA TIKRAI VISKAS GERAI: JEIGU NE, TAI GAL PATS SKAIČIAVIMAS ARBA FOR LOOPAS KURIS; NES TESTAVIME ATRODĖ BŠK NUKRYPĘ
        if (iverciu_sk < min_iverciu_sk)
        {
            int visu_pazymiu_sk = min_iverciu_sk + 1;
            visi_pazymiai = new int[visu_pazymiu_sk];
            for (int i = 0; i < iverciu_sk; i++)
                visi_pazymiai[i] = A.pazymiai[i];
            for (int i = iverciu_sk; i < min_iverciu_sk; i++)
                visi_pazymiai[i] = 0;
            visi_pazymiai[min_iverciu_sk] = A.egzo_rezas;
            std::sort(visi_pazymiai, visi_pazymiai + min_iverciu_sk); // surikiuoja masyvą did. tvarka (nuo pirmo lig paskutinio elemento)
            if ((visu_pazymiu_sk) % 2 != 0)
                A.rezas_med = visi_pazymiai[visu_pazymiu_sk / 2];
            else
                A.rezas_med = (visi_pazymiai[(visu_pazymiu_sk / 2) - 1] + visi_pazymiai[visu_pazymiu_sk / 2]) / 2.0;
        }
        else
        {
            int visu_pazymiu_sk = iverciu_sk + 1;
            visi_pazymiai = new int[visu_pazymiu_sk]; // + 1 — nes reiks dar pridėt egzamino pažymį
            for (int i = 0; i < iverciu_sk; i++)
                visi_pazymiai[i] = A.pazymiai[i];
            visi_pazymiai[visu_pazymiu_sk - 1] = A.egzo_rezas;
            std::sort(visi_pazymiai, visi_pazymiai + visu_pazymiu_sk - 1); // surikiuoja masyvą did. tvarka (nuo pirmo lig paskutinio elemento)
            if ((visu_pazymiu_sk) % 2 != 0)
                A.rezas_med = visi_pazymiai[visu_pazymiu_sk / 2];
            else
                A.rezas_med = (visi_pazymiai[(visu_pazymiu_sk / 2) - 1] + visi_pazymiai[visu_pazymiu_sk / 2]) / 2.0;
        }

        /*
        vector<int> visi_pazymiai = A.pazymiai;
        visi_pazymiai.push_back(A.egzo_rezas);
        std::sort(visi_pazymiai.begin(), visi_pazymiai.end()); // sort(..) surikiuoja visi_pazymiai vektorių did. tvarka
        int visu_pazymiu_sk = visi_pazymiai.size();
        if (visu_pazymiu_sk % 2 != 0)
            A.rezas_med = visi_pazymiai[visu_pazymiu_sk / 2];
        else
            A.rezas_med = (visi_pazymiai[(visu_pazymiu_sk / 2) - 1] + visi_pazymiai[visu_pazymiu_sk / 2]) / 2.0;
        */
        grupe[studentu_sk] = A;
        studentu_sk++;

        delete[] visi_pazymiai;
        // A.pazymiai.clear(); // apsauga: isvalo pazymiu vektoriu, kad kitam kartojime vektorius butu tuscias
    }
}

void isvestis(Studentas *&grupe)
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
        for (int i = 0; i < studentu_sk; i++)
        {
            cout
                << left << setw(15) << grupe[i].vardas
                << left << setw(20) << grupe[i].pavarde
                << setw(10) << std::fixed << std::setprecision(2) << grupe[i].rezas_vid
                << endl;
        }
    }
    else if (galutinio_pasirinkimas == "m")
    {
        for (int i = 0; i < studentu_sk; i++)
        {
            cout
                << left << setw(15) << grupe[i].vardas
                << left << setw(20) << grupe[i].pavarde
                << setw(10) << std::fixed << std::setprecision(2) << grupe[i].rezas_med
                << endl;
        }
    }

    for (int i = 0; i < studentu_sk; i++)
    {
        delete[] grupe[i].pazymiai;
    }
}