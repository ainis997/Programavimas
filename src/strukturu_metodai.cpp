#include <iostream>
#include <vector>
#include <algorithm>

#include "strukturos_konstantos.h"

void Studentas::apsk_vid()
{
    if (pazymiai.size() == 0)
        rezas_vid = egzo_rezas * 0.6;
    int pazymiu_suma = 0;
    for (auto paz : pazymiai)
        pazymiu_suma += paz;
    rezas_vid = ((pazymiu_suma * 1.0) / (pazymiai.size() * 1.0)) * 0.4 + (egzo_rezas * 0.6);
}

void Studentas::apsk_med()
{
    if (pazymiai.size() == 0)
        return;
    std::vector<int> visi_pazymiai = pazymiai;
    visi_pazymiai.push_back(egzo_rezas);
    std::sort(visi_pazymiai.begin(), visi_pazymiai.end()); // sort(..) surikiuoja visi_pazymiai vektorių did. tvarka
    int visu_pazymiu_sk = visi_pazymiai.size();
    if (visu_pazymiu_sk % 2 != 0)
        rezas_med = visi_pazymiai[visu_pazymiu_sk / 2];
    else
        rezas_med = (visi_pazymiai[(visu_pazymiu_sk / 2) - 1] + visi_pazymiai[visu_pazymiu_sk / 2]) / 2.0;
}

void Programos_laikai::spausd_laikus()
{
    std::cout << '\n'
              << "Failo duomenu apdorojimo trukme: " << duomenu_apdorojimas.count() << "s" << '\n'
              << "Failo duomenu surikiavimo trukme: " << duomenu_rikiavimas.count() << "s" << '\n'
              << "Failo duomenu isvedimo trukme: " << duomenu_isvedimas.count() << "s" << '\n'
              << "Visos programos trukme: " << visa_trukme.count() << "s" << '\n';
}