// Copy this into Arduino IDE and upload

/* 
  Author: Luca Ebner
  Date: November 2019
*/

int stage = 0;

// 7dots
const int led[] = {0,1,2,3,4,5,6}; //LED pins
const int button[] = {7,8,9,10,11,12,13}; //TODO remap these pin numbers, arduino uno doesnt have enough pins
bool buttonstate[] = {0,0,0,0,0,0,0};
bool ledstate[] = {0,0,0,0,0,0,0};
bool reset[] = {0,0,0,0,0,0,0};


bool stage1(){

  if((ledstate[0]==true) && (ledstate[1]==true) && (ledstate[2]==true) && (ledstate[3]==true) && (ledstate[4]==true) && (ledstate[5]==true) && (ledstate[6]==true)){
    Serial.println("All LEDs turned on. Stage one complete.");
  
    //visual confirmation
    for(int j=0; j<4; j++){
      for(int i=0; i<7; i++){
         digitalWrite(led[i], LOW);
      }
      delay(500);
      for(int i=0; i<7; i++){
         digitalWrite(led[i], HIGH);
      }
      delay(500);
    }
      for(int i = 0; i<7; i++){
         ledstate[i] = reset[i];
         digitalWrite(led[i], LOW);
      }

      stage++;
  }

  //update button readings
  for(int i = 0; i<7; i++){
    buttonstate[i] = digitalRead(button[i]);
  }

  for(int i = 0; i<7; i++){
    if (buttonstate[i] == HIGH){

      //Serial.println(button[i]);
      
      digitalWrite(i, !ledstate[i]);
      ledstate[i] = !ledstate[i];
      if(i==0){
        digitalWrite(6, !ledstate[6]);
        digitalWrite(1, !ledstate[1]);
        ledstate[6] = !ledstate[6];
        ledstate[1] = !ledstate[1];
      } else if(i==6){
        digitalWrite(5, !ledstate[5]);
        digitalWrite(0, !ledstate[0]);
        ledstate[5] = !ledstate[5];
        ledstate[0] = !ledstate[0];
      } else{ //usual case, neighbor leds should switch as well
        digitalWrite(i-1, !ledstate[i-1]);
        digitalWrite(i+1, !ledstate[i+1]);
        ledstate[i-1] = !ledstate[i-1];
        ledstate[i+1] = !ledstate[i+1];
      }
        delay(500);
    }
  }

}



bool stage2(){

}


void setup() {
  // put your setup code here, to run once:

  //Serial.begin(9600);

  // 7dots
  for(int i = 0; i<7; i++){
    pinMode(led[i], OUTPUT);
    pinMode(button[i], INPUT);
  }
    
  stage = 1;
  Serial.println("Initialized.");
}

void loop() {

  switch(stage){

    case 1:
      stage1();
      break;

    case 2:
      break;

    default:
      Serial.print("[switch]: stage is ");
      Serial.println(stage);
      break;
  }

}
