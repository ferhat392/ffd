#include <iostream>
#include "CalmaListesi.h"

int main() {
    CalmaListesi calmaListesi;
    int secim;
    do {
        std::cout << "1. Sarki Ekle" << std::endl;
        std::cout << "2. Sarkilari Goster" << std::endl;
        std::cout << "3. Calma Listesini Oynat" << std::endl;
        std::cout << "4. Favori Sarkilari Sec" << std::endl;
        std::cout << "5. Favori Sarkilari Listele (Stack)" << std::endl;
        std::cout << "6. Favori Sarkilari Listele (Queue)" << std::endl;
        std::cout << "7. Onerilen Sarkilari Goster" << std::endl;
        std::cout << "0. Cikis" << std::endl;
        std::cout << "Secim: ";
        std::cin >> secim;
        switch (secim) {
            case 1: {
                int no;
                std::string ad, sanatci;
                std::cout << "Sarki numarasi: ";
                std::cin >> no;
                std::cin.ignore();
                std::cout << "Sarki adi: ";
                std::getline(std::cin, ad);
                std::cout << "Sanatci: ";
                std::getline(std::cin, sanatci);
                calmaListesi.sarkiEkle(Sarki(no, ad, sanatci));
                break;
            }
            case 2:
                calmaListesi.sarkilariGoster();
                break;
            case 3:
                calmaListesi.calmaListesiniOynat();
                break;
            case 4:
                calmaListesi.favoriSarkilariSec();
                break;
            case 5:
                calmaListesi.favoriSarkilariListeleStack();
                break;
            case 6:
                calmaListesi.favoriSarkilariListeleQueue();
                break;
            case 7:
                calmaListesi.onerilenSarkilariGoster();
                break;
            default:
                break;
        }
    } while (secim != 0);

    return 0;
}