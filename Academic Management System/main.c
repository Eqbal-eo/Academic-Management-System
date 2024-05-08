#include <stdio.h>
#include "Proje1.h"
#include "Proje1.c"

int main(int argc, char *argv[])
{

    /* if (argc != 2)
         {
             printf("Kullanim: %s <ogrenci.txt>\n", argv[0]);
             return 1;
         }
     */

    //--------------------------------------
    // Örnek dersler oluşturma
    Ders ders1 = createDers("Matematik", 4, 60);
    Ders ders2 = createDers("Fizik", 5, 75);
    Ders ders3 = createDers("Bp2", 6, 44);

    Ders ders4 = createDers("Matematik", 3, 80);
    Ders ders5 = createDers("Fizik", 4, 90);
    Ders ders6 = createDers("Bp2", 5, 88);
    //---------------------------------

    // İlk öğrencinin aldığı dersleri belirleme
    Ders aldigiDersler1[] = {ders1, ders2, ders3};
    int dersSayisi1 = 3; // sizeof(aldigiDersler1) / sizeof(aldigiDersler1[0]);

    // Ogrenci olusturma
    Ogrenci ogrenci = createOgrenci("Omar", "Shalaty", "Elektrik Muhendisligi", 80.5, aldigiDersler1, dersSayisi1);

    //---------------------------------

    // İkinci öğrencinin aldığı dersleri belirleme
    Ders aldigiDersler2[] = {ders4, ders5, ders6};
    int dersSayisi2 = 3; // sizeof(aldigiDersler2) / sizeof(aldigiDersler2[0]);

    // Ogrenci olusturma
    Ogrenci ogrenci1 = createOgrenci("Eqbal", "Ayoub", "Bilgisayar Muhendisligi", 50.5, aldigiDersler2, dersSayisi2);

    //----------------------------------

    // Oluşturulan öğrencinin bilgilerini yazdır
    printOgrenci(ogrenci);

    // Öğrenci dizisi oluştur
    Ogrenci ogrenciArray[] = {ogrenci, ogrenci1};
    int ogrenciSayisi = 2; // sizeof(ogrenciArray) / sizeof(ogrenciArray[0]);

    // Öğrenci dizisini yazdır
    printOgrenciArray(ogrenciArray, ogrenciSayisi);

    // calculateMean fonksiyonunu kullanarak ortamalayı hesapla
    float matematikOrtalamasi = calculateMean("Matematik", ogrenciArray, 2);
    printf("Matematik Ortalamasi: %.2f\n", matematikOrtalamasi);

    // calculateStdDev fonksiyonunu kullanarak bir dersin standart sapmasını hesapla
    float matematikStandartSapma = calculateStdDev("Fizik", ogrenciArray, 2);
    printf("Matematik Standart Sapma: %.2f\n", matematikStandartSapma);

    // İki dersin kovaryansını hesapla
    float covariance = calculateCovariance(ders1, ders2);
    printf("%s ve %s arasindaki kovaryans: %.2f\n", ders1.dersAdi, ders2.dersAdi, covariance);

    // Dersi alan öğrencileri listeleyin
    listAboveAverage("Matematik", ogrenciArray, ogrenciSayisi);

    // Öğrenci dizisini dosyaya yaz
    writeOgrenciToFile(ogrenciArray, ogrenciSayisi, "ogrenci.txt");

    // Dosyadan öğrenci bilgilerini oku ve Ogrenci dizisine ekle
    readOgrenciFromFile(ogrenciArray, &ogrenciSayisi, argv[1]);

    // Bellekten  ayrılan yerleri serbest bırakma
    freeDers(&ders1);
    freeDers(&ders2);
    freeDers(&ders3);

    freeOgrenci(&ogrenci);
    freeOgrenci(&ogrenci1);

    free(aldigiDersler1);
    free(aldigiDersler2);

    return 0;
}
