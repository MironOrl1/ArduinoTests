#include <LiquidCrystal.h> //Dołączenie bilbioteki
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Informacja o podłączeniu nowego wyświetlacza

boolean graRozpoczeta = false;
int pinPrzycisku=12;
boolean postacWpowietrzu=false;
int czasWpowietrzu=0;
byte przeszkody[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //tworzenie pustej macierzy 16x1 o nazwie przeszkody
 
void setup() {
  pinMode(pinPrzycisku, INPUT_PULLUP);
  lcd.begin(16, 2); //Deklaracja typu
  WyswietlEkranStartowy() ;
  
  randomSeed(analogRead(0)); // zapewnia, że losowane liczby są w pełni losowe
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
}
 
void loop() {
  while (graRozpoczeta==false) {
    if (digitalRead(pinPrzycisku)==LOW) { // rozpocznij grę, gdy naciśnięto przycisk
    graRozpoczeta=true;
    }
  }
  
  lcd.clear(); // czyszczenie ekranu
  pokazBohatera();
  pokazPrzeszkody();
  
  sprawdzKolizje();
  skoczJezeliPostacJestNaZiemiOrazNacisnietoPrzycisk();
  delay(1000);
  jezeliMinolCzasSpadaniaToOpadnij(); // jeżeli minęło x tur to postac opada na ziemie
  
  
  JezeliNadalWpowietrzuToDodajCzas();
  LosujPrzeszkodeNaOstatniejPozycji();
  
}

// ---------------------------------------------------

void WyswietlEkranStartowy() {
  lcd.clear(); //czysc ekran
  lcd.setCursor(1, 0); //Ustawienie kursora
  lcd.print("Prosta gra"); //Wyświetlenie tekstu
  lcd.setCursor(0, 1); //Ustawienie kursora
  lcd.print("Nr. 1  Ver 0.01"); //Wyświetlenie tekstu

}


void pokazBohatera() {
if (postacWpowietrzu==false)  {
  lcd.setCursor(1, 1); //Ustawienie kursora
  lcd.print("A"); //Wyświetlenie bohatera
  }
  else
  {
    lcd.setCursor(1, 0); //Ustawienie kursora
    lcd.print("A"); //Wyświetlenie bohatera
   }


}

void pokazPrzeszkody() {
  for (int i=0; i <= 15; i++){
      lcd.setCursor(przeszkody[i], 1); //Ustawienie kursora w pozycji "i"
      lcd.print("/"); //Wyświetlenie przeszkody na pozycji "i"
   } 


}

void sprawdzKolizje() {
   if (przeszkody[1]==1 && postacWpowietrzu ==false) {
      delay(1000);
      lcd.clear();
      delay(100);
      lcd.setCursor(2,0);
      lcd.print("Przegrales");
      lcd.setCursor(2,1);
      lcd.print("Game Over");
      mrugnijWyswiedlaczem();
      mrugnijWyswiedlaczem();
      mrugnijWyswiedlaczem();
      WyswietlEkranStartowy();
      graRozpoczeta = false;
   }
   
}
void mrugnijWyswiedlaczem() {
   lcd.noDisplay();
   delay(300);
   lcd.display();
   delay(300);
}

void skoczJezeliPostacJestNaZiemiOrazNacisnietoPrzycisk() {
    if (digitalRead(pinPrzycisku)==LOW && postacWpowietrzu == false)  {
       postacWpowietrzu=true;
    }
}

void jezeliMinolCzasSpadaniaToOpadnij() {
    if (czasWpowietrzu==2)  {
	postacWpowietrzu=false;
	czasWpowietrzu=0;
    }
}

void JezeliNadalWpowietrzuToDodajCzas() {
  if (postacWpowietrzu==true)  {
	czasWpowietrzu=czasWpowietrzu+1;
    }
}


void LosujPrzeszkodeNaOstatniejPozycji() { 
    for (int i=0; i <= 14; i++) {
        przeszkody[i]=przeszkody[i+1] ;
    }
    
    if (przeszkody[14]==0 && przeszkody[13] == 0) { // zapewnij, że przed losowaniem pozycje 13 i 14 macierzy są puste.
	przeszkody[15] = random(0,2); // losuj losową liczbę od (0) do (2-1=1) na pozycji 15 macierzy  	
    }
    else { // jeżeli 14 lub 13 jest zajęte, to wstaw puste pole w pozycji 15, aby łatwej było przeskakiwać.
	przeszkody[15]=0;
    }
}
