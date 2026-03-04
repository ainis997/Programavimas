#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "strukturos_konstantos.h"
#include "ivestis.h"
#include "isvestis.h"

// using std::std::cin;
// using std::std::cout;
// using std::left;
// using std::right;
// using std::std::string;
// using std::std::vector;

std::string skait_failo_pav_gavimas() {
    std::string SKAIT_FAILO_PAV;
    std::cout << "Iveskite ivesties failo pavadinima:\n";
    for (;;) {
        try {
            std::cin.ignore(MAX_INT, '\n'); // ištrint įvestį iš buferio, jeigu iš ankstesnės įvesties kažkas jame liko
            std::getline(std::cin, SKAIT_FAILO_PAV);
            std::ifstream sk_failas(SKAIT_FAILO_PAV); // sukuria įvesties srautą ir atidaro failą
            if (!sk_failas.is_open())
                throw "Ivesties failas nurodytu pavadinimu nerastas.";
            break;
        }
        catch (std::exception &e) {
            std::cerr << e << '\n';
            std::cout << "Iveskite failo pavadinima is naujo: ";
    }
    return SKAIT_FAILO_PAV;
            
}

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
                  << "4 - sugeneruoti duomenis" << '\n'
                  << "5 - baigti darba" << '\n';
        while (!(std::cin >> eiga) || (eiga != 1 && eiga != 2 && eiga != 3 && eiga != 4 && eiga != 5))
        {
            std::cout << "Pasirinkite, ka norite daryti [1/2/3/4/5]: ";
            std::cin.clear();
            std::cin.ignore(MAX_INT, '\n');
        }

        std::vector<Studentas> grupe;

        const std::string RAS_FAILO_PAV = "studentu_isvestis.txt";

        Programos_laikai t;

        switch (eiga)
        {
        case 1:
        {
            // atstatom/nustatom nulin laikus
            t.duomenu_apdorojimas = t.duomenu_rikiavimas = t.duomenu_isvedimas = std::chrono::milliseconds::zero();

            // std::string SKAIT_FAILO_PAV;
            // std::cout << "Iveskite ivesties failo pavadinima:\n";
            //std::cin.ignore(MAX_INT, '\n'); // ištrint įvestį iš buferio, jeigu iš ankstesnės įvesties kažkas jame liko
            // std::getline(std::cin, SKAIT_FAILO_PAV);
            std::string SKAIT_FAILO_PAV = skait_failo_pav_gavimas();
            auto pati_pradzia = std::chrono::high_resolution_clock::now();
            failo_ivestis(SKAIT_FAILO_PAV, grupe, t);
            isvestis(RAS_FAILO_PAV, grupe, t);
            auto pati_pab = std::chrono::high_resolution_clock::now();
            t.visa_trukme = pati_pab - pati_pradzia;

            t.spausd_laikus();
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
