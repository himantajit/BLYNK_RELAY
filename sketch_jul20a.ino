#define BLYNK_TEMPLATE_ID "TMPL3qRih-wLo"
#define BLYNK_TEMPLATE_NAME "ESP8266 RELAY"
#define BLYNK_AUTH_TOKEN "AUTH_TOKEN"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "wifi";
char pass[] = "pass";

char auth[] = BLYNK_AUTH_TOKEN;  

BlynkTimer timer;

#define button1_pin D4
#define button2_pin D3
#define button3_pin D7
#define button4_pin D8

#define relay1_pin D1
#define relay2_pin D2
#define relay3_pin D5
#define relay4_pin D6

int relay1_state = 0;
int relay2_state = 0;
int relay3_state = 0;
int relay4_state = 0;

#define button1_vpin V1
#define button2_vpin V2
#define button3_vpin V3
#define button4_vpin V4

// This function is called every time the device is connected to the Blynk.Cloud
// Request the latest state from the server
BLYNK_CONNECTED() {
  Blynk.syncVirtual(button1_vpin);
  Blynk.syncVirtual(button2_vpin);
  Blynk.syncVirtual(button3_vpin);
  Blynk.syncVirtual(button4_vpin);
}

// This function is called every time the Virtual Pin state changes
// i.e., when the web push switch from Blynk App or Web Dashboard
BLYNK_WRITE(button1_vpin) {
  relay1_state = param.asInt();
  digitalWrite(relay1_pin, relay1_state);
}

BLYNK_WRITE(button2_vpin) {
  relay2_state = param.asInt();
  digitalWrite(relay2_pin, relay2_state);
}

BLYNK_WRITE(button3_vpin) {
  relay3_state = param.asInt();
  digitalWrite(relay3_pin, relay3_state);
}

BLYNK_WRITE(button4_vpin) {
  relay4_state = param.asInt();
  digitalWrite(relay4_pin, relay4_state);
}

void setup() {
  // Debug console
  Serial.begin(115200);

  pinMode(button1_pin, INPUT_PULLUP);
  pinMode(button2_pin, INPUT_PULLUP);
  pinMode(button3_pin, INPUT_PULLUP);
  pinMode(button4_pin, INPUT_PULLUP);

  pinMode(relay1_pin, OUTPUT);
  pinMode(relay2_pin, OUTPUT);
  pinMode(relay3_pin, OUTPUT);
  pinMode(relay4_pin, OUTPUT);

  // During starting, all relays should TURN OFF
  digitalWrite(relay1_pin, HIGH);
  digitalWrite(relay2_pin, HIGH);
  digitalWrite(relay3_pin, HIGH);
  digitalWrite(relay4_pin, HIGH);

  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  timer.run();
  listen_push_buttons();
}

void listen_push_buttons() {
  static unsigned long lastPressTime1 = 0;
  static unsigned long lastPressTime2 = 0;
  static unsigned long lastPressTime3 = 0;
  static unsigned long lastPressTime4 = 0;
  unsigned long currentTime = millis();
  const unsigned long debounceDelay = 200;

  if (digitalRead(button1_pin) == LOW && (currentTime - lastPressTime1 > debounceDelay)) {
    lastPressTime1 = currentTime;
    control_relay(1);
    Blynk.virtualWrite(button1_vpin, relay1_state);  // Update button state
  }

  if (digitalRead(button2_pin) == LOW && (currentTime - lastPressTime2 > debounceDelay)) {
    lastPressTime2 = currentTime;
    control_relay(2);
    Blynk.virtualWrite(button2_vpin, relay2_state);  // Update button state
  }

  if (digitalRead(button3_pin) == LOW && (currentTime - lastPressTime3 > debounceDelay)) {
    lastPressTime3 = currentTime;
    control_relay(3);
    Blynk.virtualWrite(button3_vpin, relay3_state);  // Update button state
  }

  if (digitalRead(button4_pin) == LOW && (currentTime - lastPressTime4 > debounceDelay)) {
    lastPressTime4 = currentTime;
    control_relay(4);
    Blynk.virtualWrite(button4_vpin, relay4_state);  // Update button state
  }
}

void control_relay(int relay) {
  switch (relay) {
    case 1:
      relay1_state = !relay1_state;
      digitalWrite(relay1_pin, relay1_state);
      Serial.print("Relay1 State = ");
      Serial.println(relay1_state);
      break;
    case 2:
      relay2_state = !relay2_state;
      digitalWrite(relay2_pin, relay2_state);
      break;
    case 3:
      relay3_state = !relay3_state;
      digitalWrite(relay3_pin, relay3_state);
      break;
    case 4:
      relay4_state = !relay4_state;
      digitalWrite(relay4_pin, relay4_state);
      break;
  }
  delay(50);
}
