
void leftHandWall(){
	if( leftFarReading<200 && rightFarReading<200)	//indicates either 3way intersection or end of maze
	{
		digitalWrite(leftMotor1, HIGH);
		digitalWrite(leftMotor2, LOW);
		digitalWrite(rightMotor1, HIGH);
		digitalWrite(rightMotor2, LOW);
		delay(leapTime);
		readSensors();

		if(leftFarReading<200 || rightFarReading<200)	//if it moves forward and still sees all black, maze is done
		{
	  		done();
		}
		if(leftFarReading>200 && rightFarReading>200)	//otherwise it turns left
		{ 
	  		turnLeft();
		}
	}
  
	if(leftFarReading<200)	//indicates that a left turn is possible
	{ 
		digitalWrite(leftMotor1, HIGH);
		digitalWrite(leftMotor2, LOW);
		digitalWrite(rightMotor1, HIGH);
		digitalWrite(rightMotor2, LOW);
		delay(leapTime);
		readSensors();
		if(leftFarReading>200 && rightFarReading>200)	//checks to make sure maze isn't done
		{
			turnLeft();
		}
		else
		{
			done();
		}
	}
   
	if(rightFarReading<200)	//indicates a right turn is possible
	{
		digitalWrite(leftMotor1, HIGH);
		digitalWrite(leftMotor2, LOW);
		digitalWrite(rightMotor1, HIGH);
		digitalWrite(rightMotor2, LOW);
		delay(10);	//CHANGED FROM 30 to 10
		readSensors();

		if(leftFarReading<200)	//left turn is also possible
		{
			delay(leapTime-30);
			readSensors();

			if(rightFarReading<200 && leftFarReading<200)//end of maze
			{
				done();
			}
			else	//make the left turn
			{
			turnLeft();
			return;
			}
		}
		delay(leapTime-30);
		readSensors();
		if(leftFarReading>200 && leftCenterReading>200 && rightCenterReading>200 && rightFarReading>200)
		{
			turnRight();
			return;
		}
		path[pathLength] = 'S';
		pathLength++;
		if(path[pathLength-2] == 'B')
		{
			shortPath();
		}
		straight();
	}
	readSensors();
	if(leftFarReading>200 && leftCenterReading>200 && rightCenterReading>200 
  	&& rightFarReading>200 && leftNearReading>200 && rightNearReading>200)
	{
		turnAround();
	}
}
view rawLeftHandWall.c hosted with ❤ by GitHub