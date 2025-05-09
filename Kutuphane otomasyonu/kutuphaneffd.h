#ifndef KUTUPHANEFFD_H
#define KUTUPHANEFFD_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Kitap {
	int id;
	string ad;
	string yazar;
	int adet;
	Kitap* next;
};

class KitapListesi {
	public:
		Kitap* head;
		
		KitapListesi() : head(nullptr) {}
		
		void kitapEkle(int id, string ad, string yazar, int adet);
		void kitaplariGoster();
		Kitap* kitapBul(int id);
};

struct Ogrenci {
	int ogrID;
	string adSoyad;
	int kitapID;
	Ogrenci* next;
};

class Kuyruk {
	public:
		Ogrenci* front;
		Ogrenci* rear;
		
		Kuyruk() : front(nullptr), rear(nullptr) {}
		
		void enqueue(int id, string ad, int kitapID);
		void listele();
		void islemYap(KitapListesi& liste);
};

struct Iade {
	int ogrID;
	string adSoyad;
	int kitapID;
	Iade* next;
};

class Yigin {
	public:
		Iade* top;
		
		Yigin() : top(nullptr) {}
		
		void push(int id, string ad, int kitapID);
		void listele();
		void islemYap(KitapListesi& liste);
};

void kitaplariYukle(KitapListesi& liste);
void ogrenciVerileriniYukle(Kuyruk& kuyruk, Yigin& yigin);

#endif