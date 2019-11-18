// Copy this into Arduino IDE and upload

/* 
  Author: Luca Ebner
  Date: November 2019
*/

#include "sevendots.h"
#include "magnetpanel.h"
#include "metalbar.h"

/// config ///
const bool debug = true;


// 7dots
const int led[] = {0,1,2,3,4,5,6}; //LED pins
const int button[] = {7,8,9,10,11,12,13}; //TODO remap these pin numbers, arduino uno doesnt have enough pins
SevenDots sevenDots(led, button);

// MagnetPanel
const int magnetPanelPin = A0;
MagnetPanel magnetPanel(magnetPanelPin);


// MetalBar
const int metalBarPin = A1;
MetalBar metalBar(metalBarPin);

int stage = 0;


bool stage1(){
  if(sevenDots.spinOnce()){
    if(debug){Serial.println("[stage1]: All 7 LEDs are on, success!");}
    return true;
  }
  return false;
}


bool stage2(){
  if(magnetPanel.spinOnce()){
    if(debug){Serial.println("[stage2]: Magnet Panel combination correct!");}
    return true;
  }
  return false;
}


bool stage3(){
  if(digitalRead(metalBarPin) == HIGH){
    if(debug){Serial.println("[stage3]: Metal Bar connectors bridged, success!");}
    return true;
  }
  return false;
}


void setup() {
  // put your setup code here, to run once:

  if(debug){
    Serial.begin(9600);
    delay(2000);
  }

  // 7dots
  //sevenDots.setup();

  //MagnetPanel
  magnetPanel.setup();

  //MetalBar
  metalBar.setup();
    
  stage = 1;
  if(debug){Serial.println("[Setup]: Initialized.");}
}

void loop() {

  switch(stage){

    case 1: //7dots
      if(stage1()){
        if(debug){Serial.println("[Switch]: Stage 1 complete. Proceed with stage 2.");}
        stage++;
        //TODO: maybe redeclare pinModes here? this allows re-using pins
      }
      break;

    case 2: //MagnetPanel
      if(stage2()){
        if(debug){Serial.println("[Switch]: Stage 2 complete. Proceed with stage 3.");}
        stage++;
      }
      break;

    case 3:
      if(stage3()){
        if(debug){Serial.println("[Switch]: Stage 3 complete. Proceed with stage 4.");}
        stage++;
      }
      break;

    default:
      if(debug){
        Serial.print("[Switch]: Error! default case, stage: ");
        Serial.println(stage);
      }
      delay(500);
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
