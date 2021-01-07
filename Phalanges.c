void object_calculate(float &topMotor, float &btomMotor) //storing encoder values in variables topMotor and btomMotor 
{
    eraseDisplay(); //Erases Display
    while(nNxtButtonPressed!=2)  //While-loop for when the button is not pressed it displays a text
      {
          displayString(1,"Press and hold");
          displayString(2,"left to record");  
      }
	while(nNxtButtonPressed==2)  //while-loop for when the button is pressed motor C keeps running at 10%
	motor[motorC]= 10;//changed signs  

	btomMotor= nMotorEncoder[motorC];    //assigning encoder value of motor C to variable btomMotor
	motor[motorC]=0;                  //stops motor C
	while(nNxtButtonPressed!=1)     //When button 1 is not pressed it erases previous display and then displays a new text
		{
			eraseDisplay();
		  displayString(1, "Press and hold");
		  displayString(2,"right to record");   
		}
	while(nNxtButtonPressed==1)  //when button 1 is pressed motor B keeps running at 10%
	motor[motorB]= 10;          

	topMotor = nMotorEncoder[motorB];  //assigning encoder value of motor C to variable topMotor
	motor[motorB] = 0;    //stops motor C

}
 
void object_grip(float degree1a, float degree2a)     //initialising variables degree1a and degree2a   
{
	nMotorEncoder[motorB]=0;  //reset encoder value to 0 for motor B
	nMotorEncoder[motorC] = 0;  //reset encoder value to 0 for motor C
	while(nMotorEncoder[motorC] <= degree2a)  //while encoder value for motor C is less than equal to degree2a motor C keeps running at 10%
		motor[motorC]=  10;   
    motor[motorC]= 0; //stops motor C
while(nMotorEncoder[motorB] <= degree1a)  //while encoder value for motor B is less than equal to degree1a motor B keeps running at 10% 
	motor[motorB] = 10;    
  motor[motorB] = 0;     //stops motor B
}

void object_release(float degree1a, float degree2a) 
{
SensorType[S4]= sensorSoundDB;  //assigning sound sensor to port 4
SensorValue[S4]= 0;   //initialising value of sound sensor to 0
eraseDisplay();
displayString(2,"Say Release");
while(SensorValue[S4]<80){}    //while sensor value is less than 80 DB it does nothing
	nMotorEncoder[motorB]=0;     //encoder value for motor B is 0
	nMotorEncoder[motorC] = 0;   //encoder value for motor C is 0
	while(nMotorEncoder[motorC] <= degree2a)    //while encoder value for motor C is less than equal to degreee2a motor C keeps running at 10% in reverse direction
	motor[motorC]= -10;     
	motor[motorC]= 0;     //stops motor C

  while(nMotorEncoder[motorB] <= degree1a)    //while encoder value for motor C is less than equal to degreee1a motor B keeps running at 10% in reverse direction
	motor[motorB] = -10;     

	motor[motorB] = 0;        //stops motor B

}

void pilldispenser()
{
  do                   //it is a do-while loop so it does the following commands atleast once and then checks the while condition 
  {
    eraseDisplay();   //erases display
    playSound(soundBeepBeep); //makes a BeepBeep sound 3 times
    playSound(soundBeepBeep);
    playSound(soundBeepBeep);
    wait1Msec(2000);
    nMotorEncoder[motorA]=0;  //resetting encoder value to 0 for motor A
    while(nMotorEncoder[motorA]<=120)  //while encoder value for motor A is less than equal to 120 degrees it runs motor A at 5%
    motor[motorA]=5;   
    motor[motorA]=0;   //stops the motor A
    wait1Msec(1000);
    displayString(1,"Pill dispensed!"); //waits for 1 sec and then displays text
    displayString(2,"Want more?");
    displayString(3,"(R)Yes or (L)No");
    while(nNxtButtonPressed==-1){}  //while no button is pressed it does nothing
  }
 while(nNxtButtonPressed==1);  //while button 1 is pressed it erases the display and displays a text and then erases display again after 1 sec
 eraseDisplay();
 displayString(2,"END");
 wait1Msec(1000);
 eraseDisplay();
}

void demo() 
{
	eraseDisplay();
  SensorType[S1] = sensorTouch;  //assigning touch sensor to S1 port
	SensorValue[S1] = 0;    //initialising sensor value to 0
	displayString(0,"Press Touch Sensor");
	wait1Msec(2000);
	while(SensorValue[S1] == 0){}  //While touch sensor is not pressed it does nothing
	time1[0] = 0;  //resetting timer to 0
	while(time1[0]<=3500)     //runs motor B and C at 10% untill timer is 3.5 sec
  {
		motor[motorB] = 10;  
		motor[motorC] = 10;  
  }
  
	while(time[0]<=7000 && time1[0]>3500)  //runs motor B and C at 10% in reverse for 3.5 sec more
		{
			motor[motorB] = -10;  
			motor[motorC] = -10;  
		}
		motor[motorB] = 0;  //stops motor B
		motor[motorC] = 0;  //stops motor C
}


void execute(float degree1a, float degree1b, float degree2a, float degree2b) 
{
		if(nNxtButtonPressed==3)
	  	{
	  		eraseDisplay();
	  	  displayString(0,"[R]Object 1");
	  		displayString(1,"[L]Object 2");
	  		
	  		while(nNxtButtonPressed == -1){}
	  	  if(nNxtButtonPressed==1)
	  	  {
	  	  	 object_grip( degree1a, degree1b);
	  	  	 eraseDisplay();
	  	      displayString(3,"Release with touch");
	  	      
	  	    	SensorType[S1] = sensorTouch;
	  	    	while(SensorValue[S1]==0){}
           object_release(degree1a, degree1b);
	  	  }
	  	  else if(nNxtButtonPressed==2)
	  	  {
	  	  	 object_grip(degree2a, degree2b);
	  	  	 eraseDisplay();
	  	      displayString(3,"Release with touch");
	  	     
	  	    	SensorType[S1] = sensorTouch;
	  	    	while(SensorValue[S1]==0){}
           object_release(degree2a, degree2b);
        }
}
}

void select(float &deg1a, float &deg1b, float &deg2a, float &deg2b) 
{
	   float degree1a=0.0, degree1b=0.0, degree2a=0.0, degree2b=0.0;
	  	eraseDisplay();
	    displayString(0,"[R]Record");
	  	displayString(1,"[C]Execute");
	  	
	  	while(nNxtButtonPressed == -1){}
	  	if(nNxtButtonPressed==1)
	  	{
	  		eraseDisplay();
	  	    displayString(0,"[R]Object 1");
	  		displayString(1,"[C]Object 2");
	  		while(nNxtButtonPressed == -1){}
	  	   if(nNxtButtonPressed==1)
	  	    {
	  	      object_calculate(degree1a, degree1b);
	  	      deg1a= degree1a; deg1b=degree1b;
	  	      eraseDisplay();
	  	      displayString(3,"Release with touch");
	  	
	  	    	SensorType[S1] = sensorTouch;

	  	    	while(SensorValue[S1]==0){}

           object_release(degree1a, degree1b);
	  	  }
	  	  else if(nNxtButtonPressed==3)
	  	  {


	  	  object_calculate(degree2a, degree2b);
	  	  deg2a=degree2a; deg2b=degree2b;
	  	    	eraseDisplay();
	  	      displayString(3,"Release with touch");
	  	      
	  	    	SensorType[S1] = sensorTouch;
	  	    	while(SensorValue[S1]==0){}
            object_release(degree2a, degree2b);
        }

	     }
	   }
	   
task main()  
{
  float deg1,deg2,deg3,deg4;  //initialising variables 
  displayString(1,"Choose an option: ");  //displays text
	wait1Msec(2000); //holds the display for 2 sec
	eraseDisplay();  //erases the display
	while(nNxtExitClicks != 3) //While-loop for when the bottom button is not pressed 3 times
	{
	  displayString(1,"[R]1.Grip");
	  displayString(2,"[L]2.Pill Dispense");
	  displayString(3,"[C]3.Demo");
	  displayString(4,"[B]4.Shut Down");  //displays text
	  if(nNxtButtonPressed==1)      //If the button pressed is 1 it calls select function and execute function 
	  {
	   select(deg1,deg2,deg3,deg4);     
	   execute(deg1,deg2,deg3,deg4);    
	  }
	  if(nNxtButtonPressed==2)      //If button 2 is pressed
	  {
	    pilldispenser();        //calls pilldispenser function
	  }

	  if(nNxtButtonPressed==3)   //If button 3 is pressed
	  {
	  	demo();              //calls demo function
	  }
	  if(nNxtButtonPressed == 0)   //If button 0 is pressed
	  {
	  	eraseDisplay();   //erase the display on screen
	  	displayString(1,"Push grey button three times to exit");  //displays text
	  	wait1Msec(4000);                                          //waits for 4 sec
	
	  }
  }
}               //end program 
