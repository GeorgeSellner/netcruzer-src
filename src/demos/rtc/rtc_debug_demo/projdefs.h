/**
 * Project Specific Defines. Are defines in projdefs.h. These are defines that
 * is the same for all target hardware. Place hardware specific defines in
 * "Configs/HWP_BOARDNAME.h" file for target board
 */

#ifndef _PROJDEFS_H_
#define _PROJDEFS_H_


//Ensure this define is uncommented for release build
//#define RELEASE_BUILD


// *********************************************************************
// ---------- Netcruzer System Configuration (nz_netcruzer.h) ----------
// *********************************************************************


// *********************************************************************
// ------- Circular Buffer Configuration (nz_circularBuffer.h) ---------
// *********************************************************************
//Specifies what circular buffer is used. Ensure only one of the following is uncommented. If none selected, nz_circularBufferStd is used
//#define    CIRBUF_USE_CIRCULAR_BUFFER_STD      //Use nz_circularBufferStd
#define    CIRBUF_USE_CIRCULAR_BUFFER_PWR2     //Use nz_circularBufferPwrs


// *********************************************************************
// --------------- Debug Configuration (nz_debug.h) --------------------
// *********************************************************************
#define NZ_USBHID_DEBUG_ENABLE
//#define NZ_USBCDC_DEBUG_ENABLE
//#define NZ_UART1_DEBUG_ENABLE

//Size of Debug TX buffer, MUST BE power of 2 value! Increase size of this buffer if debug information
//is getting lost. This can be the case if the application writes debug information to the debug buffer
//faster than it can be outputted.
#define DEBUG_TXBUF_SIZE 1024

//Size of Debug RX buffer, MUST BE power of 2 value! Ensure it is large enought to hold largest string
//written to debug port. For example, when using the USB port for debugging, text message are sent to
//the debug port from the @ref devtools_nzUsbTerminal.
#define DEBUG_RXBUF_SIZE 64

//Uncomment this line to disable all debugging!
//#define DEBUG_LEVEL_ALLOFF

//To enable debug configuration for additional modules, add line to each of the 3 sections below with name of new module. For example in first section, add "#define DEBUG_CONF_NEWMOD 0"
#if defined (DEBUG_LEVEL_ALLOFF)
    #define DEBUG_CONF_MAIN                     0
    #define DEBUG_CONF_CIRCULAR_BUFFER          0
    #define DEBUG_CONF_RTC                      0
    #define DEBUG_CONF_USB_BUFFERED             0
#else
    #if defined (RELEASE_BUILD)
        #define DEBUG_CONF_MAIN                     DEBUG_LEVEL_WARNING
        #define DEBUG_CONF_CIRCULAR_BUFFER          DEBUG_LEVEL_WARNING
        #define DEBUG_CONF_USB_BUFFERED             DEBUG_LEVEL_WARNING
        #define DEBUG_CONF_RTC                      DEBUG_LEVEL_WARNING
    #else
        #define DEBUG_CONF_MAIN                     DEBUG_LEVEL_INFO
        #define DEBUG_CONF_CIRCULAR_BUFFER          DEBUG_LEVEL_INFO
        #define DEBUG_CONF_USB_BUFFERED             DEBUG_LEVEL_INFO
        #define DEBUG_CONF_RTC                      DEBUG_LEVEL_INFO
    #endif
#endif



 // *********************************************************************
 // ------------ I2C 1 Configuration (from nz_serI2C.h) -------------
 // *********************************************************************
//---- Enable I2C1 Serial Port ----
#define NZ_I2C1_ENABLE

//Transmit and Receive buffer sizes, for compatibility, ensure it is a power of 2 value! This can be bypassed
//by using a "non power of 2" CircularBuffer implementation for this project. See nz_CircularBuffer.h for details.
#define    I2C1_RXBUF_SIZE  64
#define    I2C1_TXBUF_SIZE  256

//I2C1 speed, can be 62K, 100K, 200K, 300K, 400K, 506K, 600K, 708K, 909K, 970K or 1M. Can also
//use value, for example 78 will give 200kHz. IMPORTANT to limit it to speed of lowest device
//on bus! For example, is 400kHz for RTC on SBC66EC (in I2C 1)!
#define    I2C1_BAUD I2C_BAUD_400K  //[-DEFAULT-]



// *********************************************************************
// ------------ RTC Configuration (from nz_rtc.h) -------------
// *********************************************************************
#define NZ_RTC_ENABLE                               //Enable the RTC
#define NZ_RTC_UNLOCK                           (1) //Unlock RTC during initialization


// *********************************************************************
// -------------- USB Configuration (nz_serUSB.h) -----------------
// *********************************************************************
#define NZ_USBHID_ENABLE

//If set to 1, the system LED is controlled by the nz_serUSB module
#define USB_CONTROLS_SYSLED						( 1 )

//Indicates if this application handles commands via USB. When defined, the application must implement the "nz_cmdXxx" callback functions!
//#define APP_HANDLES_USB_COMMANDS


#endif  //_PROJDEFS_H_
