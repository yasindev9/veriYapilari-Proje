//Geliştirici : Yasin Durak
//Öğrenci No : B241200067
//Ödev Konusu : Kitap Yönetim Sistemi
//main.h
#ifndef MAIN_H
#define MAIN_H

#include <string>
#include <ctime>
#include <unordered_map>
using namespace std;

// Ödünç alma, iade etme işlemlerinde kullanmak üzere stack oluşturacağımız struct tanımı
struct stackBook{
	string ad = "test";
    int id;
	time_t oduncTime;
	time_t iadeTime;
	int oduncSure;
	int year;
	bool yerli;
	bool turkce;
	int pagecount;
	string kategori = "test";
	stackBook* next;
};

// Tek yönlü bağlı liste oluşturacağımız struct tanımı
struct book {
    string ad;
    int id;
    int pagecount;
    int year;
    bool damaged;
	string damageNote;
    book* next;  // Bagli liste için bir pointer
	time_t addTime;
	string comment;
	bool yerli;
	bool turkce;
	string kategori;
};

// Çift yönlü dairesel liste oluşturacağımız struct tanımı
struct dcBook {
    string ad = "test";
    int id;
    int pagecount;
    int year;
    bool damaged;
	string damageNote = "test";
    dcBook* next;
	dcBook* prev;
	time_t addTime;
	string comment = "test";
	bool yerli;
	bool turkce;
	string kategori = "test";
};

// Ağaç oluşturmak için kullanacağımız struct tanımı
struct tree {
    string ad;
    int id;
    time_t oduncTime;
    int oduncSure;
    int year;
	bool yerli;
	bool turkce;
	int pagecount;
	string kategori;
    tree* left;
    tree* right;
};

// Puanlama işlemleri için kullanacağımız hash tablosunu oluşturacağımız hash tablosu
struct PuanKayit {
    string kitapAdi;
    int toplamPuan = 0;
    int puanSayisi = 0;
    double ortalama() const {
        return puanSayisi == 0 ? 0.0 : (double)toplamPuan / puanSayisi;
    }
};

// Her yerde kullanabilmemiz için gerekli olan global tanımlamalar
extern unordered_map<int, PuanKayit> kitapPuanTablosu;
extern book* basdugum; 
extern dcBook* head; 
extern dcBook* tail; 
extern stackBook* stackBas;
extern stackBook* stackBasIade;
extern stackBook* stackSon;
extern stackBook* stackSonIade;
extern tree* treeSure;
extern tree* treeBasim;
extern tree* treeYayin;
extern tree* treeDil;
extern tree* treeSayfa;

// Fonksiyon prototipleri
void kitapYonetim(book* basdugum);
void listeGetir(book* basdugum);
void listeOlustur();
void listeOlusturDC(dcBook*& head, dcBook*& tail, book* basdugum);
void kitapYonetimK(dcBook* head, dcBook* tail,book* basdugum, stackBook* stackBas);
void oduncAlma(dcBook* head, dcBook* tail,book* basdugum, stackBook* stackBas);
void oduncIslemler();
void talepIslemler(dcBook* head,dcBook* tail);
void talepYonet(book* basdugum);


#endif
