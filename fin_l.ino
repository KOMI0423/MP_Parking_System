#include <FastLED.h>
#define NUM_LEDS 144
#define DATA_PIN 10
CRGB leds[NUM_LEDS];
#define PIN_FOTO A1

const int POCET_HODNOT = 5;  // Bude se brát 7 hodnot
const int trigPin1 = 2;     // piny arduino na senzory
const int echoPin1 = 3;

const int trigPin2 = 8;  
const int echoPin2 = 9;

const int trigPin3 = 12;
const int echoPin3 = 11;

const int trigPin4 = 7;
const int echoPin4 = 6;

const int buzzer = 5; //pin pro buzzer
// Pole pro ukládání vzdáleností v cm
float vzdalenost1[POCET_HODNOT];
float vzdalenost2[POCET_HODNOT];
float vzdalenost3[POCET_HODNOT];
float vzdalenost4[POCET_HODNOT];
int currentIndex1 = 0;
int currentIndex2 = 0;
int currentIndex3 = 0;
int currentIndex4 = 0;

int wait;

// Funkce pro výpočet klouzavého průměru
float simpleMovingAverage1(float novavzdalenost1) {
  // Přidání nové vzdálenosti do pole
  vzdalenost1[currentIndex1] = novavzdalenost1;
  currentIndex1 = (currentIndex1 + 1) % POCET_HODNOT;  // Kruhový buffer

  // Výpočet průměru
  float suma1 = 0;
  for (int i = 0; i < POCET_HODNOT; i++) {
    suma1 += vzdalenost1[i];
  }
  return suma1 / POCET_HODNOT;
}

float simpleMovingAverage2(float novavzdalenost2) {
  // Přidání nové ceny do pole
  vzdalenost2[currentIndex2] = novavzdalenost2;
  currentIndex2 = (currentIndex2 + 1) % POCET_HODNOT;  // Kruhový buffer

  // Výpočet průměru
  float suma2 = 0;
  for (int i = 0; i < POCET_HODNOT; i++) {
    suma2 += vzdalenost2[i];
  }
  return suma2 / POCET_HODNOT;
}

float simpleMovingAverage3(float novavzdalenost3) {
  // Přidání nové ceny do pole
  vzdalenost3[currentIndex3] = novavzdalenost3;
  currentIndex3 = (currentIndex3 + 1) % POCET_HODNOT;  // Kruhový buffer

  // Výpočet průměru
  float suma3 = 0;
  for (int i = 0; i < POCET_HODNOT; i++) {
    suma3 += vzdalenost3[i];
  }
  return suma3 / POCET_HODNOT;
}

float simpleMovingAverage4(float novavzdalenost4) {
  vzdalenost4[currentIndex4] = novavzdalenost4;
  currentIndex4 = (currentIndex4 + 1) % POCET_HODNOT;  // Kruhový buffer

  // Výpočet průměru
  float suma4 = 0;
  for (int i = 0; i < POCET_HODNOT; i++) {
    suma4 += vzdalenost4[i];
  }
  return suma4 / POCET_HODNOT;  //měří to jen půlku vzdálenosti z nějakého důvodu
}

void setup() {
  // Inicializace
  Serial.begin(115200);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
  FastLED.addLeds<NEOPIXEL, 10>(leds, NUM_LEDS);
  FastLED.setBrightness(20);
}

void loop() {
  //Senzor1
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(5);

  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin1, LOW);

  long duration1 = pulseIn(echoPin1, HIGH);
  long novavzdalenost1 = duration1 * 0.034 / 2;



  //Senzor2
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(5);

  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin2, LOW);

  long duration2 = pulseIn(echoPin2, HIGH);
  long novavzdalenost2 = duration2 * 0.034 / 2;



  //SENZOR 3
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(5);

  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin3, LOW);

  long duration3 = pulseIn(echoPin3, HIGH);
  long novavzdalenost3 = duration3 * 0.034 / 2;



  //SENZOR 4
  digitalWrite(trigPin4, LOW);
  delayMicroseconds(5);

  digitalWrite(trigPin4, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin4, LOW);

  long duration4 = pulseIn(echoPin4, HIGH);
  long novavzdalenost4 = duration4 * 0.034 / 2;

  // Výpočet klouzavého průměru
  float sma1 = simpleMovingAverage1(novavzdalenost1);

  // Výpočet klouzavého průměru
  float sma2 = simpleMovingAverage2(novavzdalenost2);

  // Výpočet klouzavého průměru
  float sma3 = simpleMovingAverage3(novavzdalenost3);

  // Výpočet klouzavého průměru
  float sma4 = simpleMovingAverage4(novavzdalenost4);

  int POCET_LED1 = map(sma1, 23, 300, 12, 0);
  int POCET_LED2 = map(sma2, 23, 300, 24, 12);
  int POCET_LED3 = map(sma3, 23, 300, 36, 24);
  int POCET_LED4 = map(sma4, 23, 300, 48, 36);

  for (int i = 0; i < POCET_LED1; i++) {
    for (int j = 0; j < 3 && j < POCET_LED1; j++) {
      leds[j] = CRGB::Green;
      for (int k = 3; k < 6 && k < POCET_LED1; k++) {
        leds[k] = CRGB::Yellow;
        for (int l = 6; l < 9 && l < POCET_LED1; l++) {
          leds[l] = CRGB::Orange;
          for (int m = 9; m < 12 && m < POCET_LED1; m++) {
            leds[m] = CRGB::Red;
          }
        }
      }
    }
  }
  for (int i = 12; i < POCET_LED2; i++) {
    for (int j = 12; j < 15 && j < POCET_LED2; j++) {
      leds[j] = CRGB::Green;
      for (int k = 15; k < 18 && k < POCET_LED2; k++) {
        leds[k] = CRGB::Yellow;
        for (int l = 18; l < 21 && l < POCET_LED2; l++) {
          leds[l] = CRGB::Orange;
          for (int m = 21; m < 24 && m < POCET_LED2; m++) {
            leds[m] = CRGB::Red;
          }
        }
      }
    }
  }
  for (int i = 24; i < POCET_LED3; i++) {
    for (int j = 24; j < 27 && j < POCET_LED3; j++) {
      leds[j] = CRGB::Green;
      for (int k = 27; k < 30 && k < POCET_LED3; k++) {
        leds[k] = CRGB::Yellow;
        for (int l = 30; l < 33 && l < POCET_LED3; l++) {
          leds[l] = CRGB::Orange;
          for (int m = 33; m < 36 && m < POCET_LED3; m++) {
            leds[m] = CRGB::Red;
          }
        }
      }
    }
  }
  for (int i = 36; i < POCET_LED4; i++) {
    for (int j = 36; j < 39 && j < POCET_LED4; j++) {
      leds[j] = CRGB::Green;
      for (int k = 39; k < 42 && k < POCET_LED4; k++) {
        leds[k] = CRGB::Yellow;
        for (int l = 42; l < 45 && l < POCET_LED4; l++) {
          leds[l] = CRGB::Orange;
          for (int m = 45; m < 48 && m < POCET_LED4; m++) {
            leds[m] = CRGB::Red;
          }
        }
      }
    }
  }
  FastLED.show();
  if (sma1 < 60 || sma2 < 60 || sma3 < 60 || sma4 < 60) {
    delay(300);
  } else if (sma1 < 30 || sma2 < 30 || sma3 < 30 || sma4 < 30) {
    delay(150);
  } else {
    delay(500);
  }
  //zhasnutí
  for (int i = 0; i < POCET_LED1; i++) {
    leds[i] = CRGB::Black;
  }
  for (int i = 0; i < POCET_LED2; i++) {
    leds[i] = CRGB::Black;
  }
  for (int i = 0; i < POCET_LED3; i++) {
    leds[i] = CRGB::Black;
  }
  for (int i = 0; i < POCET_LED4; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  delay(100);

  int array[4] = { sma1, sma2, sma3, sma4 };  //
  int min = 32000;                            //začít vysokou hodnotou
  for (int index = 0; index < 4; index++) {
    if (array[index] < min) {
      min = array[index];  //výpočet nového minima
    }
  }

  if (min > 300) { //závislot délky tónu na minimální naměřené vzdálenosti 
    wait = 350;
  } else if (min < 300 && min > 200) {
    wait = 280;
  } else if (min < 200 && min > 150) {
    wait = 230;
  } else if (min < 150 && min > 100) {
    wait = 180;
  } else if (min < 100 && min > 80) {
    wait = 130;
  } else if (min < 80 && min > 60) {
    wait = 90;
  } else if (min < 60 && min > 50) {
    wait = 50;
  } else if (min < 50 && min > 40) {
    wait = 30;
  } else if (min < 40 && min > 30) {
    wait = 10;
  } else {
    wait = 0;
  }

  tone(buzzer, 600);  // poslání signálu o velikosti 600 Hz
  delay(100);
  noTone(buzzer);  // zastavení tónu
  delay(wait);

  int a = analogRead(PIN_FOTO); //vrací hodnotu, kterou naměřil fotorezistor
  int Brightness = map(a, 50, 1000, 1, 50);
  FastLED.setBrightness(Brightness);
}
