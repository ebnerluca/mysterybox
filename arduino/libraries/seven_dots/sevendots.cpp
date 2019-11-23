#include "sevendots.h"
#include "Arduino.h"


SevenDots::SevenDots(int ledPins[7], int buttonPins[7]){

	for(int i=0; i<7; i++){

		ledPins_[i] = ledPins[i];
		buttonPins_[i] = buttonPins[i];
	}

}


bool SevenDots::setup(){

	for(int i=0; i<7; i++){

		pinMode(ledPins_[i], OUTPUT);
		pinMode(buttonPins_[i], INPUT);

	}

	return true;

}


bool SevenDots::spinOnce(){

	// check if complete
  if((ledstate_[0]==true) && (ledstate_[1]==true) && (ledstate_[2]==true) && (ledstate_[3]==true) && (ledstate_[4]==true) && (ledstate_[5]==true) && (ledstate_[6]==true)){

    success(); //visual confirmation
    return true;
  }

    // Check if buttons were already pressed 7 times. (Code doesn't reach here if all 7 LEDs were turned on)
  if(buttonCounter_ >= 7){
    reset();
  }

  // update button readings
  for(int i = 0; i<7; i++){
  	buttonstate_[i] = digitalRead(buttonPins_[i]);
  }

  // update led states
  for(int i = 0; i<7; i++){
    if (buttonstate_[i] == HIGH){

    	//Serial.println(button[i]);
      
    	digitalWrite(ledPins_[i], !ledstate_[i]);
    	ledstate_[i] = !ledstate_[i];

    	if(i==0){
     		digitalWrite(ledPins_[6], !ledstate_[6]);
     		digitalWrite(ledPins_[1], !ledstate_[1]);
     		ledstate_[6] = !ledstate_[6];
     		ledstate_[1] = !ledstate_[1];
    	} else if(i==6){
     		digitalWrite(ledPins_[5], !ledstate_[5]);
     		digitalWrite(ledPins_[0], !ledstate_[0]);
     		ledstate_[5] = !ledstate_[5];
     		ledstate_[0] = !ledstate_[0];
    	} else{ //usual case, neighbor leds should switch as well
     		digitalWrite(ledPins_[i-1], !ledstate_[i-1]);
    		digitalWrite(ledPins_[i+1], !ledstate_[i+1]);
     		ledstate_[i-1] = !ledstate_[i-1];
     		ledstate_[i+1] = !ledstate_[i+1];
    	}
      
      delay(500); //avoid button being pressed multiple times in a row
      buttonCounter_++;
    }
      
  }


	return false;

}


bool SevenDots::spin(){

	while(!spinOnce()){}

	return true;
}


bool SevenDots::reset(){

	for(int i = 0; i<7; i++){
        ledstate_[i] = defaultLedstate_[i];
        digitalWrite(ledPins_[i], LOW);
    }

  buttonCounter_ = 0;

  Serial.println("[SevenDots]: Reset.");

}


bool SevenDots::success(){

  Serial.println("[SevenDots]: All LEDs turned on!");
  
  //visual confirmation
  for(int j=0; j<3; j++){
    for(int i=0; i<7; i++){
      digitalWrite(ledPins_[i], LOW);
      delay(100);
    }
    //delay(500);
    for(int i=0; i<7; i++){
      digitalWrite(ledPins_[i], HIGH);
      delay(100);
    }
    //delay(500);
  }

  delay(500);

  for(int i=0; i<7; i++){
    digitalWrite(ledPins_[i], LOW);
  }

  return true;
}
