/*
 * Dynamic array!
 *  
 *  How to use:
 * 
 *      obj* array = NULL;
 *      while(o != NULL) {
 *          arrputf(array, o);
 *      }
 * 
 *      for (int i = 0; i < arrlen(array); i++) {
 *          print(array[i]);
 *      }
 * 
 *  References:
 *      - [stb/stretchy_buffer.h](https://github.com/nothings/stb/blob/master/stretchy_buffer.h)
 *      - [stb/stb_ds.h](https://github.com/nothings/stb/blob/master/stb_ds.h)
 *      - [srdja/Collections-C](https://github.com/srdja/Collections-C/blob/master/src/array.c)
 */

#ifndef _SCL_DYARRAY_H_
#define _SCL_DYARRAY_H_

#include <stdlib.h>
#include <string.h>

#define _DYARR_GET_HEADER(arr) ((int*)(arr) - 2)
#define _DYARR_RAW_SIZE(arr) (_DYARR_GET_HEADER(arr)[0])
#define _DYARR_RAW_COUNT(arr) (_DYARR_GET_HEADER(arr)[1])

#define scl_arrfree(arr) _dyarr_free(arr)
#define scl_arrlen(arr) _dyarr_count(arr)
#define scl_arrputf(arr, val)                                               \
	do {                                                                    \
		arr = _dyarr_expand(arr, 1, sizeof(*arr));                          \
		memmove(arr + 1, arr, sizeof(*arr) * (_DYARR_RAW_COUNT(arr) - 1));  \
		arr[0] = val;                                                       \
	} while (0)

#define scl_arrpopf(arr, out)                                               \
	do {                                                                    \
		*out = arr[0];                                                      \
		memmove(arr, arr + 1, sizeof(*arr) * (_DYARR_RAW_COUNT(arr)));      \
		_DYARR_RAW_COUNT(arr) -= 1;                                         \
	} while(0)

#define scl_arrputb(arr, val)                                               \
	do {                                                                    \
		arr = _dyarr_expand(arr, 1, sizeof(*arr));                          \
		arr[arrlen(arr) - 1] = val;                                         \
	} while(0)

#define scl_arrpopb(arr, out)                                               \
	do {                                                                    \
		*out = arr[arrlen(arr) - 1];                                        \
		_DYARR_RAW_COUNT(arr) -= 1;                                         \
	} while(0)

void* _dyarr_expand(void* arr, int count, int itemsz);
void _dyarr_free(void* arr);
int _dyarr_count(void* arr);

#endif // _SCL_DYARRAY_H_