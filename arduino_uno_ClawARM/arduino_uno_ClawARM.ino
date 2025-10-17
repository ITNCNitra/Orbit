#include <Servo.h>

// ----- Servos (Uno/Nano) -----
#define SERVO1_PIN 3    // D3
#define SERVO2_PIN 5    // D5
#define SERVO3_PIN 6    // D6
#define SERVO4_PIN 9    // D9

Servo s1, s2, s3, s4;
int a1=90, a2=90, a3=90, a4=90;

void moveAngle(Servo &sv, int &ang, int delta){
  ang = constrain(ang + delta, 0, 180);
  sv.write(ang);
}

// ----- Stepper (28BYJ-48 via ULN2003/2803) -----
// IN1..IN4 from driver go to A0..A3 (digital-capable on AVR)
#define STP_IN1 A0
#define STP_IN2 A1
#define STP_IN3 A2
#define STP_IN4 A3

#define STEP_DELAY_US   1500
#define STEPS_PER_PRESS 100

const uint8_t HALFSEQ[8][4] = {
  {1,0,0,0}, {1,1,0,0}, {0,1,0,0}, {0,1,1,0},
  {0,0,1,0}, {0,0,1,1}, {0,0,0,1}, {1,0,0,1}
};
int phaseIdx = 0;

inline void stepperPhaseWrite(int i){
  digitalWrite(STP_IN1, HALFSEQ[i][0]);
  digitalWrite(STP_IN2, HALFSEQ[i][1]);
  digitalWrite(STP_IN3, HALFSEQ[i][2]);
  digitalWrite(STP_IN4, HALFSEQ[i][3]);
}

void stepperStep(int dir, int steps){
  for(int n=0;n<steps;n++){
    phaseIdx = (phaseIdx + (dir>0 ? 1 : 7)) & 0x07;
    stepperPhaseWrite(phaseIdx);
    delayMicroseconds(STEP_DELAY_US);
  }
}

void setup(){
  Serial.begin(115200);

  s1.attach(SERVO1_PIN);
  s2.attach(SERVO2_PIN);
  s3.attach(SERVO3_PIN);
  s4.attach(SERVO4_PIN);
  s1.write(a1); s2.write(a2); s3.write(a3); s4.write(a4);

  pinMode(STP_IN1, OUTPUT);
  pinMode(STP_IN2, OUTPUT);
  pinMode(STP_IN3, OUTPUT);
  pinMode(STP_IN4, OUTPUT);
  stepperPhaseWrite(phaseIdx);

  Serial.println("Controls:");
  Serial.println(" arm: q(open) w(close)");
  Serial.println(" S2: a(backward) s(forward)");
  Serial.println(" S3: z(down) x(up)");
  //Serial.println(" S4: e(empty) r(empty)");
  Serial.println(" Stepper: o(left) p(right)");
}

void loop(){
  if(Serial.available()){
    switch(Serial.read()){
      case 'q': moveAngle(s1,a1,-10); break;
      case 'w': moveAngle(s1,a1,+10); break;
      case 'a': moveAngle(s2,a2,-10); break;
      case 's': moveAngle(s2,a2,+10); break;
      case 'z': moveAngle(s3,a3,-10); break;
      case 'x': moveAngle(s3,a3,+10); break;
      case 'e': moveAngle(s4,a4,-10); break;
      case 'r': moveAngle(s4,a4,+10); break;
      case 'o': stepperStep(+1, STEPS_PER_PRESS); break;
      case 'p': stepperStep(-1, STEPS_PER_PRESS); break;
    }
  }
}
