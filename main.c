const int ledPin = 13;      // Built-in LED pin (D13)
const int voltagePin = A0;  // Analog input for 1-5V signal

// Global Variables
unsigned long blinkCount = 0;  // Count of blink cycles
float measuredVoltage = 0.0;
float Pact = 0;                       // Measured input voltage
unsigned long previousBlinkTime = 0;  // For timing control
const int BLINK_INTERVAL = 1000;         // 1000ms blink interval
const int Resistence = 248;
unsigned long startTime;

void setup() {
  pinMode(ledPin, OUTPUT);  // Initialize built-in LED
  Serial.begin(115200);     // Start serial communication
  Serial.println(F("Count\tVoltage (V)\tTime (ms)"));
  Serial.println(F("--------------------------------"));
  startTime = millis();  // according to demand
}

void loop() {
  // Read and calculate input voltage
  int rawADC = analogRead(voltagePin);
  measuredVoltage = rawADC * (5.0 / 1023.0);  // Convert to voltage



  // Check if voltage is in valid range (1-5V)
  if (measuredVoltage >= 0.0 && measuredVoltage <= 5.0) {
    Pact = 10.080 * (measuredVoltage) - 10;
    unsigned long currentTime = millis();
    if (currentTime - startTime <= 60000) {
      // Blink control with millis() for non-blocking timing
      if (currentTime - previousBlinkTime >= BLINK_INTERVAL) {
        previousBlinkTime = currentTime;

        // Toggle LED state
        digitalWrite(ledPin, !digitalRead(ledPin));

        // Increment and log record
        blinkCount++;
        Serial.print(blinkCount);
        Serial.print(F("\t"));
        Serial.print(Pact, 2);
        Serial.print(F("\t\t"));
        Serial.println(currentTime);
      }
    } else {
      digitalWrite(ledPin, LOW);  // Turn off LED if voltage out of range
    }
  }
}
