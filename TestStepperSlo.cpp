/*
 * Created by Renzo Mischianti (xxReef)
 * Simple program to manage Arduino CNC Shield
 *
 * <axis> 		= x, y, z
 * <status> 	= 1 (activate), 0 (deactivate)
 * <direction> 	= 1 (invert direction), 0 (normal direction)
 * <speed> 		= impulse delay in microsenconds
 *
 * Commands:
 * g,<axis>,<status> 	--> Example: g,x,1 (start x movement)
 * d,<axis>,<direction> --> Example: d,x,1 (set direction to inverse)
 * v,<axis>,<speed> 	--> Example: v,x,2000000 (set delay step to 2000000 microseconds)
 *
 */
// Do not remove the include below
#include "TestStepperSlo.h"

#define DIR_X 5
#define STEP_X 2

#define DIR_Y 6
#define STEP_Y 3

#define DIR_Z 7
#define STEP_Z 4

#define ENABLE 8

unsigned long delayStepY = (unsigned long)80000*8;
unsigned long delayStepX = (unsigned long)80000*8; //(unsigned long)250000*8;
unsigned long delayStepZ = (unsigned long)80000*8; //(unsigned long)250000*8;

bool avviatoX = false;
bool avviatoY = false;
bool avviatoZ = false;

uint8_t directionX = LOW;
uint8_t directionY = LOW;
uint8_t directionZ = LOW;

unsigned long stepX = 0;
unsigned long stepY = 0;
unsigned long stepZ = 0;

void setup() {
	Serial.begin(9600);

	  pinMode(DIR_X, OUTPUT);
	  pinMode(STEP_X, OUTPUT);

	  pinMode(DIR_Y, OUTPUT);
	  pinMode(STEP_Y, OUTPUT);

	  pinMode(DIR_Z, OUTPUT);
	  pinMode(STEP_Z, OUTPUT);

	  pinMode(ENABLE, OUTPUT);

	  digitalWrite(DIR_X, directionX);
	  digitalWrite(DIR_Y, directionY);
	  digitalWrite(DIR_Z, directionZ);

	 digitalWrite(ENABLE, LOW);
}

void loop() {

	if (Serial.available()){
		String strTestata = Serial.readStringUntil(',');

		String strAsse = Serial.readStringUntil(',');
		Serial.print("ASSE: ");
		Serial.print(strAsse);

		bool *avviato = &avviatoX;
		unsigned long *delayStep =  &delayStepX;
		uint8_t *direction = &directionX;
		int pinDirection = DIR_X;

		if (strAsse=="y"){
			avviato = &avviatoY;
			delayStep =  &delayStepY;
			direction = &directionY;

			pinDirection = DIR_Y;
		}
		if (strAsse=="z"){
			avviato = &avviatoZ;
			delayStep =  &delayStepZ;
			direction = &directionZ;

			pinDirection = DIR_Z;
		}

		Serial.print(" - AVVIATO: ");
		Serial.print((bool)*avviato);
		Serial.print(" - DELAY: ");
		Serial.print((unsigned long)*delayStep);
		Serial.print(" - DIRECTION: ");
		Serial.print((uint8_t)*direction);


		if (strTestata=="d"){
			int dir = Serial.parseInt();
			*direction = dir;
			digitalWrite(pinDirection,dir);
		}else if (strTestata=="v"){
			*delayStep = (unsigned long)Serial.parseInt();
		}else if (strTestata=="g"){
			*avviato = (bool)Serial.parseInt();
		}
		Serial.print(" - AVVIATO: ");
		Serial.print((bool)*avviato);

		Serial.print(" - DELAY: ");
		Serial.print((unsigned long)*delayStep);
		Serial.print(" - DIRECTION: ");
		Serial.println((uint8_t)*direction);
		Serial.print("STEP X: ");
		Serial.print(stepX);
		Serial.print(" - STEP Y: ");
		Serial.print(stepY);
		Serial.print(" - STEP Z: ");
		Serial.print(stepZ);

		Serial.readString();


	}

	  if (avviatoX){
		  digitalWrite(STEP_X, HIGH);
		  delayMicroseconds(delayStepX);
		  digitalWrite(STEP_X, LOW);
		  delayMicroseconds(delayStepX);
		  if (directionX==LOW) stepX++;
		  	  	  	  	  else stepX--;
	  }
	  if (avviatoY){
		  digitalWrite(STEP_Y, HIGH);
		  delayMicroseconds(delayStepY);
		  digitalWrite(STEP_Y, LOW);
		  delayMicroseconds(delayStepY);
		  if (directionY==HIGH) stepY++;
		  	  	  	  	  else stepY--;

	  }
	  if (avviatoZ){
		  digitalWrite(STEP_Z, HIGH);
		  delayMicroseconds(delayStepZ);
		  digitalWrite(STEP_Z, LOW);
		  delayMicroseconds(delayStepZ);
		  if (directionZ==HIGH) stepZ++;
		  	  	  	  	  else stepZ--;

	  }
}
