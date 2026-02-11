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
    int masyvo_dydis = 10;
    int *pazymiai = new int[masyvo_dydis];
    int egzo_rezas;
    double rezas_vid;
    double rezas_med;
};

void ivestis(vector<Studentas> &grupe);
void isvestis(vector<Studentas> &grupe);

int main()
{
    // realiai vos ne visas main turinys turės būti begaliniam loope (jis baigsis tik vartotojui paliepus)

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
    }
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
                if (pazymys < 1 || pazymys > 10)
                    throw "Netinkama ivestis"; // tuščio "throw;" negalima palikt, nes td tsg užlauš programą
                A.pazymiai[iverciu_sk] = pazymys;
                iverciu_suma += pazymys;
                iverciu_sk++;

                // MASYVO PADIDINIMAS (jeigu pasiekiama esama masyvo dydžio riba)
                if (iverciu_sk == A.masyvo_dydis)
                {
                    int *naujo_masyvo_rod = new int[A.masyvo_dydis * 2]; // paskiriam naują, 2kart didesnę dinam. atmintį masyvui
                    for (int i = 0; i < A.masyvo_dydis; i++)
                    {
                        naujo_masyvo_rod[i] = A.pazymiai[i]; // perkeliam seno masyvo elementus naujon vieton
                    }
                    A.masyvo_dydis *= 2;           // padidinam masyvo_dydis nario vertę (kadangi padidės masyvas)
                    delete[] A.pazymiai;           // nuo masyvo rodyklės atlaisvinam senąją (mažesnę) masyvo atmintį
                    A.pazymiai = naujo_masyvo_rod; // masyvo rodyklei priskiriam naują (didesnės atminties) rodyklę
                }
            }
            catch (...) // "..." argumentas sako, kad priimk bet kokią klaidą; šiuo catch bloku valdom dvi klaidas: string>int konvertavimo galimą klaidą IR netinkamą pažymio skaitinę vertę (ne tarp 1 ir 10)
            {
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
        if (iverciu_sk == 0)
            A.rezas_vid = A.egzo_rezas * 0.6;
        else
            A.rezas_vid = (iverciu_suma * 1.0) / (iverciu_sk * 1.0) * 0.4 + (A.egzo_rezas * 0.6);

        // medianos apsk.
        int visu_pazymiu_sk = iverciu_sk + 1;
        int *visi_pazymiai = new int[visu_pazymiu_sk]; // + 1 — nes reiks dar pridėt egzamino pažymį
        for (int i = 0; i < iverciu_sk; i++)
        {
            visi_pazymiai[i] = A.pazymiai[i];
        }
        visi_pazymiai[visu_pazymiu_sk - 1] = A.egzo_rezas;
        std::sort(visi_pazymiai, visi_pazymiai + visu_pazymiu_sk - 1); // surikiuoja masyvą did. tvarka (nuo pirmo lig paskutinio elemento)
        if ((iverciu_sk + 1) % 2 != 0)
            A.rezas_med = visi_pazymiai[visu_pazymiu_sk / 2];
        else
            A.rezas_med = (visi_pazymiai[(visu_pazymiu_sk / 2) - 1] + visi_pazymiai[visu_pazymiu_sk / 2]) / 2.0;
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
        grupe.push_back(A);
        // A.pazymiai.clear(); // apsauga: isvalo pazymiu vektoriu, kad kitam kartojime vektorius butu tuscias
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