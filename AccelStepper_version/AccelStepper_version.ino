#include <AccelStepper.h>

#define HALFSTEP 4

#define STEPPER1_PIN_1  0     // IN1 on ULN2003 ==> Blue   on 28BYJ-48
#define STEPPER1_PIN_2  1     // IN2 on ULN2004 ==> Pink   on 28BYJ-48
#define STEPPER1_PIN_3  2    // IN3 on ULN2003 ==> Yellow on 28BYJ-48
#define STEPPER1_PIN_4  3    // IN4 on ULN2003 ==> Orange on 28BYJ-48

#define STEPPER2_PIN_1  4     // IN1 on ULN2003 ==> Blue   on 28BYJ-48
#define STEPPER2_PIN_2  5     // IN2 on ULN2004 ==> Pink   on 28BYJ-48
#define STEPPER2_PIN_3  6    // IN3 on ULN2003 ==> Yellow on 28BYJ-48
#define STEPPER2_PIN_4  8    // IN4 on ULN2003 ==> Orange on 28BYJ-48

#define STEPPER3_PIN_1  9     // IN1 on ULN2003 ==> Blue   on 28BYJ-48
#define STEPPER3_PIN_2  10     // IN2 on ULN2004 ==> Pink   on 28BYJ-48
#define STEPPER3_PIN_3  11    // IN3 on ULN2003 ==> Yellow on 28BYJ-48
#define STEPPER3_PIN_4  12    // IN4 on ULN2003 ==> Orange on 28BYJ-48

int endPoint = 2048*10;        // Move this many steps - 1024 = approx 1/4 turn

// NOTE: The sequence 1-3-2-4 is required for proper sequencing of 28BYJ-48
AccelStepper stepper1(HALFSTEP, STEPPER1_PIN_1, STEPPER1_PIN_3, STEPPER1_PIN_2, STEPPER1_PIN_4);
AccelStepper stepper2(HALFSTEP, STEPPER2_PIN_1, STEPPER2_PIN_3, STEPPER2_PIN_2, STEPPER2_PIN_4);
AccelStepper stepper3(HALFSTEP, STEPPER3_PIN_1, STEPPER3_PIN_3, STEPPER3_PIN_2, STEPPER3_PIN_4);

void setup()
{
  // com o serial os pins 0 e 1 não funcionam
  Serial.begin(9600);
  
  // seta todos os pins como saida
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

  stepper1.setMaxSpeed(500.0);;
  stepper1.setAcceleration(80.0);
  stepper1.setSpeed(200);
  stepper1.moveTo(endPoint);
  stepper1.setPinsInverted(); // inverte o sinal sem driver

  stepper2.setMaxSpeed(500.0);
  stepper2.setAcceleration(80.0);
  stepper2.setSpeed(200);
  stepper2.moveTo(endPoint);
  stepper2.setPinsInverted(); // inverte o sinal sem driver

  stepper3.setMaxSpeed(500.0);;
  stepper3.setAcceleration(80.0);
  stepper3.setSpeed(200);
  stepper3.moveTo(endPoint);
  stepper3.setPinsInverted(); // inverte o sinal sem driver
}

void loop()
{
  //Change direction at the limits
    if (stepper1.distanceToGo() == 0)
   {
     stepper1.setCurrentPosition(0);
     stepper1.moveTo(endPoint);
   }
    stepper1.run();

    //Change direction at the limits
    if (stepper2.distanceToGo() == 0)
   {
     stepper2.setCurrentPosition(0);
     stepper2.moveTo(endPoint);
   }
    stepper2.run();

    //Change direction at the limits
    if (stepper3.distanceToGo() == 0)
   {
     stepper3.setCurrentPosition(0);
     stepper3.moveTo(endPoint);
   }
    stepper3.run();

    
}