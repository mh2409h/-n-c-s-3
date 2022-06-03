/*
 * Created by Lam Hong Duc
 * Date 17/11/2020
 */

int trig1 = A0;
int echo1 = A1;
int trig2 = A2;
int echo2 = A3;
int trig3 = A4;
int echo3 = A5;
int Speed = 200;
int in1 = 4;
int in2 = 5;
int in3 = 6;
int in4 = 7;
int ENA = 3;
int ENB = 11;
int LeftSpeed =50;
int RightSpeed = 50;

long leftDistance = 0,middleDistance = 0,rightDistance = 0;
long pingTime,distance;
float speedSound = 0.0343;
int DIS = 18;
int DIS2 = 13;

long leftMeasurement()
{
  digitalWrite(trig1,LOW);
  delayMicroseconds(2);
  digitalWrite(trig1,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1,LOW);
  pingTime = pulseIn(echo1,HIGH);
  distance = (pingTime/2)*speedSound;
  return(distance); 
}

long middleMeasurement()
{
  digitalWrite(trig2,LOW);
  delayMicroseconds(2);
  digitalWrite(trig2,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2,LOW);
  pingTime = pulseIn(echo2,HIGH);
  distance = (pingTime/2)*speedSound;
  return(distance); 
}

long rightMeasurement()
{
  digitalWrite(trig3,LOW);
  delayMicroseconds(2);
  digitalWrite(trig3,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig3,LOW);
  pingTime = pulseIn(echo3,HIGH);
  distance = (pingTime/2)*speedSound;
  return(distance); 
}

void setup()
{
  Serial.begin(9600);
  pinMode(trig1,OUTPUT);
  pinMode(trig2,OUTPUT);
  pinMode(trig3,OUTPUT);
  pinMode(echo1,INPUT);
  pinMode(echo2,INPUT);
  pinMode(echo3,INPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  moveStop();
}

void loop()
{
  leftDistance = leftMeasurement();
  delay(10);
  middleDistance = middleMeasurement();
  delay(10);
  rightDistance = rightMeasurement();
  delay(10);
  Serial.print("leftDistance = ");
  Serial.print(leftDistance);
  Serial.print("cm /");
  Serial.print("middleDistance = ");
  Serial.print(middleDistance);
  Serial.print("cm /");
  Serial.print("rightDistance = ");
  Serial.print(rightDistance);
  Serial.println("cm");

  //  Obstacle on left side
  if(leftDistance < DIS2 && middleDistance > DIS && rightDistance > DIS2)
  {
    turnRight();
    delay(25);  //  turn lightly right    
  }
  //  Obstacle on front
  else if(leftDistance > DIS2 && middleDistance < DIS && rightDistance > DIS2)
  {
    if(leftDistance > rightDistance)
    {
      turnLeft();
      delay(140);  //  turn 90 degree left
    }
    if(leftDistance < rightDistance)
    {
      turnRight();
      delay(140);  //  turn 90 degree right
    }
  }
  //  Obstacle on right side
  else if(leftDistance > DIS2 && middleDistance > DIS && rightDistance < DIS2)
  {
    turnLeft();
    delay(25);  //turn lightly left  
  }
  //  Obstacle on front & left side
  else if(leftDistance < DIS2 && middleDistance < DIS && rightDistance > DIS2)
  {
    turnRight();
    delay(140);  //  turnRight 90 degree
  }
  //  Obstacle on front & right side
  else if(leftDistance > DIS2 && middleDistance < DIS && rightDistance < DIS2)
  {
    turnLeft();
    delay(200);  //  turnLeft 90 degree
  }
  //  Obstacle on left & right side
  else if(leftDistance < DIS2 && middleDistance > DIS && rightDistance < DIS2)
  {
        
    if(leftDistance > rightDistance)
    {
      turnLeft();
      delay(50);  //  shift left
    }
    if(leftDistance < rightDistance)
    {
      turnRight();
      delay(50);  //  shift right
    }
  }
  //  Obstacle on all 3 side
  else if(leftDistance < DIS2 && middleDistance < DIS2 && rightDistance < DIS2)
  {
    moveStop();
    delay(50);
    moveBackward();
    delay(50);
   
      if(leftDistance > rightDistance)
    {
      turnLeft();
      delay(50);  //  shift left
    }
    if(leftDistance < rightDistance)
    {
      turnRight();
      delay(50);  //  shift right
    }
  }
  else
  {
    moveForward();
  }
}

void moveForward()
{
  
  digitalWrite(in1, Speed);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, Speed);
  digitalWrite(in4, LOW); 
}

void moveBackward()
{
 
  digitalWrite(in1, LOW);
  digitalWrite(in2, 5);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, 5); 
}

void turnRight()
{

  digitalWrite(in1, RightSpeed);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, RightSpeed);
}

void turnLeft()
{


  digitalWrite(in1, LOW);
  digitalWrite(in2, LeftSpeed); 
  digitalWrite(in3, LeftSpeed);
  digitalWrite(in4, LOW); 
}

void moveStop()
{


  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW); 
}
