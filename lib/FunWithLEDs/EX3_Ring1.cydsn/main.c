/* ========================================
 *
 * EX3_Ring1
 *
 * This example contains several functions
 * to generate patterns with the common
 * LED rings.  It will work with any size
 * ring as long as you put the proper 
 * LED count in the customizer.
 *
 * You can advance from one function to the
 * next by pressing the button on port P07.
 *
 * ========================================
*/
#include "project.h"

void Rainbow(uint32 delay);
void SingleLED(uint32 delay);
void OppositeRings(uint32 delay);
void RgbChase(uint32 delay);
void OneColor(uint32 delay);

extern const uint32 StripLights_CLUT[ ];

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    StripLights_Start();

    for(;;)
    {
		OneColor(20);
		SingleLED(50);
		OppositeRings(130);
		RgbChase(100);
		Rainbow(30);
    }
}

/************************************************
 *                    SingleLED()
 *
 *  Rotate a single LED around the ring.
 *
 ************************************************/
void SingleLED(uint32 delay)
{
    uint32 ledPosition = 0;  // On LED position

	// Loop until SW1 pressed
    for(;;)  
    {
		// Wait for last update to finish
	    while( StripLights_Ready() == 0);                 
		
		// Clear all LEDs to background color
		StripLights_MemClear(StripLights_BLACK);   
		
		// Set the color of a single LED
	    StripLights_Pixel(ledPosition, 0, StripLights_RED ); 

		// Trigger update of all LEDs at once
        StripLights_Trigger(1);    
		
		// Loop delay
        CyDelay(delay);    

		// Advance to next position.  If too far, start back at 0
		ledPosition++;  
		if(ledPosition >= StripLights_TOTAL_LEDS) ledPosition = 0;

		// If SW1 is pressed, leave loop
		if(SW1_Read() == 0) break; 
    }	
	
	// Wait for button release and delay to debounce switch
	while(SW1_Read() == 0);   
	CyDelay(50);
}

/************************************************
 *                   OppositeRings()
 *
 *  A green and red LEDs go around the ring in 
 *  opposite directions, with tails.
 *
 ************************************************/
void OppositeRings(uint32 delay)
{
    uint32 fwdLED = 0;  // Forward LED Position
	uint32 bwdLED = 0;  // Backward LED Postion

	uint32 oldColor;    // Temp Color
	uint32 loop;        // Loop counter
	
	// Loop until button pressed
	for(;;)
	{
		// Loop through one revolution
        for(fwdLED = 0; fwdLED < StripLights_TOTAL_LEDS; fwdLED++)
	    {
			// Calculate backward LED position
			bwdLED = StripLights_TOTAL_LEDS - fwdLED;
			
			// Wait for last update to complete
			while( StripLights_Ready() == 0);
			
			// Loop around and dim all the LEDs to create tails
			for(loop = 0; loop < StripLights_TOTAL_LEDS; loop++)
			{
				oldColor = StripLights_GetPixel(loop, 0);
				oldColor = (oldColor >> 1) & 0x007F7F7F;
				StripLights_Pixel(loop, 0, oldColor );	
			}

			// Blend the forward LED with existing colors
			oldColor = StripLights_GetPixel(fwdLED, 0) | StripLights_GREEN;
		    StripLights_Pixel(fwdLED, 0, oldColor );
			
			// Blend the backward LED with existing colors
			oldColor = StripLights_GetPixel(bwdLED, 0) | StripLights_RED;
		    StripLights_Pixel(bwdLED, 0,  oldColor );
			
			// Udate all the LEDs at once
	        StripLights_Trigger(1);
			
			// Loop delay
			CyDelay(delay);
		
			// Leave loop is SW1 pressed
		    if(SW1_Read() == 0) break;
	    }

		// Leave if SW1 pressed
	    if(SW1_Read() == 0) break;
    }
	
	// Wait for SW1 to be released then delay a bit for debouncing
	while(SW1_Read() == 0);
	CyDelay(50);
}

/************************************************
 *                    RgbChase()
 *
 *  Rotate three LED colors around the ring.
 *  Make tails by dimming the LEDs each time.
 *
 ************************************************/
void RgbChase(uint32 delay)
{
    uint32 redPosition   = 0; // Initial color LED positions
	uint32 greenPosition = StripLights_TOTAL_LEDS/3;
	uint32 bluePosition  = (StripLights_TOTAL_LEDS * 2)/3;
	
	uint32 oldColor;   // Temp color value
	uint32 loop;       // Loop counter
	
	// Loop until SW1 pressed
    for(;;)
    {
		// Wait for last update to complete
		while( StripLights_Ready() == 0);
		
		// Loop through and dim all LEDs by half
		for(loop = 0; loop < StripLights_TOTAL_LEDS; loop++)
		{
			oldColor = StripLights_GetPixel(loop, 0);
			oldColor = (oldColor >> 1) & 0x007F7F7F;
			StripLights_Pixel(loop, 0, oldColor );	
		}
		
		// Set the three LEDs at their new position
	    StripLights_Pixel(redPosition,   0,  StripLights_RED );
	    StripLights_Pixel(greenPosition, 0,  StripLights_GREEN );
		StripLights_Pixel(bluePosition,  0,  StripLights_BLUE );
		
		// Trigger to update all the LEDs at once
        StripLights_Trigger(1);
		
		// Loop delay in mSeconds
        CyDelay(delay);
		
		// Calculate new LED positions around the ring
	    redPosition   = (redPosition + 1)   % StripLights_TOTAL_LEDS;
	    greenPosition = (greenPosition + 1) % StripLights_TOTAL_LEDS;
	    bluePosition  = (bluePosition + 1)  % StripLights_TOTAL_LEDS;
	
        // If SW1 pressed, leave loop
	    if(SW1_Read() == 0) break;
    }	
	// Wait for SW1 to be released then delay a bit for debouncing
	while(SW1_Read() == 0);
	CyDelay(50);
}

/************************************************
 *                    Rainbow()
 *
 *  Use the colorwheel section of the color lookup
 *  table to create a rotating rainbow.
 *
 ************************************************/
void Rainbow(uint32 delay)
{
    uint32 startColor = 0;  // Index color in colorwheel
	uint32 ledPosition = 0; // LED position when setting color         
    uint32 color = 0;       // Temp color to set LED
	
    for(;;)
    {   
		// Wait for last update to complete
        while( StripLights_Ready() == 0);  
		
		// Set new start color
        color = startColor;    
		
		// Loop through all LEDs giving each one a different color from the color wheel
        for(ledPosition = 0; ledPosition <= StripLights_TOTAL_LEDS; ledPosition++)
        {
            StripLights_Pixel(ledPosition, 0, StripLights_getColor( color ));
            color++;
            if(color >= StripLights_COLOR_WHEEL_SIZE) color = 0;
        }
		
		// Update the LEDs all at once
		StripLights_Trigger(1); 
		
        // Each time through the main loop start with different color
		// Wrap around at end of color wheel
		startColor++;  
        if(startColor >= StripLights_COLOR_WHEEL_SIZE) startColor = 0;
    
        CyDelay(delay);   // Loop delay

	    if(SW1_Read() == 0) break;  // If SW1 pressed leave
    }	
	// Wait for SW1 to be released then delay a bit for debouncing
	while(SW1_Read() == 0);         
	CyDelay(50);
}

/************************************************
 *                    OneColor()
 *
 *  Use the colorwheel section of the color lookup
 *  table to write all LEDs the same color.
 *
 ************************************************/
void OneColor(uint32 delay)
{
    uint32 color = 0;  // Index color in colorwheel
	uint32 nextColor = 0;
	uint32 pct = 0;
	uint32 toColor, fromColor, newColor;        
	
    for(;;)
    {   
		nextColor = color + 1;
		if(nextColor >= StripLights_COLOR_WHEEL_SIZE) nextColor = 0;
		
		fromColor = StripLights_CLUT[color];
		toColor   = StripLights_CLUT[nextColor];  

		for(pct = 0; pct <= 100; pct += 10)
		{
            newColor = StripLights_RgbBlend(fromColor, toColor, pct); 

            StripLights_DrawLine(0,0, StripLights_TOTAL_LEDS-1,0,newColor);
 		
		    // Update the LEDs all at once
            StripLights_TriggerWait(1);
			
			CyDelay(delay);   // Loop delay
	    } 
        // Each time through the main loop start with different color
		// Wrap around at end of color wheel
		color++;  
        if(color >= StripLights_COLOR_WHEEL_SIZE) color = 0;

	    if(SW1_Read() == 0) break;  // If SW1 pressed leave
    }	
	// Wait for SW1 to be released then delay a bit for debouncing
	while(SW1_Read() == 0);         
	CyDelay(50);
}

/* [] END OF FILE */
