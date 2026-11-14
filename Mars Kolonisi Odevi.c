
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int saglik, enerji, oksijen, su, parca, hasar;
int kilit;         
int gun, tur;


int firtinaTur;     
int firtinaHasar;   
int suEsikYuksek;   
int suEsikDusuk;   


void sinirla(void)
{
    if (saglik < 0)    saglik = 0;
    if (saglik > 100)  saglik = 100;
    if (enerji < 0)    enerji = 0;
    if (enerji > 100)  enerji = 100;
    if (oksijen < 0)   oksijen = 0;
    if (oksijen > 100) oksijen = 100;
    if (hasar < 0)     hasar = 0;
    if (hasar > 100)   hasar = 100;
    if (su < 0)        su = 0;
    if (parca < 0)     parca = 0;
}


void girdiTemizle(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void zarYaz(int zar, int esik, const char *olumlu, const char *olumsuz)
{
    if (zar < esik)
        printf("  Zar: %d / Esik: %d -> %s\n", zar, esik, olumlu);
    else
        printf("  Zar: %d / Esik: %d -> %s\n", zar, esik, olumsuz);
}


void turIlerlet(void)
{
    tur++;
    if (tur % 3 == 0) {
        gun++;
        oksijen -= 8;
        if (gun <= 15)
            printf("\n*** YENI GUN BASLADI: Gun %d (oksijen -8) ***\n", gun);
        else
            printf("\n*** 15. gun tamamlandi! (oksijen -8) ***\n");
        if (hasar > 70) {
            saglik -= 5;
            printf("*** Modul hasari %d (>70): saglik -5 ***\n", hasar);
        }
    }
    sinirla();
}

void durumRaporu(void)
{
    int uyari = 0;

    printf("\n========== DURUM RAPORU ==========\n");
    printf("Gun: %d/15   Tur: %d\n", gun, tur);
    printf("Saglik: %d   Enerji: %d   Oksijen: %d\n", saglik, enerji, oksijen);
    printf("Su: %d birim   Yedek parca: %d   Modul hasari: %d\n", su, parca, hasar);
    printf("Hava kilidi: %s\n", kilit == 1 ? "MUHURLU" : "ACIK");

    if (oksijen < 25) { printf("[UYARI] Oksijen kritik seviyede (<25)!\n"); uyari++; }
    if (saglik < 30)  { printf("[UYARI] Saglik kritik seviyede (<30)!\n");  uyari++; }
    if (hasar > 70)   { printf("[UYARI] Modul hasari agir (>70)!\n");       uyari++; }
    if (enerji < 20)  { printf("[UYARI] Enerji cok dusuk (<20)!\n");        uyari++; }
    if (su < 2)       { printf("[UYARI] Su yetersiz (<2 birim)!\n");        uyari++; }

    
    if (oksijen >= 25 && saglik >= 30 && hasar <= 70 && enerji >= 20 && su >= 2)
        printf("TUM SISTEMLER NORMAL\n");
    else
        printf("Toplam %d kritik uyari var.\n", uyari);
    printf("==================================\n");
}


void sonucRaporu(int sebep)
{
    int tamamlananGun = gun - 1;     
    int puan;

    if (tamamlananGun > 15) tamamlananGun = 15;
    puan = (tamamlananGun * 100) + saglik + oksijen - hasar;

    printf("\n############ SONUC RAPORU ############\n");
    if (sebep == 1)
        printf("Kurtarma ekibi geldi! KAZANDINIZ.\n");
    else if (sebep == 2) {
        if (saglik <= 0)
            printf("Saglik 0'a dustu. KAYBETTINIZ.\n");
        else
            printf("Oksijen bitti. KAYBETTINIZ.\n");
    } else
        printf("Simulasyondan cikildi.\n");

    printf("Hayatta kalinan gun : %d\n", tamamlananGun);
    printf("Toplam tur          : %d\n", tur);
    printf("Saglik: %d | Enerji: %d | Oksijen: %d\n", saglik, enerji, oksijen);
    printf("Su: %d | Yedek parca: %d | Modul hasari: %d\n", su, parca, hasar);
    printf("PUAN = (%d x 100) + %d + %d - %d = %d\n",
           tamamlananGun, saglik, oksijen, hasar, puan);
    printf("######################################\n");
}


int main(void)
{
    char komut, seviye;
    int seviyeGecerli;
    int sebep = 0;          
    int gecerliTur;

    srand((unsigned int)time(NULL));

    printf("=== MARS KOLONISI YASAM DESTEK SIMULATORU ===\n");
    printf("Hedef: Kurtarma ekibi gelene kadar 15 gun hayatta kal.\n");

   
    do {
        seviyeGecerli = 1;
        printf("\nZorluk seviyesi secin (K: Kolay, N: Normal, Z: Zor): ");
        if (scanf(" %c", &seviye) != 1)
            return 0;    

        switch (seviye) {
        case 'k': case 'K':
            saglik = 100; enerji = 100; oksijen = 100;
            su = 20; parca = 5; hasar = 0;
            firtinaTur = 3; firtinaHasar = 4;
            suEsikYuksek = 70; suEsikDusuk = 45;
            printf("Kolay seviye secildi.\n");
            break;
        case 'n': case 'N':
            saglik = 100; enerji = 100; oksijen = 90;
            su = 12; parca = 3; hasar = 10;
            firtinaTur = 5; firtinaHasar = 6;
            suEsikYuksek = 60; suEsikDusuk = 30;
            printf("Normal seviye secildi.\n");
            break;
        case 'z': case 'Z':
            saglik = 90; enerji = 80; oksijen = 80;
            su = 6; parca = 2; hasar = 20;
            firtinaTur = 7; firtinaHasar = 9;
            suEsikYuksek = 50; suEsikDusuk = 20;
            printf("Zor seviye secildi.\n");
            break;
        default:
            printf("Gecersiz seviye! Lutfen K, N veya Z girin.\n");
            seviyeGecerli = 0;
            break;
        }
    } while (seviyeGecerli == 0);

    kilit = 0;
    gun = 1;
    tur = 0;
    srand((unsigned int)time(NULL));

    printf("\nKomutlar: G=Kesif  O=Oksijen uret  T=Tamir  D=Durum  U=Uyu\n");
    printf("          K=Kum firtinasi  H=Hava kilidi sifresi  Q=Cikis\n");

    
    do {
        gecerliTur = 0;
        printf("\n[Gun %d | Tur %d] Komut: ", gun, tur);
        if (scanf(" %c", &komut) != 1)
            komut = 'Q';    

        switch (komut) {

       
        case 'g': case 'G': {
            int e0, o0, zar, esik, miktar;

            if (enerji < 15) {
                printf("Enerji yetersiz (gerekli 15, mevcut %d). Komut iptal.\n", enerji);
                break;
            }
            e0 = enerji;
            o0 = oksijen;
            enerji -= 15;
            oksijen -= 10;
            printf("Kesfe ciktiniz (enerji -15, oksijen -10).\n");

           
            zar = rand() % 100;
            zarYaz(zar, 10, "YARALANDINIZ", "guvendesiniz");
            if (zar < 10 || hasar > 70) {
                saglik -= 10;
                if (hasar > 70 && zar >= 10)
                    printf("Hasarli modul nedeniyle kazaya ugradiniz! Saglik -10.\n");
                else
                    printf("Yaralandiniz! Saglik -10.\n");
            }

            
            if (e0 > 40 && o0 > 30)
                esik = suEsikYuksek;
            else
                esik = suEsikDusuk;

            zar = rand() % 100;
            if (zar < esik) {
                miktar = 3 + (zar % 4);
                su += miktar;
                zarYaz(zar, esik, "SU BULUNDU", "su yok");
                printf("Sonuc: %d birim su buldunuz.\n", miktar);
            } else if (zar < esik + 25) {
                parca += 1;
                printf("  Zar: %d / Esik: %d -> YEDEK PARCA BULUNDU\n", zar, esik + 25);
                printf("Sonuc: 1 yedek parca buldunuz.\n");
            } else {
                printf("  Zar: %d / Esik: %d -> ELI BOS\n", zar, esik + 25);
                printf("Sonuc: Eli bos dondunuz.\n");
            }
            gecerliTur = 1;
            break;
        }

       
        case 'o': case 'O': {
            int miktar, artik, kullanilan, uretilen;

            if (enerji < 5) {
                printf("Enerji yetersiz (gerekli 5, mevcut %d). Komut iptal.\n", enerji);
                break;
            }
            if (su < 2) {
                printf("Yeterli su yok (en az 2 birim gerekli). Komut iptal.\n");
                break;
            }
            if (oksijen >= 100) {
                printf("Oksijen deposu zaten dolu. Komut iptal.\n");
                break;
            }
            printf("Kac birim su harcansin? (mevcut: %d): ", su);
            if (scanf("%d", &miktar) != 1) {
                girdiTemizle();
                printf("Gecersiz sayi. Komut iptal.\n");
                break;
            }
            if (miktar < 2) {
                printf("En az 2 birim su girilmeli. Komut iptal.\n");
                break;
            }
            if (miktar > su) {
                printf("Mevcut sudan fazla miktar girilemez. Komut iptal.\n");
                break;
            }

            artik = miktar % 2;                
            kullanilan = miktar - artik;       
            uretilen = (kullanilan / 2) * 3;  
            if (oksijen + uretilen > 100) {
                printf("Depo tasiyor, fazla oksijen bosa gitti.\n");
                uretilen = 100 - oksijen;
            }
            su -= kullanilan;
            oksijen += uretilen;
            enerji -= 5;
            printf("%d su -> %d oksijen uretildi (enerji -5).\n", kullanilan, uretilen);
            if (artik == 1)
                printf("1 birim su artik olarak depoda kaldi.\n");
            gecerliTur = 1;
            break;
        }

        
        case 't': case 'T': {
            int gerekli, onarim, kullan;

            if (parca <= 0) {
                printf("Yedek parca yok, tamir yapilamaz. Komut iptal.\n");
                break;
            }
            if (hasar == 0) {
                printf("Modulde hasar yok, tamire gerek yok. Komut iptal.\n");
                break;
            }
            if (enerji < 10) {
                printf("Enerji yetersiz (gerekli 10, mevcut %d). Komut iptal.\n", enerji);
                break;
            }

            
            if (hasar <= 30) {
                gerekli = 1; onarim = 15;
                printf("Hafif hasar: ");
            } else if (hasar <= 70) {
                gerekli = 2; onarim = 25;
                printf("Orta hasar: ");
            } else {
                gerekli = 3; onarim = 35;
                printf("Agir hasar: ");
            }

            if (parca >= gerekli) {
                kullan = gerekli;
            } else {
                kullan = parca;                     
                onarim = onarim * kullan / gerekli; 
                printf("(parca yetersiz, kismi onarim) ");
            }
            parca -= kullan;
            hasar -= onarim;
            enerji -= 10;
            sinirla();
            printf("%d parca harcandi, %d hasar onarildi (enerji -10).\n", kullan, onarim);
            printf("Yeni modul hasari: %d\n", hasar);
            gecerliTur = 1;
            break;
        }

       
        case 'd': case 'D':
            durumRaporu();
            break;

       
        case 'u': case 'U': {
            int eArtis = 20 + (100 - enerji) / 10;
            int sArtis = 8 + (100 - saglik) / 10;

            enerji += eArtis;
            if (oksijen < 20) {
                saglik -= 5;
                printf("Oksijen cok dusuk (<20)! Dinlenirken saglik -5.\n");
            } else {
                if (hasar > 70) {
                    sArtis = sArtis / 2;
                    printf("Modul hasari yuksek, dinlenme verimi yariya dustu.\n");
                }
                saglik += sArtis;
                printf("Dinlendiniz: enerji +%d, saglik +%d.\n", eArtis, sArtis);
            }
            oksijen -= 4;
            printf("Dinlenirken oksijen -4.\n");
            gecerliTur = 1;
            break;
        }

        case 'k': case 'K': {
            int i, zar, carpan, esikCan;
            int hasarliTur = 0;
            int saglikBas = saglik, oksijenBas = oksijen;

            printf("\n!!! KUM FIRTINASI BASLADI (%d tur) !!!\n", firtinaTur);
            for (i = 1; i <= firtinaTur; i++) {
              
                if (i % 2 == 0)
                    carpan = 2;
                else
                    carpan = 1;

                
                esikCan = 20;
                if (enerji < 30)
                    esikCan += 10;
                if (hasar > 70)
                    esikCan += 10;

                zar = rand() % 100;
                printf("Firtina turu %d%s | Zar: %d / Can esigi: %d\n",
                       i, carpan == 2 ? " (SIDDETLI RUZGAR x2)" : "", zar, esikCan);

                if (zar < esikCan) {
                    saglik -= 5 * carpan;
                    hasarliTur++;
                    printf("  -> Savruldunuz! Saglik -%d\n", 5 * carpan);
                } else if (zar < esikCan + 20) {
                    if (kilit == 1) {
                        printf("  -> Oksijen sizintisi, ama hava kilidi muhurlu: atlandi.\n");
                        continue;           
                    }
                    oksijen -= 6 * carpan;
                    hasarliTur++;
                    printf("  -> Oksijen sizintisi! Oksijen -%d\n", 6 * carpan);
                } else if (zar < esikCan + 45) {
                    hasar += firtinaHasar * carpan;
                    hasarliTur++;
                    printf("  -> Modul hasar aldi! Hasar +%d\n", firtinaHasar * carpan);
                } else {
                    printf("  -> Korunmaya basarili, zarar yok.\n");
                }

                sinirla();
                if (saglik <= 0 || oksijen <= 0) {
                    printf("  !!! Kritik seviye, firtina simulasyonu kesildi !!!\n");
                    break;                  
                }
            }
            sinirla();
            printf("--- Firtina ozeti ---\n");
            printf("Hasar alinan tur: %d | Kaybedilen saglik: %d | Kaybedilen oksijen: %d\n",
                   hasarliTur, saglikBas - saglik, oksijenBas - oksijen);
            gecerliTur = 1;
            break;
        }

       
        case 'h': case 'H': {
            char sifre, girdi;
            int deneme = 0;

            if (kilit == 1) {
                printf("Hava kilidi zaten muhurlu. Komut iptal.\n");
                break;
            }
            if (enerji < 5) {
                printf("Enerji yetersiz (gerekli 5, mevcut %d). Komut iptal.\n", enerji);
                break;
            }
            sifre = 'A' + (gun % 26);
            printf("Ipucu: Sifre, alfabede A harfinden bugunun gun sayisi kadar ileridedir.\n");
            printf("Tek harf girin (en fazla 3 deneme).\n");

            do {
                printf("Deneme %d/3 - Sifre: ", deneme + 1);
                if (scanf(" %c", &girdi) != 1)
                    girdi = '?';
                if (girdi >= 'a' && girdi <= 'z')
                    girdi = girdi - 'a' + 'A';      
                deneme++;

                if (girdi != sifre) {
                    enerji -= 5;
                    if (enerji < 0)
                        enerji = 0;
                    if (girdi < sifre)
                        printf("  Yanlis! Enerji -5. Ipucu: ileri git.\n");
                    else
                        printf("  Yanlis! Enerji -5. Ipucu: geri git.\n");
                }
            } while (girdi != sifre && deneme < 3);

            if (girdi == sifre) {
                kilit = 1;
                printf("Sifre dogru! Hava kilidi MUHURLENDI.\n");
            } else {
                hasar += 20;
                printf("3 deneme basarisiz! Kilit zorlandi, modul hasari +20.\n");
            }
            gecerliTur = 1;
            break;
        }

      
        case 'q': case 'Q':
            printf("Simulasyondan cikiliyor...\n");
            sebep = 3;
            break;

        
        default:
            printf("Tanimsiz komut '%c'! Gecerli komutlar: G O T D U K H Q (tur harcanmadi).\n", komut);
            break;
        }

       
        if (gecerliTur == 1)
            turIlerlet();
        sinirla();

        if (sebep == 0) {
            if (saglik <= 0 || oksijen <= 0)
                sebep = 2;
            else if (gun > 15)
                sebep = 1;
        }
    } while (sebep == 0);

    sonucRaporu(sebep);
    return 0;
}
