#include "ivesties_pagalb_fjos.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

// įvesties (skaitymo) failo pavadinimo gavimo funkcija
std::ifstream skait_failo_pav_gavimas()
{
    std::cin.ignore(MAX_INT, '\n'); // ištrint įvestį iš buferio, jeigu iš ankstesnės įvesties kažkas jame liko (reikia, nes prieš tai cin naudojom)
    std::string skait_failo_pav;
    std::cout << "Iveskite ivesties failo pavadinima:\n";
    for (;;)
    {
        try
        {
            std::getline(std::cin, skait_failo_pav);
            std::ifstream sk_failas(skait_failo_pav); // sukuria įvesties srautą ir atidaro failą
            if (!sk_failas.is_open())
                throw std::runtime_error("Ivesties failas nurodytu pavadinimu nerastas.");
            break; // jeigu prieš tai bus išmesta klaida, šio kodo programa nepasieks
        }
        catch (const std::exception &e)
        {
            std::cerr << "Ivyko klaida: " << e.what() << '\n';
            std::cout << "Iveskite failo pavadinima is naujo: ";
        }
    }
    std::ifstream skait_failas(skait_failo_pav);
    return skait_failas;
}

// pagalbinės vartotojo įvesties programoj funkcijos

void natur_skaiciaus_ivestis(int &sk, bool (*papild_salygu_fja)(int)) // default reikšmė nullptr, jeigu papildomų sąlygų nustatymo funkcija nebus pateikta iškvietime
{
    std::string ivestis;

    while (std::getline(std::cin, ivestis))
    {
        std::istringstream sr(ivestis);
        if (sr >> ivestis)
        {
            try
            {
                std::string perteklius;
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
                std::cout << "Netinkama ivestis. Iveskite dar karta: ";
            }
        }
    }
}

// grąžina bool: jeigu false, tai po vardo/pavardės įvedimo nebebus tęsiamas apskritai studentų duomenų pildymas (reikia mišrios įvesties f-jai); jeigu true, tai atvirkščiai, nieks nesikeičia
bool vardo_pavardes_ivestis(Studentas &A, bool ar_ivestis_atsaukiama)
{
    std::cout << "Iveskite varda ir pavarde: ";
    for (;;)
    {
        std::string vardas_pavarde;
        if (std::getline(std::cin, vardas_pavarde)) // jeigu sėkmingai nuskaito eilutę, tai ...
        {
            if (vardas_pavarde.empty())
            {
                std::cout << "Tuscia ivestis. Iveskite dar karta: ";
                continue;
            }
            if (vardas_pavarde == "x" && ar_ivestis_atsaukiama) // sąlyga, reikalinga mišrios įvesties f-jai
            {
                return false;
            }
            std::istringstream sr(vardas_pavarde);
            std::string vardo_ivestis, pavardes_ivestis;
            std::string perteklius;
            if (sr >> vardo_ivestis >> pavardes_ivestis) // jeigu sėkmingai nuskaitytos dvi vertės - vardo ir pavardės - tai ...
            {
                if (sr >> perteklius) // jeigu ivesta per daug duomenu
                {
                    std::cout << "Pertekline ivestis. Iveskite dar karta: ";
                    continue;
                }
                A.vardas = vardo_ivestis;
                A.pavarde = pavardes_ivestis;
                break;
            }
            else
                std::cout << "Netinkama ivestis. Iveskite dar karta: ";
        }
        else
            std::cout << "Netinkama ivestis. Iveskite dar karta: ";
    }
    return true;
}

// pagalbinės įvesties sąlygų tikrinimo funkcijos

bool ar_sk_ne_tarp_0_ir_10(int x)
{
    return x < 0 || x > 10;
}

bool ar_sk_nedidesnis_uz_0(int x)
{
    return x <= 0;
}