#include <AccelStepper.h>

#define HALFSTEP 4

#define STEPPER_X_PIN_1  0     // IN1 on ULN2003 ==> Blue   on 28BYJ-48
#define STEPPER_X_PIN_2  1     // IN2 on ULN2004 ==> Pink   on 28BYJ-48
#define STEPPER_X_PIN_3  2    // IN3 on ULN2003 ==> Yellow on 28BYJ-48
#define STEPPER_X_PIN_4  3    // IN4 on ULN2003 ==> Orange on 28BYJ-48

#define AXIS_X_0 0
#define AXIS_X_1 int(2048*1.2)
#define AXIS_X_2 int(2048*2.8)

#define STEPPER_Y_PIN_1  4     // IN1 on ULN2003 ==> Blue   on 28BYJ-48
#define STEPPER_Y_PIN_2  5     // IN2 on ULN2004 ==> Pink   on 28BYJ-48
#define STEPPER_Y_PIN_3  6    // IN3 on ULN2003 ==> Yellow on 28BYJ-48
#define STEPPER_Y_PIN_4  8    // IN4 on ULN2003 ==> Orange on 28BYJ-48

#define AXIS_Y_0 0
#define AXIS_Y_1 int(2048*1.2)
#define AXIS_Y_2 int(2048*2.8)

#define STEPPER_Z_PIN_1  9     // IN1 on ULN2003 ==> Blue   on 28BYJ-48
#define STEPPER_Z_PIN_2  10     // IN2 on ULN2004 ==> Pink   on 28BYJ-48
#define STEPPER_Z_PIN_3  11    // IN3 on ULN2003 ==> Yellow on 28BYJ-48
#define STEPPER_Z_PIN_4  12    // IN4 on ULN2003 ==> Orange on 28BYJ-48

#define AXIS_Z_0 0
#define AXIS_Z_1 int(2048*0.9)

#define DEAD_ZONE 1023/3
#define JOYSTICK_ZONE 1023

const int SW_pin = 13; // digital pin switch
const int X_pin =A0; // analog pin x
const int Y_pin =A1; // analog pin y
int joyButton=0;

long endPointZ = 0; 
long endPointY = 0;       // Move this many steps - 1024 = approx 1/4 turn
long endPointX = 0;

// NOTE: The sequence 1-3-2-4 is required for proper sequencing of 28BYJ-48
// O eixo X, Y e Z são os eixos responsáveis pelo comprimento, elevador e ejetor, respectivamente
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
  //stepperX.setPinsInverted(); // Inverte o sinal sem driver

  //Eixo Y
  stepperY.setMaxSpeed(500.0);
  stepperY.setAcceleration(80.0);
  stepperY.setSpeed(200);
  //stepperY.setPinsInverted(); // Inverte o sinal sem driver

  //Eixo Z
  stepperZ.setMaxSpeed(500.0);
  stepperZ.setAcceleration(80.0);
  stepperZ.setSpeed(200);
  //stepperZ.setPinsInverted(); // Inverte o sinal sem driver

  // Joystick

  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
}

void loop()
{    
    if(!digitalRead(SW_pin) && stepperX.distanceToGo()==0 && stepperY.distanceToGo()==0 && stepperZ.distanceToGo()==0){ // controle do eixo z
      if(!joyButton){
        joyButton=1;
        Serial.print("Switch\n"); 
        endPointZ = endPointZ == AXIS_Z_0 ? AXIS_Z_1 : AXIS_Z_0;
        Serial.print(endPointZ); 
        stepperZ.moveTo(endPointZ); 
      }
    } else {
      joyButton=0;
    }
    
    if(analogRead(Y_pin) >= (JOYSTICK_ZONE/2 + DEAD_ZONE) || (analogRead(Y_pin) <= (JOYSTICK_ZONE/2 - DEAD_ZONE)) ){ // controle do eixo y
      Serial.print("");    
      Serial.print("");    
      Serial.print("");      

      if(stepperY.distanceToGo() == 0 && stepperZ.distanceToGo()==0 && endPointZ == AXIS_Z_0){ // parou
        if(analogRead(Y_pin) <= (JOYSTICK_ZONE/2 + DEAD_ZONE)){ // pra cima
          Serial.print("y sobe: ");    
          Serial.print("\n"); 
          endPointY = endPointY == AXIS_Y_0 ? AXIS_Y_1 : 
                                    endPointY == AXIS_Y_1 ? AXIS_Y_2 : endPointY ;
        }else { // pra esquerda
          Serial.print("y desce: ");   
          Serial.print("\n"); 
          endPointY = endPointY == AXIS_Y_2 ? AXIS_Y_1 : 
                                    endPointY == AXIS_Y_1 ? AXIS_Y_0 : endPointY;
        }
        stepperY.moveTo(endPointY);
      }
    }

    if(analogRead(X_pin) >= (JOYSTICK_ZONE/2 + DEAD_ZONE) || (analogRead(X_pin) <= (JOYSTICK_ZONE/2 - DEAD_ZONE)) ){ // controle do eixo x
      Serial.print("");
      Serial.print("");
      Serial.print("");

      if(stepperX.distanceToGo() == 0 && stepperZ.distanceToGo()==0 && endPointZ == AXIS_Z_0){ // parou
        if(analogRead(X_pin) >= (JOYSTICK_ZONE/2 + DEAD_ZONE)){ // pra cima
          Serial.print("x direita: ");
          Serial.print("\n");
          endPointX = endPointX == AXIS_X_0 ? AXIS_X_1:
                                    endPointX == AXIS_X_1 ? AXIS_X_2 : endPointX;
        }else { // pra esquerda
          Serial.print("x esquerda: ");
          Serial.print("\n");
          endPointX = endPointX == AXIS_X_2 ? AXIS_X_1:
                                    endPointX == AXIS_X_1 ? AXIS_X_0 : endPointX;
        }
        stepperX.moveTo(endPointX);
      }
    }  

    stepperY.run();
    stepperX.run();
    stepperZ.run();
}
