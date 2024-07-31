// define button pins
#define RESET_BUTTON_PIN 4
#define MIN2_BUTTON_PIN 5
#define MIN3_BUTTON_PIN 6
#define MIN5_BUTTON_PIN 7
#define LED 3
#define RELAY_PIN 2
#define waitTime 500
// define variables to track timer state
int sec = 0;
unsigned long startTime = 0;
bool min2_state = false;
bool min3_state = false;
bool min5_state = false;
bool rst_state = false;
int timerlen = 0;

//void handleInterrupt() {
//  if (digitalRead(MIN5_BUTTON_PIN) == LOW) {
//    digitalWrite(RELAY_PIN, LOW);
//  } else {
//    digitalWrite(RELAY_PIN, HIGH);
//  }
//}

void setup() {
  // initialize serial communication
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(RESET_BUTTON_PIN, INPUT);
  pinMode(MIN2_BUTTON_PIN, INPUT);
  pinMode(MIN3_BUTTON_PIN, INPUT);
  pinMode(MIN5_BUTTON_PIN, INPUT);  // Enable internal pull-up resistor
  pinMode(RELAY_PIN, OUTPUT);

  // Set interrupt on change for MIN5_BUTTON_PIN
  //  attachInterrupt(digitalPinToInterrupt(MIN5_BUTTON_PIN), handleInterrupt, CHANGE);

  Serial.println("Starting");
  digitalWrite(RELAY_PIN, 0);
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
}


void loop() {
  digitalWrite(LED, LOW);
  updatebuttons();
  updateTimer(startTime);
  if (min2_state) timerlen = 2;
  else if (min3_state) timerlen = 3;
  else if (min5_state) timerlen = 5;
  else {
    Serial.print("no time selcted");
    digitalWrite(RELAY_PIN, 0);
    timerlen = 0;
    startTime = 0;
    sec = 0;
  }
  min2_state = 0;
  min3_state = 0;
  min5_state = 0;
  switch (timerlen) {
    case 5:
    digitalWrite(LED, HIGH);
      digitalWrite(RELAY_PIN, HIGH);
      delay(2);
      Serial.println("horn");
//      delay(150);
      break;
    case 3:
     digitalWrite(LED, HIGH);
      digitalWrite(RELAY_PIN, 0);
      threeMin();
      Serial.println("3 minute Timer startTime");
      break;
    case 2:
     digitalWrite(LED, HIGH);
      digitalWrite(RELAY_PIN, 0);
      twoMin();
      Serial.println("2 minute Timer startTime");
      break;
  }
  timerlen = 0;
}
void fiveMin() {
  startTime = millis();
  delay(200);
  sec = (millis() - startTime) / 1000;
  //5 min = 300s; 4 min = 240s; 3 min = 180s; 2 min = 120s; 1.5 min = 90s; 1 min = 60s
  while (sec < 300) {
    if (!updateTimer(startTime)) return;
    //    sec = (millis() - startTime) / 1000;
    delay(50);
    switch (300 - sec) {
      case 300:
        longBlast(5);
        break;
      case 180:
        longBlast(3);
        break;
      case 120:
        longBlast(2);
        break;
      case 90:
        longBlast(1);
        shortBlast(3);
        break;
      case 60:
        longBlast(1);
        break;
      case 30:
        shortBlast(3);
        break;
      case 20:
        shortBlast(2);
        break;
      case 10:
        shortBlast(1);
        break;
      case 0:
        go(startTime);
        break;
    }
    sec = (millis() - startTime) / 1000;
  }
}

void threeMin() {
  startTime = millis();
  delay(200);
  sec = (millis() - startTime) / 1000;
  //  3 min = 180s; 2 min = 120s; 1.5 min = 90s; 1 min = 60s
  while (sec < 180) {
    if (!updateTimer(startTime)) return;
    //    sec = (millis() - startTime) / 1000;
    delay(50);
    switch (180 - sec) {
      case 180:
        longBlast(3);
        break;
      case 120:
        longBlast(2);
        break;
      case 90:
        longBlast(1);
        shortBlast(3);
        break;
      case 60:
        longBlast(1);
        break;
      case 30:
        shortBlast(3);
        break;
      case 20:
        shortBlast(2);
        break;
      case 10:
        shortBlast(1);
        break;
      case 5:
        go(startTime);
        break;
    }
    sec = (millis() - startTime) / 1000;
    if (!updateTimer(startTime)) return;
  }
}

void twoMin() {
  Serial.println("two minutes");
  startTime = millis();
  if (!updateTimer(startTime)) return;
  delay(200);
  sec = (millis() - startTime) / 1000;
  //2 min = 120s; 1.5 min = 90s; 1 min = 60s
  while (sec < 120) {

    //    sec = (millis() - startTime) / 1000;
    delay(50);
    switch (120 - sec) {
      case 120:
        {
          longBlast(2);
        }
        break;
      case 90:
        {
          longBlast(1);
          shortBlast(3);
        }
        break;
      case 60:
        {
          longBlast(1);
        }
        break;
        break;
      case 30:
        {
          shortBlast(3);
        }
        break;
      case 20:
        {
          shortBlast(2);
        }
        break;
      case 10:
        {
          shortBlast(1);
        }
        break;
      case 5:
        {
          go(startTime);
        }
        break;
    }
    //    sec = (millis() - startTime) / 1000;
    if (!updateTimer(startTime)) return;
  }
  updateTimer(startTime);
}

void longBlast(int count) {
  Serial.println("Long Blast start");
  Serial.println(count);
  for (int i = 0; i < count; i++) {
    digitalWrite(RELAY_PIN, HIGH);
    delay(waitTime * 1.25);
    digitalWrite(RELAY_PIN, 0);
    delay(200);
    if (!updateTimer(startTime)) return;
  }
  delay(250);
  Serial.println("Long Blast end");
}

void shortBlast(int count) {
  for (int i = 0; i < count; i++) {
    digitalWrite(RELAY_PIN, HIGH);
    delay(waitTime / 3);
    digitalWrite(RELAY_PIN, 0);
    delay(200);
    if (!updateTimer(startTime)) return;
  }
}

void go(int startTime) {
  for (int i = 0; i < 5; i++) {
    digitalWrite(RELAY_PIN, HIGH);
    delay(750);
    digitalWrite(RELAY_PIN, 0);
    delay(250);
    if (!updateTimer(startTime)) return;
  }
  digitalWrite(RELAY_PIN, HIGH);
  delay(3000);
  digitalWrite(RELAY_PIN, 0);
}

void updatebuttons() {
  rst_state = 0;
  min2_state = 0;
  min3_state = 0;
  min5_state = 0;
  for (int i = 0; i < 25; i++) {
    if (rst_state == LOW) {
      rst_state = digitalRead(RESET_BUTTON_PIN);
    }
    if (min2_state == LOW)
      min2_state = digitalRead(MIN2_BUTTON_PIN);
    if (min3_state == LOW)
      min3_state = digitalRead(MIN3_BUTTON_PIN);
    if (min5_state == LOW)
      min5_state = digitalRead(MIN5_BUTTON_PIN);
    delay(1);
  }
}

bool updateTimer(int startTime) {
  if (digitalRead(RESET_BUTTON_PIN) == HIGH) {
    Serial.println("reset");
    return false;
  }
  sec = (millis() - startTime) / 1000;
  String out = String((timerlen * 60 - sec) / 60);
  out += ":";
  out += String((timerlen * 60 - sec - ((timerlen * 60 - sec) / 60) * 60) % 60);
  if (startTime == 0) out = "0:00";
  // else
  // Serial.println(out);
  delay(2);
  return true;
}
