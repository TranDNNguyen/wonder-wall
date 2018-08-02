/* ========================================
 *
 * EX_TextScroll
 *
 * This example uses a strip of 300 LEDs wrapped
 * around a tube.  It scrolls the string "Hello"
 * around the tube.
 *
 * ========================================
*/
#include "project.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    StripLights_Start();
    StripLights_DisplayClear(StripLights_BLACK);

    for(;;)
    {
        // Schroll 
        for(int32 x = 17; x > -30; x--)
        {
            StripLights_MemClear(StripLights_BLACK);
            StripLights_PrintString(x, 2, "Hello  ", StripLights_RED, StripLights_BLACK);
            StripLights_Trigger(1);
            CyDelay(100); 
        }
    }
}

/* [] END OF FILE */
