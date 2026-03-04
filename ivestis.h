#pragma once

#include <string>
#include <vector>

#include "strukturos_konstantos.h"

void generuota_ivestis(std::vector<Studentas> &grupe);
void misri_ivestis(std::vector<Studentas> &grupe);
void rank_ivestis(std::vector<Studentas> &grupe);
void failo_ivestis(std::string SKAIT_FAILO_PAV, std::vector<Studentas> &grupe, Programos_laikai &t);