#include "ivesties_pagalb_fjos.h"
#include "klaidu_valdymas.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

// įvesties (skaitymo) failo pavadinimo gavimo funkcija
std::ifstream skait_failo_pav_gavimas()
{
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
        catch (...)
        {
            ivesties_klaidos_valdymas();
        }
    }
    std::ifstream skait_failas(skait_failo_pav);
    return skait_failas;
}

// pagalbinės vartotojo įvesties programoj funkcijos

// papild_salygu_netenkinimo_fja turi tikrinti, ar fja NEtenkina salygos
bool natur_skaiciaus_ivestis(int &sk, bool (*papild_salygu_netenkinimo_fja)(int), bool ar_ivestis_atsaukiama) // default reikšmė nullptr, jeigu papildomų sąlygų nustatymo funkcija nebus pateikta iškvietime
{
    for (;;)
    {
        try
        {
            std::string ivestis;

            if (!std::getline(std::cin, ivestis))
                throw std::invalid_argument("Ivesties srauto klaida.");

            if (ivestis.empty())
                throw std::invalid_argument("Tuscia ivestis.");

            if (ivestis == "x" && ar_ivestis_atsaukiama)
                return false;

            std::istringstream sr(ivestis);
            int temp_sk; // laikinas kintamasis
            std::string perteklius;

            if (!(sr >> temp_sk))
                throw std::invalid_argument("Netinkama ivestis.");

            if (sr >> perteklius)
                throw std::invalid_argument("Pertekline ivestis.");

            if (temp_sk <= 0 || (papild_salygu_netenkinimo_fja != nullptr && papild_salygu_netenkinimo_fja(temp_sk))) // jeigu <=0, arba: jeigu yra sąlygos funkcija, ir jeigu netenkina įvesties skaičiaus tikrinimo sąlygos (pvz., yra <0 ar >10 (tuo atveju meta true!)), tai mesti errorą
                throw std::domain_error("Netinkama ivestis.");

            sk = temp_sk; // pagaliau priskiriam skaičiui vertę
            break;

            // std::string ivestis;
            // if (std::getline(std::cin, ivestis))
            // {
            //     std::istringstream sr(ivestis);
            //     if (sr >> ivestis)
            //     {
            //         std::string perteklius;
            //         if (sr >> perteklius) // programa nelūštų be šito (tsg paima pirmą elementą), bet tai tsg aiškumui
            //             throw std::invalid_argument("Pertekline ivestis.");
            //         size_t perskaitytu_simboliu_sk;
            //         sk = std::stoi(ivestis, &perskaitytu_simboliu_sk); // 2-as parametras: tam, kad stoi galėtų kintamajan (pro rodyklę) įrašyt perskaitytų simbolių skaičių
            //         if (perskaitytu_simboliu_sk != ivestis.length())   // tam, jeigu ivestu pvz. "7t" (pats std::stoi nesugaudo tokių!)
            //             throw std::invalid_argument("Netinkama ivestis.");
            //         if (sk <= 0)
            //             throw std::domain_error("Netinkama ivestis.");
            //         if (papild_salygu_netenkinimo_fja != nullptr)
            //             if (papild_salygu_netenkinimo_fja(sk)) // jeigu netenkina įvesties skaičiaus tikrinimo sąlygos (pvz., yra <0 ar >10 (tuo atveju meta true!)), tai mesti errorą
            //                 throw std::domain_error("Netinkama ivestis.");
            //         break; // jeigu viršuj buvo errorų, šio kodo nepasieks; jeigu nebuvo - pasieks
            //     }
            //     else
            //         throw std::invalid_argument("Neaptikta ivestis.");
            // }
            // else
            //     throw std::invalid_argument("Neaptikta ivestis.");
        }
        catch (...)
        {
            ivesties_klaidos_valdymas();
        }
    }
    return true;
}

// grąžina bool: jeigu false, tai po vardo/pavardės įvedimo nebebus tęsiamas apskritai studentų duomenų pildymas (reikia mišrios įvesties f-jai); jeigu true, tai atvirkščiai, nieks nesikeičia
bool vardo_pavardes_ivestis(Studentas &A, bool ar_ivestis_atsaukiama)
{
    std::cout << "Iveskite varda ir pavarde: ";
    for (;;)
    {
        try
        {
            std::string vardas_pavarde;
            if (std::getline(std::cin, vardas_pavarde)) // jeigu sėkmingai nuskaito eilutę, tai ...
            {
                if (vardas_pavarde.empty())
                {
                    throw std::invalid_argument("Tuscia ivestis.");
                }
                if (vardas_pavarde == "x" && ar_ivestis_atsaukiama) // sąlyga, reikalinga mišrios įvesties f-jai (kad nutraukt studentų įvedimą)
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
                        throw std::invalid_argument("Pertekline ivestis.");
                    }
                    A.vardas = vardo_ivestis;
                    A.pavarde = pavardes_ivestis;
                    break;
                }
                else
                    throw std::invalid_argument("Netinkama ivestis.");
            }
            else
                throw std::invalid_argument("Netinkama ivestis.");
        }
        catch (...)
        {
            ivesties_klaidos_valdymas();
        }
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

bool ar_sk_nera_1_2_3_4_5(int x)
{
    return x != 1 && x != 2 && x != 3 && x != 4 && x != 5;
}