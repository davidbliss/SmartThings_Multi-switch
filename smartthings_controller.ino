
#include <SoftwareSerial.h>   
#include <SmartThings.h>
 
 
#define PIN_THING_RX    3
#define PIN_THING_TX    2
 
SmartThingsCallout_t messageCallout;    // call out function forward decalaration
SmartThings smartthing(PIN_THING_RX, PIN_THING_TX, messageCallout);  // constructor
 
bool isDebugEnabled;    // enable or disable debug in this example

int button1Pin = 8;
int button2Pin = 9;
int switch1Pin = 5;
int switch2Pin = 7;
int switch3Pin = 4;

int button1State = digitalRead(button1Pin);
int button2State = digitalRead(button2Pin);
int switch1State = digitalRead(switch1Pin);
int switch2State = digitalRead(switch2Pin);
int switch3State = digitalRead(switch3Pin);  

int potPin = 0;    // select the input pin for the potentiometer
int potVal;
int potSetTime = -1;

void setup()
{
  // setup default state of global variables
  isDebugEnabled = false;
  
  if (isDebugEnabled)
  { // setup debug serial port
    Serial.begin(9600);         // setup serial with a baud rate of 9600
    Serial.println("setup..");  // print out 'setup..' on start
  }
  smartthing.send("Arduino controller online");
}
 
 
void loop()
{
  // run smartthing logic
  smartthing.run();
  
  // read button and switch values
  int curState = digitalRead(button1Pin);
  if (curState != button1State) {
    button1State = curState;
    if (isDebugEnabled) Serial.print("button1State is now:"); Serial.println(button1State);
    if (curState == 1) {
      on4();
    } 
  }
  curState = digitalRead(button2Pin);
  if (curState != button2State) {
    button2State = curState;
    if (isDebugEnabled) Serial.print("button2State is now:"); Serial.println(button2State);
    if (curState == 1) {
      on5();
    } 
  }
  curState = digitalRead(switch1Pin);
  if (curState != switch1State) {
    switch1State = curState;
    if (isDebugEnabled) Serial.print("switch1State is now:"); Serial.println(switch1State);
    if (curState == 1) {
      on1();
    } else {
      off1();
    }
  }
  curState = digitalRead(switch2Pin);
  if (curState != switch2State) {
    switch2State = curState;
    if (isDebugEnabled) Serial.print("switch2State is now:"); Serial.println(switch2State);
    if (curState == 1) {
      on2();
    } else {
      off2();
    }
  }
  curState = digitalRead(switch3Pin);
  if (curState != switch3State) {
    switch3State = curState;
    if (isDebugEnabled) Serial.print("switch3State is now:"); Serial.println(switch3State);
    if (curState == 1) {
      on3();
    } else {
      off3();
    }
  }
  
  // read pot value 
  // it will be between 0 and 1020 in increments of 20
  // Smartthings wants 0 to 99
  int curPotVal = analogRead(potPin);
  if (abs(curPotVal-potVal)>=20){
    potVal = floor(curPotVal/20)*20;
    if (isDebugEnabled) Serial.print("potVal:"); Serial.println(potVal);
    
    // TODO: SHOULD DELAY THIS SO WE DONT SEND AS IT IS TURNING
    potSetTime = millis();
  }
  
  if (potSetTime != -1 && potSetTime + 500 < millis() ){
    int newVal = min(potVal / 10, 99);
    if (isDebugEnabled) Serial.print("newVal:"); Serial.println(newVal);
    setLevel1(String(newVal));
    potSetTime = -1;
  }
}

// switch 1 is on or off (this is routable to ifttt) 
void on1()
{
  smartthing.send("on1");        // send message to cloud
  Serial.println("on1");
}
 
void off1()
{
  smartthing.send("off1");       // send message to cloud
  Serial.println("off1");
}

// switch 3 is on2 or off2
void on2()
{
  smartthing.send("on2");        // send message to cloud
  Serial.println("on2");
}
 
void off2()
{
  smartthing.send("off2");       // send message to cloud
  Serial.println("off2");
}

// switch 2 is opened and closed (this is routable to ifttt)
void on3()
{
  smartthing.send("on3");        // send message to cloud
  Serial.println("on3");
}
 
void off3()
{
  smartthing.send("off3");       // send message to cloud
  Serial.println("off3");
}

void on4()
{
  smartthing.send("on4");       // send message to cloud
  Serial.println("on4");
  
  off4(); // because this is a momentary button, turn it back off
}

void off4()
{
  smartthing.send("off4");       // send message to cloud
  Serial.println("off4");
}

void on5()
{
  smartthing.send("on5");       // send message to cloud
  Serial.println("on5");
  
  off5(); // because this is a momentary button, turn it back off
}

void off5()
{
  smartthing.send("off5");       // send message to cloud
  Serial.println("off5");
}

void setLevel1(String level)
{
  smartthing.send("setLevel1:" + level);       // send message to cloud
  Serial.print("setLevel1 to:");Serial.println(level);
}

 
void messageCallout(String message)
{
  // if debug is enabled print out the received message
  if (isDebugEnabled)
  {
    Serial.print("Received message: '");
    Serial.print(message);
    Serial.println("' ");
  }
 
  // if message contents equals to 'on' then call on() function
  // else if message contents equals to 'off' then call off() function
  if (message.equals("on1"))
  {
    on1();
  }
  else if (message.equals("off1"))
  {
    off1();
  }
  else if (message.equals("on2"))
  {
    on2();
  }
  else if (message.equals("off2"))
  {
    off2();
  }
  else if (message.equals("on3"))
  {
    on3();
  }
  else if (message.equals("off3"))
  {
    off3();
  }
  else if (message.equals("on4"))
  {
    on4();
  }
  else if (message.equals("off4"))
  {
    off4();
  }
  else if (message.equals("on5"))
  {
    on5();
  }
  else if (message.equals("off5"))
  {
    off5();
  }
  else 
  {
    //message.equals("setLevel1:$level"))
    String level;
    if (message.startsWith("setLevel1:")) 
    {
      level = message.substring(10);
      setLevel1(level);
    }
  }
}


