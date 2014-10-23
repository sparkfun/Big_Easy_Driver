#include <AccelStepper.h>
#include "ouijaFunctions.h"

// Define two steppers and the pins they will use
//AccelStepper stepperX(1, 4, 5); //(driver=true, step, dir)  X axis
//AccelStepper stepperY(1, 6, 7);//Y axis

int pos1 = 0;//Varibales to keep track of the planchet's current position 
int pos2 = 0;

int switch_x_left = 8;
int switct_y_top = 9;

void setup()
{  
  Serial.begin(115200);
  stepperX.setMaxSpeed(5000);
  stepperX.setAcceleration(4000);
  stepperY.setMaxSpeed(5000);
  stepperY.setAcceleration(4000);
  
  //stepperX.setEnablePin(10);
  //stepperY.setEnablePin(11);
  //stepperX.setPinsInverted(0,0,1);//invert the enable pin
  //stepperY.setPinsInverted(0,0,1);
  
  pinMode(switch_x_left, INPUT_PULLUP);
  pinMode(switct_y_top, INPUT_PULLUP);
    
  home();//set the cursor back to its home position at 0,0
  
  //drawCircleCW();
}
//------------------------------------------------------------------------------
void loop()
{
  //char arrayThing[30] = {'h','e','l','l','o',0};
  //ouijaPrint(arrayThing);
  
 // char arrayThing2[30] = {'z','a','m','n',0};
 // ouijaPrint(arrayThing2);
  
  char arrayThing3[30] = {'s','p','a','r','k','f','u','n',0};
  ouijaPrint(arrayThing3);
  //while(1);
  //{}
  moveWithKeyboard();
}
//------------------------------------------------------------------------------
void home()
{
  //Decided to move Y axis first since one of the magnets was hitting if it was all the way away from home. 
  if(digitalRead(switct_y_top) == HIGH)
  {
    while(digitalRead(switct_y_top) == HIGH)
    {
      stepperY.moveTo(pos2);
      stepperY.run();
      pos2 = pos2 - 1;
      //Serial.println(pos2);
    }
    if(digitalRead(switct_y_top) == LOW)
      stepperY.stop();
      pos2 = 0;
      stepperY.setCurrentPosition(0);
    }
  else
  {
  pos2 = 0;
  stepperY.setCurrentPosition(0);
  }
  
  if(digitalRead(switch_x_left) == HIGH)//check to make sure this axis isn;t already in the home posotion 
  {
    while(digitalRead(switch_x_left) == HIGH)//if it is not at home (HIGH) ...
    {
      stepperX.moveTo(pos1);//start moving the X axis back to the home position
      stepperX.run();
      pos1 = pos1 - 1;//decrement the position until we reach 0 (where the switch is triggered) 
    }
    if(digitalRead(switch_x_left) == LOW)//Once the switch is hit and the signal goes LOW...
      stepperX.stop();//stop the motor
      pos1 = 0;//set this axis position to 0
      stepperX.setCurrentPosition(0);
  }
  else
  {
  pos1 = 0;
  stepperX.setCurrentPosition(0);
  }

}
//------------------------------------------------------------------------------
void moveWithKeyboard()
//This function was used to jog each axis 100 "steps" in each direction 
{
  if(Serial.available() > 0)
  {
    int temp = Serial.read();
    
    if(temp == 119 || temp == 87)//dec for 'w'
    {
      stepperY.moveTo(stepperY.currentPosition() - 100);
      //stepperY.setSpeed(2000);
      while(stepperY.distanceToGo() != 0)
      {
        stepperY.run();
      }
      Serial.print(stepperX.currentPosition());
      Serial.print("   ");
      Serial.println(stepperY.currentPosition());
    }
    if(temp == 115 || temp == 83)//dec for 's'
    {
      stepperY.moveTo(stepperY.currentPosition() + 100);
      //stepperY.setSpeed(2000);
      while(stepperY.distanceToGo() != 0)
      {
        stepperY.run();
      } 
      Serial.print(stepperX.currentPosition());
      Serial.print("   ");
      Serial.println(stepperY.currentPosition());
    }
    if(temp == 97 || temp == 65)//dec for 'a'
    {
      stepperX.moveTo(stepperX.currentPosition() - 100);
      //stepperX.setSpeed(3000);
      while(stepperX.distanceToGo() != 0)
      {
        stepperX.run();
      }  
      Serial.print(stepperX.currentPosition());
      Serial.print("   ");
      Serial.println(stepperY.currentPosition());
    }
    if(temp == 100 || temp == 68)//dec for 'd'
    {
      stepperX.moveTo(stepperX.currentPosition() + 100.00);
      //stepperX.setSpeed(3000);
      while(stepperX.distanceToGo() != 0)
      {
        stepperX.run();
      }
      Serial.print(stepperX.currentPosition());
      Serial.print("   ");
      Serial.println(stepperY.currentPosition());
    }
    
    //move in larger increments with the right side of the keyboard
    if(temp == 105 || temp == 73)//dec for 'i'
    {
      stepperY.moveTo(stepperY.currentPosition() - 1000);
      while(stepperY.distanceToGo() != 0)
      {
        stepperY.run();
      }
      Serial.print(stepperX.currentPosition()); Serial.print("   "); Serial.println(stepperY.currentPosition());
    }
    if(temp == 107 || temp == 75)//dec for 'k'
    {
      stepperY.moveTo(stepperY.currentPosition() + 1000);
      //stepperY.setSpeed(2000);
      while(stepperY.distanceToGo() != 0)
      {
        stepperY.run();
      } 
      Serial.print(stepperX.currentPosition()); Serial.print("   "); Serial.println(stepperY.currentPosition());
    }
    if(temp == 106 || temp == 74)//dec for 'j'
    {
      stepperX.moveTo(stepperX.currentPosition() - 2000);
      //stepperX.setSpeed(3000);
      while(stepperX.distanceToGo() != 0)
      {
        stepperX.run();
      }  
      Serial.print(stepperX.currentPosition()); Serial.print("   "); Serial.println(stepperY.currentPosition());
    }
    if(temp == 108 || temp == 76)//dec for 'l'
    {
      stepperX.moveTo(stepperX.currentPosition() + 2000);
      while(stepperX.distanceToGo() != 0)
      {
        stepperX.run();
      }
      Serial.print(stepperX.currentPosition()); Serial.print("   "); Serial.println(stepperY.currentPosition());
    }
  
  }
}
//------------------------------------------------------------------------------
void drawCircleCW()
{
  stepperX.moveTo(12000);
  stepperY.moveTo(1000);
  while((stepperX.distanceToGo() != 0)||(stepperX.distanceToGo() != 0))
  {
    stepperX.run();
    stepperY.run();
  }
  
  stepperX.moveTo(14000);
  stepperY.moveTo(2000);
  while((stepperX.distanceToGo() != 0)||(stepperX.distanceToGo() != 0))
  {
    stepperX.run();
    stepperY.run();
  }
  
  stepperX.moveTo(12000);
  stepperY.moveTo(3000);
  while((stepperX.distanceToGo() != 0)||(stepperX.distanceToGo() != 0))
  {
    stepperX.run();
    stepperY.run();
  }
  
  stepperX.moveTo(8000);
  stepperY.moveTo(2000);
  while((stepperX.distanceToGo() != 0)||(stepperX.distanceToGo() != 0))
  {
    stepperX.run();
    stepperY.run();
  }
  
  stepperX.moveTo(12000);
  stepperY.moveTo(2000);
  while((stepperX.distanceToGo() != 0)||(stepperX.distanceToGo() != 0))
  {
    stepperX.run();
    stepperY.run();
  }
}
