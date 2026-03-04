#pragma once

#include "strukturos_konstantos.h"

// pagalbinės vartotojo įvesties programoj funkcijos
bool vardo_pavardes_ivestis(Studentas &A, bool ar_ivestis_atsaukiama);
void natur_skaiciaus_ivestis(int &sk, bool (*papild_salygu_fja)(int) = nullptr);

// pagalbinės įvesties sąlygų tikrinimo funkcijos
bool ar_sk_nedidesnis_uz_0(int x);
bool ar_sk_ne_tarp_0_ir_10(int x);