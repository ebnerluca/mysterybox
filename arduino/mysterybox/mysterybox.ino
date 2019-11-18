// Copy this into Arduino IDE and upload

/* 
  Author: Luca Ebner
  Date: November 2019
*/

#include "sevendots.h"
#include "magnetpanel.h"

/// config ///
const bool debug = false;


// 7dots
const int led[] = {0,1,2,3,4,5,6}; //LED pins
const int button[] = {7,8,9,10,11,12,13}; //TODO remap these pin numbers, arduino uno doesnt have enough pins
SevenDots sevenDots(led, button);

// MagnetPanel
const int magnetPanelPin = A0;
MagnetPanel magnetPanel(magnetPanelPin);


// MetalBar
const int metalBarPin = A1;

int stage = 0;


bool stage1(){
  if(sevenDots.spinOnce()){
    if(debug){Serial.println("[stage1]: All 7 LEDs are on, success!");}
  }
}


bool stage2(){
  if(magnetPanel.spinOnce()){
    if(debug){Serial.println("[stage2]: Magnet Panel combination correct!");}
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
  sevenDots.setup();

  //MagnetPanel
  magnetPanel.setup();

  //MetalBar
  pinMode(metalBarPin, INPUT);
    
  stage = 1;
  if(debug){Serial.println("[Setup]: Initialized.");}
}

void loop() {

  switch(stage){

    case 1: //7dots
      if(stage1()){
        if(debug){Serial.println("[switch]: Stage 1 complete. Proceed with stage 2.");}
        stage++;
        //TODO: maybe redeclare pinModes here? this allows re-using pins
      }
      break;

    case 2: //MagnetPanel
      if(stage2()){
        if(debug){Serial.println("[switch]: Stage 2 complete. Proceed with stage 3.");}
        stage++;
      }
      break;

    case 3:
      stage3();
      break;

    default:
      if(debug){
        Serial.print("[switch]: Error! default case, stage: ");
        Serial.println(stage);
      }
      break;

  }
  
  if(debug){
    static unsigned long int lastTimestamp = millis();
    static int throttle = 2000;
    if((millis()-lastTimestamp) > throttle){
      Serial.print("[Main Loop]: stage is ");
      Serial.println(stage);
      lastTimestamp = millis();
    }
  }
  


}
