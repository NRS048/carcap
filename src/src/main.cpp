#include <Arduino.h>

#include "BluetoothSerial.h"

/* Check if Bluetooth configurations are enabled in the SDK */
/* If not, then you have to recompile the SDK */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
byte BTData;  

bool l_blinker_status = false;
bool r_blinker_status = false;
bool h_blinker_status = false;
bool brake_status = false;
bool reverse_status = false;
bool headlight_status = false;

bool l_blinker_pin_state = false;
bool r_blinker_pin_state = false;
bool h_blinker_pin_state = false;

// set the pin for the Boolean LED
const int l_blinker_pin = 16;  // 2 orange LEDs, front and back (left side)
const int r_blinker_pin = 17;  // 2 orange LEDs, front and back (right side)
const int brake_pin = 18;      // 2 red LEDs, back
const int reverse_pin = 19;   // 2 white LEDs, back
const int headlight_pin = 21;  // 2 white LEDs, front

// blinker setup
const int interval = 500;
unsigned long previous_millis = 0;

bool light_state = false;

void setup() 
{
  Serial.begin(115200);
  delay(1000);

  /* If you want to assign a specific name to the ESP32 Bluetooth device you have to specify it as an argument of the SerialBT.begin() function.
  For example, if you want to call it "myESP32BT" put SerialBT.begin("myESP32BT").
  If you leave the command without a parameter, ie SerialBT.begin(), the default name "ESP32" will be applied. */
  
  SerialBT.begin("GradCap");
  Serial.println("Bluetooth Started! Ready to pair...");

  pinMode(l_blinker_pin, OUTPUT);
  pinMode(r_blinker_pin, OUTPUT);
  pinMode(brake_pin, OUTPUT);
  pinMode(reverse_pin, OUTPUT);
  pinMode(headlight_pin, OUTPUT);

  digitalWrite(brake_pin, HIGH);
  delay(100);
  digitalWrite(brake_pin, LOW);
  delay(100);
  digitalWrite(brake_pin, HIGH);
  delay(100);
  digitalWrite(brake_pin, LOW);
}

void send(String data)  //Return Data to User, usage only for query and manual debug
{
  String sendstring = data + "\n";
  int size = sendstring.length();

  for(int i = 0; i < size; i++)
  {
    SerialBT.write(sendstring[i]);
  }
} 

void loop()
{
  if(SerialBT.available())
  {
    BTData = SerialBT.read();
    Serial.write(BTData);
  }
  
  switch (BTData)
  {
    case 'h': //hazards
      h_blinker_status = !h_blinker_status;
      l_blinker_status = false;
      r_blinker_status = false;
      digitalWrite(l_blinker_pin, LOW);
      digitalWrite(r_blinker_pin, LOW);
      //send("switch hazards' status")
      break;
    
    case 'l': //LEFT BLINKER
      h_blinker_status = false;
      r_blinker_status = false;
      l_blinker_status = !l_blinker_status;
      digitalWrite(l_blinker_pin, LOW);
      digitalWrite(r_blinker_pin, LOW);
      //send("switch left blinkers' status");
      break;
    
    case 'r': //RIGHT BLINKER
      h_blinker_status = false;
      l_blinker_status = false;
      r_blinker_status = !r_blinker_status;
      digitalWrite(l_blinker_pin, LOW);
      digitalWrite(r_blinker_pin, LOW);
      //send("switch right blinkers' status");
      break;

    case 'b': //BRAKE LIGHTS
      brake_status = !brake_status;
      //send("switch brakes' status");
      break;

    case 'x': //REVERSE LIGHTS
      reverse_status = !reverse_status;
      //send("switch reverses' status");
      break;

    case 'y': //HEADLIGHTS
      headlight_status = !headlight_status;
      //send("switch headlights' status");
      break;

    case 'q': //QUERY
      send("Left Blinker: " + String(l_blinker_status) + ", \nRight Blinker: " + String(r_blinker_status) + ", \nHazard" + String(h_blinker_status) + ", \nBrake: " + String(brake_status) + ", \nReverse: " + String(reverse_status) + ", \n Headlights" + String(headlight_status) + ", \n");
      break;

    default:
      break;

  }

  // ----------------------------- blink code below -------------------------------

  unsigned long current_millis = millis();

  if(current_millis - previous_millis >= interval)
  {
    previous_millis = current_millis;


    if(l_blinker_status)
    {
      if(l_blinker_pin_state)
      {
        l_blinker_pin_state = !l_blinker_pin_state;
        digitalWrite(l_blinker_pin, LOW);
      } else {
        l_blinker_pin_state = !l_blinker_pin_state;
        digitalWrite(l_blinker_pin, HIGH);
      }
    }

    if(r_blinker_status)
    {
      if(r_blinker_pin_state)
      {
        r_blinker_pin_state = !r_blinker_pin_state;
        digitalWrite(r_blinker_pin, LOW);
      } else {
        r_blinker_pin_state = !r_blinker_pin_state;
        digitalWrite(r_blinker_pin, HIGH);
      }
    }

    if(h_blinker_status)
    {
      if(h_blinker_pin_state)
      {
        h_blinker_pin_state = !h_blinker_pin_state;
        digitalWrite(l_blinker_pin, LOW);
        digitalWrite(r_blinker_pin, LOW);
      } else {
        h_blinker_pin_state = !h_blinker_pin_state;
        digitalWrite(l_blinker_pin, HIGH);
        digitalWrite(r_blinker_pin, HIGH);
      }
    }
  }

  // ----------------------------- blink code above -------------------------------

  if(brake_status)
  {
    digitalWrite(brake_pin, HIGH);
  } else {
    digitalWrite(brake_pin, LOW);
  }

  if(reverse_status)
  {
    digitalWrite(reverse_pin, HIGH);
  } else {
    digitalWrite(reverse_pin, LOW);
  }

  if(headlight_status)
  {
    light_state = false;
    digitalWrite(headlight_pin, HIGH);
  } 
  else {
    if(light_state){

    } else {
      digitalWrite(headlight_pin, LOW);
      light_state = true;
    }
  }
}