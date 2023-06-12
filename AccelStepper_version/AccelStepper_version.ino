#include <AccelStepper.h>

#define HALFSTEP 4

#define STEPPER_X_PIN_1  0     // IN1 on ULN2003 ==> Blue   on 28BYJ-48
#define STEPPER_X_PIN_2  1     // IN2 on ULN2004 ==> Pink   on 28BYJ-48
#define STEPPER_X_PIN_3  2    // IN3 on ULN2003 ==> Yellow on 28BYJ-48
#define STEPPER_X_PIN_4  3    // IN4 on ULN2003 ==> Orange on 28BYJ-48

#define STEPPER_Y_PIN_1  4     // IN1 on ULN2003 ==> Blue   on 28BYJ-48
#define STEPPER_Y_PIN_2  5     // IN2 on ULN2004 ==> Pink   on 28BYJ-48
#define STEPPER_Y_PIN_3  6    // IN3 on ULN2003 ==> Yellow on 28BYJ-48
#define STEPPER_Y_PIN_4  8    // IN4 on ULN2003 ==> Orange on 28BYJ-48

#define STEPPER_Z_PIN_1  9     // IN1 on ULN2003 ==> Blue   on 28BYJ-48
#define STEPPER_Z_PIN_2  10     // IN2 on ULN2004 ==> Pink   on 28BYJ-48
#define STEPPER_Z_PIN_3  11    // IN3 on ULN2003 ==> Yellow on 28BYJ-48
#define STEPPER_Z_PIN_4  12    // IN4 on ULN2003 ==> Orange on 28BYJ-48

long endPointZ = 2048*2.8; 
long endPointY = 2048*1.5;       // Move this many steps - 1024 = approx 1/4 turn

// NOTE: The sequence 1-3-2-4 is required for proper sequencing of 28BYJ-48
// O eixo X, Y e Z são os eixos responsáveis pelo comprimento, ejetor e elevador, respectivamente
AccelStepper stepperX(HALFSTEP, STEPPER_X_PIN_1, STEPPER_X_PIN_3, STEPPER_X_PIN_2, STEPPER_X_PIN_4);
AccelStepper stepperY(HALFSTEP, STEPPER_Y_PIN_1, STEPPER_Y_PIN_3, STEPPER_Y_PIN_2, STEPPER_Y_PIN_4);
AccelStepper stepperZ(HALFSTEP, STEPPER_Z_PIN_1, STEPPER_Z_PIN_3, STEPPER_Z_PIN_2, STEPPER_Z_PIN_4);

void setup()
{
  // Com o serial, os pins 0 e 1 não funcionam
  Serial.begin(9600);
  
  // Seta todos os pins como saida
  pinMode(STEPPER_X_PIN_1, OUTPUT);
  pinMode(STEPPER_X_PIN_2, OUTPUT);
  pinMode(STEPPER_X_PIN_3, OUTPUT);
  pinMode(STEPPER_X_PIN_4, OUTPUT);

  pinMode(STEPPER_Y_PIN_1, OUTPUT);
  pinMode(STEPPER_Y_PIN_2, OUTPUT);
  pinMode(STEPPER_Y_PIN_3, OUTPUT);
  pinMode(STEPPER_Y_PIN_4, OUTPUT);

  pinMode(STEPPER_Z_PIN_1, OUTPUT);
  pinMode(STEPPER_Z_PIN_2, OUTPUT);
  pinMode(STEPPER_Z_PIN_3, OUTPUT);
  pinMode(STEPPER_Z_PIN_4, OUTPUT);

  //Eixo X
  stepperX.setMaxSpeed(500.0);
  stepperX.setAcceleration(80.0);
  stepperX.setSpeed(200);
  stepperX.moveTo(endPointZ);
  stepperX.setPinsInverted(); // Inverte o sinal sem driver

  //Eixo Y
  stepperY.setMaxSpeed(500.0);
  stepperY.setAcceleration(80.0);
  stepperY.setSpeed(200);
  stepperY.moveTo(endPointY);
  stepperY.setPinsInverted(); // Inverte o sinal sem driver

  //Eixo Z
  stepperZ.setMaxSpeed(500.0);
  stepperZ.setAcceleration(80.0);
  stepperZ.setSpeed(200);
  stepperZ.moveTo(endPointZ);
  stepperZ.setPinsInverted(); // Inverte o sinal sem driver
}

void loop()
{
    // Change direction at the limits
    if (stepperY.distanceToGo() == 0)
    {
      stepperY.setCurrentPosition(0);
      endPointY *= -1;
      stepperY.moveTo(endPointY);
    }

    stepperY.run();

    // Change direction at the limits
    if (stepperZ.distanceToGo() == 0)
    {
      stepperZ.setCurrentPosition(0);
      endPointZ *= -1;
      stepperZ.moveTo(endPointZ);
    }

    stepperZ.run();
}
