#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "strukturos_konstantos.h"
#include "ivestis.h"
#include "isvestis.h"
#include "ivesties_pagalb_fjos.h"

int main()
{
    bool ar_failas_jau_apdorotas = false;
    for (;;)
    {
        srand(time(0)); // nustatom rand() seedą (visos programos pradžioj)

        int eiga;
        std::cout << '\n'
                  << "Pasirinkite, ka norite daryti:" << '\n'
                  << "1 - ivesti duomenis is failo" << '\n'
                  << "2 - ivesti duomenis ranka" << '\n'
                  << "3 - ivesti duomenis, pazymius sugeneruoti" << '\n'
                  << "4 - sugeneruoti galutinius duomenis" << '\n'
                  << "5 - sugeneruoti visus studentu duomenis" << '\n'
                  << "6 - baigti darba" << '\n';
        natur_skaiciaus_ivestis(eiga, ar_sk_nera_1_2_3_4_5_6);

        std::vector<Studentas> grupe;

        const std::string SK_FAILO_NUORODA = "ivesties_failai/";   // root dir atžvilgiu
        const std::string RAS_FAILO_NUORODA = "isvesties_failai/"; // root dir atžvilgiu
        // const std::string RAS_FAILO_PAV = "studentu_isvestis.txt";

        Programos_laikai t;

        switch (eiga)
        {
        case 1:
        {
            // atstatom/nustatom nulin laikus
            t.duomenu_apdorojimas = t.duomenu_rikiavimas = t.duomenu_isvedimas = std::chrono::milliseconds::zero();
            auto pati_pradzia = std::chrono::high_resolution_clock::now();
            failo_ivestis(SK_FAILO_NUORODA, grupe, t);
            isvestis(RAS_FAILO_NUORODA, grupe, t);
            auto pati_pab = std::chrono::high_resolution_clock::now();
            t.visa_trukme = pati_pab - pati_pradzia;

            t.spausd_laikus();
            break;
        }
        case 2:
        {
            rank_ivestis(grupe);
            isvestis(RAS_FAILO_NUORODA, grupe, t);
            break;
        }
        case 3:
        {
            misri_ivestis(grupe);
            isvestis(RAS_FAILO_NUORODA, grupe, t);
            break;
        }
        case 4:
        {
            generuota_ivestis(grupe);
            isvestis(RAS_FAILO_NUORODA, grupe, t);
            break;
        }
        case 5:
        {
            std::vector<StudentasBeGalutiniu> grupe;
            // auto pr = std::chrono::high_resolution_clock::now();
            visu_stud_duomenu_generavimo_ivestis(grupe);
            // auto pab = std::chrono::high_resolution_clock::now();
            // std::chrono::duration<double> iv = pab - pr;
            // pr = std::chrono::high_resolution_clock::now();
            visu_stud_duomenu_generavimo_isvestis(RAS_FAILO_NUORODA, grupe, t);
            // pab = std::chrono::high_resolution_clock::now();
            // std::chrono::duration<double> isv = pab - pr;
            // std::cout << "Ivesties laikas: " << iv.count() << '\n'
            //          << "Isvesties laikas: " << isv.count() << '\n';
            break;
        }
        case 6:
        {
            return 0;
            break;
        }
        }
    }
}
