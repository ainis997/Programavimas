#pragma once

#include <string>
#include <vector>

#include "strukturos_konstantos.h"

void generuota_ivestis(std::vector<Studentas> &grupe);
void misri_ivestis(std::vector<Studentas> &grupe);
void rank_ivestis(std::vector<Studentas> &grupe);
void failo_ivestis(std::string SKAIT_FAILO_PAV, std::vector<Studentas> &grupe, Programos_laikai &t);

bool vardo_pavardes_ivestis(Studentas &A, bool ar_ivestis_atsaukiama);
void natur_skaiciaus_ivestis(int &sk, bool (*papild_salygu_fja)(int) = nullptr);

void isvestis(std::string RAS_FAILO_PAV, std::vector<Studentas> &grupe, Programos_laikai &t);