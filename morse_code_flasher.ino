/*
  Morse Code Flasher
  -------------------
  Every LED blinks the same message in Morse code, over and over.

  Morse timing (1 "unit" = UNIT milliseconds):
    dot             = 1 unit ON
    dash            = 3 units ON
    gap in a letter = 1 unit OFF   (between the dots/dashes of one letter)
    gap btwn letters= 3 units OFF
    gap btwn words  = 7 units OFF
*/

// 1) LIST YOUR LED PINS HERE.
//    From your picture the LEDs look like they're on pins 1 through 13.
//    Edit this list so it matches EXACTLY how you wired them.
const int ledPins[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
const int NUM_LEDS = sizeof(ledPins) / sizeof(ledPins[0]);

// 2) TYPE YOUR MESSAGE HERE (letters, numbers and spaces only).
const char message[] = "Mohammed";

// 3) SPEED. Higher number = slower blinking. 200 is a good starting point.
const int UNIT = 200;

// Morse patterns for A-Z
const char* LETTERS[] = {
  ".-","-...","-.-.","-..",".","..-.","--.","....","..",".---",
  "-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-",
  "..-","...-",".--","-..-","-.--","--.."
};
// Morse patterns for 0-9
const char* DIGITS[] = {
  "-----",".----","..---","...--","....-",
  ".....","-....","--...","---..","----."
};

void setLeds(int state) {
  for (int i = 0; i < NUM_LEDS; i++) digitalWrite(ledPins[i], state);
}

void playSymbol(char symbol) {
  setLeds(HIGH);
  delay(symbol == '.' ? UNIT : UNIT * 3);  // dot = 1 unit, dash = 3 units
  setLeds(LOW);
  delay(UNIT);                             // gap between symbols = 1 unit
}

void playCode(const char* code) {
  for (int i = 0; code[i] != '\0'; i++) playSymbol(code[i]);
  delay(UNIT * 2);   // brings the gap after a letter up to 3 units total
}

void setup() {
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
}

void loop() {
  for (int i = 0; message[i] != '\0'; i++) {
    char c = message[i];
    if (c >= 'a' && c <= 'z') c -= 32;      // lowercase -> uppercase

    if (c >= 'A' && c <= 'Z')      playCode(LETTERS[c - 'A']);
    else if (c >= '0' && c <= '9') playCode(DIGITS[c - '0']);
    else if (c == ' ')             delay(UNIT * 4);  // word gap = 7 units total
  }

  setLeds(LOW);      // turn every LED off
  while (true) { }   // stop here -- the message plays once, then halts
}