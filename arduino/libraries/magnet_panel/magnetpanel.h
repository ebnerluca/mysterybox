#ifndef magnetpanel_defined
#define magnetpanel_defined

class MagnetPanel{

	public:

		//constructor
    	MagnetPanel(int magnetPanelPin);

    	bool setup();
    	bool spinOnce(); 	//returns true if all 7 leds are on
    	bool spin(); 		//calls spinOnce repeatly until true
    	bool reset();


    private:

    	int magnetPanelPin_;
};

#endif