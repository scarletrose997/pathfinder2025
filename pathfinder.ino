int KEY1 = D0;
int KEY2 = D1;
int KEY3 = D2;
int KEY4 = D3;

int LED1 = D11;
int LED2 = D10;
int LED3 = D9;
int LED4 = D8;

int KEYS[4];
int LEDS[4];

const int MAX_LENGTH = 50;
int sequence[MAX_LENGTH];
int numOfRounds=1;

void setup(){
    KEYS[0] = KEY1;
    KEYS[1] = KEY2;
    KEYS[2] = KEY3;
    KEYS[3] = KEY4;
    LEDS[0] = LED1;
    LEDS[1] = LED2;
    LEDS[2] = LED3;
    LEDS[3] = LED4;

    for(int i=0; i<4; i++){
        pinMode(KEYS[i], INPUT_PULLUP);
        pinMode(LEDS[i], OUTPUT);
    }

    randomSeed(analogRead(0));
    newSequence();
    long startTime = millis();

}

void loop(){
    playPattern();

    if (!playerTurn()){
        allLightOn(3,200 );
        numOfRounds=1;
        newSequence();

    }else{
        delay(250);
        numOfRounds++;
        newSequence();
    }
    delay(1000);
}

void playPattern() {
    for (int i = 0; i < numOfRounds; i++) {
        int ledIndex = sequence[i];
        digitalWrite(LEDS[ledIndex], HIGH);
        delay(400);
        digitalWrite(LEDS[ledIndex], LOW);
        delay(200);
    }
}

bool playerTurn() {
    for (int i = 0; i < numOfRounds; i++) {
        int input = pendingKeypress();
        if (input != sequence[i]) {
        return false;
        }
    }
  return true;
}

int pendingKeypress() {
    while (true) {
        for (int i = 0; i < 4; i++) {
        if (digitalRead(KEYS[i]) == LOW) {
            digitalWrite(LEDS[i], HIGH);
            delay(200);
            digitalWrite(LEDS[i], LOW);
            waitUnpress(i);
            return i;
        }
        }
    }
}

void waitUnpress(int i) {
    while (digitalRead(KEYS[i]) == LOW) {
        delay(10);
    }
}

void allLightOn(int times, int delayTime) {
    for (int t = 0; t < times; t++) {
        for (int i = 0; i < 4; i++) {
        digitalWrite(LEDS[i], HIGH);
        }
        delay(delayTime);
        for (int i = 0; i < 4; i++) {
        digitalWrite(LEDS[i], LOW);
        }
        delay(delayTime);
    }
}

void newSequence() {
    for (int i = 0; i < numOfRounds; i++) {
        sequence[i] = random(0, 4);
    }
}
