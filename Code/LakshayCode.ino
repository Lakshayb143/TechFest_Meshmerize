
const int left_motor = 3;
const int right_motor = 6;
const int left_motor_c = 4;
const int left_motor_ac = 2;
const int right_motor_c = 5;
const int right_motor_ac = 7;

// IR sensor
#define IR1  A0
#define IR2  A1
#define IR3  A2
#define IR4  A3
#define IR5  A4

// PID Variables
float Kp = 0.2;
float Ki = 0.5;
float Kd = 0;

int P ;
int I ; 
int D ;

// unsigned long currentTime, previousTime;
// double elapsedTime;
double error;
double lastError = 0;
double input, output, setPoint;
int slm = 70;
int srm = 70;
int pidValue;

// double cumError, rateError;
// PID myPID(&input, &output, &setPoint, Kp, Ki, Kd, DIRECT);
// Priority Order -  LSRB

// Sensors
int sensor1 ;
int sensor2 ;
int sensor3 ; 
int sensor4 ; 
int sensor5 ; 

int THRESHOLD;

void readSensor(){
  sensor1 = analogRead(IR1);
  sensor2 = analogRead(IR2);
  sensor3 = analogRead(IR3);
  sensor4 = analogRead(IR4);
  sensor5 = analogRead(IR5);

}

void PID()
{
  error = (analogRead(IR2) - analogRead(IR4));

  P = error;
  I = I + error;
  D = error - lastError;
  lastError = error;

  pidValue = Kp*P + Ki*I + Kd*D;


  slm = 150 - pidValue;
  srm = 150 + pidValue;


  if(slm > 240){
    slm = 240;
  }
  if(slm < 0){
    slm = 0;
  }
  if(srm > 240){
    srm = 240;
  }
  if(srm < 0){
    srm = 0;
  }

  
}

// int readLine(){
//   sensor1 = analogRead(IR1);
//   sensor2 = analogRead(IR2);
//   sensor3 = analogRead(IR3);
//   sensor4 = analogRead(IR4);
//   sensor5 = analogRead(IR5);
//   int v;
//   v = (0*sensor1 + 1000*sensor2 + 2000*sensor3 + 3000*sensor4 + 4000*sensor5)/(sensor1+sensor2+sensor3+sensor4+sensor5);
//   return v;
// }



void calibrateSensors() 
  {
  // 0 and 1023
  int minValue = 1023;  // Set to maximum initially
  int maxValue = 0;     // Set to minimum initially
  int sensorValue;
  

  for(int i = 0 ; i <=200 ; i++){
    left();
    // delay(10);
    sensorValue = analogRead(IR3);
    if (sensorValue < minValue)
    {
        minValue = sensorValue;
    } 
    if (sensorValue > maxValue)
    {
      maxValue = sensorValue;
    } 

  }

  THRESHOLD = (minValue+maxValue) / 2;
  }
void stopMotors() 
  {
  digitalWrite(left_motor_c, LOW);
  digitalWrite(right_motor_c, LOW);
  digitalWrite(left_motor_ac,LOW);
  digitalWrite(right_motor_ac,LOW);
  delay(6000);
  }

void left(){
  PID();
  digitalWrite(left_motor_ac,HIGH);
  digitalWrite(left_motor_c,LOW);
  digitalWrite(right_motor_c,HIGH);
  digitalWrite(right_motor_ac,LOW);
  analogWrite(left_motor,slm);
  analogWrite(right_motor,srm);

}

void right(){
  PID();   
  digitalWrite(right_motor_ac,HIGH);
  digitalWrite(right_motor_c,LOW);
  digitalWrite(left_motor_c,HIGH);
  digitalWrite(left_motor_ac,LOW);
  analogWrite(left_motor,slm);
  analogWrite(right_motor,srm);
}



void straight()
{
  PID();
  digitalWrite(left_motor_c,HIGH);
  digitalWrite(right_motor_c,HIGH);
  digitalWrite(left_motor_ac,LOW);
  digitalWrite(right_motor_ac,LOW);
  analogWrite(left_motor,slm);
  analogWrite(right_motor,srm);

}

void setup() {

  Serial.begin(9600);

  pinMode(left_motor, OUTPUT);
  pinMode(right_motor, OUTPUT);
  pinMode(left_motor_c, OUTPUT);
  pinMode(left_motor_ac, OUTPUT);

  pinMode(right_motor_c, OUTPUT);
  pinMode(right_motor_ac, OUTPUT);

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5,INPUT);


  // Turning the PID ON
  // myPID.SetMode(AUTOMATIC);
  calibrateSensors();

  stopMotors();



}

void loop() {
  // put your main code here, to run repeatedly:

  readSensor();
  // input = IR3;

  // output = PID_control(input);



  if(sensor1 > THRESHOLD && sensor2 > THRESHOLD && sensor3 > THRESHOLD && sensor4 > THRESHOLD && sensor5 > THRESHOLD) 
  {
    delay(10);
    left();
    delay(10);

    if (sensor1 > THRESHOLD && sensor2 > THRESHOLD && sensor3 > THRESHOLD && sensor4 > THRESHOLD && sensor5 > THRESHOLD)
    {
      stopMotors();
    }

    else {
    left();
    delay(10);
    
    }

  }

  else if(sensor1 > THRESHOLD && sensor2 > THRESHOLD && sensor3 > THRESHOLD && sensor4 < THRESHOLD && sensor5 < THRESHOLD){
    left();

  }

  else if(sensor1 < THRESHOLD && sensor2 < THRESHOLD && sensor3 > THRESHOLD && sensor4 < THRESHOLD && sensor5 < THRESHOLD ){
    straight();
  }

  else if(sensor1 < THRESHOLD && sensor2 < THRESHOLD && sensor3 > THRESHOLD && sensor4 > THRESHOLD && sensor5 > THRESHOLD){
    straight();

  }

  else if(sensor1 < THRESHOLD && sensor2 < THRESHOLD && sensor3 < THRESHOLD && sensor4 > THRESHOLD && sensor5 > THRESHOLD){
    right();

  }

  else if(sensor1 > THRESHOLD && sensor2 > THRESHOLD && sensor3 < THRESHOLD && sensor4 < THRESHOLD && sensor5 < THRESHOLD){
    left();

  }
  else if(sensor1 < THRESHOLD && sensor2 < THRESHOLD && sensor3 < THRESHOLD && sensor4 < THRESHOLD && sensor5 < THRESHOLD ){

    left();
  }

}

