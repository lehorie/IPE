#include <Servo.h>
Servo servo1; //Servos
Servo servo2;
Servo servo3;

const int button1 = 12; //Buttons
const int button2 = 13;
bool button2flag=0;

int button1Presses = 0; //Button values
boolean button2Pressed = false;

const int pot1 = A0; //Potentimeters
const int pot2 = A1; 
const int pot3 = A2;

int pot1Val; //Potentimeter values
int pot2Val;
int pot3Val;
int pot1Angle;
int pot2Angle;
int pot3Angle;

int servo1PosSaves[30] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; //position saves
int servo2PosSaves[30] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int servo3PosSaves[30] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

int previousAngle1 = 0;
int previousAngle2 = 0;
int previousAngle3 = 0;

void move(int angle1, int angle2, int angle3) {


  if(angle1>previousAngle1)
  {
    for(int j=previousAngle1; j<=angle1; j++)
    {
      servo1.write(j); //turn servo by 1 degrees
      delay(10);        //delay for smoothness
    }
  }

  if(angle1<previousAngle1)
  {
    for(int j=previousAngle1; j>=angle1; j--)
    {
      servo1.write(j); //turn servo by 1 degrees
      delay(10);        //delay for smoothness
    }
  }
  
  if(angle3>previousAngle3)
  {
    for(int j=previousAngle3; j<=angle3; j++)
    {
      servo3.write(j); //turn servo by 1 degrees
      delay(10);        //delay for smoothness
    }
  }

  if(angle3<previousAngle3)
  {
    for(int j=previousAngle3; j>=angle3; j--)
    {
      servo3.write(j); //turn servo by 1 degrees
      delay(10);        //delay for smoothness
    }
  } 

  if(angle2>previousAngle2)
  {
    for(int j=previousAngle2; j<=angle2; j++)
    {
      servo2.write(j); //turn servo by 1 degrees
      delay(10);        //delay for smoothness
    }
  }

  if(angle2<previousAngle2)
  {
    for(int j=previousAngle2; j>=angle2; j--)
    {
      servo2.write(j); //turn servo by 1 degrees
      delay(10);        //delay for smoothness
    }
  }
  previousAngle1 = angle1;
  previousAngle2 = angle2;
  previousAngle3 = angle3;
}

void setup() {
  servo1.attach(5); // Set up everything and will run once; attach servos and define the pin modes
  servo2.attach(6);
  servo3.attach(9);

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);

  Serial.begin(9600);
}

void loop() {
  pot1Val = analogRead(pot1); // This will read the values from the potentimeters and store it...
  pot1Angle = map(pot1Val, 0, 1023, 62, 83); // ... and this will map the values from the potentiometers to values the servos can use and store it for later use
  pot2Val = analogRead(pot2); 
  pot2Angle = map(pot2Val, 0, 1023, 0, 179);
  pot3Val = analogRead(pot3);
  pot3Angle = map(pot3Val, 0, 1023, 0, 179);
  
  servo1.write(pot1Angle); // These will make the servos move to the mapped angles
  servo2.write(pot2Angle);
  servo3.write(pot3Angle);

  //Serial.println("########################");
  //Serial.println(pot1Angle);
  //Serial.println(pot2Angle);
  //Serial.println(pot3Angle);
  
  if(digitalRead(button1) == HIGH){ // This will check how many times button1 is pressed and save the positions to an array depending on how many times it is pressed; switch/case works like a if statement
    servo1PosSaves[button1Presses] = pot1Angle;
    servo2PosSaves[button1Presses] = pot2Angle;
    servo3PosSaves[button1Presses] = pot3Angle;
    
    Serial.println("Pos");
    Serial.println(button1Presses, DEC);
    Serial.println("Saved");
    button1Presses++;
 
    delay(1000);
  }

  if(digitalRead(button2) == HIGH){ // Pretty self-explnatory here
    button2Pressed = true;  
    previousAngle1 = pot1Angle;
    previousAngle2 = pot2Angle;
    previousAngle3 = pot3Angle; 
  }
  
  if(button2Pressed){ // if the boolean button2Press is true, then the servos will run though all their saved positions
    for(int i = 0; i < button1Presses; i++){
        move(servo1PosSaves[i], servo2PosSaves[i], servo3PosSaves[i]);
        Serial.println(" potentimeter Angles: ");
        Serial.println(servo1PosSaves[i]);
        Serial.println(servo2PosSaves[i]);
        Serial.println(servo3PosSaves[i]);
        delay(10);
        if (i == 0 || i == button1Presses -1 || i == button1Presses -2)
        {
          delay(1000);
        }
    } 
  }
}
