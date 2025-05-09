#include "kutuphaneffd.h"

void KitapListesi::kitapEkle(int id, string ad, string yazar, int adet) {
	Kitap* yeni = new Kitap{id, ad, yazar, adet, nullptr};
	if (!head) {
		head = yeni;
	} else {
		Kitap* tmp = head;
		while (tmp->next) tmp = tmp->next;
		tmp->next = yeni;
	}
}

void KitapListesi::kitaplariGoster() {
	Kitap* tmp = head;
	cout << "\n--- Kitap Listesi ---\n";
	while (tmp) {
		cout << tmp->id << " - " << tmp->ad << " - " << tmp->yazar << "- Adet: " << tmp->adet << endl;
		tmp = tmp->next;
	}
}

Kitap* KitapListesi::kitapBul(int id) {
	Kitap* tmp = head;
	while (tmp) {
		if (tmp->id == id) return tmp;
		tmp = tmp->next;
	}
	return nullptr;
}

void Kuyruk::enqueue(int id, string ad, int kitapID) {
	Ogrenci* yeni = new Ogrenci{id, ad, kitapID, nullptr};
	if (!rear) {
		front = rear = yeni;
	} else {
		rear->next = yeni;
		rear = yeni;
	}
}

void Kuyruk::listele(){
	cout << "\n--- Odunc Alma Kuyrugu ---\n";
	Ogrenci* tmp = front;
	while (tmp) {
		cout << tmp->ogrID << " - " << tmp->adSoyad << " - KitapID: " << tmp->kitapID << endl;
		tmp = tmp->next;
	}
}

void Kuyruk::islemYap(KitapListesi& liste) {
	if (!front) {
		cout << "Kuyruk bos.\n";
		return;
	}
	Ogrenci* ogr = front;
	Kitap* kitap = liste.kitapBul(ogr->kitapID);
	if (kitap && kitap->adet > 0) {
		kitap->adet--;
		cout << ogr->adSoyad << " adli ogrenciye \"" << kitap->ad << "\" kitabi verildi.\n";
    } else {
		cout << "Kitap mevcut degil.\n";
	}
	front = front->next;
	delete ogr;
	if (!front) rear = nullptr;
}

void Yigin::push(int id, string ad, int kitapID) {
	Iade* yeni = new Iade{id, ad, kitapID, top};
	top = yeni;
}

void Yigin::listele() {
	cout << "\n--- Iade Edilen Kitaplar ---\n";
	Iade* tmp = top;
	while (tmp) {
		cout << tmp->ogrID << " - " << tmp->adSoyad << " - Kitap ID: " << tmp->kitapID << endl;
		tmp = tmp->next;	
	}
}

void Yigin::islemYap(KitapListesi& liste) {
	if (!top) {
		cout << "yıgın bos.\n";
		return;
	}
	Iade* iade = top;
	Kitap* kitap = liste.kitapBul(iade->kitapID);
	if (kitap) {
		kitap->adet++;
		cout << iade->adSoyad << " adli ogrenciden \"" << kitap->ad << "\" kitabi iade alindi.\n";
	}
	top = top->next;
	delete iade;
}

void kitaplariYukle(KitapListesi& liste) {
	ifstream dosya("Kitaplar.txt");
	if (!dosya) {
		cerr << "Kitaplar.txt dosyasi acilmadi.\n";
		return;
	}
	
	int id, adet;
	string ad, yazar;
	string satir;
	getline(dosya, satir);
	while (dosya >> id){
		dosya.ignore();
		getline(dosya, ad, '\t');
		getline(dosya, yazar, '\t');
		dosya >> adet;
		liste.kitapEkle(id, ad, yazar, adet);
	}
	dosya.close();
}

void ogrenciVerileriniYukle(Kuyruk& kuyruk, Yigin& yigin) {
	ifstream dosya("Ogrenciler.txt");
	if (!dosya) {
		cerr << "Ogrenciler.txt dosyasi acilmadi.\n";
		return;
	}
	
	string satir;
	getline(dosya, satir);
	int id, kitapID, islem;
	string adSoyad;
	while (dosya >> id) {
		dosya.ignore();
		getline(dosya, adSoyad, '\t');
		dosya >> kitapID >> islem;
		if (islem == 0)
		    kuyruk.enqueue(id, adSoyad, kitapID);
		else
		    yigin.push(id, adSoyad, kitapID);
	}
	dosya.close();
}

int main() {
	KitapListesi kitaplar;
	Kuyruk kuyruk;
	Yigin yigin;
	
	kitaplariYukle(kitaplar);
	ogrenciVerileriniYukle(kuyruk, yigin);
	
	int secim;
	do {
		cout << "\n=== Kutuphane Otomasyon Sistemi ===\n";
		cout << "1. Tum kitap listesini goster\n";
		cout << "2. Odunc alma listesini goster\n";
		cout << "3. Iade edilen kitaplari goster\n";
		cout << "4. Kitap odunc ver\n";
		cout << "5. Kitap iade al\n";
		cout << "6. Cikis\n";
		cout << "Secim: ";
		cin >> secim;
		
		switch (secim) {
			case 1: kitaplar.kitaplariGoster(); break;
			case 2: kuyruk.listele(); break;
			case 3: yigin.listele(); break;
			case 4: kuyruk.islemYap(kitaplar); break;
			case 5: yigin.islemYap(kitaplar); break;
			case 6: cout << "Programdan cikiliyor...\n"; break;
			default: cout << "Gecersiz secim.\n";
		}
		
	} while (secim != 6);
	
	return 0;
}