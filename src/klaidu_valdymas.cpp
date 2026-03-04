#include <iostream>

#include "klaidu_valdymas.h"

// wīrst boūwuns mazīngi panzdau powalnint šin pūnkcijan, preikalsīt wisēimans prēipalimans (preidāt tolimesne_zinute paramētran)
void ivesties_klaidos_valdymas()
{
    try
    {
        throw; // permetam klaidą vėl, kad fjoj galėtumbim apdorot
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Klaida: Netinkama ivestis." << '\n';
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Klaida: Netinkamo intervalo ivestis ivestis." << '\n';
    }
    catch (const std::exception &e) // "..." argumentas sako, kad priimk bet kokią klaidą; šiuo catch bloku valdom dvi klaidas: std::string>int konvertavimo galimą klaidą IR netinkamą pažymio skaitinę vertę (ne tarp 1 ir 10)
    {
        std::cerr << "Klaida: " << e.what() << '\n';
    }
    catch (...)
    {
        std::cerr << "Ivyko nezinoma klaida." << '\n';
    }
    std::cout << "Iveskite dar karta: ";
}