#include "isvestis.h"
#include "isvesties_pagalb_fjos.h"
#include "strukturos_konstantos.h"
#include "klaidu_valdymas.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>

void isvestis(std::string RAS_FAILO_NUORODA, std::vector<Studentas> &grupe, Programos_laikai &t)
{
    if (grupe.empty())
        return;

    std::string galutinio_pasirinkimas;
    std::cout << "Ar norite rasti galutini vidurki ar galutine mediana?" << '\n'
              << "Jeigu vidurki, iveskite 'v'. Jeigu mediana, iveskite 'm'. " << '\n';
    for (;;)
    {
        try
        {
            std::string ivestis;
            std::getline(std::cin, ivestis);
            if (ivestis == "v" || ivestis == "m")
            {
                galutinio_pasirinkimas = ivestis;
                break;
            }
            throw std::invalid_argument("Ivestas netinkamas atsakymas (galimi atsakymai: v, m).");
        }
        catch (...)
        {
            ivesties_klaidos_valdymas();
        }
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
    for (;;)
    {
        try
        {
            std::string ivestis;
            std::getline(std::cin, ivestis);
            if (ivestis == "vard" || ivestis == "pav" || ivestis == "vid" || ivestis == "med" || ivestis == "ne")
            {
                rus = ivestis;
                break;
            }
            throw std::invalid_argument("Ivestas netinkamas atsakymas (galimi atsakymai: vard, pav, vid, med, ne).");
        }
        catch (...)
        {
            ivesties_klaidos_valdymas();
        }
    }

    if (rus != "ne")
    {
        std::string tvarka;
        std::cout << "Pasirinkite studentu rusiavimo tvarka:" << '\n'
                  << "'d' - didejimo tvarka" << '\n'
                  << "'m' - mazejimo tvarka" << '\n';
        for (;;)
        {
            try
            {
                std::string ivestis;
                std::getline(std::cin, ivestis);
                if (ivestis == "d" || ivestis == "m")
                {
                    tvarka = ivestis;
                    break;
                }
                throw std::invalid_argument("Ivestas netinkamas atsakymas (galimi atsakymai: d, m).");
            }
            catch (...)
            {
                ivesties_klaidos_valdymas();
            }
        }

        auto pr = std::chrono::high_resolution_clock::now();

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

        auto pab = std::chrono::high_resolution_clock::now();
        t.duomenu_rikiavimas = pab - pr;
    }

    auto pr = std::chrono::high_resolution_clock::now();

    std::ofstream ras_failas = ras_failo_paruosimas(RAS_FAILO_NUORODA);
    // std::ofstream ras_failas(RAS_FAILO_NUORODA + RAS_FAILO_PAV);

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

    auto pab = std::chrono::high_resolution_clock::now();
    // t.duomenu_isvedimas = pab - pr;

    std::cout << '\n'
              << "Isvedimas baigtas."
              << '\n';
}

// ==========================================

void visu_stud_duomenu_generavimo_isvestis(std::string RAS_FAILO_NUORODA, std::vector<StudentasBeGalutiniu> &grupe, Programos_laikai &t)
{
    if (grupe.empty())
        return;

    auto pr = std::chrono::high_resolution_clock::now();

    std::ofstream ras_failas = ras_failo_paruosimas(RAS_FAILO_NUORODA);
    // std::ofstream ras_failas(RAS_FAILO_NUORODA + RAS_FAILO_PAV);

    if (!ras_failas.is_open())
    {
        // MEST AR PARODYT ERRORĄ, GAL IR SU TEMPLATE KLAIDŲ VALDYMO F-JA
        std::cout << "Nepavyko atidaryti isvesties failo." << '\n';
        return;
    }

    ras_failas
        << std::left << std::setw(20) << "Vardas"
        << std::left << std::setw(25) << "Pavarde";

    for (int i = 0; i < grupe.at(0).pazymiai.size(); i++) // kiek pažymių bus pirmame masyve, tai tiek turi būti ir visuose kituose! (pagal dab. įvesties funkcijos įgyvendinimą)
        ras_failas << std::left << std::setw(15) << "ND" + std::to_string(i + 1);
    ras_failas << std::left << std::setw(20) << "Egz." << '\n';

    for (const auto &A : grupe)
    {
        ras_failas
            << std::left << std::setw(20) << A.vardas
            << std::left << std::setw(25) << A.pavarde;
        for (const int &paz : A.pazymiai)
            ras_failas << std::left << std::setw(15) << paz;
        ras_failas << std::left << std::setw(20) << A.egzo_rezas << '\n';
    }

    ras_failas.close();

    auto pab = std::chrono::high_resolution_clock::now();
    // t.duomenu_isvedimas = pab - pr;

    std::cout << '\n'
              << "Isvedimas baigtas."
              << '\n';
}

// =====================================

void skirstoma_isvestis(std::string RAS_FAILO_NUORODA, std::vector<Studentas> &grupe, Programos_laikai &t)
{
    if (grupe.empty())
        return;

    std::string galutinio_pasirinkimas;
    std::cout << "Ar norite rasti galutini vidurki ar galutine mediana?" << '\n'
              << "Jeigu vidurki, iveskite 'v'. Jeigu mediana, iveskite 'm'. " << '\n';
    for (;;)
    {
        try
        {
            std::string ivestis;
            std::getline(std::cin, ivestis);
            if (ivestis == "v" || ivestis == "m")
            {
                galutinio_pasirinkimas = ivestis;
                break;
            }
            throw std::invalid_argument("Ivestas netinkamas atsakymas (galimi atsakymai: v, m).");
        }
        catch (...)
        {
            ivesties_klaidos_valdymas();
        }
    }

    std::string rus; // rus - rūšiavimo būdas
    std::cout << "Pasirinkite studentu rusiavimo buda:" << '\n'
              << "'vard' - pagal varda" << '\n'
              << "'pav' - pagal pavarde" << '\n'
              << "'vid' - pagal vidurki" << '\n'
              << "'med' - pagal mediana" << '\n'
              << "'ne' - nerusiuoti" << '\n';
    for (;;)
    {
        try
        {
            std::string ivestis;
            std::getline(std::cin, ivestis);
            if (ivestis == "vard" || ivestis == "pav" || ivestis == "vid" || ivestis == "med" || ivestis == "ne")
            {
                rus = ivestis;
                break;
            }
            throw std::invalid_argument("Ivestas netinkamas atsakymas (galimi atsakymai: vard, pav, vid, med, ne).");
        }
        catch (...)
        {
            ivesties_klaidos_valdymas();
        }
    }

    if (rus != "ne")
    {
        std::string tvarka;
        std::cout << "Pasirinkite studentu rusiavimo tvarka:" << '\n'
                  << "'d' - didejimo tvarka" << '\n'
                  << "'m' - mazejimo tvarka" << '\n';
        for (;;)
        {
            try
            {
                std::string ivestis;
                std::getline(std::cin, ivestis);
                if (ivestis == "d" || ivestis == "m")
                {
                    tvarka = ivestis;
                    break;
                }
                throw std::invalid_argument("Ivestas netinkamas atsakymas (galimi atsakymai: d, m).");
            }
            catch (...)
            {
                ivesties_klaidos_valdymas();
            }
        }

        auto pr = std::chrono::high_resolution_clock::now();

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

        auto pab = std::chrono::high_resolution_clock::now();
        t.duomenu_rikiavimas = pab - pr;
    }

    // STUDENTŲ SKIRSTYMAS
    auto pr = std::chrono::high_resolution_clock::now();

    std::vector<Studentas> geri;
    std::vector<Studentas> blogi;

    if (galutinio_pasirinkimas == "v")
    {
        for (const auto &stud : grupe)
        {
            if (stud.rezas_vid >= 5.0)
                geri.push_back(stud);
            else
                blogi.push_back(stud);
        }
    }
    else if (galutinio_pasirinkimas == "m")
    {
        for (const auto &stud : grupe)
        {
            if (stud.rezas_med >= 5.0)
                geri.push_back(stud);
            else
                blogi.push_back(stud);
        }
    }

    auto pab = std::chrono::high_resolution_clock::now();
    t.studentu_skirstymas = pab - pr;

    std::cout << "Geru studentu isvedimas:\n";
    t.geru_isvedimas = spausdinimas(RAS_FAILO_NUORODA, galutinio_pasirinkimas, geri); // išspausdina ir td grąžina mum spausdinimo trukmę (be vartotojo įvesčių)

    std::cout << "Blogu studentu isvedimas:\n";
    t.blogu_isvedimas = spausdinimas(RAS_FAILO_NUORODA, galutinio_pasirinkimas, blogi);

    std::cout << '\n'
              << "Isvedimas baigtas."
              << '\n';
}

std::chrono::duration<double> spausdinimas(std::string RAS_FAILO_NUORODA, std::string galutinio_pasirinkimas, std::vector<Studentas> &grupe)
{
    std::ofstream ras_failas = ras_failo_paruosimas(RAS_FAILO_NUORODA);
    // std::ofstream ras_failas(RAS_FAILO_NUORODA + RAS_FAILO_PAV);

    if (!ras_failas.is_open())
    {
        // MEST AR PARODYT ERRORĄ, GAL IR SU TEMPLATE KLAIDŲ VALDYMO F-JA
        std::cout << "Nepavyko atidaryti isvesties failo." << '\n';
        return std::chrono::milliseconds::zero();
    }

    auto pr = std::chrono::high_resolution_clock::now();

    // dinamiškam lentelės stulpelių pavadinimų pavaizdavimui
    std::string pasirinktas_galutinis;
    if (galutinio_pasirinkimas == "v")
        pasirinktas_galutinis = "Galutinis (Vid.)";

    else if (galutinio_pasirinkimas == "m")
        pasirinktas_galutinis = "Galutinis (Med.)";

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

    auto pab = std::chrono::high_resolution_clock::now();

    ras_failas.close();

    std::chrono::duration<double> isvedimo_trukme = pab - pr;

    return isvedimo_trukme;
}