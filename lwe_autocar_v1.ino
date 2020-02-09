/* ************************************************
  LWE Science Club Auto Car

  Description
  
  Details, Details, Details, Details, Details, Details, Details, 
  Details, Details, Details, Details, Details, Details, Details, 
  Details, Details, vDetails, Details, Details, Details, Details, 
  Details, Details, Details, Details, Details, Details, Details, 

  https://github.com/jumblobinley/LWSC_Auto_Rob.git
  (See git examples below)

  
  --Created 2020 Dec 15
  --by Joseph Hauser
  --Modified 2020 jan 26
  --by Joseph Hauser

************************************************** */

// setting up global values for sensors
  
  #define MOTOR1 9
  #define MOTOR2 10
  #define MAXCONTROLROWS 14
  #define MAXSENSVALS 5
  int mot1speed = 0;
  int mot2speed = 0;
  int motControlMatrix[MAXCONTROLROWS][7]{
           {0, 0, 0, 0, 0, 0, 0},
           {1, 0, 0, 0, 0, 0, 100},
           {0, 1, 0, 0, 0, 0, 75},
           {0, 0, 1, 0, 0, 85, 85},
           {0, 0, 0, 1, 0, 75, 0},
           {0, 0, 0, 0, 1, 100, 0},
           {1, 1, 0, 0, 0, 0, 85},
           {0, 1, 1, 0, 0, 50, 100},
           {0, 0, 1, 1, 0, 100, 50},
           {0, 0, 0, 1, 1, 85, 0},
           {1, 1, 1, 0, 0, 0, 70},
           {0, 1, 1, 1, 0, 50, 50},
           {0, 0, 1, 1, 1, 70, 0}
            }; 
            
  bool sensVals[MAXSENSVALS] = {LOW, LOW, LOW, LOW, LOW};
  int sensAn = 0;
  
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  //pinMode(A5, OUTPUT); but it's analog
}

// the loop function runs over and over again forever
//---------- Main Program --------------------------
//--------------------------------------------------                         
void loop() {
  
  //flashing pin 2
  digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(50);                       // wait for a second
  digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
  delay(50);                       // wait for a second

//Step 1. Read the line sensor  
  sensorRead();
  delay(10);

//Step 2. process the incoming data, and determine the motor commands   
   dataFilter();

//Step 3. send out the motor commands
   motorControl(MOTOR1, mot1speed);
   motorControl(MOTOR2, mot2speed);
 
 

    //ad  a new line at the end of the output data
    Serial.println(" ");

}


// recieves information from the Cytron Maker Line
void sensorRead(void) {
  // initialize digital pin LED_BUILTIN as an output.
 sensVals[0] = digitalRead(A0);
 sensVals[1] = digitalRead(A1); 
 sensVals[2] = digitalRead(A2);
 sensVals[3] = digitalRead(A3);
 sensVals[4] = digitalRead(A4);
 sensAn = analogRead(A5);

 Serial.print(sensVals[0]);
 Serial.print(", ");
 Serial.print(sensVals[1]);
 Serial.print(", ");
 Serial.print(sensVals[2]);
 Serial.print(", ");
 Serial.print(sensVals[3]);
 Serial.print(", ");
 Serial.print(sensVals[4]);
 Serial.print(", ");
 Serial.print(sensAn);
 Serial.print(" -- ");
}

// filters the data recieved so the motors can understand what actions to take
void dataFilter(void) {
   
    bool rowMatch = true;
    
    for (int row = 0; row < MAXCONTROLROWS; row++) {
      
      //compare one row of control matrix with sensor array
      //if it compares, control the motor
      for(int col = 0; col < MAXSENSVALS; col++) {
        if (sensVals[col] != motControlMatrix[row][col]){
          rowMatch = false;
          break;
        }
        else {
          rowMatch = true;  
        }
      } //done with inner loop 
      if (rowMatch == true) {
        mot1speed = motControlMatrix[row][5];
        mot2speed = motControlMatrix[row][6];
        break;
      } 
    }//end of outer loop
    if (rowMatch == false) {
      mot1speed = 0;
      mot2speed = 0;
      Serial.println("uh oh, something went wrong >:(");
    }
}

// commmands sent to the motor controller
bool motorControl(int motorNum, int motorPow) {
  
  Serial.print(" --> ");
  Serial.print(motorNum);
  Serial.print(", ");
  Serial.print(motorPow);
  Serial.print(" <-- ");
  
  if (motorNum == MOTOR1) {
    analogWrite(MOTOR1, motorPow); 
 }
  else if (motorNum == MOTOR2) {
    analogWrite(MOTOR2, motorPow);
    
 }
  else {
    Serial.println("motor nonexiststant");
    return false;
 }
return true;
}

/* GitHub Examples
 *  
 *  New Git Repo - do this one time
 *  echo "# LWSC_Auto_Rob_V1" >> README.md
 *  git init
 *  git add README.md
 *  git commit -m "first commit"
 *  git remote add origin git@github.com:jumblobinley/LWSC_Auto_Rob_V1.git
 *  git push -u origin master
 *  
 *  ---Write code
 *  ---Add file to repo:
 *  git add <filename>
 *  
 *   --Attach a remote origin to your code repo, Do this one time
 *  git remote add origin git@github.com:jumblobinley/LWSC_Auto_Rob_V1.git
 *  (Note: ssh keys are set up for this computer.  Other students will have to set up thier keys)
 *  
 *  ---When done writing code, commit your code and push to github in the cloud
 *  
 *  cd ~/Documents/ArduinoSketchBook/autocar_testing
 *  git add autocar_testing.ino
 *  git commit -m "comment"
 *  
 *  git push -u origin master
 *  
 */
