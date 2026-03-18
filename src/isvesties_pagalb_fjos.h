#include <algorithm>

#include "strukturos_konstantos.h"

std::ofstream ras_failo_paruosimas(std::string RAS_FAILO_NUORODA);

void stud_rikiavimas(Container<Studentas> &grupe, bool (*rikiavimo_taisykle)(Studentas &, Studentas &));

// APRAŠAS PERKELTAS ČIA, NES TEMPLATE FUNKCIJA (.cpp failan įdėjus — neveikia)
// be nurodytos specif taisyklės, bet kokiam tipui
template <typename T>
void rikiavimas(Container<T> &konteineris)
{
    // LIST
    konteineris.sort();

    // VECTOR / DEQUE
    // std::sort(konteineris.begin(), konteineris.end());
}

bool pagal_varda_did(Studentas &A, Studentas &B);
bool pagal_varda_maz(Studentas &A, Studentas &B);
bool pagal_pavarde_did(Studentas &A, Studentas &B);
bool pagal_pavarde_maz(Studentas &A, Studentas &B);
bool pagal_vidurki_did(Studentas &A, Studentas &B);
bool pagal_vidurki_maz(Studentas &A, Studentas &B);
bool pagal_mediana_did(Studentas &A, Studentas &B);
bool pagal_mediana_maz(Studentas &A, Studentas &B);