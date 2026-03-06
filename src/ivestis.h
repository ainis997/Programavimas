#pragma once

#include <string>
#include <vector>

#include "strukturos_konstantos.h"

void failo_ivestis(std::string SK_FAILO_NUORODA, std::vector<Studentas> &grupe, Programos_laikai &t);
void rank_ivestis(std::vector<Studentas> &grupe);
void misri_ivestis(std::vector<Studentas> &grupe);
void generuota_ivestis(std::vector<Studentas> &grupe);
void visu_stud_duomenu_generavimo_ivestis(std::vector<StudentasBeGalutiniu> &grupe);
// void generuota_skirstoma_pazymiu_ivestis(std::vector<Studentas> &geri, std::vector<Studentas> &blogi);