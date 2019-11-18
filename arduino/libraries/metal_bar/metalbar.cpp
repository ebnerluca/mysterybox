#include "metalbar.h"
#include "Arduino.h"


MetalBar::MetalBar(int metalBarPin){

  metalBarPin_ = metalBarPin;

}


bool MetalBar::setup(){

	pinMode(metalBarPin_, INPUT);

	return true;

}


bool MetalBar::spinOnce(){

	if(digitalRead(metalBarPin_)==HIGH){
    Serial.println("[MetalBar]: Metal Bar connection bridged!");
    return true;
  }

  return false;

}


bool MetalBar::spin(){

	while(!spinOnce()){}

	return true;
}


bool MetalBar::reset(){

  //empty

 return true;

}

