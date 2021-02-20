#include <Keypad.h>


const byte ROWS = 2;
const byte COLS = 8;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', '4', '5','6', '7', '8'},
  {'9', 'a', 'b', 'c', 'c', 'd','e', 'f'},
 
};
byte colPins[COLS] = {A0,A1,A2,A3,A4,A5,A6,A7};
byte rowPins[ROWS] = {A8,A9};

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
int patchnum =1;
#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

void setup() {
pinMode(14, INPUT_PULLUP);
pinMode(16, INPUT_PULLUP);
  
  Serial.begin(115200);
 
 lcd.print("HRTE PROJECTS");
  delay(2000);
  lcd.setCursor(6,0); 
  lcd.print("DRUM CHANNEL 16");
  lcd.setCursor(6,2); 
  lcd.print("OCTAPAD");
  delay(2000);
   lcd.setCursor(0,0); 
  lcd.print("created by:");
 lcd.setCursor(0,1);
 lcd.print("UchithaInduranga ");
 delay(2000);
 }

void loop() {
  char customKey = customKeypad.getKey();

  if (customKey) {
    switch (customKey) {
      case '1':
        Serial.write(B10010000);
        Serial.write(10);
        Serial.write(127);
        break;
      case '2':
      
        Serial.write(B10010000);
        Serial.write(20);
        Serial.write(127);
        break;
        case '3':
        Serial.write(B10010000);
        Serial.write(30);
        Serial.write(127);
        break;
      case '4':
      
        Serial.write(B10010000);
        Serial.write(35);
        Serial.write(127);
        break;   
    
     case '5':
        Serial.write(B10010000);
        Serial.write(40);
        Serial.write(127);
        break;
      case '6':
      
        Serial.write(B10010000);
        Serial.write(50);
        Serial.write(127);
        break;
      
      case '7':
      
        Serial.write(B10010000);
        Serial.write(55);
        Serial.write(127);
        break; 
        case '8':
        Serial.write(B10010000);
        Serial.write(60);
        Serial.write(127);
        break;
         case '9':
        Serial.write(B10010000);
        Serial.write(65);
        Serial.write(127);
        break;
      case 'a':
     
        Serial.write(B10010000);
        Serial.write(70);
        Serial.write(127);
        break;
     case 'b':
     
        Serial.write(B10010000);
        Serial.write(75);
        Serial.write(127);
        break;
         case 'c':
     
        Serial.write(B10010000);
        Serial.write(80);
        Serial.write(127);
        break;
         case 'd':
     
        Serial.write(B10010000);
        Serial.write(90);
        Serial.write(127);
        break;
         case 'e':
     
        Serial.write(B10010000);
        Serial.write(100);
        Serial.write(127);
        break;
     case 'f':
     
        Serial.write(B10010000);
        Serial.write(110);
        Serial.write(127);
        break;
    }
  }
   lcd.setCursor(0,0);
   lcd.print("patch number:");
   if(digitalRead(14) == LOW && patchnum < 127){
    
    patchnum++;
      Serial.write(B00000000);
        
        Serial.write(patchnum);
     delay(200);
   }


   if(digitalRead(16) == LOW && patchnum > 127){
    patchnum--;
 
     Serial.write(B00000000);
        
        Serial.write(patchnum);
    delay(200);
  }
}
