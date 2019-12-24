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
const int led[] = {8,7,6,5,4,3,2};
const int button[] = {A0,A1,A2,A3,A4,A5,A6};
const int code[] = {5,2,6};
SevenDots sevenDots(led, button, code);

// MagnetPanel
const int magnetPanelPin = 9; //uses INPUT_PULLUP
MagnetPanel magnetPanel(magnetPanelPin);


// MetalBar
/*const int metalBarPin = A1;
MetalBar metalBar(metalBarPin);*/

int stage = 0;


void setup() {

  if(debug){
    Serial.begin(9600);
  }

  // 7dots
  sevenDots.setup();

  //MagnetPanel
  magnetPanel.setup();

  //MetalBar
  //metalBar.setup();
    
  stage = 1;
  sevenDots.success();
  
  if(debug){Serial.println("[Setup]: Initialized.");}
  
}


void loop() {

  switch(stage){

    case 1: //MagnetPanel
      if(magnetPanel.spinOnce()){
        if(debug){Serial.println("[Switch]: Stage 1 complete. Proceed with stage 2.");}
        stage++;
        sevenDots.success(); //visual success confirmation
      }
      break;
      
    case 2: //SevenDots
    if(sevenDots.spinOnce()){
      if(debug){Serial.println("[Switch]: Stage 2 complete. Repeat stage 2.");}
      //stage++;
      }
      break;

    /*case 3: //MetalBar
      if(metalBar.spinOnce()){
        if(debug){Serial.println("[Switch]: Stage 3 complete. Repeat stage 3.");}
        //stage++;
      }
      break;*/

    default:
      if(debug){
        Serial.print("[Switch]: Error, stage number invalid! Stage: ");
        Serial.println(stage);
      }
      delay(2000);
      break;
      
  } //end switch
  
  if(debug){
    static unsigned long int lastTimestamp = millis();
    static int throttle = 2000;
    if((millis()-lastTimestamp) > throttle){
      Serial.print("[Main Loop]: Stage is ");
      Serial.println(stage);
      lastTimestamp = millis();
    }
  }
  
}
