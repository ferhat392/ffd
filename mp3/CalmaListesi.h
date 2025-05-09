#ifndef CALMALISTESI_H
#define CALMALISTESI_H

#include "Sarki.h"
#include "Stack.h"
#include "Queue.h"

class CalmaListesi {
private:
    Sarki* sarkilar;
    int* dinlenmeSuresi;
    int* dinlenmeSayisi;
    std::pair<Sarki, int>* favoriSarkilar;
    int capacity;
    int size;
    Stack stack;
    Queue queue;
    Stack favoriSarkilarStack;
    Queue favoriSarkilarQueue;
    static bool secilenler[100];

public:
    CalmaListesi();
    ~CalmaListesi();

    void sarkiEkle(Sarki s);
    void sarkilariGoster();
    void calmaListesiniOynat();
    void favoriSarkilariSec();
    void favoriSarkilariListeleStack();
    void favoriSarkilariListeleQueue();
    void onerilenSarkilariGoster();
};

#endif /* CALMALISTESI_H */
