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
    uint32 cmd = 33;
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
        if(cmd > 56u) {
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
        case 21u:
            setLED (520, 547, color);
            break; //1x6
        
        case 20u:
            setLED (437, 464, color);
            break; //0x6
            
        case 19u:
            setLED (408, 436, color);
            break; //0x5
            
        case 18u:
            setLED (324, 352, color);
            break; //1x5
            
        case 17u:
            setLED (294, 323, color);
            break; // 1x4
            
        case 16u:
            setLED (206, 235, color);
            break; // 0x4
            

        case 13u:
            setLED (492, 519, color);
            break; // 1x3
            
        case 12u:
            setLED (465, 491, color);
            break; // 1x2
            
        case 11u:
            setLED (380, 407, color);
            break; // 0x2
            
        case 10u:
            setLED (353, 379, color);
            break; //0x1
        
        case 9u:
            setLED (265, 293, color);
            break; // 1x1
            
        case 8u:
            setLED (236, 264, color);
            break; // 1x0
            
        case 7u:
            setLED (0, 24, color);
            break; // 0x0
            
        case 6u:
            setLED (25, 50, color);
            break; //1x7
            
        case 5u:
            setLED (51, 75, color);
            break;
        
        case 4u:
            setLED (76, 100, color);
            break; // 0x3
            
        case 3u:
            setLED (101, 125, color);
            break; // 0x3
            
        case 2u:
            setLED (126, 151, color);
            break; // 0x3

        case 1u:
            setLED (152, 178, color);
            break; // 0x3
            
        case 0u:
            setLED (179, 205, color);
            break; // 0x3
            
        default:
            //setBG (0, 550);
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
