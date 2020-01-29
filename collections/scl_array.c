#include "scl_array.h"

void* _dyarr_expand(void* arr, int count, int itemsz) {
    int head_sz = sizeof(int) * 2;
    int data_sz = count * itemsz;

    if (arr == NULL) {
        int* p = malloc(head_sz + data_sz);
        p[0] = count;
        p[1] = count;
        return p + 2;
    }
	else if (_DYARR_RAW_SIZE(arr) <= _DYARR_RAW_COUNT(arr) + count) {
		int expand_sz = _DYARR_RAW_SIZE(arr) * 2;
		int needed_sz = _DYARR_RAW_COUNT(arr) + count;
		int capacity = expand_sz > needed_sz + count ? expand_sz : needed_sz;
		int new_sz = head_sz + itemsz * capacity;
		int* p = realloc(_DYARR_GET_HEADER(arr), new_sz);
		p[0] = capacity;
		p[1] = needed_sz;
		return p + 2;
	}

	_DYARR_RAW_COUNT(arr) += count;

    return arr;
}

void _dyarr_free(void* arr) {
    if (arr != NULL) {
        free(_DYARR_GET_HEADER(arr));
    }
}

int _dyarr_count(void* arr) {
    return arr == NULL ? 0 :_DYARR_RAW_COUNT(arr);
}
