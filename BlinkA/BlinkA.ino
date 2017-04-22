/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino model, check
  the Technical Specs of your board  at https://www.arduino.cc/en/Main/Products

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald

  modified 2 Sep 2016
  by Arturo Guadalupi

  modified 8 Sep 2016
  by Colby Newman
*/

int ledPin = 8;
int buttonPin = 6;
int etatDuBouton ;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {

  etatDuBouton =  digitalRead(buttonPin);  // turn the LED on (HIGH is the voltage level)

  Serial.print("Etat du bouton: ");
  Serial.print(etatDuBouton);
  Serial.println();

  if (etatDuBouton == HIGH) {
    allumeLed(100);
  }
  else (etatDuBouton == LOW) {
    allumeLed(100);
    eteindLed(300);// wait for a second
    allumeLed(100);
    eteindLed(300);// wait for a second
    allumeLed(300);
    eteindLed(300);// wait for a second
  }

  //JE FAIS DES CHOSES COMPLIQUES QUI PRENNENT DU TEMPS
  //allumeLed(100);
  //eteindLed(100);// wait for a second

}
void allumeLed(int dureeEnMillisecondes) {
  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(dureeEnMillisecondes);
}

void eteindLed(int dureeEnMillisecondes) {
  digitalWrite(ledPin, LOW);   // turn the LED on (LOW is the voltage level)
  delay(dureeEnMillisecondes);
}
