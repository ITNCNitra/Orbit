#include "ESP8266_ISR_Servo.h"

// ----- Servos -----
#define SERVO1_PIN D5   // GPIO14
#define SERVO2_PIN D6   // GPIO12
#define SERVO3_PIN D7   // GPIO13

#define MIN_US 500
#define MAX_US 2400

int s1 = -1, s2 = -1, s3 = -1;
int a1 = 90,  a2 = 90,  a3 = 90;

// ----- Stepper (28BYJ-48 via ULN2003/ULN2803) -----
// If boot issues occur, swap pins off D3/D4 (they're boot pins).
#define STP_IN1 D0      // GPIO5
#define STP_IN2 D1      // GPIO4
#define STP_IN3 D2      // GPIO0 (boot pin)
#define STP_IN4 D8      // GPIO2 (boot/LED pin)

#define STEP_DELAY_US     1500     // µs between half-steps (lower = faster)
#define STEPS_PER_PRESS   100      // how many half-steps per keypress

// 8-step half-step sequence (A,AB,B,BC,C,CD,D,DA)
const uint8_t HALFSEQ[8][4] = {
  {1,0,0,0}, {1,1,0,0}, {0,1,0,0}, {0,1,1,0},
  {0,0,1,0}, {0,0,1,1}, {0,0,0,1}, {1,0,0,1}
};
int phaseIdx = 0;

void attachOrHalt(int &idx, uint8_t pin) {
  idx = ISR_Servo.setupServo(pin, MIN_US, MAX_US);
  if (idx < 0) { Serial.printf("Attach failed on pin %d\n", pin); while (true) { delay(1000);} }
}

void moveAngle(int idx, int &ang, int delta) {
  ang = constrain(ang + delta, 0, 180);
  bool ok = ISR_Servo.setPosition(idx, ang);
  Serial.printf("Servo[%d] -> %d° : %s\n", idx, ang, ok ? "OK" : "FAIL");
}

// ---- Stepper helpers ----
inline void stepperPhaseWrite(int i) {
  digitalWrite(STP_IN1, HALFSEQ[i][0]);
  digitalWrite(STP_IN2, HALFSEQ[i][1]);
  digitalWrite(STP_IN3, HALFSEQ[i][2]);
  digitalWrite(STP_IN4, HALFSEQ[i][3]);
}

void stepperStep(int dir, int steps) {
  // dir = +1 (CW), -1 (CCW)
  for (int n = 0; n < steps; n++) {
    phaseIdx = (phaseIdx + (dir > 0 ? 1 : 7)) & 0x07; // wrap 0..7
    stepperPhaseWrite(phaseIdx);
    delayMicroseconds(STEP_DELAY_US);
    yield();
  }
}

void setup() {
  Serial.begin(115200);

  // Servos
  attachOrHalt(s1, SERVO1_PIN);
  attachOrHalt(s2, SERVO2_PIN);
  attachOrHalt(s3, SERVO3_PIN);
  ISR_Servo.setPosition(s1, a1);
  ISR_Servo.setPosition(s2, a2);
  ISR_Servo.setPosition(s3, a3);

  // Stepper pins
  pinMode(STP_IN1, OUTPUT);
  pinMode(STP_IN2, OUTPUT);
  pinMode(STP_IN3, OUTPUT);
  pinMode(STP_IN4, OUTPUT);
  stepperPhaseWrite(phaseIdx); // energize initial phase

  Serial.println("Controls:");
  Serial.println(" Servo1: q(-10) w(+10)");
  Serial.println(" Servo2: a(-10) s(+10)");
  Serial.println(" Servo3: z(-10) x(+10)");
  Serial.println(" Stepper: o(CCW/left) p(CW/right)");
}

void loop() {
  if (Serial.available()) {
    char k = Serial.read();
    switch (k) {
      // Servos
      case 'q': moveAngle(s1, a1, -10); break;
      case 'w': moveAngle(s1, a1, +10); break;
      case 'a': moveAngle(s2, a2, -10); break;
      case 's': moveAngle(s2, a2, +10); break;
      case 'z': moveAngle(s3, a3, -10); break;
      case 'x': moveAngle(s3, a3, +10); break;

      // Stepper
      case 'o': stepperStep(-1, STEPS_PER_PRESS); Serial.println("Stepper: CCW"); break;
      case 'p': stepperStep(+1, STEPS_PER_PRESS); Serial.println("Stepper: CW");  break;
      default: break;
    }
  }
  yield();
}
