#include <Deneyap_OLED.h>
OLED ekran;

int durum = 0;  //durum = 0 -> beklemede
int sayac = 0; //her sayımda artacak
unsigned long oncekiZaman = 0;
unsigned long aralik = 1000; //iki işlem arasındaki süre

void setup(){ //başlangıç ayarları
    Serial.begin(115200);

    ekran.begin(0x7A); //oled I2C adresi
    ekran.clearDisplay();
    ekran.setTextXY(0, 0);
    ekran.putString("Sistem basladi");
    ekran.setTextXY(1, 0);
    ekran.putString("b ile basla");

}

void loop(){ 

    if(Serial.available()){ //Seri hatta okunacak veri var mı?
        char komut = Serial.read(); //komut oku

        if (komut == 'b' && durum == 0){ //Beklemedeyse veya b geldiyse başla
            durum = 1; //durum = 1 -> sayma
            sayac = 0;
            oncekiZaman = millis();
            ekran.clearDisplay();
            ekran.setTextXY(0, 0);
            ekran.putString("Sayma");
            ekran.setTextXY(1, 0);
            ekran.putString("Basladi");
        }
    }

    if (durum == 1){ //eğer durum sayma ise
        unsigned long simdikiZaman = millis(); //kart açıldığından beri geçen süre

        if (simdikiZaman - oncekiZaman >= aralik){
            oncekiZaman = simdikiZaman;
            sayac++;

            ekran.clearDisplay();
            ekran.setTextXY(0, 0);
            ekran.putString("Sayac: ");
            ekran.setTextXY(1, 0);
            ekran.putNumber(sayac);

            if (sayac >= 10) {
                durum = 2; //durum = 2 -> sayma tamamlandı
                ekran.clearDisplay();
                ekran.setTextXY(0, 0);
                ekran.putString("Sayma");
                ekran.setTextXY(1, 0);
                ekran.putString("Tamamlandi");
            }
        }
    }
}


