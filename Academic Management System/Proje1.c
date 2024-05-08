#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Proje1.h"


// Yardımcı fonksiyonlar...

char *allocateStringMemory(size_t size)
{
    char *str = (char *)malloc(size * sizeof(char));

    if (str == NULL)
    {
        printf("Bellek tahsisi basarisiz.\n");
        exit(EXIT_FAILURE);
    }

    return str;
}

// Bellekten Derse ayrılan yerleri serbest bırakma
void freeDers(Ders *ders)
{
    free(ders->dersAdi);
}

// Bellekten Öğrenciye ayrılan yerleri serbest bırak
void freeOgrenci(Ogrenci *ogrenci)
{
    free(ogrenci->ogrAdi);
    free(ogrenci->ogrSoyAdi);
    free(ogrenci->bolumu);
    for (int i = 0; i < ogrenci->dersSayisi; ++i)
    {
        free(ogrenci->aldigiDersler[i].dersAdi);
    }
}

void freeAldigiDersler(Ders **aldigiDersler, int dersSayisi)
{
    for (int i = 0; i < dersSayisi; ++i)
    {
        freeDers(aldigiDersler[i]);
    }
}

                    //////////////// Istenilen Fokisyonlar \\\\\\\\\\\\\\\\\\

// Ders oluşturma
Ders createDers(char *dersAdi, unsigned short int kredi, unsigned short int puan)
{
    Ders ders;

    ders.dersAdi = allocateStringMemory(256); // yaptığım özel fonkisyanla bellekte yer açılıyor
    strcpy(ders.dersAdi, dersAdi);

    ders.kredi = kredi;
    ders.puan = puan;

    return ders;
}

// Ogrenci oluşturma
Ogrenci createOgrenci(char *ogrAdi, char *ogrSoyAdi, char *bolumu, float ortalama, Ders *aldigiDersler, int dersSayisi)
{
    Ogrenci ogrenci;

    ogrenci.ogrAdi = allocateStringMemory(256);
    strcpy(ogrenci.ogrAdi, ogrAdi);

    ogrenci.ogrSoyAdi = allocateStringMemory(256);
    strcpy(ogrenci.ogrSoyAdi, ogrSoyAdi);

    ogrenci.bolumu = allocateStringMemory(256);
    strcpy(ogrenci.bolumu, bolumu);

    ogrenci.ortalama = ortalama;
    ogrenci.aldigiDersler = aldigiDersler;
    ogrenci.dersSayisi = dersSayisi;

    return ogrenci;
}

// Ogrenci bilgilerini yazdırma
void printOgrenci(Ogrenci ogrenci)
{
    printf("\nOgrenci Adi: %s\n", ogrenci.ogrAdi);
    printf("Ogrenci Soyadi: %s\n", ogrenci.ogrSoyAdi);
    printf("Bolumu: %s\n", ogrenci.bolumu);
    printf("Ortalama: %.2f\n", ogrenci.ortalama);

    // Öğrencinin aldığı ders bilgilerini yazdırma
    printf("\nAldigi Dersler:\n");
    for (int i = 0; i < ogrenci.dersSayisi; ++i)
    {
        printf("%d. Ders Adi: %s, Kredi: %hu, Puan: %hu\n",
               i + 1,
               ogrenci.aldigiDersler[i].dersAdi,
               ogrenci.aldigiDersler[i].kredi,
               ogrenci.aldigiDersler[i].puan);
    }
    printf("\n");
}

// Ogrenci dizisini yazdırma
void printOgrenciArray(Ogrenci *ogrenciArray, int ogrenciSayisi)
{
    for (int i = 0; i < ogrenciSayisi; ++i)
    {
        printf("Ogrenci #%d\n", i + 1);
        printOgrenci(ogrenciArray[i]);
    }
}

// Ortalamayı hesaplama
float calculateMean(char *dersAdi, Ogrenci *ogrenciArray, int arraySize)
{
    float toplamPuan = 0.0;
    int ogrenciSayisi = 0;

    for (int i = 0; i < arraySize; ++i)
    {
        for (int j = 0; j < ogrenciArray[i].dersSayisi; ++j)
        {
            if (strcmp(ogrenciArray[i].aldigiDersler[j].dersAdi, dersAdi) == 0)
            {
                toplamPuan += ogrenciArray[i].aldigiDersler[j].puan;
                ++ogrenciSayisi;
                break;
            }
        }
    }

    if (ogrenciSayisi == 0)
    {
        return 0.0;
    }
    return toplamPuan / ogrenciSayisi;
}

// Standart Sapma hesaplama
float calculateStdDev(char *dersAdi, Ogrenci *ogrenciArray, int arraySize)
{
    float mean = calculateMean(dersAdi, ogrenciArray, arraySize);
    float toplamKareFark = 0.0;
    int ogrenciSayisi = 0;

    for (int i = 0; i < arraySize; ++i)
    {
        for (int j = 0; j < ogrenciArray[i].dersSayisi; ++j)
        {
            if (strcmp(ogrenciArray[i].aldigiDersler[j].dersAdi, dersAdi) == 0)
            {
                float fark = ogrenciArray[i].aldigiDersler[j].puan - mean;
                toplamKareFark += fark * fark;
                ++ogrenciSayisi;
                break;
            }
        }
    }
    if (ogrenciSayisi == 0)
    {
        return 0.0;
    }
    return sqrt(toplamKareFark / ogrenciSayisi);
}

// Ders türünden iki dersin kovaryansıni hesaplama
float calculateCovariance(Ders ders1, Ders ders2)
{
    // Ortalamalari hesaplama
    float meanDers1 = (float)(ders1.puan) / ders1.kredi;
    float meanDers2 = (float)(ders2.puan) / ders2.kredi;

    // Covariance hesaplama
    float covariance = 0.0;
    covariance += ((ders1.puan - meanDers1) * (ders2.puan - meanDers2));

    return covariance;
}

void listAboveAverage(char *dersAdi, Ogrenci *ogrenciArray, int arraySize)
{
    // ilk once secilen dersin ortalamasini hesaplama
    float dersOrtalamasi = calculateMean(dersAdi, ogrenciArray, arraySize);

    // Dersi alan öğrencileri listeleme
    printf("%s dersi ortalamasindan yuksek alan ogrenciler: ", dersAdi);
    for (int i = 0; i < arraySize; ++i)
    {
        for (int j = 0; j < ogrenciArray[i].dersSayisi; ++j)
        {
            if (strcmp(ogrenciArray[i].aldigiDersler[j].dersAdi, dersAdi) == 0)
            {
                // İlgili derse ait puani kontrol etme
                if (ogrenciArray[i].aldigiDersler[j].puan > dersOrtalamasi)
                {
                    printf("%s %s, Notu: %hu\n", ogrenciArray[i].ogrAdi, ogrenciArray[i].ogrSoyAdi, ogrenciArray[i].aldigiDersler[j].puan);
                }
            }
        }
    }
}

// Öğrenci bilgilerini bir dosyaya yaz
void writeOgrenciToFile(Ogrenci *ogrenciArray, int ogrenciSayisi, char *dosyaAdi)
{
    FILE *dosya = fopen(dosyaAdi, "w");

    if (dosya == NULL)
    {
        printf("Dosya acilamadi.\n");
        return;
    }

    // Her öğrenciyi dosyaya yaz
    for (int i = 0; i < ogrenciSayisi; ++i)
    {
        fprintf(dosya, "Ad: %s\n", ogrenciArray[i].ogrAdi);
        fprintf(dosya, "Soyad: %s\n", ogrenciArray[i].ogrSoyAdi);
        fprintf(dosya, "Bolum: %s\n", ogrenciArray[i].bolumu);
        fprintf(dosya, "Ortalama: %.2f\n", ogrenciArray[i].ortalama);

        // Aldığı dersleri yaz
        fprintf(dosya, "Aldigi Dersler:\n");
        for (int j = 0; j < ogrenciArray[i].dersSayisi; ++j)
        {
            fprintf(dosya, "Ders Adi: %s, Kredi: %hu, Puan: %hu\n",
                    ogrenciArray[i].aldigiDersler[j].dersAdi,
                    ogrenciArray[i].aldigiDersler[j].kredi,
                    ogrenciArray[i].aldigiDersler[j].puan);
        }

        fprintf(dosya, "\n");
    }

    fclose(dosya);
}

// Dosyadan öğrenci bilgilerini oku ve Ogrenci dizisine ekle
void readOgrenciFromFile(Ogrenci *ogrenciArray, int *ogrenciSayisi, char *dosyaAdi)
{
    FILE *dosya = fopen(dosyaAdi, "r");

    if (dosya == NULL)
    {
        printf("\nDosya acilamadi.\n");
        return;
    }

    // Her öğrenciyi dosyadan oku
    while (fscanf(dosya, "Ad: %s", ogrenciArray[*ogrenciSayisi].ogrAdi) == 1)
    {
        // Diğer öğrenci bilgilerini oku
        fscanf(dosya, "Soyad: %s", ogrenciArray[*ogrenciSayisi].ogrSoyAdi);
        fscanf(dosya, "Bolum: %s", ogrenciArray[*ogrenciSayisi].bolumu);
        fscanf(dosya, "Ortalama: %f", &ogrenciArray[*ogrenciSayisi].ortalama);

        // Aldığı dersleri oku
        fscanf(dosya, "Aldigi Dersler:");
        int dersIndex = 0;
        while (fscanf(dosya, "Ders Adi: %s, Kredi: %hu, Puan: %hu",
                      ogrenciArray[*ogrenciSayisi].aldigiDersler[dersIndex].dersAdi,
                      &ogrenciArray[*ogrenciSayisi].aldigiDersler[dersIndex].kredi,
                      &ogrenciArray[*ogrenciSayisi].aldigiDersler[dersIndex].puan) == 3)
        {
            dersIndex++;
        }

        (*ogrenciSayisi)++;
    }

    fclose(dosya);
}

