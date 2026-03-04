#include "isvestis.h"
#include "isvesties_pagalb_fjos.h"
#include "strukturos_konstantos.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>

void isvestis(std::string RAS_FAILO_PAV, std::vector<Studentas> &grupe, Programos_laikai &t)
{
    if (grupe.empty())
        return;

    std::string galutinio_pasirinkimas;
    bool ar_ivestas_tinkamas_galutinio_tipas = false;
    while (ar_ivestas_tinkamas_galutinio_tipas == false)
    {
        std::cout << "Ar norite rasti galutini vidurki ar galutine mediana?" << '\n'
                  << "Jeigu vidurki, iveskite 'v'. Jeigu mediana, iveskite 'm'. " << '\n';
        std::cin >> galutinio_pasirinkimas;
        if (galutinio_pasirinkimas == "v" || galutinio_pasirinkimas == "m")
            ar_ivestas_tinkamas_galutinio_tipas = true;
    }

    // dinamiškam lentelės stulpelių pavadinimų pavaizdavimui
    std::string pasirinktas_galutinis;
    if (galutinio_pasirinkimas == "v")
        pasirinktas_galutinis = "Galutinis (Vid.)";

    else if (galutinio_pasirinkimas == "m")
        pasirinktas_galutinis = "Galutinis (Med.)";

    std::string rus; // rus - rūšiavimo būdas
    std::cout << "Pasirinkite studentu rusiavimo buda:" << '\n'
              << "'vard' - pagal varda" << '\n'
              << "'pav' - pagal pavarde" << '\n'
              << "'vid' - pagal vidurki" << '\n'
              << "'med' - pagal mediana" << '\n'
              << "'ne' - nerusiuoti" << '\n';
    // bool tinkama_rus_ivestis = rus == "vard" || rus == "pav" || rus == "vid" || rus == "med" || rus == "ne";
    for (;;)
    {
        std::cin >> rus;
        if (rus == "vard" || rus == "pav" || rus == "vid" || rus == "med" || rus == "ne")
            break;
        std::cout << "Netinkama ivestis. Galimos ivesti reiksmes: 'vard', 'pav', 'vid', 'med', 'ne': ";
    }

    auto pr = std::chrono::high_resolution_clock::now();
    if (rus != "ne")
    {
        std::string tvarka;
        std::cout << "Pasirinkite studentu rusiavimo tvarka:" << '\n'
                  << "'d' - didejimo tvarka" << '\n'
                  << "'m' - mazejimo tvarka" << '\n';
        for (;;)
        {
            std::cin >> tvarka;
            if (tvarka == "d" || tvarka == "m")
                break;
            std::cout << "Netinkama ivestis. Galimos ivesti reiksmes: 'd', 'm': ";
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
        std::cout << "Nepavyko atidaryti isvesties failo." << '\n';
        return;
    }

    ras_failas
        << std::left << std::setw(20) << "Vardas"
        << std::left << std::setw(25) << "Pavarde"
        << std::left << std::setw(15) << pasirinktas_galutinis
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
                << std::left << std::setw(20) << A.vardas
                << std::left << std::setw(25) << A.pavarde
                << std::setw(15) << std::fixed << std::setprecision(2) << A.rezas_vid
                << '\n';
        }
    }
    else if (galutinio_pasirinkimas == "m")
    {
        for (const auto &A : grupe)
        {
            ras_failas
                << std::left << std::setw(20) << A.vardas
                << std::left << std::setw(25) << A.pavarde
                << std::setw(15) << std::fixed << std::setprecision(2) << A.rezas_med
                << '\n';
        }
    }
    ras_failas.close();

    pab = std::chrono::high_resolution_clock::now();
    t.duomenu_isvedimas = pab - pr;
}