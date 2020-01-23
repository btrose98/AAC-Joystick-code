#include <Mouse.h>

int cursorSpeed = 3; //TO MODIFY CURSOR SPEED CHANGE THIS VALUE, HIGHER VALUE = SLOWER SPEED 

int horzPin = A1;  // Analog output of horizontal joystick pin
int vertPin = A0;  // Analog output of vertical joystick pin
int selPin = 8;  // select button pin of joystick

float vertZero, horzZero;  // Stores the initial value of each axis, usually around 512
float vertValue, horzValue;  // Stores current analog output of each axis
const int sensitivity = 490;  // Higher sensitivity value = slower mouse, should be <= about 500
                              // Unable to go higher without causing problems with joystick functionality
int mouseClickFlag = 0;
void setup()
{
  Serial.begin(9600); //setup serial and sets data rate in bits per second
  pinMode(horzPin, INPUT);  // Set both analog pins as inputs
  pinMode(vertPin, INPUT);
  pinMode(selPin, INPUT);  // set button select pin as input
  digitalWrite(selPin, HIGH);  // Pull button select pin high
  delay(1000);  // short delay to let outputs settle
  vertZero = analogRead(vertPin);  // get the initial values
  horzZero = analogRead(horzPin);  // Joystick should be in neutral position when reading these
  //Mouse.begin();
}

void loop()
{                                 
  vertValue = analogRead(vertPin) - vertZero;  // read vertical offset
  horzValue = analogRead(horzPin) - horzZero;  // read horizontal offset

  if (vertValue!=0 || horzValue!=0) //move mouse if position of joystick has changed
    Mouse.move(-horzValue*2/sensitivity, vertValue*2/sensitivity, 0); //adjust speed of cursor by increasing numerator, start with a multiple of 2

  if ((digitalRead(selPin) == 0) && (!mouseClickFlag))  // if the joystick button is pressed
  {
    mouseClickFlag = 1;
    Mouse.press(MOUSE_LEFT);  // click the left button down
    Mouse.release(MOUSE_LEFT); //release the left button
    delay(250); //delay half a second between presses
  }
  else if ((digitalRead(selPin))&&(mouseClickFlag)) // if the joystick button is not pressed
  {
    mouseClickFlag = 0;
    Mouse.release(MOUSE_LEFT);  // release the left button
  }
  delay(cursorSpeed); //Creates a delay between each loop thus changing the (variable) speed of the cursor 
}
