#include "pitches.h"


int buttonState = 0;
int ledNr = 13;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(2, INPUT_PULLUP);
    for(int i = 4; i<=13; i++){
      pinMode(i, OUTPUT);
    }

}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = !digitalRead(2);

  //Buttonpress
  if(buttonState == HIGH){
    Serial.println(ledNr);
    digitalWrite(ledNr, HIGH);
    ledNr--;
    delay(250v fc);
  }

  //Success
  if(ledNr <= 3){
    playSuccess();
    ledNr = 13;
    clearLeds();
  }
}

void clearLeds(){
  for(int i = 4; i<=13; i++){
      digitalWrite(i, LOW);
  }
}

void playSuccess(){
  int songlen = 5;
  int song[] = {NOTE_A5, NOTE_A5, NOTE_A5, NOTE_G5, NOTE_A5};
  int dur[] = {400, 200, 200, 200, 800};
  for(int note = 0; note < songlen; note++){
    tone(3, song[note]);
    delay(dur[note]);
    noTone(3);
  }
}
