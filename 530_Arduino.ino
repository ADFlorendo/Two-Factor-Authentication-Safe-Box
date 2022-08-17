#include <Servo.h>
#include <Keypad.h>

Servo servo;

//set up pin numbers
const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //three columns

int switchThree = 13;
int switchTwo = 12;
int switchOne = 11; 


//set up keypad arrray
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );


String password = "2424"; // change your password here
String inputPassword;


void setup(){
  Serial.begin(9600);
  inputPassword.reserve(32); // maximum input characters is 33, change if needed

  //set up pinmodes for 3 toggle switches
  pinMode(switchThree, INPUT_PULLUP);
  pinMode(switchTwo, INPUT_PULLUP);
  pinMode(switchOne, INPUT_PULLUP);

  //set servo angle
  servo.attach(10);
  servo.write(270);
}

void loop(){
  char key = keypad.getKey();

  //flag variables to detect if toggle swith is on/off  1 = on, 0 = off
  int three = digitalRead(switchThree);
  int two = digitalRead(switchTwo);
  int one = digitalRead(switchOne);

  
  if (key){
    Serial.println(key);

    Serial.println(inputPassword);
    //if user presses '1' key, reset password
    if(key == '1') 
    {
      inputPassword = ""; // clear input password
    } 
    //'3' key is an enter key
    //after user believes they've entered the correct pw, they press 3
    else if(key == '3') {
      //check if user's pw matches with ide's pw
      if(password == inputPassword) 
      {
        //check if switches are correct
        //change toggle switch settings here 
        if (three == 1 && two == 1 && one == 0)
        {
          //unlock servo
          servo.write(90);
        }
        
      }else 
      {
        Serial.println("password is incorrect, try again");
      }

      inputPassword = ""; //clear input password
    }else 
    {
      inputPassword += key; //append new character to input password string
    }
  }
}
  

    
   
        
