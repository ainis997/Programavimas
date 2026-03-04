#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>  // maksimaliai int reikšmei gauti
#include <cstdlib> // atsitiktiniam skaičiam
#include <sstream> // std::string streamui
#include <chrono>  // laiko fiksavimui
#include <fstream> // failam

#include "ivestis.h"
#include "ivesties_pagalb_fjos.h"
#include "strukturos_konstantos.h"

void failo_ivestis(std::vector<Studentas> &grupe, Programos_laikai &t)
{
    std::ifstream sk_failas = skait_failo_pav_gavimas();

    auto pr = std::chrono::high_resolution_clock::now(); // matuojam nuo čia, nes skait_failo_pav_gavimas turi įvesties

    std::string sk_failo_eil;

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

void rank_ivestis(std::vector<Studentas> &grupe)
{
    int min_iverciu_sk;
    std::cout << "Iveskite, kiek studentai privalo tureti iverciu: ";
    natur_skaiciaus_ivestis(min_iverciu_sk, ar_sk_nedidesnis_uz_0);

    for (int i = 0;; i++)
    {
        if (i > 0)
        {
            std::string arDarVestiStudenta;
            std::string ivestis;
            std::cout << "Ar norite suvesti dar vieno studento duomenis?" << '\n'
                      << "t - taip, n - ne\n";
            for (;;)
            {
                std::getline(std::cin, ivestis);
                if (ivestis == "t" || ivestis == "n")
                {
                    arDarVestiStudenta = ivestis;
                    break;
                }
                std::cout << "Netinkama ivestis. Iveskite dar karta: ";
            }
            if (arDarVestiStudenta == "n")
                break;
        }

        Studentas A;

        bool ar_ivestis_atsaukiama = false;
        vardo_pavardes_ivestis(A, ar_ivestis_atsaukiama); // false reiškia, kad šioje įvestyje negalima atšaukti studentų duomenų pildymo apskritai

        std::cout << "Iveskite semestro ivercius: (kai suvesite visus semestro ivercius, iveskite 'x')" << '\n';
        // čia palikti std::cin, kad būtų lankstesnis įvedimas: gali ir enteriais, ir tarpais atskirt pažymius
        for (;;) // for loopas be parametrų — begalinis loopas (iš jo išeis tik jeigu vartotojas įves "x")
        {
            int pazymys;
            std::string ivercio_ivestis;
            std::cin >> ivercio_ivestis;
            if (ivercio_ivestis == "x")
                break;

            try
            {
                pazymys = std::stoi(ivercio_ivestis); // std::stoi funkcija paverčia std::string į int.
                if (pazymys < 0 || pazymys > 10)
                    throw "Netinkama ivestis"; // tuščio "throw;" negalima palikt, nes td tsg užlauš programą
                A.pazymiai.push_back(pazymys);
            }
            catch (...) // "..." argumentas sako, kad priimk bet kokią klaidą; šiuo catch bloku valdom dvi klaidas: std::string>int konvertavimo galimą klaidą IR netinkamą pažymio skaitinę vertę (ne tarp 1 ir 10)
            {
                std::cout << "Netinkama ivestis. Iveskite pazymi tarp 0 iki 10: ";
            }
        }

        std::cout << "Iveskite egzamino vertinima: ";
        natur_skaiciaus_ivestis(A.egzo_rezas, ar_sk_ne_tarp_0_ir_10);
        // while (!(std::cin >> A.egzo_rezas) || A.egzo_rezas < 0 || A.egzo_rezas > 10)
        // {
        //     std::cout << "Netinkama ivestis. Iveskite pazymi tarp 0 ir 10: ";
        //     std::cin.clear();
        //     std::cin.ignore(MAX_INT, '\n');
        // }
        // std::cin.ignore(MAX_INT, '\n'); // SKIRTA TAM, jeigu būtų įvestas float skaičius: ši komanda ištrins bufery likusią pokablelinę dalį (jinai lieka, kadangi programa pasiima tik sveikąją dalį iš įvesties). To reikia todėl, nes ta likusi bufery dalis po to tampa sekančios įvesties dalim (o to mum nereik)

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

void misri_ivestis(std::vector<Studentas> &grupe)
{
    int min_iverciu_sk = 0;
    std::string ivestis3;
    std::cout << "Iveskite, kiek studentai privalo tureti iverciu: ";
    natur_skaiciaus_ivestis(min_iverciu_sk, nullptr); // perduodam kintamojo *referencą*

    std::cout << "Įveskite studentų duomenis. Kai įvesite visus studentus, įveskite 'x'." << '\n';

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

void generuota_ivestis(std::vector<Studentas> &grupe)
{
    int min_iverciu_sk = 0;
    std::string ivestis1;
    std::cout << "Iveskite, kiek studentai privalo tureti iverciu: ";
    natur_skaiciaus_ivestis(min_iverciu_sk, ar_sk_nedidesnis_uz_0); // perduodam kintamojo *referencą*

    int reikiamas_studentu_sk = 0;
    std::string ivestis2;
    std::cout << "Iveskite, kiek norite sugeneruoti studentu: ";
    natur_skaiciaus_ivestis(reikiamas_studentu_sk, ar_sk_nedidesnis_uz_0); // perduodam kintamojo *referencą*

    // vardų generavimui
    std::vector<std::string> vardai = {"Jonas", "Lina", "Lukas", "Egle", "Marius", "Migle", "Azuolas", "Aiste", "Tomas", "Ieva", "Mindaugas", "Austeja", "Vytautas", "Saule", "Rimvydas", "Gabija", "Povilas", "Lukne", "Audrius", "Ugne"};
    std::vector<std::string> vyr_pavardes = {"Butkus", "Zemaitis", "Rimkus", "Simkus", "Mazeika", "Petraitis", "Braziunas", "Sukys", "Simonis", "Bareikis"};
    std::vector<std::string> mot_pavardes = {"Butkute", "Zemaityte", "Rimkute", "Simkute", "Mazeikaite", "Petraityte", "Braziunaite", "Sukyte", "Simonyte", "Bareikyte"};

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