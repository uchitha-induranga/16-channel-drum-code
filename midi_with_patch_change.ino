#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int pinRead;
char pinAssignments[16] = {'A0', 'A1', 'A2', 'A3', 'A4', 'A5', 'A6', 'A7','A8', 'A9','A10', 'A11','A12', 'A13','A14', 'A15'};
byte PadNote[16] = { 60, 61, 62, 63, 64, 65, 66, 67,68,69,70,71,72,73,74,75};
int PadCutOff[16] = { 900, 900, 900, 900, 900, 900, 900, 900,900, 900, 900, 900, 900, 900, 900, 900};
int MaxPlayTime[16] = { 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40};
#define midichannel 1;
boolean VelocityFlag = true;
// Internal Use Variables
boolean activePad[16] = { 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0 };
int PinPlayTime[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
byte status1;
int pin = 0;
int hitavg = 0;
#define Btn_L 9
#define Btn_R 8
byte patchNum = 0;
int c = 1;
void setup()
{
Serial.begin(115200); 
pinMode(Btn_L, INPUT_PULLUP);
pinMode(Btn_R, INPUT_PULLUP);
lcd.begin(16, 2);
 lcd.setCursor(0,0); 
  lcd.print("HRTE PROJECTS");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("DRUM CHANNEL16");
  lcd.setCursor(6,2); 
  lcd.print("OCTAPAD");
  delay(2000);
  lcd.clear();
   lcd.setCursor(0,0); 
  lcd.print("created by:");
 lcd.setCursor(0,1);
 lcd.print("UchithaInduranga ");
 delay(2000);
 lcd.clear();
}
void loop()
{
for (int pin = 0; pin < 16; pin++)
{
hitavg = analogRead(pinAssignments[pin]);
if ((hitavg > PadCutOff[pin]))
{
if ((activePad[pin] == false))
{
if (VelocityFlag == true)
{
hitavg = (hitavg / 16) - 1 ;
}
else
{
hitavg = 127;
}
MIDI_TX(144, PadNote[pin], hitavg);
PinPlayTime[pin] = 0;
activePad[pin] = true;
}
else
{
PinPlayTime[pin] = PinPlayTime[pin] + 1;
}
}
else if ((activePad[pin] == true))
{
PinPlayTime[pin] = PinPlayTime[pin] + 1;
if (PinPlayTime[pin] > MaxPlayTime[pin])
{
activePad[pin] = false;
MIDI_TX(144, PadNote[pin], 0);
}
}
}
if (digitalRead(Btn_R) == HIGH && patchNum < 256) {
patchNum++;
c ++;
lcd.clear();
lcd.setCursor(4, 0);
lcd.print("PATCH: ");
lcd.print(c);
delay(200);
}
if (digitalRead(Btn_L) == HIGH && patchNum >= 1) {
patchNum--;
c --;
lcd.clear();
lcd.setCursor(4, 0);
lcd.print("PATCH: ");
lcd.print(c);
delay(200);
}
}
// Transmit MIDI Message
void MIDI_TX(byte MESSAGE, byte PITCH, byte VELOCITY)
{
status1 = MESSAGE + midichannel;
Serial.write(status1);
Serial.write(PITCH);
Serial.write(VELOCITY);
}
