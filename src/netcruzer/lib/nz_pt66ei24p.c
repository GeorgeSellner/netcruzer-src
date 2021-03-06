/**
 * @brief           PT66EI-24P Driver Functions
 * @file            nz_pt66ei24p.c
 * @author          <a href="www.modtronix.com">Modtronix Engineering</a>
 * @compiler        MPLAB XC16 compiler
 *
 **********************************************************************
 * Software License Agreement
 *
 * The software supplied herewith is owned by Modtronix Engineering, and is
 * protected under applicable copyright laws. The software supplied herewith is
 * intended and supplied to you, the Company customer, for use solely and
 * exclusively on products manufactured by Modtronix Engineering. The code may
 * be modified and can be used free of charge for commercial and non commercial
 * applications. All rights are reserved. Any use in violation of the foregoing
 * restrictions may subject the user to criminal sanctions under applicable laws,
 * as well as to civil liability for the breach of the terms and conditions of this license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN 'AS IS' CONDITION. NO WARRANTIES, WHETHER EXPRESS,
 * IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE
 * COMPANY SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 **********************************************************************
 * File History
 *
 * 2012-02-22, David Hosken (DH):
 *    - Initial version
 *********************************************************************/
#define THIS_IS_NZ_PT66EI_24P_C

#include "HardwareProfile.h"

#if defined(XBRD_PT66EI24P)

#include "nz_pt66ei24p.h"

/////////////////////////////////////////////////
// Defines
#define LATCH_SER       LAT_34
#define LATCH_SCLK      LAT_33
#define LATCH_RCLK      LAT_35

#define TRIS_LATCH_SER  DIR_34
#define TRIS_LATCH_SCLK DIR_33
#define TRIS_LATCH_RCLK DIR_35

//LED Brightness, a value from 0 to 3
#ifndef PT66EI_24P_LED_BRIGHTNESS
#define PT66EI_24P_LED_BRIGHTNESS 1
#endif


/////////////////////////////////////////////////
// Global variables.
BYTE pt66ei24pLeds0to7;

/**
 * Initializes the PT66EI-24P board
 */
void pt66ei24p_Init() {
    //Reset all outputs to 0
    TRIS_LATCH_SER  = 0;
    TRIS_LATCH_SCLK = 0;
    TRIS_LATCH_RCLK = 0;

    //Clear all LEDs
    pt66ei24p_WriteLeds(0);

    //Clock 595's internal register
    LATCH_RCLK = 1;
    LATCH_RCLK = 0;
}

/**
 * Sets all 8 LEDs to the given value. Each bit represents a LED.<br>
 * For example:
 * - To clear all LEDs, call pt66ei24p_WriteLeds(0);
 * - To set first LED (binary format), call  pt66ei24p_WriteLeds(0b00000001);
 * - To set first LED (hex format), call  pt66ei24p_WriteLeds(0x01);
 * - To set first, second and fifth LED (binary format), call  pt66ei24p_WriteLeds(0b00010011);
 * - To set first, second and fifth LED (hex format), call  pt66ei24p_WriteLeds(0x13);
 *
 * @param value The value to set all 8 LEDs to. Each bit represents a LED, 0 if off, 1 is on
 */
void pt66ei24p_WriteLeds(BYTE value) {
    BYTE i;
    BYTE mask = 0x01;

    pt66ei24pLeds0to7 = value;

    //Shift all 8 bits into latch
    for (i=8; i!=0; i--) {
        //Shift out next bit
        LATCH_SCLK = 0;
        if (value & mask)
            LATCH_SER = 1;
        else
            LATCH_SER = 0;
        LATCH_SCLK = 1;
        mask = mask << 1;
    }

    //Clock 595's internal register
    LATCH_RCLK = 1;
    LATCH_RCLK = 0;
}

#endif //#if defined(XBRD_PT66EI24P)
