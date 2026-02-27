#include "pagalbines_fjos.h"

// ===== Studentu rikiavimo funkcijos =====

bool pagal_varda_did(Studentas &A, Studentas &B)
{
    // for (char &raide : A.vardas)
    //     raide = std::tolower(raide);
    // for (char &raide : B.vardas)
    //     raide = std::tolower(raide);
    return A.vardas < B.vardas;
}

bool pagal_varda_maz(Studentas &A, Studentas &B)
{
    // for (char &raide : A.vardas)
    //     raide = std::tolower(raide);
    // for (char &raide : B.vardas)
    //     raide = std::tolower(raide);
    return A.vardas > B.vardas;
}

bool pagal_pavarde_did(Studentas &A, Studentas &B)
{
    // for (char &raide : A.pavarde)
    //     raide = std::tolower(raide);
    // for (char &raide : B.pavarde)
    //     raide = std::tolower(raide);
    return A.pavarde < B.pavarde;
}

bool pagal_pavarde_maz(Studentas &A, Studentas &B)
{
    // for (char &raide : A.pavarde)
    //     raide = std::tolower(raide);
    // for (char &raide : B.pavarde)
    //     raide = std::tolower(raide);
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

// ===== =====

bool ar_sk_ne_tarp_0_ir_10(int x)
{
    return x < 0 || x > 10;
}

bool ar_sk_nedidesnis_uz_0(int x)
{
    return x <= 0;
}