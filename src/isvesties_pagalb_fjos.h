#include "strukturos_konstantos.h"

std::ofstream ras_failo_paruosimas(std::string RAS_FAILO_NUORODA);

void stud_rikiavimas(Container<Studentas> &grupe, bool (*rikiavimo_taisykle)(Studentas &, Studentas &));
template <typename T>
void rikiavimas(Container<T> &grupe);

bool pagal_varda_did(Studentas &A, Studentas &B);
bool pagal_varda_maz(Studentas &A, Studentas &B);
bool pagal_pavarde_did(Studentas &A, Studentas &B);
bool pagal_pavarde_maz(Studentas &A, Studentas &B);
bool pagal_vidurki_did(Studentas &A, Studentas &B);
bool pagal_vidurki_maz(Studentas &A, Studentas &B);
bool pagal_mediana_did(Studentas &A, Studentas &B);
bool pagal_mediana_maz(Studentas &A, Studentas &B);