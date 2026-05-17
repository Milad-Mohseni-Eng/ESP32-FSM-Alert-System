// ======================================================
// LIBRARIES
// ======================================================

#include <Wire.h>

#include <Adafruit_GFX.h>

#include <Adafruit_SSD1306.h>


// ======================================================
// OLED SETTINGS
// ======================================================

#define SCREEN_WIDTH 128

#define SCREEN_HEIGHT 64


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


// ======================================================
// PIN DEFINITIONS
// ======================================================

const int led1Pin = 15;
const int led2Pin = 2;
const int led3Pin = 4;

const int buzzerPin = 14;

const int buttonPin = 13;


// ======================================================
// TIMER VARIABLES
// ======================================================

// Stores time since last button interaction
unsigned long lastInteractionTime = 0;

// Stores how long button is held
unsigned long pressStartTime = 0;


// ======================================================
// SYSTEM STATES
// ======================================================

enum SystemState
{
  OFF,
  IDLE,
  ALERT,
  ERROR_STATE,
  ACTIVE
};

SystemState currentState = OFF;


// ======================================================
// SETUP
// ======================================================

void setup()
{
  // Configure LEDs
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);

  // Configure buzzer
  pinMode(buzzerPin, OUTPUT);

  // Configure button
  pinMode(buttonPin, INPUT_PULLUP);

  // Start I2C
  Wire.begin(21, 22);

  // Initialize OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    while(true);
  }

  // Start in OFF state
  showMessage("OFF");
}


// ======================================================
// MAIN LOOP
// ======================================================

void loop()
{
  int buttonState = digitalRead(buttonPin);


  // ======================================================
  // BUTTON PRESSED
  // ======================================================

  if(buttonState == LOW)
  {
    // Save press start time
    pressStartTime = millis();

    // Wait while button held
    while(digitalRead(buttonPin) == LOW)
    {
      // Long press detection
      if(millis() - pressStartTime > 3000)
      {
        currentState = ACTIVE;

        executeState();

        return;
      }
    }

    // Short press
    currentState = IDLE;

    // Reset inactivity timer
    lastInteractionTime = millis();
  }


  // ======================================================
  // INACTIVITY TIMERS
  // ======================================================

  // 7 seconds = ERROR
  if(millis() - lastInteractionTime > 7000)
  {
    currentState = ERROR_STATE;
  }

  // 3 seconds = ALERT
  else if(millis() - lastInteractionTime > 3000)
  {
    currentState = ALERT;
  }


  // ======================================================
  // EXECUTE CURRENT STATE
  // ======================================================

  executeState();

  delay(100);
}


// ======================================================
// STATE EXECUTION FUNCTION
// ======================================================

void executeState()
{
  switch(currentState)
  {

    // --------------------------------------------------
    // OFF STATE
    // --------------------------------------------------

    case OFF:

      digitalWrite(led1Pin, LOW);
      digitalWrite(led2Pin, LOW);
      digitalWrite(led3Pin, LOW);

      digitalWrite(buzzerPin, LOW);

      showMessage("OFF");

      break;


    // --------------------------------------------------
    // IDLE STATE
    // --------------------------------------------------

    case IDLE:

      digitalWrite(led1Pin, HIGH);

      digitalWrite(led2Pin, LOW);

      digitalWrite(led3Pin, LOW);

      shortBeep();

      showMessage("IDLE");

      break;


    // --------------------------------------------------
    // ALERT STATE
    // --------------------------------------------------

    case ALERT:

      digitalWrite(led1Pin, LOW);

      digitalWrite(led2Pin, HIGH);

      digitalWrite(led3Pin, LOW);

      shortBeep();

      showMessage("ALERT");

      break;


    // --------------------------------------------------
    // ERROR STATE
    // --------------------------------------------------

    case ERROR_STATE:

      digitalWrite(led1Pin, LOW);

      digitalWrite(led2Pin, LOW);

      digitalWrite(led3Pin, HIGH);

      longBeep();

      showMessage("ERROR");

      break;


    // --------------------------------------------------
    // ACTIVE STATE
    // --------------------------------------------------

    case ACTIVE:

      digitalWrite(led1Pin, HIGH);

      digitalWrite(led2Pin, HIGH);

      digitalWrite(led3Pin, HIGH);

      shortBeep();

      showMessage("ACTIVE");

      break;
  }
}


// ======================================================
// OLED MESSAGE FUNCTION
// ======================================================

void showMessage(String text)
{
  display.clearDisplay();

  display.setTextSize(2);

  display.setTextColor(SSD1306_WHITE);

  display.setCursor(10, 20);

  display.println(text);

  display.display();
}


// ======================================================
// SHORT BEEP
// ======================================================

void shortBeep()
{
  digitalWrite(buzzerPin, HIGH);

  delay(100);

  digitalWrite(buzzerPin, LOW);
}


// ======================================================
// LONG BEEP
// ======================================================

void longBeep()
{
  digitalWrite(buzzerPin, HIGH);

  delay(500);

  digitalWrite(buzzerPin, LOW);
}