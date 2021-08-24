const int NUM_SLIDERS = 5;
const int analogInputs[NUM_SLIDERS] = {A1, 10, A3, A2, A0};

const int LED1 = 4; // OK
const int LED2 = 2; // OK
const int LED3 = 5; // OK
const int LED4 = 6; // OK
const int LED5 = 3; // OK

const int INTER1 = 16; // OK
const int INTER2 = 14; // OK
const int INTER3 = 8; // OK
const int INTER4 = 9; // OK
const int INTER5 = 7; // OK

int MUTE1 = 0;
int MUTE2 = 0;
int MUTE3 = 0;
int MUTE4 = 0;
int MUTE5 = 0;

int analogSliderValues[NUM_SLIDERS];

void setup() { 
  for (int i = 0; i < NUM_SLIDERS; i++) {
    pinMode(analogInputs[i], INPUT);
  }

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);

  pinMode (INTER1, INPUT);
  pinMode (INTER2, INPUT);
  pinMode (INTER3, INPUT);
  pinMode (INTER4, INPUT);
  pinMode (INTER5, INPUT);
      
  Serial.begin(9600);
}

void loop() {
  ledon();
  interon();
  updateSliderValues();
  sendSliderValues(); // Actually send data (all the time)
  // printSliderValues(); // For debug
  delay(10);
}

void interon() {
    if (digitalRead (INTER1) == HIGH)
    {
      digitalWrite(LED1, HIGH);
      MUTE1 = 1;
    } else {
      digitalWrite(LED1, LOW);
      MUTE1 = 0;
    }

    if (digitalRead (INTER2) == HIGH)
    {
      digitalWrite(LED2, HIGH);
      MUTE2 = 1;
    } else {
      digitalWrite(LED2, LOW);
      MUTE2 = 0;
    }

    if (digitalRead (INTER3) == HIGH)
    {
      digitalWrite(LED3, HIGH);
      MUTE3 = 1;
    } else {
      digitalWrite(LED3, LOW);
      MUTE3 = 0;
    }

    if (digitalRead (INTER4) == HIGH)
    {
      digitalWrite(LED4, HIGH);
      MUTE4 = 1;
    } else {
      digitalWrite(LED4, LOW);
      MUTE4 = 0;
    }

    if (digitalRead (INTER5) == HIGH)
    {
      digitalWrite(LED5, HIGH);
      MUTE5 = 1;
    } else {
      digitalWrite(LED5, LOW);
      MUTE5 = 0;
    }
}

void updateSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {

    if( i == 0 ) {
      if( MUTE1 == 1 ) {
        analogSliderValues[i] = 0;
      } else {
        analogSliderValues[i] = analogRead(analogInputs[i]);
      }
    }

    if( i == 1 ) {
      if( MUTE2 == 1 ) {
        analogSliderValues[i] = 0;
      } else {
        analogSliderValues[i] = analogRead(analogInputs[i]);
      }
    }
    
    if( i == 2 ) {
      if( MUTE3 == 1 ) {
        analogSliderValues[i] = 0;
      } else {
        analogSliderValues[i] = analogRead(analogInputs[i]);
      }
    }

    if( i == 3 ) {
      if( MUTE4 == 1 ) {
        analogSliderValues[i] = 0;
      } else {
        analogSliderValues[i] = analogRead(analogInputs[i]);
      }
    }

    if( i == 4 ) {
      if( MUTE5 == 1 ) {
        analogSliderValues[i] = 0;
      } else {
        analogSliderValues[i] = analogRead(analogInputs[i]);
      }
    }
  }
}

void sendSliderValues() {
  String builtString = String("");

  for (int i = 0; i < NUM_SLIDERS; i++) {
    builtString += String((int)analogSliderValues[i]);

    if (i < NUM_SLIDERS - 1) {
      builtString += String("|");
    }
  }
  
  Serial.println(builtString);
}

void printSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    String printedString = String("Slider #") + String(i + 1) + String(": ") + String(analogSliderValues[i]) + String(" mV");

    Serial.write(printedString.c_str());

    if (i < NUM_SLIDERS - 1) {
      Serial.write(" | ");
    } else {
      Serial.write("\n");
    }
  }
}
