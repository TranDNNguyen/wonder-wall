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
//#include <main.h>

static uint32 SPIS_WaitForCommand(void);
static void SPIS_CleanupAfterRead(void);
static uint8 ExecuteCommand(uint32 cmd, uint32 color);
void setLED(uint32 firstLED, uint32 onLED, uint32 color);
void determineColor(uint32 red, uint32 green, uint32 blue);
const uint8 dummyBuffer[3u] = {0xFFu, 0xFFu, 0xFFu};
void setBG(uint32 firstLED, uint32 lastLED);
void rainbowFade2White();

int main(void)
{
    uint32 cmd = 0;
    uint32 status;
    CyGlobalIntEnable; /* Enable global interrupts. */
    StripLights_Start();
    SPIS_Start();

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    //
    setBG (0, 550);
    
    int i = 51;
    
    for(;;){
        
        
        //cmd = SPIS_WaitForCommand();
        
        ExecuteCommand(cmd, StripLights_getColor((i + StripLights_CWHEEL_SIZE)));
        
        
        cmd = cmd + 1u;
        if(cmd > 15u) {
            cmd = 0u;
        }
        
        i = i + 10;
        if(i >= 100) {
            i = 10;
        }
        

        
        //SPIS_CleanupAfterRead();
    }
    CyDelay(100);
}


static uint32 SPIS_WaitForCommand(void)
{
    uint8 tmpBuffer[3u];
    uint32 cmd;
    uint32 i;

    /* Wait for the end of the transfer */
    while (3u != SPIS_SpiUartGetRxBufferSize())
    {
    }

    /* Read packet from the buffer */
    i = 0u;
    while (0u != SPIS_SpiUartGetRxBufferSize())
    {
        tmpBuffer[i] = SPIS_SpiUartReadRxData();
        i = i + 1u;
    }

    cmd = tmpBuffer[1u];

    return (cmd);
}

static void SPIS_CleanupAfterRead(void)
{
    /* Wait for the end of the transfer */

    SPIS_SpiUartClearRxBuffer();

}

static uint8 ExecuteCommand(uint32 cmd, uint32 color)
{
    uint8 status;

    //status = STS_CMD_DONE;

    /* Execute received command */
    switch (cmd)
    {
       
        case 40u:
            setLED (29, 54, color);
            break; //1x7
            
        case 48u:
            setLED (0, 28, color);
            break;

        case 41u:
            setLED (55, 82, color);
            break; //1x6
        
        case 49u:
            setLED (83, 112, color);
            break; //0x6
            
        case 50u:
            setLED (113, 140, color);
            break; //0x5
            
        case 42u:
            setLED (141, 167, color);
            break; //1x5
            
        case 43u:
            setLED (168, 194, color);
            break; // 1x4
            
        case 51u:
            setLED (195, 221, color);
            break; // 0x4
            
        case 52u:
            setLED (222, 248, color);
            break; // 0x3

        case 44u:
            setLED (249, 275, color);
            break; // 1x3
            
        case 45u:
            setLED (277, 304, color);
            break; // 1x2
            
        case 53u:
            setLED (305, 331, color);
            break; // 0x2
            
        case 54u:
            setLED (332, 358, color);
            break; //0x1
        
        case 46u:
            setLED (359, 385, color);
            break; // 1x1
            
        case 47u:
            setLED (386, 412, color);
            break; // 1x0
            
        case 55u:
            setLED (413, 438, color);
            break; // 0x0

        default:
            setBG (0, 550);
            break;
    }

    return (status);
}

void setLED (uint32 firstLED, uint32 lastLED, uint32 color) {
    uint32 led;
    
    StripLights_Dim(2);
    
    for(led = firstLED; led <= lastLED; led++) {
        StripLights_Pixel(led, 0, color);
        while(StripLights_Ready() == 0);
        CyDelay(10);
        
    }
    StripLights_Trigger(1);
    CyDelay(100);
}

void setBG(uint32 firstLED, uint32 lastLED) {
uint32 led;
    
    StripLights_Dim(4);
    
    for(led = firstLED; led <= lastLED; led++) {
        StripLights_Pixel(led, 0, StripLights_OFF);
        while(StripLights_Ready() == 0);
        CyDelay(10);
        
    }
    StripLights_Trigger(1);
    CyDelay(100);
}


void rainbow(uint32 startingColor, uint32 firstLED, uint32 lastLED) {
    
    for(int i = startingColor; i < 256; i++){
        for(int j = firstLED; j <= lastLED; j++) {
            StripLights_Pixel(j, 0, StripLights_getColor(i + StripLights_CWHEEL_SIZE));
            while(StripLights_Ready() == 0);
            StripLights_Trigger(1);
            
        }
        if (i == 256) {
            i=0;
        }
    }
}

void rainbowCrawl(uint32 firstLED, uint32 lastLED) {
    for(uint32 i = 0, j = firstLED; i < 27 && j < lastLED; i++, j++){
            StripLights_Dim(2);
            StripLights_Pixel(j, 0, StripLights_getColor(i));
            while(StripLights_Ready() == 0);
            CyDelay(20);
            if(i >= 26) {
                i = 0;
            }
        StripLights_Trigger(1);
        CyDelay(20);    
    }
    //CyDelay(100);

}
