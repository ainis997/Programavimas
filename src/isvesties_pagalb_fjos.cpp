#include "strukturos_konstantos.h"

// ===== Studentu rikiavimo funkcijos =====

bool pagal_varda_did(Studentas &A, Studentas &B)
{
    return A.vardas < B.vardas;
}

bool pagal_varda_maz(Studentas &A, Studentas &B)
{
    return A.vardas > B.vardas;
}

bool pagal_pavarde_did(Studentas &A, Studentas &B)
{
    return A.pavarde < B.pavarde;
}

bool pagal_pavarde_maz(Studentas &A, Studentas &B)
{
    return A.pavarde > B.pavarde;
}

bool pagal_vidurki_did(Studentas &A, Studentas &B)
{
    return A.rezas_vid < B.rezas_vid;
}

bool pagal_vidurki_maz(Studentas &A, Studentas &B)
{
    return A.rezas_vid > B.rezas_vid;
}

bool pagal_mediana_did(Studentas &A, Studentas &B)
{
    return A.rezas_med < B.rezas_med;
}

bool pagal_mediana_maz(Studentas &A, Studentas &B)
{
    return A.rezas_med > B.rezas_med;
}