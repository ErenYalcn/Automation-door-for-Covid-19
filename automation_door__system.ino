// ***ISIYA DUYARLI OTOMATİK KAPI KODLARI***
//*Eren Yalçın*//

#include <LiquidCrystal.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
// Kütüphanleri kodumuza dahil ettik.


int role = 50;
int role2 = 51;
int trigPin = 32;
int echoPin = 33;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
// Giriş-Çıkış pinlerimizi arduinoya tanımladık. role = Siren, role2 = Motor şeklinde ayarladık.
// We defined our Input-Output pins to the arduino. We have set role = Siren, role2 = Motor.

long sure;
long uzaklik;
// Mesafe ölçümü yapabilmek için iki adet giriş tanımı yaptık.
// We have defined two inputs to measure distance.

void setup() {
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(role,OUTPUT);
  pinMode(role2,OUTPUT);
  pinMode(44,OUTPUT);
  // Pinlerimizin Giriş yada çıkış olduğunu belirttik.
  // We specified that our pins are Input or Output.
  
  Serial.begin(9600);
  // Serial haberleşmeyi başlatıp aldığımız değerleri okumayı sağladık.
  // We have started the serial communication and read the values ​​we have received.
  
  mlx.begin();  
  lcd.begin(16, 2);
  // LCD ve Sıcaklık değerlerimizi aldık.
  // We got our LCD and Temperature values.
}

void loop() {




  Serial.print("  tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  Serial.print("  Ambient = "); Serial.print(mlx.readAmbientTempC());Serial.println("*C");
  
  // Serial print ile sıcaklık sensörümüzün değerlerini Serial monitöre aldık. İlk değer objenin yani kişinin. İkinci değer ortamın ısısı.
  // We took the values ​​of our temperature sensor to Serial monitor with Serial print. The first value is the object, the person. The second value is the temperature of the environment.


  digitalWrite(trigPin,LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  sure = pulseIn(echoPin,HIGH);
  uzaklik = sure /29.1/2;
  Serial.print(uzaklik);
  // Bu blokta Uzaklık ölçümünü yazdık.
  // We wrote the Distance measurement in this block.

  
    if(uzaklik < 20){
      
      lcd.print(mlx.readObjectTempC()+3); // Serial printte gördüğümüz dereceyi +3 ile toplayarak ekrana yazdırdık. DEĞERİ DEĞİŞTİRMEK İÇİN "+3" KISMINDAKİ RAKAMI DEĞİŞTİRİN.   // We added the grade we saw in serial print with +3 and printed it on the screen TO CHANGE THE VALUE, CHANGE THE NUMBER IN "+3".
      lcd.setCursor(6, 0);   // Ekrandaki yazının başlama konumunu ayarladık.     // We set the starting position of the text on the screen.
      lcd.print("C  KISI");  // Ekrana derecemizin yanına "C KİŞİ" yazdırdık.     // We have written "PERSON C" next to our degree on the screen.
      lcd.setCursor(1,1);  // Ekrandaki yazının başlama konumunu ayarladık.       // We set the starting position of the text on the screen.
      lcd.print("HOS GELDINIZ!"); // Ekrana yazı yazdırdık.                       // We have written text on the screen.     
      delay(500);
      lcd.clear();
      Serial.println();
      
      
    }
    if(mlx.readObjectTempC()+3 < 38){

      digitalWrite(role,HIGH); 
      delay(100);                                               // Bu blokta okunan değerin 3 fazlası 38den büyük ise sireni çaldırma komutunu yazdık.
                                                                // We wrote the command to ring the siren if 3 more than the value read in this block is greater than 38
    }
     if(mlx.readObjectTempC()+3 > 38){
      lcd.clear();
      lcd.print(mlx.readObjectTempC()+3);
      digitalWrite(role,LOW);

      delay(4000);
      lcd.clear();
      delay(100);                                             // Bu blokta okunan değerin 3 fazlası 38den küçük ise sireni kapaması için komut yazdık.
                                                              // If 3 more than the value read in this block is less than 38, we wrote a command to turn off the siren.
    }

    if(38>mlx.readObjectTempC()+3 and 34<mlx.readObjectTempC()+3){
      lcd.print(mlx.readObjectTempC()+3);
      delay(3000);
      lcd.clear();
      digitalWrite(role2,LOW);
      delay(100);

      // Bu blokta okunan değerin 3 fazlası 38'den küçük ve 36'dan büyük ise Motoru çalıştır komutu yazdık.
      // If 3 more of the value read in this block is less than 38 and greater than 36, we wrote the Run engine command.
      }
    else{
      digitalWrite(role2,HIGH);
      delay(300);                                            // Bu blokta ise üsteki blok çalışmazsa yani istediğimiz aralıkta değilse ölçülen sıcaklık motoru kapalı tut komutu yazdık.
                                                             // In this block, if the block above does not work, that is, if the temperature is not in the range we want, we wrote the command to keep the engine off.
      }
}
