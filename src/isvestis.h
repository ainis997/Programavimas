#pragma once

#include <string>
#include <vector>

#include "strukturos_konstantos.h"

void isvestis(std::string RAS_FAILO_NUORODA, std::string RAS_FAILO_PAV, std::vector<Studentas> &grupe, Programos_laikai &t);
void visu_stud_duomenu_generavimo_isvestis(std::string RAS_FAILO_NUORODA, std::string RAS_FAILO_PAV, std::vector<StudentasBeGalutiniu> &grupe, Programos_laikai &t);