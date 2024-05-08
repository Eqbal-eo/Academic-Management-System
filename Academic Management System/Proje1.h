#ifndef PROJE1_H
#define PROJE1_H

// Ders veri yapısı
typedef struct
{
    char *dersAdi;
    unsigned short int kredi;
    unsigned short int puan;
} Ders;

// Ogrenci veri yapısı
typedef struct
{
    char *ogrAdi;
    char *ogrSoyAdi;
    char *bolumu;
    float ortalama;
    Ders *aldigiDersler;
    int dersSayisi;

} Ogrenci;

// Fonksiyon prototipleri:

// İlgili değerleri alıp bir Ders struct döndüren.
Ders createDers(char *dersAdi, unsigned short int kredi, unsigned short int puan);

// İlgili değerleri alıp bir Ogrenci struct döndüren.
Ogrenci createOgrenci(char *ogrAdi, char *ogrSoyAdi, char *bolumu, float ortalama, Ders *aldigiDersler, int dersSayisi);

// Parametre olarak Ogrenci türünden değişken alıp bilgilerini yazdıran.
void printOgrenci(Ogrenci ogrenci);

//Parametre olarak Ogrenci türünden dinamik bir dizi alıp bilgilerini yazdıran.
void printOgrenciArray(Ogrenci *ogrenciArray, int ogrenciSayisi);

//Parametre olarak aldığı dersAdi değerine göre bir dersin aritmetik ortalamasını hesaplayan.
float calculateMean(char *dersAdi, Ogrenci *ogrenciArray, int arraySize);

//Parametre olarak aldığı dersAdi değerine göre bir dersin standart sapmasını hesaplayan.
float calculateStdDev(char *dersAdi, Ogrenci *ogrenciArray, int arraySize);

//Parametre olarak aldığı Ders türünden iki dersin kovaryansını hesaplayan.
float calculateCovariance(Ders ders1, Ders ders2);

//Parametre olarak aldığı dersAdi değerine göre bir dersin ortalama
//puanından daha yüksek not almış öğrencileri listeleyen.
void listAboveAverage(char *dersAdi, Ogrenci *ogrenciArray, int arraySize);

//Tüm öğrenci bilgilerini bir dosyaya yazan.
void writeOgrenciToFile(Ogrenci *ogrenciArray, int ogrenciSayisi, char *dosyaAdi);

// Dosyadan öğrenci bilgilerini oku ve Ogrenci dizisine ekle
void readOgrenciFromFile(Ogrenci *ogrenciArray, int *ogrenciSayisi, char *dosyaAdi);

// Öğrenci dizisinin bellek alanını serbest bırak
void freeOgrenciArray(Ogrenci *ogrenciArray, int ogrenciSayisi);

// Ders dizisinin bellek alanını serbest bırak
void freeOgrenciArray(Ogrenci *ogrenciArray, int ogrenciSayisi);

#endif
