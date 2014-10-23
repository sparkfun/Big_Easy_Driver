#include <AccelStepper.h>

// Define two steppers and the pins they will use
AccelStepper stepper1(1, 4, 5); //(driver=true, step, dir)  X axis
AccelStepper stepper2(1, 6, 7);//Y axis

int pos1 = 0;//Varibales to keep track of the planchet's current position 
int pos2 = 0;

int switch_x_left = 8;
int switct_y_top = 9;

int enable = 10;
int enable2 = 11;

void setup()
{  
  Serial.begin(115200);
  stepper1.setMaxSpeed(5000);
  stepper1.setAcceleration(1);
  stepper2.setMaxSpeed(4000);
  stepper2.setAcceleration(1);
  
  pinMode(switch_x_left, INPUT_PULLUP);
  pinMode(switct_y_top, INPUT_PULLUP);
  
  pinMode(enable, OUTPUT);
  pinMode(enable2, OUTPUT);
  digitalWrite(enable, LOW);//Diable both motors to start
  digitalWrite(enable2, HIGH);
  
  //home();//set the cursor back to its home position at 0,0
  

  
  //digitalWrite(enable, LOW);//enable motor1
  stepper1.moveTo(50000);
  while(stepper1.distanceToGo() != 0)
    stepper1.run();
    Serial.println(stepper1.currentPosition());
  //digitalWrite(enable, HIGH);//disable motor1
}
void loop()
{

}
//------------------------------------------------------------------------------
void home()
{
  //Decided to move Y axis first since one of the magnets was hitting if it was all the way away from home. 
  digitalWrite(enable2, LOW);//enable motor 1
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
  
  digitalWrite(enable2, HIGH);//disable the motor 
  
    /////////////////////////////////////////////
  
  digitalWrite(enable, LOW);//enable motor 1
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
  digitalWrite(enable, HIGH);//disable the motor 
}
//------------------------------------------------------------------------------
