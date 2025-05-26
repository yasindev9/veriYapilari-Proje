//Geliştirici : Yasin Durak
//Öğrenci No : B241200067
//Ödev Konusu : Kitap Yönetim Sistemi
//main.cpp 
#include <iostream>
#include "main.h"
#include "personel.h"
#include "kullanici.h"
#include <windows.h>
using namespace std;

// Baş düğüm, kuyruk, stack, tree, hash tablosu bütün scriptlerden erişilebilmesi için burada tanımladım.
book* basdugum = nullptr;
dcBook* head = nullptr;
dcBook* tail = nullptr;
stackBook* stackBas = nullptr;
stackBook* stackSon = nullptr;
stackBook* stackBasIade = nullptr;
stackBook* stackSonIade = nullptr;
tree* treeSure = nullptr;
tree* treeBasim = nullptr;
tree* treeYayin = nullptr;
tree* treeDil = nullptr;
tree* treeSayfa = nullptr;
unordered_map<int, PuanKayit> kitapPuanTablosu;

// Birbirini çağıran fonksiyonlar olduğu için fonksiyon prototipleri tanımladım.
void anaMenu();
void kullaniciMenu(dcBook* head, dcBook* tail, book* basdugum, stackBook* stackBas);
void personelMenu();
void personelIslemler();
void listeOlustur();
void kullaniciIslemler(dcBook* head, dcBook* tail, book* basdugum, stackBook* stackBas);
void listeOlusturDC(dcBook*& head, dcBook*& tail, book* basdugum);

// Main 
int main(){
	// Konsolu temizlemek için bir çok yerde kullandım.
    system("cls");
    setlocale(LC_ALL, "Turkish");
    // Listeyi oluşturuyoruz
    listeOlustur();
    // Ana Menü fonksiyonu
    anaMenu();
    return 0;
}

// Ana Menü
void anaMenu(){
	system("cls");
    int menuSecim;
    cout << "Kitap Yonetim Sistemine Hosgeldiniz..." << endl;
    cout << "1. Personel Girisi" << endl;
    cout << "2. Kullanici Girisi" << endl;
    cout << "3. Cikis" << endl;
    cin >> menuSecim;

    switch(menuSecim)
    {
    case 1:
        personelMenu(); // Personel menüsüne yönlendiriyoruz.
        break;
    case 2:
        kullaniciMenu(head, tail, basdugum, stackBas); // Kullanici menüsüne yönlendiriyoruz.
        break;
    case 3:
        exit(0); // Çıkış
        break;    
    default:
        cout << "Hatali secim! Lutfen tekrar deneyin." << endl;
        anaMenu();  // Yanlış seçim yapılırsa menüyü tekrar göster
        break;
    }
}

// Personel Menü
void personelMenu(){
    system("cls");
	// İsim ve şifre girme işlemi iptal edildi.
    /*string personelAD = "yasin";
    string personelSifre = "123";
    string girilenAD;
    string girilenSifre;
	cin.ignore();
    cout << "Personel girisi..." << endl;
    cout << "Personel adi: ";
    cin >> girilenAD;
    cout << "Personel Sifre: ";
    cin >> girilenSifre;

    // Giriş doğrulaması
    if (girilenAD == personelAD && girilenSifre == personelSifre)
    {
       personelIslemler();
    }
    else
    {
        cout << "Girilen ad veya sifre hatali. Tekrar deneyin!" << endl;
		Sleep(2000);
        personelMenu();  // Yanlış giriş yapılırsa menüyü tekrar göster
    }*/
	personelIslemler(); // Direkt personel işlemler menüsüne yönlendiriyoruz.
}

// Personel İşlemleri Menü
void personelIslemler(){
    system("cls");
    int menuSecim;
    cout << "Islem basarili! Yapmak istediginiz islemi seciniz:" << endl;
    cout << "1. Kitap Yonetimi" << endl;
    cout << "2. Odunc Alinan Kitap Islemleri" << endl;
	cout << "3. Kitap Talep Islemleri" << endl;
    cout << "0. Ana Menu" << endl;
    cin >> menuSecim;

    switch(menuSecim)
    {
    case 1:
        kitapYonetim(basdugum);  // Kitap yönetim menüsüne yönlendiriyoruz
        break;
    case 2:
        oduncIslemler(); // Ödünç işlemler menüsüne yönlendiriyoruz
        break;
	case 3:
        talepYonet(basdugum); // Talep menüsüne yönlendiriyoruz
        break;
    case 0:
        anaMenu();  // Ana menüye dön
        break;
    default:
        cout << "Hatali secim!" << endl;
        personelIslemler();  // Yanlış seçim yapılırsa işlemleri tekrar göster
        break;
    }
}

// Kullanıcı Menü
void kullaniciMenu(dcBook* head, dcBook* tail, book* basdugum, stackBook* stackBas){
    system("cls");
	// İsim ve şifre girme işlemi iptal edildi.
    /*string personelAD = "yasin";
    string personelSifre = "123";
    string girilenAD;
    string girilenSifre;
	cin.ignore();
    cout << "Kullanici girisi..." << endl;
    cout << "Kullanici adi: ";
    cin >> girilenAD;
    cout << "Kullanici Sifre: ";
    cin >> girilenSifre;

    // Giriş doğrulaması
    if (girilenAD == personelAD && girilenSifre == personelSifre)
    {
        kullaniciIslemler(head,tail,basdugum, stackBas);
    }
    else
    {
        cout << "Girilen ad veya sifre hatali. Tekrar deneyin!" << endl;
		Sleep(2000);
        kullaniciMenu(head, tail, basdugum, stackBas);  // Yanlış giriş yapılırsa menüyü tekrar göster
    }*/
	kullaniciIslemler(head,tail,basdugum, stackBas); // Direkt kullanıcı işlemleri menüsüne yönlendiriyoruz
}

// Kullanıcı İşlemleri Menü
void kullaniciIslemler(dcBook* head, dcBook* tail, book* basdugum, stackBook* stackBas){
	system("cls");
    int menuSecim;
    cout << "Islem basarili! Yapmak istediginiz islemi seciniz:" << endl;
    cout << "1. Kitap Yonetimi(Cift yonlu dairesel liste)" << endl;
    cout << "2. Odunc Alma Islemleri(stack)" << endl;
    cout << "3. Talep Islemleri(queue)" << endl;
    cout << "0. Ana Menu" << endl;
    cin >> menuSecim;

    switch(menuSecim)
    {
    case 1:
		listeOlusturDC(head, tail, basdugum);
        kitapYonetimK(head, tail,basdugum,  stackBas);
        break;
    case 2:
		listeOlusturDC(head, tail, basdugum);
        oduncAlma(head, tail, basdugum, stackBas);
        break;
	case 3:
		listeOlusturDC(head, tail, basdugum);
        talepIslemler(head, tail);
        break;
    case 0:
        anaMenu();  // Ana menüye dön
        break;
    default:
        cout << "Hatali secim!" << endl;
        kullaniciIslemler(head, tail, basdugum, stackBas);  // Yanlış seçim yapılırsa işlemleri tekrar göster
        break;
    }
}

// Listeyi oluşturma fonksiyonu
void listeOlustur(){
	// Program başında eklenmesini istediğimiz kitapların tanımları
    struct book* kitap1 = new book{"Sefiller", 111, 300, 1943, 1, "sayfa yirtik",nullptr, time(0), "henuz bir yorum yok!",false, true, "roman"};
    struct book* kitap2 = new book{"Osmancik", 112, 250, 1948, 0, "hasar yok" ,nullptr, time(0), "henuz bir yorum yok!", true, true, "roman"};
    struct book* kitap3 = new book{"Foundation", 113, 1230, 1980, 1, "sayfa yirtik" ,nullptr, time(0), "henuz bir yorum yok!",false, false, "aksiyon"};
    struct book* kitap4 = new book{"Fahrenheit 451", 114, 150, 2002, 0,"hasar yok" ,nullptr, time(0), "henuz bir yorum yok!",false, true, "bilimkurgu"};
    struct book* kitap5 = new book{"Vakif ve Dunya", 115, 540, 2023, 1, "sayfa yirtik",nullptr, time(0), "henuz bir yorum yok!",false, true, "bilimkurgu"};
    
    // Listeyi oluşturup birbirine bağlama
    kitap1->next = kitap2;
    kitap2->next = kitap3;
    kitap3->next = kitap4;
    kitap4->next = kitap5;
    kitap5->next = nullptr;

    // Baş düğümünü basdugum'a atıyoruz
    basdugum = kitap1;
}

// Tek yönlü bağlı liste verilerini istenen yerde kullanmak için dairesel çift yönlü listeye aktarma fonksiyonu
void listeOlusturDC(dcBook*& head, dcBook*& tail, book* basdugum) {
    // Önce listeyi boşaltalım (önceki veriler varsa)
    head = nullptr;
    tail = nullptr;

    book* temp = basdugum;
    while (temp != nullptr) {
        // Yeni düğüm oluştur
        dcBook* yeni = new dcBook{
            temp->ad,
            temp->id,
            temp->pagecount,
            temp->year,
            temp->damaged,
            temp->damageNote,
            nullptr,  // next
            nullptr,  // prev
            temp->addTime,
			temp ->comment,
			temp->yerli,
			temp->turkce,
			temp->kategori
        };

        if (head == nullptr) {
            // İlk düğüm
            head = yeni;
            tail = yeni;
            yeni->next = yeni;  // Dairesel bağlantı
            yeni->prev = yeni;
        } else {
            // Kuyruğa ekle
            yeni->prev = tail;
            yeni->next = head;
            tail->next = yeni;
            head->prev = yeni;
            tail = yeni;
        }

        temp = temp->next;
    }
}



