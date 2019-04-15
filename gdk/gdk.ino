#include <Servo.h>
#include <SoftwareSerial.h>

Servo servo;


/*
Fields to represent connecting WIFI module
*/
const int rxPin = 0;
const int txPin = 1;
SoftwareSerial ArduinoUNO(rxPin, txPin);

/*
Fields to represent for connecting Servo motor
*/
const int servoPin = 7;

/*
Fields to represent for connecting Stepper motor
*/

//Vertical stepper motor
const int in11 = 11;
const int in10 =10;
const int in9 = 9;
const int in8 = 8;

//Horizontal stepper motor
const int in6 = 6;
const int in5 = 5;
const int in4 = 4;
const int in3 = 3;

//Delay between the step of the stepper motor
const int dl = 3;

//Step Vertical motor
const int STEP = 13;
//Step Horizontal motor
const int STEP_H = 15; 

/*
Fields to represent for size of blank
1cm = 6
8cm = 48
*/
const int HEIGHT = 48;
const int WIDTH = 48;

/*
Fields to control plotter's movings
*/
int movingRIGHT = 1;
int containsPOINT = 0;
int START = 0;
int INVERT = 0;
int COUNTER = 0;
int lastPosition = 0;
int GET = 0;
int endPosition = 0;
String str = "";

/*
Fields to represent input data
*/
int arr[48];
int arr1[48];
int arr2[48];


void setup() {
    //Servo attaching
    servo.attach(servoPin);
    
    //Staring WIFI
    ArduinoUNO.begin(115200);
    
    //Motor vertical
    pinMode(in11, OUTPUT);
    pinMode(in10, OUTPUT);
    pinMode(in9, OUTPUT);
    pinMode(in8, OUTPUT);

    //Motor horizontal
    pinMode(in6, OUTPUT);
    pinMode(in5, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(in3, OUTPUT);
}

// Function for moving vertical motor up
void moveTop() {
  for(int j = 0; j < STEP_H; ++j) {
        digitalWrite( in11, HIGH ); 
        digitalWrite( in10, HIGH ); 
        digitalWrite( in9, LOW ); 
        digitalWrite( in8, LOW );
        delay(dl);
    
        digitalWrite( in11, LOW ); 
        digitalWrite( in10, HIGH ); 
        digitalWrite( in9, HIGH ); 
        digitalWrite( in8, LOW );
        delay(dl);
    
        digitalWrite( in11, LOW ); 
        digitalWrite( in10, LOW ); 
        digitalWrite( in9, HIGH ); 
        digitalWrite( in8, HIGH );
        delay(dl);
    
        digitalWrite( in11, HIGH ); 
        digitalWrite( in10, LOW ); 
        digitalWrite( in9, LOW ); 
        digitalWrite( in8, HIGH );
        delay(dl);
    }
}


// Function for moving vertical motor down
void moveBottom() {
  for(int j = 0; j < STEP_H; ++j) {
        digitalWrite( in11, HIGH ); 
        digitalWrite( in10, LOW ); 
        digitalWrite( in9, LOW ); 
        digitalWrite( in8, HIGH );
        delay(dl);
    
        digitalWrite( in11, LOW ); 
        digitalWrite( in10, LOW ); 
        digitalWrite( in9, HIGH ); 
        digitalWrite( in8, HIGH );
        delay(dl);
    
        digitalWrite( in11, LOW ); 
        digitalWrite( in10, HIGH ); 
        digitalWrite( in9, HIGH ); 
        digitalWrite( in8, LOW );
        delay(dl);
    
        digitalWrite( in11, HIGH ); 
        digitalWrite( in10, HIGH ); 
        digitalWrite( in9, LOW ); 
        digitalWrite( in8, LOW );
        delay(dl); 
    } 
}


// Function for moving horizontal motor right
void moveRight() {
        for(int j = 0; j < STEP; ++j) {
              digitalWrite( in6, HIGH ); 
              digitalWrite( in5, HIGH ); 
              digitalWrite( in4, LOW ); 
              digitalWrite( in3, LOW );
              delay(dl);
          
              digitalWrite( in6, LOW ); 
              digitalWrite( in5, HIGH ); 
              digitalWrite( in4, HIGH ); 
              digitalWrite( in3, LOW );
              delay(dl);
          
              digitalWrite( in6, LOW ); 
              digitalWrite( in5, LOW ); 
              digitalWrite( in4, HIGH ); 
              digitalWrite( in3, HIGH );
              delay(dl);
          
              digitalWrite( in6, HIGH ); 
              digitalWrite( in5, LOW ); 
              digitalWrite( in4, LOW ); 
              digitalWrite( in3, HIGH );
              delay(dl);
        }
}


// Function for moving vertical motor left
void moveLeft() {
  for(int j = 0; j < STEP; ++j) {
        digitalWrite( in6, HIGH ); 
        digitalWrite( in5, LOW ); 
        digitalWrite( in4, LOW ); 
        digitalWrite( in3, HIGH );
        delay(dl);
    
        digitalWrite( in6, LOW ); 
        digitalWrite( in5, LOW ); 
        digitalWrite( in4, HIGH ); 
        digitalWrite( in3, HIGH );
        delay(dl);
    
        digitalWrite( in6, LOW ); 
        digitalWrite( in5, HIGH ); 
        digitalWrite( in4, HIGH ); 
        digitalWrite( in3, LOW );
        delay(dl);
    
        digitalWrite( in6, HIGH ); 
        digitalWrite( in5, HIGH ); 
        digitalWrite( in4, LOW ); 
        digitalWrite( in3, LOW );
        delay(dl); 
    } 
}

/*
Funcion for comparising of three identical arrays of input data for the presence of garbage
*/
void garbage(int* arr, int* arr1, int* arr2) {
    for(int i = 0; i < 48; ++i) {
      if(arr[i] != 0 && arr[i] != 1) {

              if(arr1[i] == 0 || arr1[i] == 1) {
                    arr[i] = arr1[i];
              } else if(arr2[i] == 0 || arr2[i] == 1) {
                      arr[i] == arr2[i];
              } else {
                arr[i] = 0;
              }
      }
    }
}

/*Function for adding input string to array: {array, array1, array2}
if char isn't 0 or 1, it becomes 2;
*/

void addStrToArray(String & str, int* arr) {
      for(int i = 0; i < str.length(); ++i) {
          char c = str.charAt(i);
          if(c != '0' && c != '1') {
            c = '2';
          }
          arr[i] = c - '0';
          //Serial.print(arr[i]);
          //Serial.print(" ");
    }
}

//Function for changing direction of the plotter
void invert(int* arr, int len) {
  if(INVERT == 1) {
        int temp = 0;
        for(int j = 0; j < WIDTH/2; ++j) {
            temp = arr[WIDTH - 1 - j];
            arr[WIDTH - 1 - j] = arr[j];
            arr[j] = temp;         
        }
        INVERT = 0;

    }
}

//Function for drawing
void drawing(int* arr) {
    
       for(int j = 0; j < WIDTH; ++j) {
          if(arr[j] == 1) {
            containsPOINT = 1;
            
            //Moving to position
            for(int k = 0; k < j - lastPosition; ++k) {
              if(movingRIGHT == 1) {
                moveRight();
              } else {
                moveLeft();
              }
            }

            servo.write(0);
            delay(500);
          
          int countLen = 0;
          while(j + 1 < WIDTH && arr[j+1] == 1) {
            countLen++;
            j++;
          }

          lastPosition = j;
          endPosition = lastPosition;

          //Drawing
          for(int k = 0; k < countLen; ++k) {
              if(movingRIGHT == 1) {
                moveRightQuickly();
              } else {
                moveLeftQuckcly();
              }
          }

          servo.write(20);
          delay(500);
      }
    }


      //Changing moving
      if(containsPOINT == 1) {

        if(movingRIGHT == 1) {
      
             if(lastPosition <= WIDTH / 2) {
              
                  for(int j = 0; j < lastPosition; ++j) {
                       moveLeft();
                  }
                  movingRIGHT = 1;
                   
             } else {
                  for(int j = 0; j < WIDTH - lastPosition - 1; ++j) {
                    moveRight();
                  }  
                  INVERT = 1;
                  movingRIGHT = 0;
             }
         
        } else {
    
            if(lastPosition <= WIDTH / 2) {
    
              for(int j = 0; j < lastPosition; ++j) {
                   moveRight();
              }
              INVERT = 1;
              movingRIGHT = 0;
              
            } else {

                for(int j = 0; j < WIDTH - lastPosition - 1; ++j) {
                      moveLeft();
                }
                movingRIGHT = 1;
                
                
              }
       }      
}  

      moveTop();

      containsPOINT = 0;
      lastPosition = 0;      
      START = 0;
      COUNTER++;
      GET = 0;
  
}

void loop() {
  
  //Set start position of plotter
  servo.write(20);
  delay(500);

  //Check for WIFI connection
  if (ArduinoUNO.available()) {
          str = ArduinoUNO.readString();
        if(GET == 0) {
           addStrToArray(str, arr);
        } else if(GET == 1) {
            addStrToArray(str, arr1);
        } else if (GET == 2) {
            addStrToArray(str, arr2);
            garbage(arr, arr1, arr2);   
            servo.write(25);
            delay(1000);
            START = 1;
            invert(arr, WIDTH);        
        }
        GET++;
  }



  



if(START == 1) {  
        drawing(arr);
        Serial.println(movingRIGHT);   
}


//After finishing drawing, returning to position
if(COUNTER == HEIGHT) {
  for(int i = 0; i < HEIGHT; ++i) {
    moveBottom();
  }

  for(int i = 0; i < endPosition; ++i) {
    moveLeft();
  }
}       
}
