unsigned long currentTime = 0;
int ledPins[] = {8, 9, 10, 11};
int nbLeds = (sizeof(ledPins)) / sizeof(ledPins[0]);
int pot_val = 0;
int potPin = A1;
int pinBtn = 2;
int range = 20;
int mapIndex = 0;
int mapLed = 0;

int estClic(unsigned long ct);
void afficherProgression(int mapIndex, unsigned long ct);
void ledTask(int nbLeds, int mapLed);

void setup() {
  Serial.begin(9600);

  // Ton code ici
  for( int i = 0; i < nbLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(pinBtn, INPUT_PULLUP);


  Serial.println("Setup completed");
}

void loop() {
  currentTime = millis();
  pot_val = analogRead(potPin);
  mapIndex = map(pot_val, 0, 1023, 0, range);
  mapLed = map(pot_val, 0, 1023, 0, 3);

  ledTask(nbLeds, mapLed);
  afficherProgression(mapIndex, currentTime);
  
  
  

}
void ledTask(int nbLeds, int mapLed) {
  for(int i = 0; i < nbLeds; i++) {
    if(i == mapLed) {
      digitalWrite(ledPins[i], HIGH);
    }
    else {
    digitalWrite(ledPins[i], LOW);
    }
  }
}
int estClic(unsigned long ct) {
  int clic = 0;
  static int previous_state = 1;
  static unsigned long previousTime = 0;
  const int rate = 20;
  
  if(ct - previousTime < rate) {
    return clic;
  }

  previousTime = ct;

  int actual_state = digitalRead(pinBtn);
  
  if(actual_state == 0) {
    if(actual_state != previous_state) {
      clic = 1;
    }
  }
  previous_state = actual_state;
  return clic;
}
void afficherProgression(int mapIndex, unsigned long ct) {
  int pourcentage = map(pot_val, 0, 1023, 0, 100);

  if(estClic(ct)) {
    Serial.print(pourcentage);
    Serial.print("%");
    Serial.print(" [");
    for(int i = 0; i < range; i++) {
      
      if(i < mapIndex) {
        Serial.print("@");
      }
      else {
        Serial.print(".");
      }
    }
    Serial.println("]");
  }
}