#include <Servo.h>
#include <SoftwareSerial.h>

Servo servo;


//Wifi
const int rxPin = 0;
const int txPin = 1;
SoftwareSerial ArduinoUNO(rxPin, txPin);

//Servo
const int servoPin = 7;

//Motor vertical
const int in11 = 11;
const int in10 =10;
const int in9 = 9;
const int in8 = 8;

//Motor horizontal
const int in6 = 6;
const int in5 = 5;
const int in4 = 4;
const int in3 = 3;

//Delay
const int dl = 3;

//Size
const int HEIGHT = 48;
const int WIDTH = 48;

//Step
const int STEP = 13;
const int STEP_Q = 13;
const int STEP_H = 16; 

int movingRIGHT = 1;
int containsPOINT = 0;
int START = 0;
int INVERT = 0;
int COUNTER = 1;
int lastPosition = 0;
int GET = 0;
int endPosition = 0;

//Line
int arr[48];
int arr1[48];
int arr2[48];

void setup() {
    servo.attach(servoPin);
    ArduinoUNO.begin(115200);
    Serial.begin(9600);
  
    
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

void moveRightQuickly() {
        for(int j = 0; j < STEP_Q; ++j) {
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

void moveLeftQuckcly() {
  for(int j = 0; j < STEP_Q; ++j) {
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

void addStrToArray(String & str, int* arr) {
      for(int i = 0; i < str.length(); ++i) {
          char c = str.charAt(i);
          if(c != '0' && c != '1') {
            c = '2';
          }
          arr[i] = c - '0';
          Serial.print(arr[i]);
          Serial.print(" ");
    }
}

void invert(int* arr, int len) {
  if(INVERT == 1) {
        int temp = 0;
        for(int j = 0; j < WIDTH/2; ++j) {
          //if(arr[i+1][WIDTH - 1 - j] == arr[i+1][j]) continue;
            temp = arr[WIDTH - 1 - j];
            arr[WIDTH - 1 - j] = arr[j];
            arr[j] = temp;         
        }
        INVERT = 0;

    }
}

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
//
//          while(i + 1 < HEIGHT && arr[i+1][lastPosition] == 1) {
//
//            int exit = 0;
//            
//                for(int j = 0; j < WIDTH; ++j) {
//                    if(j == lastPosition) continue;
//                    if(arr[i+1][j] == 1) {
//                      exit = 1;
//                      break;
//                    }
//                }
//
//               if(exit == 1) break;
//  
//               servo.write(0);
//               moveTop();
//               i++;
//       }
//
//       servo.write(35);
//       delay(1000);

        if(movingRIGHT == 1) {
      
             if(lastPosition <= WIDTH / 2) {
              
                  for(int j = 0; j < lastPosition; ++j) {
                       moveLeft();
                  }
                   
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
              
            } else {

                for(int j = 0; j < WIDTH - lastPosition - 1; ++j) {
                      moveLeft();
                }
                movingRIGHT = 1;
                
                
              }
       }      
}  

      moveTop();

    
//    if(INVERT == 1) {
//        int temp = 0;
//        for(int j = 0; j < WIDTH/2; ++j) {
//          //if(arr[i+1][WIDTH - 1 - j] == arr[i+1][j]) continue;
//            temp = arr[WIDTH - 1 - j];
//            arr[WIDTH - 1 - j] = arr[j];
//            arr[j] = temp;         
//        }
//
//    }

      containsPOINT = 0;
      lastPosition = 0;      
      START = 0;
      COUNTER++;
      GET = 0;
  
}



void loop() {
  
//  int arr[WIDTH] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
//  int arr3[WIDTH] = {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
//  int arr2[WIDTH] = {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
//  int arr1[WIDTH] = {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
//  int arr4[WIDTH] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
//  int arr5[WIDTH] = {1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1 };
//  int arr6[WIDTH] = {1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1 };
//  int arr7[WIDTH] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
//  int arr8[WIDTH] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
//  int arr9[WIDTH] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
//  int arr10[WIDTH] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
  

  servo.write(20);
  delay(500);

  //START = 1;


  if (ArduinoUNO.available()) {
        Serial.print("\nMessage N ");
        Serial.print(GET);
        Serial.print(": ("); 
        String str = ArduinoUNO.readString();
        Serial.print(str.length());
        Serial.print(") ");
        Serial.println(str);

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
      invert(arr, WIDTH);
      
//      invert(arr1, WIDTH);
//      drawing(arr1);
//      invert(arr2, WIDTH);
//      drawing(arr2);
//      invert(arr3, WIDTH);
//      drawing(arr3);
      
//      invert(arr1, WIDTH);
//      drawing(arr1);
//      invert(arr2, WIDTH);
//      drawing(arr2);
//      invert(arr4, WIDTH);
//      drawing(arr4);
//      invert(arr5, WIDTH);
//      drawing(arr5);
//      invert(arr6, WIDTH);
//      drawing(arr6);
//      invert(arr7, WIDTH);
//      drawing(arr7);
//      invert(arr8, WIDTH);
//      drawing(arr8);
//      invert(arr9, WIDTH);
//      drawing(arr9);
//      invert(arr10, WIDTH);
//      drawing(arr10);
      
}

if(COUNTER == HEIGHT) {
  for(int i = 0; i < HEIGHT; ++i) {
    moveBottom();
  }

  for(int i = 0; i < endPosition; ++i) {
    moveLeft();
  }

  exit(0);
}
       
}
