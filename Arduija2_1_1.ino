#include <AccelStepper.h>

// Define two steppers and the pins they will use
AccelStepper stepper1(1, 4, 5); //(driver=true, step, dir)  X axis
AccelStepper stepper2(1, 6, 7);//Y axis

int pos1 = 0;//Varibales to keep track of the planchet's current position 
int pos2 = 0;

int switch_x_left = 8;
int switct_y_top = 9;

void setup()
{  
  Serial.begin(115200);
  stepper1.setMaxSpeed(3000);
  stepper1.setAcceleration(1);
  stepper2.setMaxSpeed(2000);
  stepper2.setAcceleration(1);
  
  //stepper1.setEnablePin(10);
  //stepper2.setEnablePin(11);
  //stepper1.setPinsInverted(0,0,1);//invert the enable pin
  //stepper2.setPinsInverted(0,0,1);
  
  pinMode(switch_x_left, INPUT_PULLUP);
  pinMode(switct_y_top, INPUT_PULLUP);
    
  home();//set the cursor back to its home position at 0,0
  
  delay(500);
  /*
  stepper1.moveTo(5000);
  stepper1.setSpeed(3000);
  while(stepper1.distanceToGo() != 0)
  {
    stepper1.runSpeed();
    Serial.println(stepper1.currentPosition());
  }*/
}
void loop()
{
  if(Serial.available() > 0)
  {
    int temp = Serial.read();
    
    if(temp == 119 || temp == 87)//dec for 'w'
    {
      stepper2.moveTo(stepper2.currentPosition() - 100);
      stepper2.setSpeed(2000);
      while(stepper2.distanceToGo() != 0)
      {
        stepper2.runSpeed();
        Serial.print(stepper1.currentPosition());
        Serial.print("   ");
        Serial.println(stepper2.currentPosition());
      }
    }
    if(temp == 115 || temp == 83)//dec for 's'
    {
      stepper2.moveTo(stepper2.currentPosition() + 100.00);
      stepper2.setSpeed(2000);
      while(stepper2.distanceToGo() != 0)
      {
        stepper2.runSpeed();
        Serial.print(stepper1.currentPosition());
        Serial.print("   ");
        Serial.println(stepper2.currentPosition());
      } 
    }
    if(temp == 97 || temp == 65)//dec for 'a'
    {
      stepper1.moveTo(stepper1.currentPosition() - 100);
      stepper1.setSpeed(3000);
      while(stepper1.distanceToGo() != 0)
      {
        stepper1.runSpeed();
        Serial.print(stepper1.currentPosition());
        Serial.print("   ");
        Serial.println(stepper2.currentPosition());
      }  
    }
    if(temp == 100 || temp == 68)//dec for 'd'
    {
      stepper1.moveTo(stepper1.currentPosition() + 100.00);
      stepper1.setSpeed(3000);
      while(stepper1.distanceToGo() != 0)
      {
        stepper1.runSpeed();
        Serial.print(stepper1.currentPosition());
        Serial.print("   ");
        Serial.println(stepper2.currentPosition());
      }
    }
  
  }
}
//------------------------------------------------------------------------------
void home()
{
  //Decided to move Y axis first since one of the magnets was hitting if it was all the way away from home. 
  if(digitalRead(switct_y_top) == HIGH)
  {
    while(digitalRead(switct_y_top) == HIGH)
    {
      stepper2.moveTo(pos2);
      stepper2.run();
      pos2 = pos2 - 1;
      //Serial.println(pos2);
    }
    if(digitalRead(switct_y_top) == LOW)
      stepper2.stop();
      pos2 = 0;
      stepper2.setCurrentPosition(0);
    }
  else
  {
  pos2 = 0;
  stepper2.setCurrentPosition(0);
  }
  
    /////////////////////////////////////////////
  
  if(digitalRead(switch_x_left) == HIGH)//check to make sure this axis isn;t already in the home posotion 
  {
    while(digitalRead(switch_x_left) == HIGH)//if it is not at home (HIGH) ...
    {
      stepper1.moveTo(pos1);//start moving the X axis back to the home position
      stepper1.run();
      pos1 = pos1 - 1;//decrement the position until we reach 0 (where the switch is triggered) 
    }
    if(digitalRead(switch_x_left) == LOW)//Once the switch is hit and the signal goes LOW...
      stepper1.stop();//stop the motor
      pos1 = 0;//set this axis position to 0
      stepper1.setCurrentPosition(0);
  }
  else
  {
  pos1 = 0;
  stepper1.setCurrentPosition(0);
  }

}
//------------------------------------------------------------------------------
