//Geliştirici : Yasin Durak
//Öğrenci No : B241200067
//Ödev Konusu : Kitap Yönetim Sistemi
//kullanici.cpp
#include "kullanici.h"
#include "main.h"
#include <iostream>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>
using namespace std;
//  Baş düğüm tanımlamaları, stack tanımlamaları, queue tanımlamaları
dcBook* koleksiyonBas = nullptr;
stack<stackBook> oduncKitaplar;
stack<stackBook> iadeKitaplar;
queue<string> talepKitap;
queue<string> oncelikliTalepKitap;
// Fonksiyonlarda kullanmak üzere oluşturulan değişkenler
bool koleksiyonVar = false;
string koleksiyonAdi = "";
int menuSecimK;
int ID;
string eklenecekYorum;
// Fonksiyon prototipi
void stacktenHashTablosunaAktar(stack<stackBook>);

// Yorum ekleme fonksiyonu
void yorumEkle(dcBook* head){
	system("cls");
    dcBook* temp = head;
	cout << "Yorum eklemek istediginiz kitap ID'si: ";
	cin >> ID;
	// Dairesel çift yönlü listede yorum eklenecek kitabı bulmak için gerekli döngü
	do {
	if(temp -> id == ID){
	cout << "Eklemek istediginiz yorum: ";
	cin.ignore();
	getline(cin, eklenecekYorum);
	temp -> comment = eklenecekYorum; // Bulunan kitaba girilen yorumun eklenmesi
	cout << "Yorum eklendi. Onceki menuye yonlendiriliyorsunuz..." << endl;
	Sleep(2000); // 2 saniye beklendikten sonra önceki menüye yönlendirme kısmı
    kitapYonetimK(head, tail,basdugum, stackBas);
    return;
	}
    temp = temp->next;
    } while (temp != head);
	cout << "Girilen ID bulunamadi! tekrar dene!" << endl;
	yorumEkle(head); // yanlış id girilmesi durumunda fonksiyonun baştan çalışması
}
// Yorum görme fonksiyonu
void yorumGor(dcBook* head){
	system("cls");
    dcBook* temp = head;
	cout << "Yorumu gormek istediginiz kitap ID'si: ";
	cin >> ID;
	// Alınan id'ye göre dairesel çift yönlü listede kitabı bulma
	do {
	if(temp -> id == ID){
	cout << "Kitap adi: " << temp -> ad << " Kitap yorumu: " << temp -> comment << endl; // Bulunan kitabı yazdırma
	int a=1;
	cout << "0. Onceki menu" << endl;
	cin >> a;
	if(a == 0){kitapYonetimK(head, tail,basdugum, stackBas);} // 0 tuşlandığında önceki menüye yönlendirme
    return;
	}
    temp = temp->next;
    } while (temp != head);
	cout << "Girilen ID bulunamadi! tekrar dene!" << endl;
	yorumGor(head); // Bulunamaması durumunda fonksiyonun kendini çağırması
}
// Koleksiyon oluşturma fonksiyonu
void koleksiyonOlustur(dcBook* head) {
    system("cls");
	// En fazla bir koleksiyon oluşturulacağı için önceden oluşturulma durumunu kontrol etme
    if (koleksiyonVar) {
        cout << "Zaten '" << koleksiyonAdi << "' adinda bir koleksiyonunuz var. Onceki menuye yonlendiriliyorsunuz..." << endl;
        Sleep(2000);
        kitapYonetimK(head, tail,basdugum, stackBas);
        return;
    }

    cout << "Koleksiyon ismi girin: ";
    cin.ignore();
    getline(cin, koleksiyonAdi);

    int id;
    cout << "Koleksiyonu baslatmak icin kitap ID girin: ";
    cin >> id;

    dcBook* temp = head;
    bool bulundu = false;

	// Dairesel çift yönlü listenin boş olması durumu
    if (temp == nullptr) {
        cout << "Kitap listesi bos!" << endl;
        Sleep(2000);
        kitapYonetimK(head, tail,basdugum, stackBas);
        return;
    }

	// Dairesel çift yönlü listede kitabı arama
    do {
        if (temp->id == id) {
		// Bulunan kitabı koleksiyon oluşturup baş düğüm olarak belirleme
            koleksiyonBas = new dcBook(*temp);
            koleksiyonBas->next = nullptr;
            koleksiyonBas->prev = nullptr;
            koleksiyonVar = true;
            bulundu = true;

            cout << "Koleksiyon '" << koleksiyonAdi << "' olusturuldu. Onceki menuye yonlendiriliyorsunuz..." << endl;
            Sleep(2000);
            kitapYonetimK(head, tail,basdugum, stackBas);
            return;
        }
        temp = temp->next;
    } while (temp != head);  // Dairesel liste

    // Kitap bulunamadıysa
    if (!bulundu) {
        cout << "Kitap ID bulunamadi. Tekrar dene..." << endl;
        Sleep(2000);
        koleksiyonOlustur(head);
    }
}
// Koleksiyona kitap ekleme fonksiyonu
void kolKitapEkle(dcBook* head) {
	system("cls");
	// Koleksiyon olmaması durumunda önceki menüye yönlendirme
    if (!koleksiyonVar) {
        cout << "Once bir koleksiyon olusturmaniz gerekiyor." << endl;
        Sleep(2000);
        kitapYonetimK(head, tail,basdugum, stackBas);
        return;
    }

    int id;
    cout << "Koleksiyona kitap eklemek icin kitap ID girin: ";
    cin >> id;

    // Aynı kitap koleksiyonda var mı kontrolü
    dcBook* kontrol = koleksiyonBas;
    while (kontrol != nullptr) {
        if (kontrol->id == id) {
            cout << "Bu kitap zaten koleksiyonda mevcut!" << endl;
            Sleep(2000);
            kitapYonetimK(head, tail,basdugum, stackBas);
            return;
        }
        kontrol = kontrol->next;
    }

    // Çift yönlü listede kitabı ara
    dcBook* temp = head;
    bool bulundu = false;

    do {
        if (temp->id == id) {
            dcBook* yeniKitap = new dcBook(*temp);
            yeniKitap->next = nullptr;
            yeniKitap->prev = nullptr;

            // Koleksiyon sonuna ekleme
            dcBook* koleksiyonTemp = koleksiyonBas;
            while (koleksiyonTemp->next != nullptr) {
                koleksiyonTemp = koleksiyonTemp->next;
            }
            koleksiyonTemp->next = yeniKitap;

            cout << yeniKitap->ad << " koleksiyona eklendi." << endl;
            Sleep(2000);
            kitapYonetimK(head, tail, basdugum, stackBas);
            return;
        }
        temp = temp->next;
    } while (temp != head);

    // Kitap bulunamazsa
    cout << "Kitap ID bulunamadi. Tekrar deneyin." << endl;
    Sleep(2000);
    kolKitapEkle(head);
}
// Koleksiyondan kitap silme fonksiyonu
void kolKitapSil(dcBook* head) {
	system("cls");
	// Koleksiyon olmaması durumu
    if (koleksiyonBas == nullptr) {
        cout << "Koleksiyon bos!" << endl;
        Sleep(2000);
        kitapYonetimK(head, tail,basdugum, stackBas);
    }

    int id;
    cout << "Silmek icin kitap ID'sini girin: ";
    cin >> id;

    dcBook* temp = koleksiyonBas;
    dcBook* prev = nullptr;

    // Koleksiyonun başını kontrol et
    if (temp != nullptr && temp->id == id) {
        koleksiyonBas = temp->next;  // Baş düğümü bir sonraki elemana yönlendir
        delete temp;  // Baş düğüm silindi
        cout << "Kitap silindi." << endl;
        Sleep(2000);
        kitapYonetimK(head, tail,basdugum, stackBas);
    }

    // Listede ID'yi arıyoruz
    while (temp != nullptr && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    // ID bulunmazsa
    if (temp == nullptr) {
        cout << "Kitap bulunamadi!" << endl;
        Sleep(2000);
        kolKitapSil(head);  // Tekrar dene
    }

    // Kitap bulundu, sil
    prev->next = temp->next;
    delete temp;  // Kitap silindi
    cout << "Kitap silindi." << endl;
    Sleep(2000);
    kitapYonetimK(head, tail,basdugum, stackBas);
}
// Koleksiyonun hepsini yazdırma fonksiyonu
void koleksiyonListele(dcBook* koleksiyonBas) {
	system("cls");
	// Koleksiyon olmaması durumu
    if (koleksiyonBas == nullptr) {
        cout << "Koleksiyon bos, listeleme yapilamiyor!" << endl;
        Sleep(2000);
        kitapYonetimK(head, tail,basdugum, stackBas);  // Önceki menüye geri dön
    }

    dcBook* temp = koleksiyonBas;
    cout << "Koleksiyonunuzdaki Kitaplar:" << endl;
	// Koleksşyonu gezerek her elemanı yazdırma
    while (temp != nullptr) {
        cout << "Kitap Adi: " << temp->ad << " | Kitap ID: " << temp->id;
        cout << " | Okundu: " << (temp->damaged ? "Okunmadi" : "Okundu") << endl;
        temp = temp->next;
    }
	int a=1;
	cout << "0. Onceki menu" << endl;
	cin >> a;
	if(a == 0){kitapYonetimK(head, tail,basdugum, stackBas);}
}
// Kitabın okundu bilgisini güncelleme fonksiyonu
void kitapDurumGuncelle(dcBook* koleksiyonBas) {
	system("cls");
	// Koleksiyon olmaması durumu
    if (koleksiyonBas == nullptr) {
        cout << "Koleksiyon bos, kitap durumu guncellenemez!" << endl;
        Sleep(2000);
        kitapYonetimK(head, tail, basdugum,  stackBas);  // Önceki menüye geri dön
    }

    int id;
    cout << "Durumunu guncellemek istediginiz kitabin ID'sini girin: ";
    cin >> id;

    dcBook* temp = koleksiyonBas;
    bool bulunamadi = true;
	// Kitabı koleksiyonda arama 
    while (temp != nullptr) {
        if (temp->id == id) {
            bulunamadi = false;
            // Okundu/Okunmadı durumunu değiştiriyoruz
            if (temp->damaged) {
                temp->damaged = false;  // Kitap okundu
                cout << "Kitap OKUNDU olarak isaretlendi." << endl;
            } else {
                temp->damaged = true;  // Kitap okunmadı
                cout << "Kitap OKUNMADI olarak isaretlendi." << endl;
            }
        }
        temp = temp->next;
    }
	// girilen kitabın bulunamaması
    if (bulunamadi) {
        cout << "Kitap ID bulunamadi. Tekrar deneyin." << endl;
    }
	int a=1;
	cout << "0. Onceki menu" << endl;
	cin >> a;
	if(a == 0){kitapYonetimK(head, tail, basdugum, stackBas);}
}
// Kitap yönetim menü fonksiyonu
void kitapYonetimK(dcBook* head, dcBook* tail,book* basdugum, stackBook* stackBas){
	system("cls");
	cout << "KULLANICI" << endl;
    cout << "1. ID'ye gore kitaba yorum yap" << endl;
    cout << "2. ID'ye gore yorumlari gor" << endl;
    cout << "3. Koleksiyon olustur(en fazla 1 koleksiyonunuz olabilir)" << endl;
    cout << "4. Koleksiyona kitap ekle" << endl;
    cout << "5. Koleksiyondaki kitaplari okundu/okunmadi olarak isaretle" << endl;
    cout << "6. ID'ye gore koleksiyondan kitap sil" << endl;
    cout << "7. Koleksiyondaki kitaplari listele" << endl;
    cout << "0. Onceki menu" << endl;
	cin >> menuSecimK;

    switch (menuSecimK) {
        case 1:
			yorumEkle(head); // Yorum ekleme fonksiyonu çağırılması
            break;
        case 2:
			yorumGor(head); // Yorum görme fonksiyonu çağırılması
            break;
        case 3:
			koleksiyonOlustur(head); // Koleksiyon oluşturma fonksiyonu çağırılması
            break;
        case 4:
			kolKitapEkle(head); // Koleksiyona kitap ekleme fonksiyonu çağırılması
            break;
        case 5:
			kitapDurumGuncelle(koleksiyonBas); // Koleksiyondaki kitabın okundu bilgisini güncelleme fonksiyonu çağırılması
            break;
        case 6:
			kolKitapSil(head); // Koleksiyondan kitap silme fonksiyonu çağırılması
            break;
        case 7:
			koleksiyonListele(koleksiyonBas); // Koleksiyonu yazdırma fonksiyonu çağırılması
            break;
        case 0:
			kullaniciIslemler(head, tail,basdugum, stackBas); // Önceki menü fonksiyonu çağırılması
            break;
        default:
            cout << "Hatali secim!" << endl;
            break;
    }
	
}
// Ödünç alma fonksiyonu
void oduncAl(dcBook* head, dcBook* tail,book* basdugum, stackBook* stackBas) {
	system("cls");
	stackBook odunc; // stackBook tipinde bir değişken oluşturma
	dcBook* temp = head;
	//cout << head << endl;
	// Dairesel çift yönlü listenin boş olma durumu
	if (head == nullptr) {
		cout << "Kitap listesi bos!" << endl;
		Sleep(2000);
		oduncAlma(head, tail, basdugum, stackBas);
	}
	int id;
	int sure;
	bool basarili = false;
	cout << "Odunc almak istediginiz kitap ID'si: ";
	cin >> id;
	// ID ile kitabı listede arama
	do {
		if (temp->id == id) {
		// odunc isimli değişkene bulunan kitabın bilgilerini verip stack'e ekleme işlemi
		cout << "'" << temp->ad << "' isimli kitabi kac gun odunc alma istiyorsunuz?: ";
		cin >> sure;
		odunc.ad = temp->ad;
		odunc.id = temp->id;
		odunc.year = temp->year;
		odunc.oduncTime = time(0);
		odunc.iadeTime = time(nullptr);
		odunc.oduncSure = sure;
		odunc.yerli = temp->yerli;
		odunc.turkce = temp->turkce;
		odunc.pagecount = temp->pagecount;
		odunc.kategori = temp->kategori;
		oduncKitaplar.push(odunc);
		cout << "'" << temp->ad << "' isimli kitap odunc alindi..." << endl;
		basarili = true;
		Sleep(2000);
		oduncAlma(head, tail,basdugum, stackBas);
		}
		temp = temp->next;
	} while (temp != head);
	// Kitap bulunamaması durumu
	if (!basarili) {
		cout << "Kitap bulunamadi. Onceki menuye yonlendiriliyorsunuz..." << endl;
		Sleep(1500);
		oduncAlma(head, tail, basdugum, stackBas);
	}
}
// Ödünç listeleme fonksiyonu
void oduncListele(dcBook* head) {
	system("cls");
	// stack boş olma durumu
    if (oduncKitaplar.empty()) {
        cout << "Odunc alinan kitap yok." << endl;
		Sleep(2000);
		oduncAlma(head, tail,basdugum, stackBas);
    }

    stack<stackBook> gecici = oduncKitaplar; // stack bozulmaması için kopyalama
    cout << "Odunc Alinan Kitaplar:" << endl;
	// stack yazdırma
    while (!gecici.empty()) {
        stackBook kitap = gecici.top();
        cout << "- " << kitap.ad << " (ID: " << kitap.id << ")" << endl;
        gecici.pop();
    }
	int a=1;
	cout << "0. Onceki menu" << endl;
	cin >> a;
	if(a == 0){oduncAlma(head, tail,basdugum, stackBas);}
}
// Ödünç kitabın iade stack'e eklenmesi fonksiyonu
void kitapIadeEt(dcBook* head) {
	system("cls");
	// Ödünç kitap olmaması durumu
    if ( oduncKitaplar.empty()) {
        cout << "Iade edilecek kitap bulunamadi. Odunc listesi bos. Onceki menuye yonlendiriliyorsunuz..." << endl;
		Sleep(2000);
		oduncAlma(head, tail,basdugum, stackBas);
    }
	// Ödünç alınan son kitabın iade edilmesi
    stackBook kitap = oduncKitaplar.top();
    oduncKitaplar.pop();
	kitap.iadeTime = time(0);
    iadeKitaplar.push(kitap);

    cout << "'" << kitap.ad << "' isimli kitap iade edildi. Onceki menuye yonlendiriliyorsunuz..." << endl;
	Sleep(2000);
	oduncAlma(head, tail,basdugum, stackBas);
}
// İade stack yazdırma fonksiyonu
void iadeListesiGoster(dcBook* head) {
	system("cls");
    if (iadeKitaplar.empty()) {
        cout << "Henuz hic kitap iade edilmedi." << endl;
		Sleep(2000);
		oduncAlma(head, tail,basdugum, stackBas);
    }

    stack<stackBook> gecici = iadeKitaplar;
    cout << "Iade Edilen Kitaplar:" << endl;

    while (!gecici.empty()) {
        stackBook kitap = gecici.top();
        cout << "- " << kitap.ad << " (ID: " << kitap.id << ")" << endl;
        gecici.pop();
    }
	int a=1;
	cout << "0. Onceki menu" << endl;
	cin >> a;
	if(a == 0){oduncAlma(head, tail,basdugum, stackBas);}
}
// Stack'den Ağaca aktarma fonksiyonu
void stackToYayinTree(stack<stackBook>& oduncKitaplar, tree*& treeYayin) {
    stack<stackBook> tempStack = oduncKitaplar;  // Orijinali bozmamak için kopyaladık

    while (!tempStack.empty()) {
        stackBook kitap = tempStack.top();  // stack'in üst elemanını al
        tempStack.pop();  // üst elemanı çıkart

        // ID kontrolü: ağaca zaten ekli mi?
        tree* current = treeYayin;
        bool zatenVar = false;

        while (current != nullptr) {
            if (kitap.id == current->id) {
                zatenVar = true;
                break;
            }

            // Yerli bilgisine göre yönlendirme
            if (kitap.yerli && current->left != nullptr) {
                current = current->left;
            }
            else if (!kitap.yerli && current->right != nullptr) {
                current = current->right;
            }
            else {
                break;
            }
        }

        // Varsa geç, yoksa ağaca ekle
        if (zatenVar) continue;

        // Yeni düğüm oluştur
        tree* yeni = new tree{
            kitap.ad,
            kitap.id,
            kitap.oduncTime,
            kitap.oduncSure,
            kitap.year,
            kitap.yerli,
            kitap.turkce,
			kitap.pagecount,
			kitap.kategori,
            nullptr,
            nullptr
        };

        // Ağacın kökü boşsa yeni düğüm kök olur
        if (treeYayin == nullptr) {
            treeYayin = yeni;
        } else {
            current = treeYayin;
            while (true) {
                if (kitap.yerli) {
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
    }
}
// Ağaç yazdırma
void yayinAgacYazdir(tree* kok) {
    if (kok == nullptr) return;

    // Önce yerli olan (left tarafı) yaz
    if (kok->yerli) {
        yayinAgacYazdir(kok->left);
        cout << kok->ad << " | ID: " << kok->id << " | Yerli: " << (kok->yerli ? "Evet" : "Hayir") << endl;
        yayinAgacYazdir(kok->right);
    }
    // Sonra yerli olmayan (right tarafı) yaz
    else {
        yayinAgacYazdir(kok->left);
        yayinAgacYazdir(kok->right);
        cout << kok->ad << " | ID: " << kok->id << " | Yerli: " << (kok->yerli ? "Evet" : "Hayir") << endl;
    }
}
// Stack'den Ağaca aktarma fonksiyonu
void stackToDilTree(stack<stackBook>& oduncKitaplar, tree*& treeDil) {
    stack<stackBook> tempStack = oduncKitaplar;  // Stack'in kopyası, orijinali bozulmaz

    while (!tempStack.empty()) {
        stackBook kitap = tempStack.top();
        tempStack.pop();

        // ID zaten var mı kontrolü
        tree* current = treeDil;
        bool zatenVar = false;

        while (current != nullptr) {
            if (kitap.id == current->id) {
                zatenVar = true;
                break;
            }

            if (kitap.turkce && current->left != nullptr) {
                current = current->left;
            } else if (!kitap.turkce && current->right != nullptr) {
                current = current->right;
            } else {
                break;
            }
        }

        if (zatenVar) continue;

        // Yeni düğüm oluştur
        tree* yeni = new tree{
            kitap.ad,
            kitap.id,
            kitap.oduncTime,
            kitap.oduncSure,
            kitap.year,
            kitap.yerli,
            kitap.turkce,
			kitap.pagecount,
			kitap.kategori,
            nullptr,
            nullptr
        };

        if (treeDil == nullptr) {
            treeDil = yeni;
        } else {
            current = treeDil;
            while (true) {
                if (kitap.turkce) {
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
    }
}
// Ağaç yazdırma
void dilAgacYazdir(tree* kok) {
    if (kok == nullptr) return;

    // Önce Türkçe olanlar (sol taraf)
    if (kok->turkce) {
        dilAgacYazdir(kok->left);
        cout << kok->ad << " | ID: " << kok->id << " | Turkce: Evet" << endl;
        dilAgacYazdir(kok->right);
    }
    // Sonra yabancı olanlar (sağ taraf)
    else {
        dilAgacYazdir(kok->left);
        dilAgacYazdir(kok->right);
        cout << kok->ad << " | ID: " << kok->id << " | Turkce: Hayir" << endl;
    }
}
// Stack'den Ağaca aktarma fonksiyonu
void stackToSayfaTree(stack<stackBook>& oduncKitaplar, tree*& treeSayfa) {
    stack<stackBook> tempStack = oduncKitaplar;

    while (!tempStack.empty()) {
        stackBook kitap = tempStack.top();
        tempStack.pop();

        // ID kontrolü: aynı ID varsa ekleme
        tree* current = treeSayfa;
        bool zatenVar = false;

        while (current != nullptr) {
            if (kitap.id == current->id) {
                zatenVar = true;
                break;
            }

            if (kitap.pagecount < current->pagecount)
                current = current->left;
            else
                current = current->right;
        }

        if (zatenVar) continue;

        // Yeni düğüm oluştur
        tree* yeni = new tree{
            kitap.ad,
            kitap.id,
            kitap.oduncTime,
            kitap.oduncSure,
            kitap.year,
            kitap.yerli,
            kitap.turkce,
			kitap.pagecount,
			kitap.kategori,
            nullptr,
            nullptr
        };
        yeni->pagecount = kitap.pagecount;  // sayfa alanını da atadık

        if (treeSayfa == nullptr) {
            treeSayfa = yeni;
        } else {
            current = treeSayfa;
            while (true) {
                if (kitap.pagecount < current->pagecount) {
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
    }
}
// Ağaç yazdırma
void yazdir1000denAz(tree* kok) {
    if (kok == nullptr) return;

    yazdir1000denAz(kok->left);
    if (kok->pagecount < 1000) {
        cout << kok->ad << " | Sayfa: " << kok->pagecount << endl;
    }
    yazdir1000denAz(kok->right);
}
// Ağaç yazdırma
void yazdir1000denCok(tree* kok) {
    if (kok == nullptr) return;

    yazdir1000denCok(kok->left);
    if (kok->pagecount >= 1000) {
        cout << kok->ad << " | Sayfa: " << kok->pagecount << endl;
    }
    yazdir1000denCok(kok->right);
}
// Stack'den Hash tablosuna aktarma fonksiyonu
void stacktenHashTablosunaAktar(stack<stackBook> oduncKitaplar) {
    stack<stackBook> gecici = oduncKitaplar;

    while (!gecici.empty()) {
        stackBook kitap = gecici.top();
        gecici.pop();

        // Eğer daha önce eklenmemişse
        if (kitapPuanTablosu.find(kitap.id) == kitapPuanTablosu.end()) {
            kitapPuanTablosu[kitap.id] = {kitap.ad, 0, 0};  // kitap->ad değil, kitap.ad
        }
    }
}
// Hash tablosuna puan kaydetme fonksiyonu
void kitaplariPuanla() {
	system("cls");
    if (kitapPuanTablosu.empty()) {
        cout << "Henuz puanlanacak kitap yok." << endl;
        return;
    }

    for (auto it = kitapPuanTablosu.begin(); it != kitapPuanTablosu.end(); ++it) {
        int id = it->first;
        PuanKayit& kayit = it->second;

        cout << "Kitap: " << kayit.kitapAdi << " (ID: " << id << ") -> Puan (1-5): ";
        int puan;
        cin >> puan;

        while (puan < 1 || puan > 5) {
            cout << "Gecersiz puan. Lutfen 1 ile 5 arasında girin: ";
            cin >> puan;
        }

        kayit.toplamPuan += puan;
        kayit.puanSayisi += 1;
    }
	
}
// Hash tablosunu yazdırma fonksiyonu
void hashTablosunuListele() {
	system("cls");
    if (kitapPuanTablosu.empty()) {
        cout << "Hash tablosu bos. Henüz hic kitap puanlanmamis ya da eklenmemis.\n";
        return;
    }

    cout << "Hash Tablosundaki Kitaplar ve Puan Bilgileri:\n";
    cout << "-----------------------------------------------------\n";

    for (auto it = kitapPuanTablosu.begin(); it != kitapPuanTablosu.end(); ++it) {
        int id = it->first;
        const PuanKayit& kayit = it->second;

        cout << "Kitap Adi   : " << kayit.kitapAdi << endl;
        cout << "Kitap ID    : " << id << endl;
        cout << "Puan Sayisi : " << kayit.puanSayisi << endl;
        cout << "Toplam Puan : " << kayit.toplamPuan << endl;
        cout << "Ortalama    : ";
        if (kayit.puanSayisi == 0) {
            cout << "Henuz puanlanmamıs.";
        } else {
            cout << fixed << setprecision(2) << kayit.ortalama();
        }
        cout << endl << "-----------------------------------------------------\n";
    }
}
// Kategori değerine göre kitap önerme fonksiyonu
void kitapOner(dcBook* head){
	system("cls");
	stack<stackBook> gecici = oduncKitaplar;
	dcBook* temp = head;
    while (!gecici.empty()) {
        stackBook kitap = gecici.top();
        gecici.pop();
		cout << "Odunc alinan kitap: " << kitap.ad << endl;
    	do {
		if (temp->kategori == kitap.kategori && temp->id != kitap.id) {
		cout <<"Benzer kitap: " << temp->ad << " Kategorileri: " << kitap.kategori << endl;
		}
		temp = temp->next;
	} while (temp != head);
	cout << "***********************************" << endl;
    }
}
// Filtreleme menü fonksiyonu
void oduncFiltre(dcBook* head){
	if(oduncKitaplar.empty()){
		cout << "Henuz hic kitap odunc alinmamis. Onceki menuye yonlendiriliyorsunuz..." << endl;
		Sleep(2000);
		oduncAlma(head, tail, basdugum, stackBas);
	}
	stackToYayinTree(oduncKitaplar, treeYayin);
	stackToDilTree(oduncKitaplar, treeDil);
	stackToSayfaTree(oduncKitaplar, treeSayfa);
	stacktenHashTablosunaAktar(oduncKitaplar);
	int a = 1;
	system("cls");
	cout << "KULLANICI" << endl;
	cout << "1. Yayin evi durumuna gore filtrele" << endl;
	cout << "2. Dile gore filtele" << endl;
	cout << "3. Sayfa sayisi 1000'den az olanlari goster" << endl;
	cout << "4. Sayfa sayisi 1000'den cok olanlari goster" << endl;
	cout << "5. Odunc alinan kitaplari paunla" << endl;
	cout << "6. Odunc alinan kitaplari paun durumlari ile listele" << endl;
	cout << "7. Odunc alinan kitaplara benzer kitaplar oner" << endl;
	cout << "0. onceki menu" << endl;
	cin >> menuSecimK;
	switch(menuSecimK){
	case 1:
	cout << "YAYIN EVI DURUMUNA GORE YERLIDEN YABANCIYA" << endl;
	yayinAgacYazdir(treeYayin);
	cout << "0. Onceki menu" << endl;
	cin >> a;
	if(a == 0){oduncFiltre(head);}
	break;
	case 2:
	cout << "DIL DURUMUNA GORE YERLIDEN YABANCIYA" << endl;
	dilAgacYazdir(treeDil);
	cout << "0. Onceki menu" << endl;
	cin >> a;
	if(a == 0){oduncFiltre(head);}
	break;
	case 3:
	cout << "SAYFA SAYISINA GORE 1000'DEN AZ" << endl;
	yazdir1000denAz(treeSayfa);
	cout << "0. Onceki menu" << endl;
	cin >> a;
	if(a == 0){oduncFiltre(head);}
	break;
	case 4:
	cout << "SAYFA SAYISINA GORE 1000'DEN COK" << endl;
	yazdir1000denCok(treeSayfa);
	cout << "0. Onceki menu" << endl;
	cin >> a;
	if(a == 0){oduncFiltre(head);}
	break;
	case 5:
	kitaplariPuanla();
	cout << "0. Onceki menu" << endl;
	cin >> a;
	if(a == 0){oduncFiltre(head);}
	break;
	case 6:
	hashTablosunuListele();
	cout << "0. Onceki menu" << endl;
	cin >> a;
	if(a == 0){oduncFiltre(head);}
	break;
	case 7:
	kitapOner(head);
	cout << "0. Onceki menu" << endl;
	cin >> a;
	if(a == 0){oduncFiltre(head);}
	break;
	case 0:
	oduncAlma(head, tail, basdugum, stackBas);
	break;
	default:
	oduncAlma(head, tail, basdugum, stackBas);	
	break;
	}
}
// Odunc alma işlemleri menü fonksiyonu
void oduncAlma(dcBook* head, dcBook* tail,book* basdugum, stackBook* stackBas){
	system("cls");
	cout << "KULLANICI" << endl;
	cout << "1. ID'ye gore odunc kitap al" << endl;
	cout << "2. Odunc alinan kitaplari listele" << endl;
	cout << "3. En son odunc alinan kitabi iade et" << endl;
	cout << "4. Iade edilen kitaplari listele" << endl;
	cout << "5. Odunc kitaplari filtrele" << endl;
	cout << "0. Onceki menu" << endl;
	cin >> menuSecimK;
	switch(menuSecimK){
	case 1:
	oduncAl(head, tail,basdugum, stackBas);
	break;
	case 2:
	oduncListele(head);
	break;
	case 3:
	kitapIadeEt(head);
	break;
	case 4:
	iadeListesiGoster(head);
	break;
	case 5:
	oduncFiltre(head);
	break;
	case 0:
	kullaniciIslemler(head, tail,basdugum, stackBas);
	break;
	default:
	kullaniciIslemler(head, tail, basdugum, stackBas);
	break;
	}
}
// Talep işlemleri menü fonksiyonu
void talepIslemler(dcBook* head, dcBook* tail){
	system("cls");
	cout << "KULLANICI" << endl;
	dcBook* temp = head;
	int oncelik;
	string talepAd;
	int b=1;
	cout << "Talep onceliginiz: 1. Normal, 2. Akademik: ";
	cin>>oncelik;
	cout << "Talep edilen kitabin adi: ";
	cin.ignore();
	getline(cin, talepAd);
	do{
	if(temp -> ad == talepAd){
	cout << "Talep edilen kitap zaten mevcut." << endl;
	Sleep(2000);
	talepIslemler(head, tail);
	}
	}while(temp != head);
	switch(oncelik){
	case 1:
	talepKitap.push(talepAd);
	cout << "'" << talepAd << "' isimli kitap normal talep kuyruguna eklendi." << endl;
	Sleep(2000);
	break;
	case 2:
	oncelikliTalepKitap.push(talepAd);
	cout << "'" << talepAd << "' isimli kitap oncelikli talep kuyruguna eklendi." << endl;
	Sleep(2000);
	break;
	default:
	cout << "hatali secim... tekrar dene" << endl;
	Sleep(2000);
	talepIslemler(head, tail);
	break;
	}
	system("cls");
	int secim;
	cout << "1. Talep edilen kitaplari listele" << endl;
	cout << "0. Onceki menu" << endl;
	cin >> secim;
	switch(secim){
	case 0:
	kullaniciIslemler(head, tail,basdugum, stackBas);
	break;
	case 1:{
	system("cls");
	cout << "*** Talep Edilen Kitaplar ***" << endl;
    queue<string> gecici1 = talepKitap;
    queue<string> gecici2 = oncelikliTalepKitap;
    while (!gecici2.empty()) {
        cout << "- " << gecici2.front() << " -" << " * AKADEMIK ONCELIK *" << endl;
        gecici2.pop();
    }
	while (!gecici1.empty()) {
        cout << "- " << gecici1.front() << " -"<< endl;
        gecici1.pop();
    }
	cout << "0. Onceki menu" << endl;
	cin >> b;
	if(b == 0){talepIslemler(head, tail);}
	}
	break;
	}
}