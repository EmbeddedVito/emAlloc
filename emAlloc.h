/*
 * emAlloc.h
 *
 *      Author: vitomannone
 *
 * Description:
 * This module allows to use a static allocated buffer to make
 * dynamic allocation of memory. It uses a first fit algorithm.
 * It is possibile to define the functions to use for the locking mechanism in the
 * emAllocPort.h file.
 * In this file it is possibile to configure:
 * 	whether or not to use a user-defined memory buffer and the size of the memory
 * 	buffer to be used.
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
 *
 */

#ifndef EMALLOC_H_
#define EMALLOC_H_

#include <stddef.h>

/*
 * Necessary to define the porting functions
 */
#include "emAllocPort.h"

/*
 * User defines for configuration
 */
#define EM_USE_USER_HEAP 0 // Set 1 if you want to use your own heap memory buffer

#define EM_TOTAL_HEAP_MEM 1024 // Dimension in bytes for the heap memory

typedef size_t Address_t;

/*
 * Return values for the getEmMallocError() function
 */
typedef enum
{
	emNotInizialised = -1,
	emMalloc_OK,
	emMalloc_SizeError,
	emMalloc_NoFreeBlockFound,
	emMalloc_NullPointerInput,
	emMalloc_InvalidPointerInput,
	emMalloc_SemError
} emErrorReturn_t;

/*
 * Definition of the malloc function
 * Input: size --> size in bytes for the block of memory to be allocated
 * Returns: pointer to the block of memory allocated, NULL if it was not possible
 * 		to allocate memory. Check getEmMallocError return value for the error.
 */
void *emMalloc(size_t size);

/*
 * Definition of the free function
 * Input: ptr --> pointer for the block of memory to be freed.
 * Returns: no return values. Check getEmMallocError return value
 * 		for the eventually present error.
 */
void emFree(void *ptr);

/*
 * Definition of the function to get the software module status.
 * The internal error status code is reset to emMalloc_OK only if a call to this function is made.
 */
emErrorReturn_t getEmMallocError(void);

/*
 * This functions returns the total remaining bytes.
 * Note that the remaining bytes can be not aligned. Due to fragmentation,
 * it is not possible to guarantee that this value represent an actual usable
 * memory area.
 */
size_t getRemainingMem(void);

#endif /* EMALLOC_H_ */
