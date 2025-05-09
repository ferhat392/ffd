#include "CalmaListesi.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

bool CalmaListesi::secilenler[100] = {false};

CalmaListesi::CalmaListesi() : capacity(10), size(0) {
    sarkilar = new Sarki[capacity];
    dinlenmeSuresi = new int[capacity];
    dinlenmeSayisi = new int[capacity];
    favoriSarkilar = new std::pair<Sarki, int>[capacity];
}

CalmaListesi::~CalmaListesi() {
    delete[] sarkilar;
    delete[] dinlenmeSuresi;
    delete[] dinlenmeSayisi;
    delete[] favoriSarkilar;
}

void CalmaListesi::sarkiEkle(Sarki s) {
    if (size >= capacity) {
        capacity *= 2;
        Sarki* tempSarkilar = new Sarki[capacity];
        int* tempDinlenmeSuresi = new int[capacity];
        int* tempDinlenmeSayisi = new int[capacity];
        std::pair<Sarki, int>* tempFavoriSarkilar = new std::pair<Sarki, int>[capacity];

        for (int i = 0; i < size; i++) {
            tempSarkilar[i] = sarkilar[i];
            tempDinlenmeSuresi[i] = dinlenmeSuresi[i];
            tempDinlenmeSayisi[i] = dinlenmeSayisi[i];
            tempFavoriSarkilar[i] = favoriSarkilar[i];
        }

        delete[] sarkilar;
        delete[] dinlenmeSuresi;
        delete[] dinlenmeSayisi;
        delete[] favoriSarkilar;

        sarkilar = tempSarkilar;
        dinlenmeSuresi = tempDinlenmeSuresi;
        dinlenmeSayisi = tempDinlenmeSayisi;
        favoriSarkilar = tempFavoriSarkilar;
    }

    sarkilar[size] = s;
    dinlenmeSuresi[size] = 0;
    dinlenmeSayisi[size] = rand() % 100 + 1;
    size++;
}

void CalmaListesi::sarkilariGoster() {
    for (int i = 0; i < size; i++) {
        std::cout << sarkilar[i].no << ". " << sarkilar[i].ad << " - " << sarkilar[i].sanatci << std::endl;
    }
}

void CalmaListesi::calmaListesiniOynat() {
    srand(time(0));
    int index = 0;
    while (true) {
        int sure = rand() % 100 + 1;
        int calmaSayisi = rand() % 100 + 1;
        std::cout << "Playing: " << sarkilar[index].ad << " - " << sarkilar[index].sanatci << ", Sure: " << sure << ", Calma Sayisi: " << calmaSayisi << std::endl;
        dinlenmeSuresi[index] += sure;
        dinlenmeSayisi[index] += calmaSayisi;

        std::cout << "1. Ileri, 2. Geri, 0. Cikis" << std::endl;
        int choice;
        std::cin >> choice;
        if (choice == 1) {
            index++;
            if (index >= size) {
                index = 0;
            }
        } else if (choice == 2) {
            index--;
            if (index < 0) {
                index = size - 1;
            }
        } else {
            break;
        }
    }
}

void CalmaListesi::favoriSarkilariSec() {
    std::cout << "Favori sarkilarinizi secin (Cikmak icin 0'a basin):" << std::endl;
    int secim;
    do {
        std::cout << "Sarki numarasi: ";
        std::cin >> secim;
        if (secim != 0) {
            if (secim < 1 || secim > size) {
                std::cout << "Gecersiz sarki numarasi. Tekrar deneyin." << std::endl;
            } else if (secilenler[secim - 1]) {
                std::cout << "Bu sarkiyi zaten sectiniz. Tekrar deneyin." << std::endl;
            } else {
                secilenler[secim - 1] = true;
                int index = secim - 1;
                std::pair<Sarki, int> favoriSarki = std::make_pair(sarkilar[index], dinlenmeSayisi[index]);
                favoriSarkilar[index] = favoriSarki;
                favoriSarkilarStack.push(sarkilar[index]);
                favoriSarkilarQueue.enqueue(sarkilar[index]);
                std::cout << sarkilar[index].ad << " favori sarkilariniza eklendi." << std::endl;
            }
        }
    } while (secim != 0);
    for (int i = 0; i < 100; i++) {
        secilenler[i] = false;
    }
}

void CalmaListesi::favoriSarkilariListeleStack() {
    std::cout << "Favori Sarkilar (Stack):" << std::endl;
    Stack tempStack = favoriSarkilarStack;
    while (!tempStack.isEmpty()) {
        Sarki s = tempStack.topElement();
        std::cout << s.no << ". " << s.ad << " - " << s.sanatci << std::endl;
        tempStack.pop();
    }
}

void CalmaListesi::favoriSarkilariListeleQueue() {
    std::cout << "Favori Sarkilar (Queue):" << std::endl;
    Queue tempQueue = favoriSarkilarQueue;
    while (!tempQueue.isEmpty()) {
        Sarki s = tempQueue.frontElement();
        std::cout << s.no << ". " << s.ad << " - " << s.sanatci << std::endl;
        tempQueue.dequeue();
    }
}

void CalmaListesi::onerilenSarkilariGoster() {
    std::pair<Sarki, int>* siraliSarkilar = new std::pair<Sarki, int>[size];

    for (int i = 0; i < size; i++) {
        int puan = dinlenmeSuresi[i] + dinlenmeSayisi[i];
        siraliSarkilar[i] = std::make_pair(sarkilar[i], puan);
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (siraliSarkilar[j].second < siraliSarkilar[j + 1].second) {
                std::swap(siraliSarkilar[j], siraliSarkilar[j + 1]);
            }
        }
    }

    std::cout << "Onerilen Sarkilar:" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << siraliSarkilar[i].first.no << ". " << siraliSarkilar[i].first.ad << " - " << siraliSarkilar[i].first.sanatci
                 << ", Dinlenme Suresi: " << dinlenmeSuresi[siraliSarkilar[i].first.no - 1]
                 << ", Dinlenme Sayisi: " << dinlenmeSayisi[siraliSarkilar[i].first.no - 1] << std::endl;
    }

    delete[] siraliSarkilar;
}