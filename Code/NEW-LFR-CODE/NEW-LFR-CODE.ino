

// <----------------------------------------------------Variables and Constants------------------------------------------------------------------>



// Defining Motor pins
const int left_motor = 3;
const int right_motor = 6;
const int left_motor_c = 4;
const int left_motor_ac = 2;
const int right_motor_c = 5;
const int right_motor_ac = 7;

// Defining the IR array sensors
#define IR1  A0
#define IR2  A1
#define IR3  A2
#define IR4  A3
#define IR5  A4
#define IR6  A5
#define IR7  A6

// Sensors
int sensor1 ;
int sensor2 ;
int sensor3 ; 
int sensor4 ; 
int sensor5 ; 
int sensor6 ;
int sensor7 ;

// PID VALUES
#define Kp 0.2 // experiment to determine this, start by something small that just makes your bot follow the line at a slow speed
#define Ki 0.4
#define Kd 1.25// experiment to determine this, slowly increase the speeds and adjust this value. ( Note: Kp < Kd) 
int P, I, D;
float error;
float pidValue = 0;
float previousError=0, previous_I=0;

// int lsp, rsp;
// long denominator = 0;
// long numerator = 0;
// float pos;
// int numBlack = 0;
// float Kp = 0.025;
// float Kd = 1.48;
// float Ki = 0.00023;

// SPEED VALUES
#define MaxSpeed 240// max speed of the robot
// #define BaseSpeed 110 
int speed_left_motor = 110;
int speed_right_motor = 110;


int THRESHOLD;

// FOR STORING THE PATH DETAILS

char path[120] = {};
int pathLength;
int readLength;

void readSensor(){
  sensor1 = analogRead(IR1);
  sensor2 = analogRead(IR2);
  sensor3 = analogRead(IR3);
  sensor4 = analogRead(IR4);
  sensor5 = analogRead(IR5);
  sensor6 = analogRead(IR6);
  sensor7 = analogRead(IR7);

  calculate_error(300 , 600);

}


// <----------------------------------------------------Calibration------------------------------------------------------------------>
void calibrateSensors(){



}
// <----------------------------------------------------PID------------------------------------------------------------------>
void calculate_PID()
{
    P = error;
    I = I + previous_I;
    D = error-previousError;

    pidValue = (Kp*P) + (Ki*I) + (Kd*D);

    previous_I=I;
    previousError=error;

}

void calculate_error(int black , int white){

  if( (sensor1<=black)&&(sensor2>=white)&&(sensor3>=white)&&(sensor4>=white)&&(sensor5>=white) ) //B W W W W W
  error = 3;
  else if( (sensor1<=black)&&(sensor2<=black)&&(sensor3>=white)&&(sensor4>=white)&&(sensor5>=white) ) //B B W W W
  error = 2;
  else if( (sensor1<=black)&&(sensor2<=black)&&(sensor3<=black)&&(sensor4>=white)&&(sensor5>=white) ) //B B B W W
  error = 1;
  else if( (sensor1>=white)&&(sensor2<=black)&&(sensor3<=black)&&(sensor4<=black)&&(sensor5>=white) ) //W B B B W
  error = 0;
  else if((sensor1>=white)&&(sensor2>=white)&&(sensor3<=black)&&(sensor4<=black)&&(sensor5<=black)) // W W B B B 
  error = -1;
  else if((sensor1>=white)&&(sensor2>=white)&&(sensor3>=white)&&(sensor4<=black)&&(sensor5<=black) ) // W W W B B
  error = -2;
  else if((sensor1>=white)&&(sensor2>=white)&&(sensor3>=white)&&(sensor4>=white)&&(sensor5==black)) // W W W W B
  error = -3;
  else if((sensor1>=white)&&(sensor2>=white)&&(sensor3>=white)&&(sensor4>=white)&&(sensor5>=white)) //  W W W W W
    if(error == -3) error = -4;
    else error = 4;

}



// <----------------------------------------------------Motor Functions------------------------------------------------------------------>
void stopMotors() 
{
  digitalWrite(left_motor_c, LOW);
  digitalWrite(right_motor_c, LOW);
  digitalWrite(left_motor_ac,LOW);
  digitalWrite(right_motor_ac,LOW);
  delay(6000);
}


// <----------------------------------------------------Setup and Loop------------------------------------------------------------------>


void setup() 
{
  Serial.begin(9600);
  // Setting the motor pins
  pinMode(left_motor, OUTPUT);
  pinMode(right_motor, OUTPUT);
  pinMode(left_motor_c, OUTPUT);
  pinMode(left_motor_ac, OUTPUT);
  pinMode(right_motor_c, OUTPUT);
  pinMode(right_motor_ac, OUTPUT);

  // Setting the IR sensors as input
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5,INPUT);
  pinMode(IR6,INPUT);
  pinMode(IR7,INPUT);


  calibrateSensors();

  stopMotors();



}

void loop() 
{

   // Calculating the effective motor speed:
  speed_left_motor = speed_left_motor - pidValue;
  speed_right_motor = speed_right_motor + pidValue;
  // The motor speed should not exceed the max PWM value
  constrain(speed_left_motor,0,255);
  constrain(speed_right_motor,0,255);

  readSensor();
  // it will only move forward if two sensors are on the line


  // else it we will call the LSRB algorithm

  



}

// <----------------------------------------------------Shortest Path------------------------------------------------------------------>
void shortPath()
{
	int shortDone = 0;
	if(path[pathLength-3] == 'L' && path[pathLength - 1] == 'R')
	{
		pathLength -= 3;
		path[pathLength] = 'B';
		shortDone = 1;
	}
	if(path[pathLength-3] == 'L' && path[pathLength - 1] == 'S' && shortDone == 0)
	{
		pathLength -= 3;
		path[pathLength] = 'R';
		shortDone = 1;
	}
	if(path[pathLength-3] == 'R' && path[pathLength - 1] == 'L' && shortDone == 0)
	{
		pathLength-=3;
		path[pathLength] = 'B';
		shortDone=1;
	}
	if(path[pathLength-3] == 'S' && path[pathLength - 1] == 'L' && shortDone == 0)
	{
		pathLength -= 3;
		path[pathLength] = 'R';
		shortDone = 1;
	}
	if(path[pathLength-3] == 'S' && path[pathLength - 1] =='S' && shortDone == 0)
	{
		pathLength-=3;
		path[pathLength] = 'B';
		shortDone=1;
	}
	if(path[pathLength-3] == 'L' && path[pathLength - 1] =='L' && shortDone == 0)
	{
		pathLength -= 3;
		path[pathLength] = 'S';
		shortDone = 1;
	}
	path[pathLength+1] = 'D';
	path[pathLength+2] = 'D';
	pathLength++;
}