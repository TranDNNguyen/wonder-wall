/* ========================================
 *
 * EX2_String
 *
 * A simple function to cycle the color table
 * through the string.
 *
 * ========================================
*/
#include "project.h"

void SlowColorBlend(uint32 delay, uint32 time);

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    StripLights_Start();
    
    

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        SlowColorBlend(0, 10000);
       
    }
}

/************************************************
 *                    SlowColorBlend()
 *
 *  Slowly migate all the LEDs through the color
 *  table.
 *
 ************************************************/
void SlowColorBlend(uint32 delay, uint32 time)
{
    uint32 timeCnt = 0; 
    uint32 led = 0;
    uint32 x = 0;
    uint32 pct = 0;
    uint32 fromColor, toColor, color;
    extern const uint32 StripLights_CLUT[ ];

    StripLights_Dim(0); 

    for(;;)
    {   
        while(1)
        {
           
            for(pct = 0; pct < 100; pct += 4)
            {
                for(led = 0; led <= StripLights_MAX_X; led++)
                {
 
                    fromColor =  StripLights_CLUT[(x + 0 + ((led * StripLights_COLOR_WHEEL_SIZE)/StripLights_TOTAL_LEDS)) % StripLights_COLOR_WHEEL_SIZE];
                    toColor =  StripLights_CLUT[(x + 1 + ((led * StripLights_COLOR_WHEEL_SIZE)/StripLights_TOTAL_LEDS)) % StripLights_COLOR_WHEEL_SIZE];
                    
                    color = StripLights_RgbBlend(fromColor, toColor, pct);                  
                    StripLights_Pixel(led, 0, color );
                }
                
                 while( StripLights_Ready() == 0);
	
	            StripLights_Dim(2);
                StripLights_Trigger(1);
                
                CyDelay(delay);

            }
            x++;  // Advance through color wheel
        }
        timeCnt += delay;
 
     
     if(SW1_Read() == 0) break;  // If SW1 pressed leave
         if(timeCnt > time) break;
    }	
	// Wait for SW1 to be released then delay a bit for debouncing
	while(SW1_Read() == 0);         
	CyDelay(50);  
}

/* [] END OF FILE */
