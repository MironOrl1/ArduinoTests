#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
#define LCDkomX 16
#define LCDkomY 2
#define LCDkratkiX 5
#define LCDkratkiY 7



int pozycjaBohatera[]  ={3 , 3}; // (-x , -y) globalne
int pozycjaJedzenia[] ={0 , 0}; // (-x , -y) globalne
byte kom[]= {0,0};
byte Punkt[] = {0,0};

byte punkty = 0;

char kierunek = 'S';

byte smiley[7] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
};

byte pustaCzcionka[7] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};


void setup() {
  lcd.begin(LCDkomX, LCDkomY);
  lcd.createChar(0, smiley);
  lcd.write(byte(0));
  Serial.begin(9600);
  randomSeed(analogRead(A1));
}

void loop() {
  
  AktualizujKierunekRuchu();
  idz();
  skomponujCzcionki();
  pokazBohateraIjedzenie();
  sprawdzCzyBohaterZjadl();  // jezeli tak, to dodaje punkt i losuje pozycje kolejnego jedzenia
  pokazPunkty();
  
  //lcd.clear();
  //lcd.setCursor(0,0);
  //for (int i=0 ; (i<8) ; i++) {
  //  lcd.write(byte(i));
  //}
}


// -------------------------------------------------

void AktualizujKierunekRuchu() { //nie mylić z kierunkiem ruchania
  char odczyt;
  //char litera[1];
  if (Serial.available()>0) {
    odczyt=Serial.read();
  }
  if (odczyt == 'w' || odczyt =='W') {
    kierunek = 'N';
  }
  if (odczyt == 's' || odczyt =='S') {
    kierunek = 'S';
  }
  if (odczyt == 'a' || odczyt =='A') {
    kierunek = 'W';
  }
  if (odczyt == 'd' || odczyt =='D') {
    kierunek = 'E';
  }

  
    
}


void idz(){
  
  if (CzyBohaterJestNaKrawedzi(kierunek)==false) {
    
    switch (kierunek) {
      case 'N':
	pozycjaBohatera[1]=pozycjaBohatera[1]-1;
	break;
      case 'S':
	pozycjaBohatera[1]=pozycjaBohatera[1]+1;
	break;
      case 'E':
	pozycjaBohatera[0]=pozycjaBohatera[0]+1;
	break;
      case 'W':
	pozycjaBohatera[0]=pozycjaBohatera[0]-1;
	break;
     }
  }
   else {
      switch (kierunek) {
       case 'N':
	pozycjaBohatera[1]=LCDkomY*LCDkratkiY-1;
	break;
      case 'S':
	pozycjaBohatera[1]=0;
	break;
      case 'E':
	pozycjaBohatera[0]=0;
	break;
      case 'W':
	pozycjaBohatera[0]=LCDkomX*LCDkratkiX-1  -5; // -5 to miejsce na ramke punktacji
	break;
      }
    }
  
}

void pokazPunkty() {
  int mJednosci;
  int mDzesietne;
  
  if (punkty==100) {
    punkty=1 ;
  }  
  mDzesietne= punkty / 10;
  mJednosci = punkty - mDzesietne;
  lcd.setCursor(15,0);
  lcd.print(mDzesietne);
  lcd.setCursor(15,1);
  lcd.print(mJednosci);
}

boolean CzyBohaterJestNaKrawedzi(char kier) {
  boolean NaKrawedzi=false;
  switch (kier) {
   case 'N':
     if (pozycjaBohatera[1]==0) {
      NaKrawedzi = true;
     }
     break;
   case 'S':
     if (pozycjaBohatera[1]== LCDkomY*LCDkratkiY-1) {
      NaKrawedzi = true; 
     }
     break;
   case 'E':
     if (pozycjaBohatera[0]== LCDkomX*LCDkratkiX-1  -5) {  // -5 to miejsce na ramke punktacji
      NaKrawedzi = true; 
     }     
     break;
   case 'W':
     if (pozycjaBohatera[0]==0) {
      NaKrawedzi = true; 
     }
     break;
     
 }
  return NaKrawedzi;
}
  
void sprawdzCzyBohaterZjadl() {
  
  // sprawdź czy PacMan i jedzenie jest w tym samym punkcie i komórce.
  if (pozycjaBohatera[0]==pozycjaJedzenia[0] && pozycjaBohatera[1]==pozycjaJedzenia[1]) {
    punkty = punkty+1;
    losujPozycjeJedzenia();
  }
  
}

void losujPozycjeJedzenia(){
  
  pozycjaJedzenia[0]=random(0,LCDkomX*LCDkratkiX-1 -5);
  pozycjaJedzenia[1]=random(0,LCDkomY*LCDkratkiY-1);
}


void skomponujCzcionki() {
  byte komB[2];
  byte komJ[2];
  byte pnkB[2];
  byte pnkJ[2];
   
   rozdzielPozycjeGlobalnaNaKomorke(pozycjaBohatera[0], pozycjaBohatera[1] );
   komB[0] = kom[0];
   komB[1] = kom[1];
   rozdzielPozycjeGlobalnaNaKomorke(pozycjaJedzenia[0], pozycjaJedzenia[1] );
   komJ[0] = kom[0];
   komJ[1] = kom[1];
   
   rozdzielPozycjeGlobalnaNaPixelKomorki(pozycjaBohatera[0], pozycjaBohatera[1] );
   komB[0] = Punkt[0];
   komB[1] = Punkt[1];
   rozdzielPozycjeGlobalnaNaPixelKomorki(pozycjaJedzenia[0], pozycjaJedzenia[1] );
   pnkJ[0] = Punkt[0];
   pnkJ[1] = Punkt[1];
   
   byte znakB[7];
   for (int i =0; i<2 ; i++) {
     znakB[i] = pustaCzcionka[i];  
   }
   byte znakJ[7];
   for (int i =0; i<2 ; i++) {
     znakJ[i] = pustaCzcionka[i];  
   }
   
   zamalujPixelCzcionki(znakB , komB[0] , komB[1]);
   
   
   if (ObiektySaWtejSamejKom(komB,komJ) ==true) {
    //jednaCzcionka z Pacmanem i jedzeniem 
     zamalujPixelCzcionki(znakB , komJ[0] , komJ[1]);
     lcd.createChar(0,znakB);
   }
   else {
    //dwie czcionki 
     zamalujPixelCzcionki(znakJ , komJ[0] , komJ[1]);
     lcd.createChar(0,znakB);
     lcd.createChar(1,znakJ);
   }
   
   
   
}

boolean ObiektySaWtejSamejKom(byte komB[2] , byte komJ[2]) {
  
  if (komB[0] == komJ[0] && komB[1] == komJ[1]) {
    return true;
  }
  else {
    
    return false;
  }
  
}

void pokazBohateraIjedzenie() {
    byte komB[2];
    byte komJ[2];
    
   rozdzielPozycjeGlobalnaNaKomorke(pozycjaBohatera[0], pozycjaBohatera[1] );
   komB[0] = kom[0];
   komB[1] = kom[1];
   
   rozdzielPozycjeGlobalnaNaKomorke(pozycjaJedzenia[0], pozycjaJedzenia[1] );
   komJ[0] = kom[0];
   komJ[1] = kom[1];
   
   if (komB[0] < komJ[0]) {
    lcd.setCursor(komB[0],komB[1]);
    lcd.write(byte(0));
    lcd.setCursor(komJ[0],komJ[1]);
    lcd.write(byte(1));
   }
   else if (komB[0] == komJ[0]) {
     
    lcd.setCursor(komJ[0],komJ[1]);
    lcd.write(byte(1)); 
    lcd.setCursor(komB[0],komB[1]);
    lcd.write(byte(0));
   }
    else {
    lcd.setCursor(komJ[0],komJ[1]);
    lcd.write(byte(1)); 
    lcd.setCursor(komB[0],komB[1]);
    lcd.write(byte(0));
      
    }
   
   
   //lcd.setCursor(0,0);
  //for (int i=0 ; (i<8) ; i++) {
  //  lcd.write(byte(i));
   
   
}

void rozdzielPozycjeGlobalnaNaKomorke(int xGlobalne , int yGlobalne) {

  kom[0] = (xGlobalne-1) / (LCDkratkiX - 5);
  kom[1] = (yGlobalne-1) / LCDkratkiY;
}

void rozdzielPozycjeGlobalnaNaPixelKomorki(int xGlobalne , int yGlobalne) {
  
  Punkt[0] = (xGlobalne-1) / (LCDkomX- 1);
  Punkt[1] = (yGlobalne-1) / LCDkomY;
}



void zamalujPixelCzcionki(byte czcionka[7] , int columnX , int rowY) {
  bitWrite(czcionka[rowY], (LCDkratkiX-columnX), 1);
}

void wymazPixelCzcionki(byte czcionka[7] , int columnX , int rowY) {
  bitWrite(czcionka[rowY], (LCDkratkiX-columnX), 0);
}
