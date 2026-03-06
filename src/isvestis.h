#pragma once

#include <string>
#include <vector>

#include "strukturos_konstantos.h"

void isvestis(std::string RAS_FAILO_NUORODA, std::vector<Studentas> &grupe, Programos_laikai &t);

void skirstoma_isvestis(std::string RAS_FAILO_NUORODA, std::vector<Studentas> &grupe, Programos_laikai &t);
std::chrono::duration<double> spausdinimas(std::string RAS_FAILO_NUORODA, std::string galutinio_pasirinkimas, std::vector<Studentas> &grupe);

void visu_stud_duomenu_generavimo_isvestis(std::string RAS_FAILO_NUORODA, std::vector<StudentasBeGalutiniu> &grupe, Programos_laikai &t);