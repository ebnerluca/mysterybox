// Copy this into Arduino IDE and upload

/* 
  Author: Luca Ebner
  Date: November 2019
*/

int stage = 0;
const bool debug = false;

// 7dots
const int led[] = {0,1,2,3,4,5,6}; //LED pins
const int button[] = {7,8,9,10,11,12,13}; //TODO remap these pin numbers, arduino uno doesnt have enough pins
bool buttonstate[] = {0,0,0,0,0,0,0};
bool ledstate[] = {0,0,0,0,0,0,0};
bool reset[] = {0,0,0,0,0,0,0};

//MagnetPanel
const int magnetPanelPin = A0;

//MetalBar
const int metalBarPin = A1;


bool stage1(){

  if((ledstate[0]==true) && (ledstate[1]==true) && (ledstate[2]==true) && (ledstate[3]==true) && (ledstate[4]==true) && (ledstate[5]==true) && (ledstate[6]==true)){
    if(debug){Serial.println("[7dots]: All LEDs turned on. Stage one complete.");}
  
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
  if(digitalRead(magnetPanelPin)==HIGH){
    stage++;
    if(debug){Serial.println("[stage2]: Magnet Panel combination correct! Proceed with stage 3.");}
  }

}


bool stage3(){

  if(digitalRead(metalBarPin) == HIGH){
    stage++;
    if(debug){Serial.println("[stage3]: Metal Bar connectors bridged, success! Proceed with stage 4.");}
  }
  
}


void setup() {
  // put your setup code here, to run once:

  if(debug){Serial.begin(9600);}

  // 7dots
  for(int i = 0; i<7; i++){
    pinMode(led[i], OUTPUT);
    pinMode(button[i], INPUT);
  }

  //MagnetPanel
  pinMode(magnetPanelPin, INPUT);

  //MetalBar
  pinMode(metalBarPin, INPUT);
    
  stage = 1;
  if(debug){Serial.println("[Setup]: Initialized.");}
}

void loop() {

  switch(stage){

    case 1: //7dots
      stage1();
      break;

    case 2: //MagnetPanel
      stage2();
      break;

    case 3:
      stage3();
      break;

    default:
      if(debug){Serial.println("[Switch]: Error! default case");}
      break;

  }
  
  if(debug){
    static int lastTimestamp = millis();
    static int throttle = 2000;
    if((millis()-lastTimestamp) > throttle){
      Serial.print("[Main Loop]: stage is ");
      Serial.println(stage);
      lastTimestamp = millis();
    }
  }
  


}
