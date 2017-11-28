#include <LiquidCrystal.h> //Dołączenie bilbioteki
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Informacja o podłączeniu nowego wyświetlacza
int pinPrzycisku=12;
long timer =0;
long czasWyzwolenia;
boolean czyGraJestPrzegrana = false;

byte znak[7] = {
  B10101,
  B01010,
  B10101,
  B01010,
  B10101,
  B01010,
  B10101,
};
 
void setup() {
  pinMode(pinPrzycisku, INPUT_PULLUP);
  lcd.begin(16, 2); //Deklaracja typu
  lcd.createChar(0, znak); // tworzenie "customowego" znaku
  WyswietlEkranPoczatkowy ;
  
  randomSeed(analogRead(0)); // zapewnia, że losowane liczby są w pełni losowe
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
}

void WyswietlEkranPoczatkowy() {
  
  lcd.clear();
  lcd.setCursor(2,1);
  lcd.print("Sprawdz swoj");
  lcd.setCursor(0,1);
  lcd.print("refleks!");

  while (digitalRead(pinPrzycisku)==HIGH) {
  }
     
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Nacisnij guzik");
  lcd.setCursor(0,1);
  lcd.print("aby wystartowac");
  delay(300);
  
  while (digitalRead(pinPrzycisku)==HIGH) {
  }
  
}


void loop() {
  
  PoczatekTestu();
  test();
  
  
}

void PoczatekTestu(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Gdy zobaczysz: ");
  lcd.write(byte(0)); // wstawienie znaku
  lcd.setCursor(0,1);
  lcd.print("Nacisnij guzik");
  timer =0;
  while (timer < 5000) {
    delay(1);  
    timer=timer+1;
    if (digitalRead(pinPrzycisku)==LOW) {
      timer==5000;
    }
  }
  
  
}

void test() {
  
  timer =0;
  czyGraJestPrzegrana==false;
  
  generujLosowyCzasWyzwolenia();
  czasPrzedWyzwoleniem();
  if (czyGraJestPrzegrana==false) {
    wyzwolenie();
    czasPoWyzwoleniu();
    PokazWynik();
  }
   
}

void generujLosowyCzasWyzwolenia() {
  czasWyzwolenia = random(1000,8000);
}

void czasPrzedWyzwoleniem() {
  while (timer < czasWyzwolenia) {
   delay(1);
    timer =timer+1;
    if (digitalRead(pinPrzycisku)==LOW) {
      Przegrana();
      break;
    }
  }
    
}
void wyzwolenie() {
  lcd.clear();
  lcd.setCursor(0,0);
  for (int i=0; i<16 ; i++) {
   lcd.write(byte(0));  //wstaw znak 15 razy
  }
  lcd.setCursor(0,1);
  for (int i=0; i<16 ; i++) {
   lcd.write(byte(0));  //wstaw znak 15 razy
  } 
  
  
  
}


void czasPoWyzwoleniu() {
  timer=0;
  while (true) {
    if (digitalRead(pinPrzycisku)==LOW) {
     break; 
    }
    else {
     delay(1);
     timer=timer+1;
    }
    
    
  }
    
}

void PokazWynik() {
  float Wynik;
  Wynik = timer / 1000;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Nacisnoles po:");
  lcd.setCursor(0,1);
  lcd.print(Wynik);
  lcd.print(" sec!");
  
  
}

void Przegrana() {
  czyGraJestPrzegrana = true;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Za wczesnie!");
  lcd.print("");
  lcd.setCursor(0,1);
  lcd.print("Przegrales!");
  delay(2000);
  
}
