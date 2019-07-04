#include <QTRSensors.h>

#define NUM_SENSORS   6     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 us for sensor outputs to go low

QTRSensorsRC qtrrc((unsigned char[]) {
  2, 4, 5, 6, 7, 10
},  NUM_SENSORS,
TIMEOUT, QTR_NO_EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

int esik = 1000;
int hiz = 200;
int hiz1 = 150;

void sol()
{
  // digitalWrite(8, HIGH);   /* fren yapıldı */

  /* B motoru geri yönde dönmesi için ayarlanıyor */
  digitalWrite(13, LOW); /* geri yön ayarı yapıldı */
  digitalWrite(8, LOW);   /* fren kapatıldı */
  analogWrite(11, 255);   /* dönme hızı ayarlandı */

  /* A motoru ileri yönde dönmesi için ayarlanıyor */
  digitalWrite(12, HIGH); /* ileri yön ayarı yapıldı */
  digitalWrite(9, LOW);   /* fren kapatıldı */
  analogWrite(3, 255);   /* dönme hızı ayarlandı,  150 hızında dönecek, maximum 255*/
}

void sag()
{
  // digitalWrite(9, HIGH);   /* fren yapıldı */
  /* A motoru geri yönde dönmesi için ayarlanıyor */
  digitalWrite(12, LOW); /* geri yön ayarı yapıldı */
  digitalWrite(9, LOW);   /* fren kapatıldı */
  analogWrite(3, 255);   /* dönme hızı ayarlandı */

  /* B motoru ileri yönde dönmesi için ayarlanıyor */
  digitalWrite(13, HIGH); /* ileri yön ayarı yapıldı */
  digitalWrite(8, LOW);   /* fren kapatıldı */
  analogWrite(11, 255);   /* dönme hızı ayarlandı */
}

void sol1()
{
  // digitalWrite(8, HIGH);   /* fren yapıldı */

  /* B motoru geri yönde dönmesi için ayarlanıyor */
  digitalWrite(13, LOW); /* geri yön ayarı yapıldı */
  digitalWrite(8, LOW);   /* fren kapatıldı */
  analogWrite(11, hiz1);   /* dönme hızı ayarlandı */

  /* A motoru ileri yönde dönmesi için ayarlanıyor */
  digitalWrite(12, HIGH); /* ileri yön ayarı yapıldı */
  digitalWrite(9, LOW);   /* fren kapatıldı */
  analogWrite(3, hiz1);   /* dönme hızı ayarlandı,  150 hızında dönecek, maximum 255*/
}

void sag1()
{
  // digitalWrite(9, HIGH);   /* fren yapıldı */
  /* A motoru geri yönde dönmesi için ayarlanıyor */
  digitalWrite(12, LOW); /* geri yön ayarı yapıldı */
  digitalWrite(9, LOW);   /* fren kapatıldı */
  analogWrite(3, hiz1);   /* dönme hızı ayarlandı */

  /* B motoru ileri yönde dönmesi için ayarlanıyor */
  digitalWrite(13, HIGH); /* ileri yön ayarı yapıldı */
  digitalWrite(8, LOW);   /* fren kapatıldı */
  analogWrite(11, hiz1);   /* dönme hızı ayarlandı */
}

void setup()
{
  /* A motorunun ayarları */
  pinMode(12, OUTPUT); /* Yön pini çıkış olarak ayarlandı */
  pinMode(9, OUTPUT); /* Fren pini çıkış olarak ayarlandı */

  /* B motorunun ayarları */
  pinMode(13, OUTPUT);  /* Yön pini çıkış olarak ayarlandı */
  pinMode(8, OUTPUT);  /* Fren pini çıkış olarak ayarlandı */


  //  Serial.begin(9600);  delay(1000);


} // setup bitti

int values0 = 0;
int values1 = 0;
int values2 = 0;
int values3 = 0;
int values4 = 0;
int values5 = 0;

int t1 = 0;
int t2 = 0;
int t3 = 0;
int t4 = 0;
int t5 = 0;

byte d1;
byte d2;
byte d3;
byte d4;
byte d5;



void readSensors() {
  qtrrc.read(sensorValues);

  unsigned char i;

  values0 = sensorValues[0]; // sensörden gelen verileri değişkenlere tanımladık
  values1 = sensorValues[1];
  values2 = sensorValues[2];
  values3 = sensorValues[3];
  values4 = sensorValues[4];
  values5 = sensorValues[5];

  t1 = values0 + values1;
  t2 = values2 + values3;
  t3 = values4 + values5;
  t4 = values1 + values2;
  t5 = values3 + values4;

  if (t1 > esik)
  {
    d1 = 1;
  }
  else
    d1 = 0;
  if (t2 > esik)
  {
    d2 = 1;
  }
  else
    d2 = 0;
  if (t3 > esik)
  {
    d3 = 1;
  }
  else
    d3 = 0;
  if (t4 > esik)
  {
    d4 = 1;
  }
  else
    d4 = 0;
  if (t5 > esik)
  {
    d5 = 1;
  }
  else
    d5 = 0;

}
boolean siyah_gordu = false;
boolean siyahmi() {
  readSensors();
  int toplam = values0 + values1 + values2 + values3 + values4 + values5;
  //if (values0 > s && values1 > s && values2 > s && values3 > s && values4 > s && values5 > s) // hepsi siyah ve motorlar dursun
  if (toplam > 8000)
  {
    /* A motoru durması için ayarlanıyor */
    digitalWrite(9, HIGH);   /* fren yapıldı */

    /* B motoru durması için ayarlanıyor */
    digitalWrite(8, HIGH);  /* fren yapıldı */
    //siyah_gordu = 1;
    siyah_gordu = true;

    return true;

  } else {
    //siyah_gordu = false;
    return false;

  }


}



void loop()
{

  if (!siyah_gordu) {
    siyahmi();

    /* A motoru ileri yönde dönmesi için ayarlanıyor */
    digitalWrite(12, HIGH); /* ileri yön ayarı yapıldı */
    digitalWrite(9, LOW);   /* fren kapatıldı */
    analogWrite(3, hiz);   /* dönme hızı ayarlandı,  150 hızında dönecek, maximum 255*/

    /* B motoru ileri yönde dönmesi için ayarlanıyor */
    digitalWrite(13, HIGH); /* ileri yön ayarı yapıldı */
    digitalWrite(8, LOW);   /* fren kapatıldı */
    analogWrite(11, hiz);   /* dönme hızı ayarlandı */

    // *********************************************************************************************************** //
    if (d2 == 1 && d4 != 1 && d5 != 1 && d3 != 1 && d1 != 1)
    {

      /* A motoru ileri yönde dönmesi için ayarlanıyor */
      digitalWrite(12, HIGH); /* ileri yön ayarı yapıldı */
      digitalWrite(9, LOW);   /* fren kapatıldı */
      analogWrite(3, hiz);   /* dönme hızı ayarlandı,  150 hızında dönecek, maximum 255*/

      /* B motoru ileri yönde dönmesi için ayarlanıyor */
      digitalWrite(13, HIGH); /* ileri yön ayarı yapıldı */
      digitalWrite(8, LOW);   /* fren kapatıldı */
      analogWrite(11, hiz);   /* dönme hızı ayarlandı */

      if (!siyahmi());
    }
    else if (d1 == 1)
    {
      hiz = 100;
      sol();
      if (!siyahmi());
    }

    else if (d3 == 1)
    {
      hiz = 100;
      sag();
      if (!siyahmi());
    }
    else if (d4 == 1 && d2 != 1)
    {
      hiz=150;
      sol1();
      if (!siyahmi());
    }
    else if (d5 == 1 && d2 != 1)
    {
      hiz=150;
      sag1();
      if (!siyahmi());
    }

  } //if

  else {
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
  }

} //loop

