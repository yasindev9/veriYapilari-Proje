//Geliştirici : Yasin Durak
//Öğrenci No : B241200067
//Ödev Konusu : Kitap Yönetim Sistemi
//kullanici.h
#ifndef KULLANICI_H
#define KULLANICI_H

#include <string>
#include <ctime>
#include "main.h"
#include <stack>
#include <queue>
using namespace std;

// Fonksiyon prototipleri
void kitapYonetimK(dcBook* head, dcBook* tail,book* basdugum, stackBook* stackBas);
void anaMenu();
void kullaniciIslemler(dcBook* head, dcBook* tail, book* basdugum, stackBook* stackBas);
void oduncAlma(dcBook* head, dcBook* tail,book* basdugum, stackBook* stackBas);
// Her yerde kullanabilmemiz için gereken global tanımlamalar
extern dcBook* koleksiyonBas;
extern bool koleksiyonVar;
extern string koleksiyonAdi;
extern stack<stackBook> oduncKitaplar;
extern stack<stackBook> iadeKitaplar;
extern queue<string> talepKitap;
extern queue<string> oncelikliTalepKitap;
#endif