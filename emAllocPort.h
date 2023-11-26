/*
 * emAllocPort.h
 *
 *      Author: vitomannone
 *
 * Porting header file for the emAlloc software module. This header file must be used
 * to define the functions that implements all the system calls to manage cuncurrency
 * access to the emAlloc memory buffer.
 * Only binary sempahore are used.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef EMALLOCPORT_H_
#define EMALLOCPORT_H_

/*
 * Use this define to enable/disable the use of locking mechanisms
 */
#define ALLOC_USE_LOCK_MECHANISM 1

//check if the compiler is GCC then find the byte alignment
//if the compiler is not GCC the user must defines the Byte Alignment
#if defined(__GNUC__)
#define BYTE_ALIGNMENT __BIGGEST_ALIGNMENT__
#else
//#define BYTE_ALIGNMENT
#ifndef BYTE_ALIGNMENT
#error "You have to define the number of bytes necessary for the alignment if the compiler is not GCC"
#endif /* BYTE_ALIGNMENT */
#endif /* defined(__GNUC__) */

/*
 * Necessary definition for lock/unlock functions
 * It is necessary to define these functions:
 * 		emAllocPort_EnterCritical(ptrSem) [semaphore acquisition]
 * 			input values: ptrSem --> pointer to the semaphore to be used
 * 			must returns: 0 if there is no errors on the semaphore
 *		emAllocPort_ExitCritical(ptrSem) [semaphore release]
 * 			input values: ptrSem --> pointer to the semaphore to be used
 * 			must returns: is not evaluated
 *		emAllocPort_InitBynSem(strName) [semaphore creation, only binary semaphore]
 * 			input values: strName --> string to be used as the semaphore name
 * 			must returns: pointer to the created semaphore
 *		emAllocPort_BynSemDelete(ptrSem) [semaphore deletion. This function is not currently used, here for future use]
 * 			input values: ptrSem --> pointer to the semaphore to be used
 * 			must returns: not evaluated
 *
 * Note: here is used the library "cmsis_os2.h" to handle the system-calls as example
 */
#if ALLOC_USE_LOCK_MECHANISM
#include "cmsis_os2.h"
#define emAllocPort_EnterCritical(ptrSem)			( osSemaphoreAcquire(ptrSem, osWaitForever) )
#define emAllocPort_ExitCritical(ptrSem)			( osSemaphoreRelease(ptrSem) )
#define emAllocPort_InitBynSem(strName)				( osSemaphoreNew(1, 1, NULL) )
#define emAllocPort_BynSemDelete(ptrSem)			( osSemaphoreDelete(ptrSem) )
typedef osSemaphoreId_t emAllocSem_t;
#else
#define emAllocPort_EnterCritical(ptrSem)			( 0 )
#define emAllocPort_ExitCritical(ptrSem)			(void)ptrSem
#define emAllocPort_InitBynSem(strName)				( NULL )
#define emAllocPort_BynSemDelete(ptrSem)			(void)ptrSem
typedef void * emAllocSem_t;
#endif /* USE_LOCK_MECHANISM */


#endif /* EMALLOCPORT_H_ */
