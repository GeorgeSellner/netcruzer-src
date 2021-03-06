 /**
 * @brief           Variable size Circular Buffer.
 * @file            nz_circularBufferStd.h
 * @author          <a href="www.modtronix.com">Modtronix Engineering</a>
 * @compiler        MPLAB XC16 compiler
 *
 * @section nz_circularBufferStd_desc Description
 *****************************************
 * This module contains the implementation for a Circular Buffer, as defined in the
 * nz_circularBuffer.h interface. This implementation is for a variable size circular buffers.
 * The size can be configured at run time, and is not limited to a power of 2 value.
 *
 *********************************************************************/

 /*********************************************************************
 * @section nz_circularBufferStd_lic Software License Agreement
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
 * 2010-11-10, David H. (DH):
 *    - Initial version
 *********************************************************************/
#ifndef NZ_CIRCULAR_BUFFER_STD_H
#define NZ_CIRCULAR_BUFFER_STD_H

#if defined(CIRBUF_USE_CIRCULAR_BUFFER_STD)

#if defined(NZ_CIRCULAR_BUFFER_PWR2_H)
#error "Can not include both nz_circularBufferPwr2.h AND nz_circularBufferStd.h! Only included the one corresponding to the *.c file used in project!"
#endif

#if defined(THIS_IS_NZ_CIRCULAR_BUFFER_PWR2_C)
#error "Can not include nz_circularBufferStd.h in nz_circularBufferPwr2.c! For some reason MPLAB X keeps adding it! Remove nz_circularBufferStd.h from nz_circularBufferPwr2.c!"
#endif

#define BUF_SYNC_CHAR 0xC5

#include "nz_circularBuffer.h"


/**
 * Empty the given buffer. Any data contained in the buffer is lost.
 *
 * @param pBuf Pointer to CIRBUF structure
 */
#if !defined(CIRBUF_OPTIMIZE_SIZE)
#define cbufEmpty(pBuf)  {(pBuf)->get = (pBuf)->put; /*Don't update put, only GET*/}
//#define cbufEmpty(pBuf)  {(pBuf)->get = (pBuf)->put = 0;}
#endif

#if !defined(CIRBUF_DISABLE_ALL_MACRO_FUNCTIONS)
/** Macro version of cbufEmpty() that is always available */
#define cbufEmpty_MACRO(pBuf) {(pBuf)->get = (pBuf)->put; /*Don't update put, only GET*/}
#else
#define cbufEmpty_MACRO cbufEmpty
#endif


/**
 * Checks if the given buffer is empty.
 *
 * @param pBuf Pointer to CIRBUF structure
 *
 * @return Returns true if the given buffer is empty. Else, returns false.
 */
#if !defined(CIRBUF_OPTIMIZE_SIZE)
#define cbufIsEmpty(pBuf) ((pBuf)->get == (pBuf)->put)
#endif

#if !defined(CIRBUF_DISABLE_ALL_MACRO_FUNCTIONS)
/** Macro version of cbufIsEmpty() that is always available */
#define cbufIsEmpty_MACRO(pBuf) ((pBuf)->get == (pBuf)->put)
#else
#define cbufIsEmpty_MACRO cbufIsEmpty
#endif


#if !defined(CIRBUF_DISABLE_ALL_MACRO_FUNCTIONS)
/** Macro version of function that is always available */
#define cbufIsFull_MACRO(pBuf) ( ((pBuf)->put==(pBuf)->maxOffset) ? ((pBuf)->get==0) : (((pBuf)->put+1)==(pBuf)->get) )
#else
#define cbufIsFull_MACRO cbufIsFull
#endif

/**
 * Checks if the given buffer contains data.
 *
 * @param pBuf Pointer to CIRBUF structure
 *
 * @return Returns true if the given buffer has data.
 */
#define cbufHasData(pBuf) (cbufIsEmpty(pBuf)==0)
#define cbufHasData_MACRO(pBuf)  ((pBuf)->get != (pBuf)->put)


#if !defined(CIRBUF_DISABLE_ALL_MACRO_FUNCTIONS)
/** Macro version of function that is always available */
#define cbufHasSpace_MACRO(pBuf)  ( ((pBuf)->put==(pBuf)->maxOffset) ? ((pBuf)->get!=0) : (((pBuf)->put+1)!=(pBuf)->get) )
#else
#define cbufHasSpace_MACRO(pBuf) (cbufIsFull(pBuf)==0)
#endif


#if !defined(CIRBUF_DISABLE_ALL_MACRO_FUNCTIONS)
/** Macro version of function that is always available */
#define cbufGetCount_MACRO(pBuf) ( ((pBuf)->put>=(pBuf)->get) ? ((pBuf)->put-(pBuf)->get) : (((pBuf)->put+(pBuf)->maxOffset+1)-(pBuf)->get) )
#else
#define cbufGetCount_MACRO cbufGetCount
#endif


#if !defined(CIRBUF_DISABLE_ALL_MACRO_FUNCTIONS)
/** Macro version of function that is always available */
#define cbufGetFree_MACRO(pBuf) ( ((pBuf)->put < (pBuf)->get) ? ((pBuf)->get-(pBuf)->put-1) : (((pBuf)->get + (pBuf)->maxOffset) - (pBuf)->put) )
#else
#define cbufGetFree_MACRO cbufGetFree
#endif

#if !defined(CIRBUF_DISABLE_ALL_MACRO_FUNCTIONS)
/** Macro version of cbufGetFormat() that is always available */
#define cbufGetFormat_MACRO(pBuf) ((pBuf)->flagTF.format)
#else
#define cbufGetFormat_MACRO cbufGetFormat
#endif


#if !defined(CIRBUF_DISABLE_ALL_MACRO_FUNCTIONS)
/** Macro version of cbufGetType() that is always available */
#define cbufGetType_MACRO(pBuf) ((pBuf)->flagTF.type)
#else
#define cbufGetType_MACRO cbufGetType
#endif


/**
 * Gets a byte from the Buffer, without removing it. The byte is NOT removed from the
 * buffer, and the buffer pointers are NOT updated! To remove the byte, and update the
 * pointers, call the cbufRemoveByte() function.
 *
 * @preCondition cbufIsEmpty() must have been called to confirm the Buffer has data!
 *
 * For <b>Multi Threaded Applications</b>, call from "GET context".
 *
 * @param pBuf Pointer to CIRBUF structure
 *
 * @return Returns the next byte in the given buffer.
 */
#if !defined(CIRBUF_OPTIMIZE_SIZE)
#define cbufPeekByte(pBuf) ( (pBuf)->buf[(pBuf)->get] )
#endif

#if !defined(CIRBUF_DISABLE_ALL_MACRO_FUNCTIONS)
/** Macro version of cbufPeekByte() that is always available */
#define cbufPeekByte_MACRO(pBuf) ( (pBuf)->buf[(pBuf)->get] )
#else
#define cbufPeekByte_MACRO cbufPeekByte
#endif


/**
 * Removes a byte from the Buffer.
 *
 * @preCondition Before calling this function, it must be confirmed that the buffer has data.
 * The cbufHasData() is an example function that can be used to do this check.
 *
 * For <b>Multi Threaded Applications</b>, call from "GET context".
 *
 * @param pBuf Pointer to CIRBUF structure
 */
#if !defined(CIRBUF_OPTIMIZE_SIZE)
    #define cbufRemoveByte(pBuf) ( (pBuf)->get = (((pBuf)->get==(pBuf)->maxOffset) ? 0 : ((pBuf)->get+1)) )
#endif


#if !defined(CIRBUF_DISABLE_ALL_MACRO_FUNCTIONS) && !defined(cbufRemoveByte_MACRO)
/** Macro version of function that is always available */
#define cbufRemoveByte_MACRO(pBuf) ( (pBuf)->get = (((pBuf)->get==(pBuf)->maxOffset) ? 0 : ((pBuf)->get+1)) )
#else
#define cbufRemoveByte_MACRO cbufRemoveByte
#endif


#if !defined(CIRBUF_DISABLE_ALL_MACRO_FUNCTIONS)
/**
 * Macro version of cbufGetByte(). Gets a byte from the Buffer, and removes it from buffer.
 * <br>!!!! IMPORTANT !!!!<br>
 * Only use on single line like this:<br>
 * i = cbufGetByte_MACRO(1);
 *
 * NEVER use in statment - DON'T USE LIKE THIS!!<br>
 * if ((i = cbufGetByte_MACRO(1)) > 1)
 *
 * @preCondition cbufIsEmpty() must have been called to confirm the buffer has data!
 *
 * For <b>Multi Threaded Applications</b>, call from "GET context".
 *
 * @param pBuf Pointer to CIRBUF structure
 *
 * @return Returns the next byte in the given buffer.
 */
#define cbufGetByte_MACRO(pBuf) ((pBuf)->buf[ (pBuf)->get ]); ( (pBuf)->get = (((pBuf)->get==(pBuf)->maxOffset) ? 0 : ((pBuf)->get+1)) )
#else
#define cbufGetByte_MACRO cbufGetByte
#endif


#if !defined(CIRBUF_DISABLE_ALL_MACRO_FUNCTIONS)
/** Macro version of function that is always available */
#define cbufGetRdArrSize_MACRO(pBuf) (((pBuf)->put < (pBuf)->get) ? (((pBuf)->maxOffset + 1) - (pBuf)->get) : ((pBuf)->put - (pBuf)->get))
#else
#define cbufGetRdArrSize_MACRO cbufGetRdArrSize
#endif


/**
 * Get byte pointer to current GET location. Use this function with cbufGetRdArrSize() function.
 *
 * For <b>Multi Threaded Applications</b>, call from "GET context".
 *
 * @return BYTE pointer to current GET location
 */
#define cbufGetRdArr(pBuf)  ( (BYTE*) &((pBuf)->buf[(pBuf)->get]) )


/**
 * Adds a BYTE to the buffer, and updates the buffer pointers. No check is done
 * to see if there is space available in the buffer!
 *
 * @preCondition cbufIsFull() must have been called to confirm the buffer is not full!
 *
 * For <b>Multi Threaded Applications</b>, call from "PUT context".
 *
 * @param pBuf Pointer to CIRBUF structure
 * @param b Byte to add to the buffer
 */
#if !defined(CIRBUF_OPTIMIZE_SIZE)
#define cbufPutByteNoCheck(pBuf, b) {(pBuf)->buf[(pBuf)->put] = (b); /* Write byte to buf */ (pBuf)->put = (((pBuf)->put==(pBuf)->maxOffset) ? 0 : ((pBuf)->put+1));}
#endif
#if defined(CIRBUF_USE_PUTBYTE_FOR_PUTBYTENOCHECK)
#define cbufPutByteNoCheck(pBuf, b) cbufPutByte(pBuf, b)
#endif

#if !defined(CIRBUF_DISABLE_ALL_MACRO_FUNCTIONS)
/** Macro version of function that is always available */
#define cbufPutByteNoCheck_MACRO(pBuf, b) {(pBuf)->buf[(pBuf)->put] = (b); /* Write byte to buf */ (pBuf)->put = (((pBuf)->put==(pBuf)->maxOffset) ? 0 : ((pBuf)->put+1));}
#else
#define cbufPutByteNoCheck_MACRO cbufPutByteNoCheck
#endif


/**
 * Function for getting byte pointer to current PUT location. Use this function with
 * cbufGetWrArrSize() function.
 *
 * For <b>Multi Threaded Applications</b>, call from "PUT context".
 *
 * @param pBuf Pointer to CIRBUF structure
 *
 * @return Byte pointer to put buffer.
 */
#define cbufGetWrArr(pBuf)  ( (BYTE*) &((pBuf)->buf[(pBuf)->put]) )


/**
 * Get the bErrorFull flag. Use the cbufClearError() function to clear the error flag.
 *
 * @param pBuf Pointer to CIRBUF structure
 *
 * @return The bErrorFull flag
 */
#define cbufGetError(pBuf)  ((pBuf)->flags.bErrorFull)


/**
 * Clears all error flags.
 *
 * @param pBuf Pointer to CIRBUF structure
 */
#define cbufClearError(pBuf)  ((pBuf)->flags.bErrorFull = 0)


/**
 * Indicates if given buffer is a "Packet Type" buffer.
 * If true, the cbufIsPacketLarge() function can be used to determine if it is a normal or
 * large "Packet Circular Buffer".
 *
 * @param pBuf Pointer to CIRBUF structure
 *
 * @return Returns 1 if this is a Packet buffer.
 */
#define cbufIsPacket(pBuf) (pBuf->flagBits.bPacket==TRUE)


/**
 * Indicates if the given buffer is a "Large Packet Type" buffer. This is the case if the bPacketLarge flag is set.
 * <br>!!! IMPORTANT !!!<br>
 * This function does not check it is is a packet, but only the bPacketLarge flag. This flag is only
 * valid if this buffer is a packet type. First use cbufIsPacket() function to check if this buffer is a
 * packet. To check if this buffer is a packet AND if it is a large packet, use:
 * if (cbufIsPacket() && cbufIsPacketLarge()) { .... }
 *
 * @param pBuf Pointer to CIRBUF structure
 *
 * @return Returns 1 if this is Large Packet buffer (has a 16-bit size field).
 */
#define cbufIsPacketLarge(pBuf) (pBuf->flagBits.bPacketLarge==TRUE)

#endif  //#if defined(CIRBUF_USE_CIRCULAR_BUFFER_STD)
#endif  //#ifndef NZ_CIRCULAR_BUFFER_STD_H
