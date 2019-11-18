#ifndef metalbar_defined
#define metalbar_defined

class MetalBar{

	public:

		//constructor
    	MetalBar(int magnetPanelPin);

    	bool setup();
    	bool spinOnce(); 	//returns true if all 7 leds are on
    	bool spin(); 		//calls spinOnce repeatly until true
    	bool reset();


    private:

    	int metalBarPin_;
};

#endif