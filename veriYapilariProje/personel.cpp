//Geliştirici : Yasin Durak
//Öğrenci No : B241200067
//Ödev Konusu : Kitap Yönetim Sistemi
//personel.cpp
#include "personel.h"
#include "main.h"
#include "kullanici.h"
#include <iostream>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <iomanip>
using namespace std;
int menuSecim;
string newAd = " ";
int newId;
int newPageCount;
int newYear;
int newDamage;
bool newYerli;
bool newTurkce;
string newKategori;
void raporlamaMenu();
// listeGetir fonksiyonunun tanımlanması
void listeGetir(book* basdugum) {
	system("cls");
    book* temp = basdugum;  // Baş düğüm üzerinden listeyi dolaş
	int a=1;
	switch(menuSecim)
	{
	case 4:
	while (temp != nullptr) {
    cout << "Kitap Adi: "<< temp->ad <<" Eklenme zamani: "<<ctime(&(temp->addTime))<< endl;  // Kitap adını ekrana yazdır
    cout << "------------------------------------------------" << endl;
	temp = temp->next;  // Sonraki kitaba geç
    }
	cout << "0. Onceki menu" << endl;
	cin >> a;
	if(a == 0){kitapYonetim(basdugum);}
	break;
	case 10:
	while (temp != nullptr) {
	if(temp -> damaged == true)
	{
	cout << "Kitap Adi: "<< temp->ad <<" Eklenme zamani: "<<ctime(&(temp->addTime))<<" Hasar Durumu: " << temp -> damaged << " Hasar notu: " << temp -> damageNote <<endl;  // Kitap adını ekrana yazdır
	cout << "------------------------------------------------" << endl;
	}
    temp = temp->next;  // Sonraki kitaba geç
    }
	cout << "0. Onceki menu" << endl;
	cin >> a;
	if(a == 0){kitapYonetim(basdugum);}
	break;
	}
}
// Tek yönlü listeye kitap ekleme fonksiyonu
void kitapEkle(book* basdugum){
	system("cls");
	int yerli = 0;
	int turkce = 0;
	book* iter = basdugum;
	while(iter->next != nullptr){
		iter = iter ->next;
	}
	cout<<"Eklemek istediginiz kitabin adi: ";
	cin.ignore();		
	getline(cin, newAd);
	cout<<"Eklemek istediginiz kitabin ID'si: ";
	cin >> newId;
	cout<<"Eklemek istediginiz kitabin sayfa sayisi: ";
	cin >> newPageCount;
	cout<<"Eklemek istediginiz kitabin basim yili: ";
	cin >> newYear;
	cout<<"Eklemek istediginiz kitabin hasar durumu(1-hasarli/0-hasarsiz): ";
	cin >> newDamage;
	cout << "Eklemek istediginiz kitap yerli yayin evine mi ait? 1-evet 0-hayir: ";
	cin >> yerli;
	if(yerli == 1){newYerli = true;}
	cout << "Eklemek istediginiz kitap turkce mi? 1-evet 0-hayir: ";
	cin >> turkce;
	if(turkce == 1){newTurkce = true;}
	cout<<"Eklemek istediginiz kitabin kategorisi(bilimkurgu, aksiyon, roman, korku): ";
	cin.ignore();		
	getline(cin, newKategori);
	struct book* yeniKitap = new book{newAd, newId, newPageCount, newYear, newDamage,"" , nullptr, time(0),"", newYerli, newTurkce, newKategori};
	iter -> next =yeniKitap;
	yeniKitap -> next = nullptr;
	cout << "Kitap basariyla eklendi!";
	Sleep(800);
	kitapYonetim(basdugum);
}
// Tek yönlü listeden kitap arama fonksiyonu
void kitapAra(book* basdugum) {
	system("cls");
	string arananAd;
	int arananId;
	int kitapSayi = 0;
	book* temp = basdugum;
	book* temp2 = basdugum;
	bool bulundu = false;
	bool silindi = false;

	switch (menuSecim) {
	case 6: // Kitap sayısını göster
		while (temp != nullptr) {
			kitapSayi++;
			temp = temp->next;
		}
		cout << "Kitap sayisi: " << kitapSayi << endl;
		cout << "1. Onceki Menu" << endl;
		cin >> menuSecim;
		kitapYonetim(basdugum);
		break;

	case 2: // Kitap düzenle
		cout << "Duzenlemek istediginiz kitabin adi: ";
		cin.ignore();
		getline(cin, arananAd);

		while (temp != nullptr) {
			if (temp->ad == arananAd) {
				cout << "Kitabin yeni adi: ";
				getline(cin, newAd);
				cout << "Kitabin yeni ID'si: ";
				cin >> newId;
				cout << "Kitabin hasar durumu (1-hasarli / 0-hasarsiz): ";
				cin >> newDamage;

				temp->ad = newAd;
				temp->id = newId;
				temp->damaged = newDamage;
				temp->addTime = time(0);

				cout << "Kitap basariyla duzenlendi! Zaman bilgisi guncellendi." << endl;
				bulundu = true;
				Sleep(2000);
				kitapYonetim(basdugum);
			}
			temp = temp->next;
		}
		if (!bulundu) {
			cout << "Aranan kitap bulunamadi. Menuye yonlendiriliyorsunuz..." << endl;
			Sleep(2000);
			kitapYonetim(basdugum);
		}
		break;

	case 3: // Kitap sil
		cout << "Silmek istediginiz kitabin ID'si: ";
		cin >> arananId;

		if (basdugum != nullptr && basdugum->id == arananId) {
			book* silinecek = basdugum;
			basdugum = basdugum->next;
			delete silinecek;
			cout << "Silme islemi basarili! Ana menuye yonlendiriliyorsunuz." << endl;
			Sleep(2000);
			kitapYonetim(basdugum);
		}
		else {
			temp = basdugum;
			while (temp->next != nullptr) {
				if (temp->next->id == arananId) {
					book* silinecek = temp->next;
					temp->next = silinecek->next;
					delete silinecek;
					cout << "Silme islemi basarili! Ana menuye yonlendiriliyorsunuz." << endl;
					Sleep(2000);
					kitapYonetim(basdugum);
				}
				temp = temp->next;
			}
		}

		cout << "Aranan kitap bulunamadi. Menuye yonlendiriliyorsunuz..." << endl;
		Sleep(2000);
		kitapYonetim(basdugum);
		break;

	case 5: // Kitap bilgisi getir
		cout << "Getirmek istediginiz kitabin ID'si: ";
		cin >> arananId;

		temp = basdugum;
		while (temp != nullptr) {
			if (temp->id == arananId) {
				cout << "AD: " << temp->ad
					<< " | ID: " << temp->id
					<< " | SAYFA SAYISI: " << temp->pagecount
					<< " | BASIM YILI: " << temp->year
					<< " | HASAR DURUMU: " << temp->damaged
					<< " | Zaman damgasi: " << ctime(&(temp->addTime));

				bulundu = true;
				int a = 1;
				cout << "0. Onceki menu" << endl;
				cin >> a;
				if (a == 0) kitapYonetim(basdugum);
			}
			temp = temp->next;
		}
		if (!bulundu) {
			cout << "Aranan kitap bulunamadi. Menuye yonlendiriliyorsunuz..." << endl;
			Sleep(2000);
			kitapYonetim(basdugum);
		}
		break;

	default:
		cout << "Hatali secim!" << endl;
		break;
	}
}
// Sayfa sayısına göre listeleme fonksiyonu
void siraliListeleSayfaSayisinaGore(book* basdugum) {
    vector<book*> kitaplar;
	system("cls");
    // 1. Linked listten kitapları vektöre al
    book* temp = basdugum;
    while (temp != nullptr) {
        kitaplar.push_back(temp);
        temp = temp->next;
    }

    // 2. Sayfa sayısına göre sırala
    sort(kitaplar.begin(), kitaplar.end(), [](book* a, book* b) {
        return a->pagecount < b->pagecount;
    });

    // 3. Sıralı şekilde yazdır
    for (book* b : kitaplar) {
        cout << "Kitap: " << b->ad << ", Sayfa: " << b->pagecount << endl;
    }
	int a=1;
	cout << "0. Onceki menu" << endl;
	cin >> a;
	if(a == 0){kitapYonetim(basdugum);}
}
// Basım yılına göre listeleme fonksiyonu
void enEskiBesKitap(book* basdugum) {
    vector<book*> kitaplar;
	system("cls");
    // 1. Linked listten kitapları vektöre al
    book* temp = basdugum;
    while (temp != nullptr) {
        kitaplar.push_back(temp);
        temp = temp->next;
    }

    // 2. Basım yılına göre küçükten büyüğe sırala
    sort(kitaplar.begin(), kitaplar.end(), [](book* a, book* b) {
        return a->year < b->year;
    });

    // 3. En eski 5 kitabı yazdır
    cout << "En eski 5 kitap:" << endl;
    for (int i = 0; i < kitaplar.size() && i < 5; i++) {
        cout << kitaplar[i]->ad << " - Basim Yili: " << kitaplar[i]->year << endl;
    }
	int a=1;
	cout << "0. Onceki menu" << endl;
	cin >> a;
	if(a == 0){kitapYonetim(basdugum);}
}
// Hasar notu ekleme fonksiyonu
void hasarNotEkle(book* basdugum){
	system("cls");
	book* temp = basdugum;
	int arananId;
	int secim;
	string eklenecekNot;
	cout << "Hasar notu eklemek istediginiz kitabin ID'si: ";
	cin >> arananId;
	while(temp != nullptr)
	{
	if(temp -> id == arananId && temp -> damaged == true)
	{
	cout << "Eklemek istediginiz notu giriniz: ";
	cin.ignore();
	getline(cin, eklenecekNot);
	temp -> damageNote = eklenecekNot;
	cout << "Not basariyla eklendi. Onceki menuye yonlendiriliyorsunuz..." << endl;
	Sleep(2000);
	kitapYonetim(basdugum);
	}
	else if(temp -> id == arananId && temp -> damaged == false){
	cout << "Girilen ID'deki kitap hasarli degil. Hasar durumunu degistirmek istiyor musunuz? Onceki menu icin 0, Hasar durumunu degistirmek icin 1:";
	cin >> secim;
	switch(secim){
	case 0:
	kitapYonetim(basdugum);
	break;
	case 1:
	temp -> damaged = true;
	cout << "Hasar durumu degistirildi. Not ekleme kismina yonlendiriliyorsunuz..." << endl;
	Sleep(2000);
	hasarNotEkle(basdugum);
	break;
	default:
	kitapYonetim(basdugum);
	break;
	}
		}
	temp = temp -> next;
	}
	cout << "Girilen ID'de bir kitap bulunamadi! Bir onceki menu icin 0, Tekrar denemek icin 1:"<< endl;
	cin >> secim;
	switch(secim){
	case 0:
	kitapYonetim(basdugum);
	break;
	case 1:
	hasarNotEkle(basdugum);
	break;
	default:
	kitapYonetim(basdugum);
	break;
	}
}
// Kitap yönetim menü fonksiyonu
void kitapYonetim(book* basdugum) {
    system("cls");
	cout << "PERSONEL" << endl;
    cout << "1. Kitap ekle" << endl;
    cout << "2. Ismine gore kitap duzenle(Tek yonlu bagli liste)" << endl;
    cout << "3. ID bilgisine gore kitabi sil(Tek yonlu bagli liste)" << endl;
    cout << "4. Kitaplari zaman damgalari ile birlikte listele(Tek yonlu bagli liste)" << endl;
    cout << "5. ID bilgisine gore kitabi getir(Tek yonlu bagli liste)" << endl;
    cout << "6. Toplam kitap sayisi(Tek yonlu bagli liste)" << endl;
    cout << "7. Sayfa sayisina gore kucukten buyuge sirala(Tek yonlu bagli liste)" << endl;
    cout << "8. Basim yilina gore en eski 5 kitap(Tek yonlu bagli liste)" << endl;
    cout << "9. Hasar bilgi notu ekle(Tek yonlu bagli liste)" << endl;
    cout << "10. Hasarli kitaplari goster(Tek yonlu bagli liste)" << endl;
    cout << "0. Onceki menu" << endl;

    cin >> menuSecim;

    switch (menuSecim) {
        case 1:
            kitapEkle(basdugum);
            break;
        case 2:
            kitapAra(basdugum);
            break;
        case 3:
            kitapAra(basdugum);
            break;
        case 4:
            listeGetir(basdugum);
            break;
        case 5:
            kitapAra(basdugum);
            break;
        case 6:
            kitapAra(basdugum);
            break;
        case 7:
            siraliListeleSayfaSayisinaGore(basdugum);
            break;
        case 8:
            enEskiBesKitap(basdugum);
            break;
        case 9:
            hasarNotEkle(basdugum);
            break;
        case 10:
            listeGetir(basdugum);
            break;
        case 0:
			personelIslemler();
            break;
        default:
            cout << "Hatali secim!" << endl;
            break;
    }
}
// Ödünç alınan kitapları tek yönlü dairesel listeden yazdırma fonksiyonu
void yazdirOduncTD(stackBook* stackBas) {
	system("cls");
	stackBook* temp = stackBas;
	cout << "===Odunc Alinan Kitaplar===" << endl; 
	do{
	cout << "Kitap adi: " << temp->ad << endl;
	cout << "Kitap ID: " << temp->id << endl;
    cout << "Odunc alma zamani: " << ctime(&(temp->oduncTime))<< endl;
    cout << "Odunc suresi: " << temp->oduncSure << " gun" << endl;
    cout << "------------------------\n";
	temp = temp-> next;
	}while(temp != stackBas);
	int a=1;
	cout << "0. Onceki menu" << endl;
	cin >> a;
	if(a == 0){oduncIslemler();}
}
// İade edilen kitapları tek yönlü dairesel listeden yazdırma fonksiyonu
void yazdirIadeTD(stackBook* stackBasIade) {
	system("cls");
	stackBook* temp = stackBasIade;
	cout << "===Iade Edilen Kitaplar===" << endl; 
	do{
	cout << "Kitap adi: " << temp->ad << endl;
	cout << "Kitap ID: " << temp->id << endl;
    cout << "Odunc alma zamani: " << ctime(&(temp->oduncTime))<< endl;
    cout << "Iade etme zamani: " << ctime(&(temp->iadeTime))<< endl;
    cout << "Odunc suresi: " << temp->oduncSure << " gun" << endl;
    cout << "------------------------\n";
	temp = temp-> next;
	}while(temp != stackBasIade);
	int a=1;
	cout << "0. Onceki menu" << endl;
	cin >> a;
	if(a == 0){oduncIslemler();}
}

bool kitapVarMi(stackBook* bas, int id) {
	if (bas == nullptr) return false;

	stackBook* temp = bas;
	do {
		if (temp->id == id) return true;
		temp = temp->next;
	} while (temp != bas);

	return false;
}
// Stack'den tek yönlü dairesel listeye aktarma fonksşyonu
void stackToTekDairesel(stackBook*& stackBas, stackBook*& stackBasIade, stackBook*& stackSon, stackBook*& stackSonIade){
	stack<stackBook> oduncKopya = oduncKitaplar;
	stack<stackBook> iadeKopya = iadeKitaplar;

	while(!oduncKopya.empty()){
		stackBook kitap = oduncKopya.top();
		oduncKopya.pop();

		if (kitapVarMi(stackBas, kitap.id)) continue; // zaten varsa ekleme

		stackBook* yeni = new stackBook{kitap.ad, kitap.id, kitap.oduncTime, time(nullptr), kitap.oduncSure,kitap.year, kitap.yerli, kitap.turkce, kitap.pagecount, kitap.kategori};

		if(stackBas == nullptr){
			stackBas = stackSon = yeni;
			yeni->next = yeni;
		} else {
			yeni->next = stackBas;
			stackSon->next = yeni;
			stackSon = yeni;
		}
	}

	while(!iadeKopya.empty()){
		stackBook kitap = iadeKopya.top();
		iadeKopya.pop();

		if (kitapVarMi(stackBasIade, kitap.id)) continue; // zaten varsa ekleme

		stackBook* yeni = new stackBook{kitap.ad, kitap.id, kitap.oduncTime, time(nullptr), kitap.oduncSure,kitap.year, kitap.yerli, kitap.turkce,kitap.pagecount, kitap.kategori};

		if(stackBasIade == nullptr){
			stackBasIade = stackSonIade = yeni;
			yeni->next = yeni;
		} else {
			yeni->next = stackBasIade;
			stackSonIade->next = yeni;
			stackSonIade = yeni;
		}
	}
}
// Kuyruk yazdırma fonksiyonu
void talepYazdir(){
	system("cls");
	cout << "*** Talep Edilen Kitaplar ***" << endl;
    queue<string> gecici1 = talepKitap;
    queue<string> gecici2 = oncelikliTalepKitap;
	if(gecici1.empty() && gecici2.empty()){
	cout << "Henuz hic kitap talep edilmemis..." << endl;
	Sleep(2000);
	talepYonet(basdugum);
	}
    while (!gecici2.empty()) {
        cout << "- " << gecici2.front() << " -" << " * AKADEMIK ONCELIK *" << endl;
        gecici2.pop();
    }
	while (!gecici1.empty()) {
        cout << "- " << gecici1.front() << " -"<< endl;
        gecici1.pop();
    }
	cout << "0. Onceki menu" << endl;
	int a;
	cin >> a;
	if(a == 0){talepYonet(basdugum);}
}
// Talebi kütüphaneye ekleme fonksiyonu
void talepEkle(book* basdugum){
	system("cls");
	book* iter = basdugum;
	string talepAd = "";
	while(iter->next != nullptr){
		iter = iter ->next;
	}
	if(talepKitap.empty() && oncelikliTalepKitap.empty()){
	cout << "Henuz hic kitap talep edilmemis..." << endl;
	Sleep(2000);
	talepYonet(basdugum);
	}
	else if(oncelikliTalepKitap.empty()){
	cout << "'" << talepKitap.front() << "' isimli kitap eklenecek. Istenen bilgileri girin: " << endl;
	talepAd = talepKitap.front();
	talepKitap.pop();
	cout<<"Eklemek istediginiz kitabin ID'si: ";
	cin >> newId;
	cout<<"Eklemek istediginiz kitabin sayfa sayisi: ";
	cin >> newPageCount;
	cout<<"Eklemek istediginiz kitabin basim yili: ";
	cin >> newYear;
	cout<<"Eklemek istediginiz kitabin hasar durumu(1-hasarli/0-hasarsiz): ";
	cin >> newDamage;
	struct book* yeniKitap = new book{talepAd, newId, newPageCount, newYear, newDamage,"" , nullptr, time(0)};
	iter -> next =yeniKitap;
	yeniKitap -> next = nullptr;
	cout << "Kitap basariyla eklendi!";
	Sleep(2000);
	talepYonet(basdugum);
	}
	else{
	cout << "'" << oncelikliTalepKitap.front() << "' isimli kitap eklenecek. Istenen bilgileri girin: " << endl;
	talepAd = oncelikliTalepKitap.front();
	oncelikliTalepKitap.pop();
	cout<<"Eklemek istediginiz kitabin ID'si: ";
	cin >> newId;
	cout<<"Eklemek istediginiz kitabin sayfa sayisi: ";
	cin >> newPageCount;
	cout<<"Eklemek istediginiz kitabin basim yili: ";
	cin >> newYear;
	cout<<"Eklemek istediginiz kitabin hasar durumu(1-hasarli/0-hasarsiz): ";
	cin >> newDamage;
	struct book* yeniKitap = new book{talepAd, newId, newPageCount, newYear, newDamage,"" , nullptr, time(0)};
	iter -> next =yeniKitap;
	yeniKitap -> next = nullptr;
	cout << "Kitap basariyla eklendi!";
	Sleep(2000);
	talepYonet(basdugum);	
	}
}
// Talep yönetme menü fonksiyonu
void talepYonet(book* basdugum){
	system("cls");
	cout << "PERSONEL" << endl;
	cout << "1. Talepleri goruntule (Oncelik sirasi)" << endl;
	cout << "2. Oncelik sirasindaki ilk kitabi sisteme ekle" << endl;
	cout << "0. Onceki menu" << endl;
	cin >> menuSecim;
	switch(menuSecim){
	case 0:
	personelIslemler();
	break;
	case 1:
	talepYazdir();
	break;
	case 2:
	talepEkle(basdugum);
	break;
	}
}
/// Tek yönlü dairesel listeden ağaca aktarma fonksiyonu
void tekDaireselToSureTree(stackBook* stackBas, tree*& treeSure) {
    if (stackBas == nullptr) return;

    stackBook* temp = stackBas;
    bool ilkDonus = true;

    do {
        // ID zaten ağaçta var mı kontrolü
        tree* current = treeSure;
        bool zatenVar = false;

        while (current != nullptr) {
            if (temp->id == current->id) {
                zatenVar = true;
                break;
            }

            if (temp->oduncSure < current->oduncSure)
                current = current->left;
            else
                current = current->right;
        }

        // Varsa geç
        if (zatenVar) {
            temp = temp->next;
            ilkDonus = false;
            continue;
        }

        // Yeni düğüm oluştur
        tree* yeni = new tree{
            temp->ad, temp->id, temp->oduncTime, temp->oduncSure, temp->year,
            temp->yerli, temp->turkce,temp->pagecount, temp->kategori, nullptr, nullptr
        };

        if (treeSure == nullptr) {
            treeSure = yeni;
        } else {
            current = treeSure;
            while (true) {
                if (yeni->oduncSure < current->oduncSure) {
                    if (current->left == nullptr) {
                        current->left = yeni;
                        break;
                    } else {
                        current = current->left;
                    }
                } else {
                    if (current->right == nullptr) {
                        current->right = yeni;
                        break;
                    } else {
                        current = current->right;
                    }
                }
            }
        }

        temp = temp->next;
        ilkDonus = false;
    } while (temp != stackBas || ilkDonus);
}
// Ağaç yazdırma fonksiyonu
void agacInOrder30Alti(tree* kok) {
    if (kok == nullptr) return;
    agacInOrder30Alti(kok->left);
    if (kok->oduncSure < 30) {
        cout << kok->ad << " (" << kok->oduncSure << " gun)" << endl;
    }
    agacInOrder30Alti(kok->right);
}
// Ağaç yazdırma fonksiyonu
void agacInOrder30Ustu(tree* kok) {
    if (kok == nullptr) return;
    agacInOrder30Ustu(kok->left);
    if (kok->oduncSure >= 30) {
        cout << kok->ad << " (" << kok->oduncSure << " gun)" << endl;
    }
    agacInOrder30Ustu(kok->right);
}
/// Tek yönlü dairesel listeden ağaca aktarma fonksiyonu
void tekDaireselToBasimTree(stackBook* stackBas, tree*& treeBasim) {
    if (stackBas == nullptr) return;

    stackBook* temp = stackBas;
    bool ilkDonus = true;

    do {
        // ID zaten ağaçta var mı kontrolü
        tree* current = treeBasim;
        bool zatenVar = false;

        while (current != nullptr) {
            if (temp->id == current->id) {
                zatenVar = true;
                break;
            }

            if (temp->year < current->year)
                current = current->left;
            else
                current = current->right;
        }

        // Varsa geç
        if (zatenVar) {
            temp = temp->next;
            ilkDonus = false;
            continue;
        }

        // Yeni düğüm oluştur
        tree* yeni = new tree{
            temp->ad, temp->id, temp->oduncTime, temp->oduncSure, temp->year,
            temp->yerli, temp->turkce,temp->pagecount,temp->kategori, nullptr, nullptr
        };

        if (treeBasim == nullptr) {
            treeBasim = yeni;
        } else {
            current = treeBasim;
            while (true) {
                if (yeni->year < current->year) {
                    if (current->left == nullptr) {
                        current->left = yeni;
                        break;
                    } else {
                        current = current->left;
                    }
                } else {
                    if (current->right == nullptr) {
                        current->right = yeni;
                        break;
                    } else {
                        current = current->right;
                    }
                }
            }
        }

        temp = temp->next;
        ilkDonus = false;
    } while (temp != stackBas || ilkDonus);
}
// Ağaç yazdırma fonksiyonu
void agacInOrder1950Oncesi(tree* kok) {
    if (kok == nullptr) return;
    agacInOrder1950Oncesi(kok->left);
    if (kok->year <= 1950) {
        cout << kok->ad << " (" << kok->year << ")" << endl;
    }
    agacInOrder1950Oncesi(kok->right);
}
// Ağaç yazdırma fonksiyonu
void agacInOrder1950Sonrasi(tree* kok) {
    if (kok == nullptr) return;
    agacInOrder1950Sonrasi(kok->left);
    if (kok->year > 1950) {
        cout << kok->ad << " (" << kok->year << ")" << endl;
    }
    agacInOrder1950Sonrasi(kok->right);
}
// Ağaç yazdırma fonksiyonu
void yazdir1950OnceVe30Ustu(tree* kok) {
    if (kok == nullptr) return;

    yazdir1950OnceVe30Ustu(kok->left);

    if (kok->year < 1950 && kok->oduncSure >= 30) {
        cout << kok->ad << " | Yıl: " << kok->year << " | Süre: " << kok->oduncSure << " gün" << endl;
    }

    yazdir1950OnceVe30Ustu(kok->right);
}
// Hash tablosu filtreleyerek yazma fonksiyonu
void puanOrtalamasiYuksekKitaplariListele() {
    if (kitapPuanTablosu.empty()) {
        cout << "Henuz puanlanmis kitap yok.\n";
        return;
    }

    cout << "\nOrtalamasi 4 ve uzeri olan kitaplar:\n";
    cout << "-------------------------------------\n";
    for (const auto& it : kitapPuanTablosu) {
        int id = it.first;
        const PuanKayit& kayit = it.second;

        if (kayit.puanSayisi > 0) {
            double ort = static_cast<double>(kayit.toplamPuan) / kayit.puanSayisi;
            if (ort >= 4.0) {
                cout << "Kitap Adi   : " << kayit.kitapAdi << endl;
                cout << "Kitap ID    : " << id << endl;
                cout << "Ortalama    : " << fixed << setprecision(2) << ort << endl;
                cout << "-------------------------------------\n";
            }
        }
    }
}
// Raporlama menü fonksiyonu
void raporlamaMenu() {
    int secim = 0;
	int a=1;
	system("cls");
        cout << "RAPORLAMA MENUSU" << endl;
        cout << "1. Odunc suresi 30 gunden AZ olan kitaplar(Agac)" << endl;
        cout << "2. Odunc suresi 30 gunden COK olan kitaplar(Agac)" << endl;
        cout << "3. Basim yili 1950'den ONCE olan kitaplar(Agac)" << endl;
        cout << "4. Basim yili 1950'den SONRA olan kitaplar(Agac)" << endl;
        cout << "5. Basim yili 1950'den SONRA olan kitaplar(Agac)" << endl;
        cout << "6. Odunc alinan kitaplari yazdir(tek yonlu dairesel)" << endl;
        cout << "7. Odunc alinan kitaplardan puan ortalamasi 4 uzeri olanlari yazdir(Hash)" << endl;
        cout << "0. Geri don" << endl;
        cout << "Secim: ";
        cin >> secim;

        switch (secim) {
            case 1:
                cout << "\n--- 30 Gun ALTINDA ---\n";
				agacInOrder30Alti(treeSure);
				cout << "0. Onceki menu" << endl;
				cin >> a;
				if(a == 0){raporlamaMenu();}
                break;
            case 2:
                cout << "\n--- 30 Gun USTUNDE ---\n";
                agacInOrder30Ustu(treeSure);
				cout << "0. Onceki menu" << endl;
				cin >> a;
				if(a == 0){raporlamaMenu();}
                break;
            case 3:
                cout << "\n--- 1950 ONCESI ---\n";
                agacInOrder1950Oncesi(treeBasim);
				cout << "0. Onceki menu" << endl;
				cin >> a;
				if(a == 0){raporlamaMenu();}
                break;
            case 4:
                cout << "\n--- 1950 SONRASI ---\n";
                agacInOrder1950Sonrasi(treeBasim);
				cout << "0. Onceki menu" << endl;
				cin >> a;
				if(a == 0){raporlamaMenu();}
                break;
			case 5:
                cout << "\n--- 1950 ONCESI VE 30 GUN USTU ---\n";
                yazdir1950OnceVe30Ustu(treeSure);
				cout << "0. Onceki menu" << endl;
				cin >> a;
				if(a == 0){raporlamaMenu();}
                break;
			case 6:
				yazdirOduncTD(stackBas);
				break;
			case 7:
				puanOrtalamasiYuksekKitaplariListele();
				break;
            case 0:
                oduncIslemler();
            default:
                cout << "Hatali secim!\n";
		break;
		}
}
// Ödünç işlemler menü fonksiyonu
void oduncIslemler(){
	system("cls");
	cout << "PERSONEL" << endl;	
	stackToTekDairesel(stackBas, stackBasIade, stackSon, stackSonIade);
	tekDaireselToSureTree(stackBas, treeSure);
	tekDaireselToBasimTree(stackBas, treeBasim);
	int menuSecim;
	if(stackBas == nullptr && stackBasIade == nullptr){
		cout << "Henuz hic kitap odunc alinmamis veya iade edilmemis. Onceki menuye yonlendiriliyorsunuz..." << endl;
		Sleep(3000);
		personelIslemler();
	}
	cout << "1. Odunc alinan kitaplarin raporunu olustur" << endl;
	cout << "2. Iade edilen kitaplarin raporunu olustur(Tek yonlu dairesel)" << endl;
	cout << "0. Onceki menu" << endl;
	cin >> menuSecim;
	switch(menuSecim){
	case 1:
	raporlamaMenu();
		break;
	case 2:
	yazdirIadeTD(stackBasIade);
		break;
	case 0:
	personelIslemler();
		break;
	default:
	cout << "Hatali secim!" << endl;
	Sleep(1500);
	oduncIslemler();
		break;
	}
}
