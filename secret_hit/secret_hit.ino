// Code for playing Secret Hit

#include <LiquidCrystal.h>
#define DEBOUNCE_DELAY 1000  // Debounce time in milliseconds

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int reply = 0;

int toggleButtonPin = 6;
int toggleButtonState = 0;
int previousToggleButtonState = 0;

int jaButtonPin = 13;
int jaButtonState = 0;
int previousJaButtonState = 0;

int neinButtonPin = 8;
int neinButtonState = 0;
int previousNeinButtonState = 0;

int neinCount = 0;
int jaCount = 0;
bool showingVotes = false;

unsigned int lastPressTime = 0;

void hideVotes(){
    lcd.clear();
    int totVotes = neinCount + jaCount;
    String votesString = "Total votes: " + String(totVotes);
    lcd.print(votesString);
    showingVotes = false;
}

void showVotes(){
    lcd.clear();
    String result = "Nein: " + String(neinCount) + " Ja: " + String(jaCount);
    lcd.print(result);
    showingVotes = true;
}

void resetVotes(){
    neinCount = 0;
    jaCount = 0;
    hideVotes();
}

bool ButtonPressed(int& currentState, int& previousState) {
    unsigned long currentTime = millis();
    if(currentState == HIGH && previousState == LOW && currentTime - lastPressTime > DEBOUNCE_DELAY) {
        lastPressTime = currentTime;
        previousState = currentState;  // Update previous state here
        return true;
    }
    if(currentState == LOW && previousState == HIGH){
        previousState = currentState;  // Update previous state here
    }
    return false;
}


void setup() {
    hideVotes();
}

void loop() {
    toggleButtonState = digitalRead(toggleButtonPin);
    jaButtonState = digitalRead(jaButtonPin);
    neinButtonState = digitalRead(neinButtonPin);

    if (ButtonPressed(toggleButtonState, previousToggleButtonState)) {
        if (showingVotes) {
            hideVotes();
        } else {
            showVotes();
        }
    }

    if (ButtonPressed(jaButtonState, previousJaButtonState)) {
        jaCount++;
        hideVotes();
    }

    if (ButtonPressed(neinButtonState, previousNeinButtonState)) {
        neinCount++;
        hideVotes();
    }

    if (jaButtonState == HIGH && neinButtonState == HIGH){
        resetVotes();
    }
}
