include <LiquidCrystal.h> //LCD-Bibliothek laden

//LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //Festlegung der Pins des Mikrocontrollerboards für das LCD

//Ultraschallsensor
int trigger=7; //Trigger-Pin des USS an Pin7 des Mikrocontrollerboards
int echo=6; //Echo-Pin des USS an Pin6 des Mikrocontrollerboards
long dauer=0; //Variable, mit der die Zeit die eine Schallwelle bis zur Relektion und zurück benötigt
long entfernung=0; // Variable, zum speichern der Entfernung

//Buzzer
int buzzer=13; //Buzzer auf Pin13 des Mikrocontrollerboards
int ton=300; //Tonhöhe

//LED
int ledbl=10; //LEDbl auf Pin10 des Mikrocontrollerboards
int ledge=9; //LEDge auf Pin9 des Mikrocontrollerboards
int ledrt=8; //LEDrt auf Pin8 des Mikrocontrollerboards

void setup()
{
//LCD
lcd.begin(16,2); //Verwendete Zeichen und Zeilen

//Ultraschallsensor
pinMode(trigger, OUTPUT); //Trigger-Pin ist ein Ausgang
pinMode(echo, INPUT); //Echo-Pin ist ein Eingang

//Buzzer
pinMode(buzzer, OUTPUT); //Buzzer-Pin ist ein Ausgang

//LED
pinMode(ledbl, OUTPUT); //LEDbl-Pin ist ein Ausgang
pinMode(ledge, OUTPUT); //LEDge-Pin ist ein Ausgang
pinMode(ledrt, OUTPUT); //LEDrt-Pin ist ein Ausgang

}

void loop()
{
digitalWrite(trigger, LOW); //Hier nimmt man die Spannung für kurze Zeit vom Trigger-Pin, damit man später beim senden des Trigger-Signals ein rauschfreies Signal hat.
delay(5); //Dauer: 5 Millisekunden
digitalWrite(trigger, HIGH); //Jetzt sendet man eine Ultraschallwelle los.
delay(10); //Dieser „Ton“ erklingt für 10 Millisekunden.
digitalWrite(trigger, LOW);//Dann wird der „Ton“ abgeschaltet.
dauer = pulseIn(echo, HIGH); //Mit dem Befehl „pulseIn“ zählt der Mikrokontroller die Zeit in Mikrosekunden, bis der Schall zum Ultraschallsensor zurückkehrt.
entfernung = (dauer/2) * 0.03432; //Nun berechnet man die Entfernung in Zentimetern. Man teilt zunächst die Zeit durch zwei  (Weil man ja nur eine Strecke berechnen möchte und nicht die Strecke hin- und zurück). Den Wert multipliziert man mit der Schallgeschwindigkeit in der Einheit Zentimeter/Mikrosekunde und erhält dann den Wert in Zentimetern.

  if (entfernung >= 300 || entfernung <= 10) //Wenn die gemessene Entfernung über 300cm oder unter 10cm liegt,…
  {
    lcd.setCursor(0, 0); //Startpositon auf dem LCD; erstes Zeichen, erste Zeile
    lcd.print("Nicht messbar"); //Ausgabewert1
    lcd.setCursor(0, 1); //Startpositon auf dem LCD; erstes Zeichen, zweite Zeile
    lcd.println(""); //Ausgabewert2
  }
  else //  Ansonsten…
  {
    lcd.setCursor(0, 0); //Startpositon auf dem LCD; erstes Zeichen, erste Zeile
    lcd.print("Abstand"); //Ausgabewert1
    lcd.setCursor(0, 1); //Startpositon auf dem LCD; erstes Zeichen, zweite Zeile
    lcd.print(entfernung); //Ausgabewert2
    lcd.println(" cm"); //Angabe der Einheit hinter dem Ausgabewert
  }
  if (entfernung < 300)
  {
    digitalWrite(ledbl, HIGH); //Ansteuerung der LEDbl bei einem Abstand kleiner als 300
    ton = 250; //Tonhöhe bei Abstand kleiner als 300
  }
  else
  {
    digitalWrite(ledbl,LOW); //keine Ansteuerung der LEDbl
  }

  if (entfernung < 100)
  {
    digitalWrite(ledge, HIGH); //Ansteuerung der LEDge bei einem Abstand kleiner als 100
    ton = 270; //Tonhöhe bei Abstand kleiner als 100
  }
  else
  {
    digitalWrite(ledge, LOW); //keine Ansteuerung der LEDge
  }
  if (entfernung < 50)
  {
    digitalWrite(ledrt, HIGH); //Ansteuerung der LEDrt bei einem Abstand kleiner als 50
    ton = 300; //Tonhöhe bei Abstand kleiner als 50
  }
  else
  {
    digitalWrite(ledrt,LOW); //keine Ansteuerung der LEDrt
  }
  if (entfernung >= 300 || entfernung <= 10)
  {
    noTone(buzzer); //kein Ton im ausgewählten Bereich
  }
  else
  {
    tone(buzzer, ton); //Tonwiedergabe wenn im ausgewählten Bereich
  }
  delay(500); //Messwerterfassung ca. jede halbe Sekunde
}
