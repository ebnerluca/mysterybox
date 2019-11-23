#ifndef sevendots_defined
#define sevendots_defined

class SevenDots{

	public:

		//constructor
    	SevenDots(int ledPins[7], int buttonPins[7]);

    	bool setup();
    	bool spinOnce(); 	//returns true if all 7 leds are on
    	bool spin(); 		//calls spinOnce repeatly until true
    	bool reset();


    private:

    	int ledPins_[7];
    	int buttonPins_[7];
    	bool buttonstate_[7] = {0,0,0,0,0,0,0};
		bool ledstate_[7] = {0,0,0,0,0,0,0};
		const bool defaultLedstate_[7] = {0,0,0,0,0,0,0};
        int buttonCounter_ = 0;

        bool updateReadings();
        bool updateStates();
        bool success();
};

#endif