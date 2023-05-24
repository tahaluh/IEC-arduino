#define STEPPER1_PIN_1 0
#define STEPPER1_PIN_2 1
#define STEPPER1_PIN_3 2
#define STEPPER1_PIN_4 3

#define STEPPER2_PIN_1 4
#define STEPPER2_PIN_2 5
#define STEPPER2_PIN_3 6
#define STEPPER2_PIN_4 8

#define STEPPER3_PIN_1 12
#define STEPPER3_PIN_2 11
#define STEPPER3_PIN_3 10
#define STEPPER3_PIN_4 9
int step_number = 0;
int maxSteps = 2072;
void setup() {
  pinMode(STEPPER1_PIN_1, OUTPUT);
  pinMode(STEPPER1_PIN_2, OUTPUT);
  pinMode(STEPPER1_PIN_3, OUTPUT);
  pinMode(STEPPER1_PIN_4, OUTPUT);

  pinMode(STEPPER2_PIN_1, OUTPUT);
  pinMode(STEPPER2_PIN_2, OUTPUT);
  pinMode(STEPPER2_PIN_3, OUTPUT);
  pinMode(STEPPER2_PIN_4, OUTPUT);

  pinMode(STEPPER3_PIN_1, OUTPUT);
  pinMode(STEPPER3_PIN_2, OUTPUT);
  pinMode(STEPPER3_PIN_3, OUTPUT);
  pinMode(STEPPER3_PIN_4, OUTPUT);
}

void loop() {

  if (step_number<=maxSteps){
    OneStep(true, STEPPER1_PIN_1, STEPPER1_PIN_2, STEPPER1_PIN_3, STEPPER1_PIN_4, step_number % 4);
    OneStep(true, STEPPER2_PIN_1, STEPPER2_PIN_2, STEPPER2_PIN_3, STEPPER2_PIN_4, step_number % 4);
    OneStep(true, STEPPER3_PIN_1, STEPPER3_PIN_2, STEPPER3_PIN_3, STEPPER3_PIN_4, step_number % 4);

    step_number++;
    if (step_number > 3) {
      //step_number = 0;
    }

    delay(2);
  }

 
}

void OneStep(bool dir, int pin1, int pin2, int pin3, int pin4, int step_number) {
  if (dir) {
    switch (step_number) {
      case 0:
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);
        break;
      case 1:
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);
        break;
      case 2:
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, HIGH);
        digitalWrite(pin4, LOW);
        break;
      case 3:
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, HIGH);
        break;
    }
  } else {
    switch (step_number) {
      case 0:
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, HIGH);
        break;
      case 1:
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, HIGH);
        digitalWrite(pin4, LOW);
        break;
      case 2:
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);
        break;
      case 3:
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);
    }
  }
}
