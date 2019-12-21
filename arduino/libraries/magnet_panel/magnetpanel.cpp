#include "magnetpanel.h"
#include "Arduino.h"


MagnetPanel::MagnetPanel(int magnetPanelPin){

  magnetPanelPin_ = magnetPanelPin;

}


bool MagnetPanel::setup(){

	pinMode(magnetPanelPin_, INPUT_PULLUP);

	return true;

}


bool MagnetPanel::spinOnce(){

	if(digitalRead(magnetPanelPin_)==LOW){
    Serial.println("[MagnetPanel]: Magnet Panel combination correct!");
    return true;
  }

  return false;

}


bool MagnetPanel::spin(){

	while(!spinOnce()){}

	return true;
}


bool MagnetPanel::reset(){

  //empty

 return true;

}

