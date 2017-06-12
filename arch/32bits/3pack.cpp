#include "matrix.h"

_TPackMatrix::_TPackMatrix(int8_t* vali, size_t col, size_t row) {
	rows = row;
	column = col;
	size_t size = rows*column;
	size_t orig_size = size;
	if (size % 3) {
		size /= 3;
		size += 1;
	}
	else {
		size /= 3;
	}
	values = (uint32_t*)malloc(size * sizeof(uint32_t));
	memset(values, 0, size * sizeof(uint32_t));
	length = size;
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < 3; j++) {
			if (i * 3 + j < orig_size) {
				uint32_t castable = (uint32_t)vali[i*3+j];
				switch (j) {
				case 0:
					values[i] = castable;
					break;
				case 1:
					values[i] |= castable << 12;
					break;
				case 2:
					values[i] |= castable << 23;
					break;
				}
			}
		}
	}
}

_TPackMatrix::_TPackMatrix(size_t col, size_t row){
	rows = row;
	column = col;
	size_t size = rows*column;
	size_t orig_size = size;
	if (size % 3) {
		size /= 3;
		size += 1;
	}
	else {
		size /= 3;
	}
	values = (uint32_t*)malloc(size * sizeof(uint32_t));
	memset(values, 0, size * sizeof(uint32_t));
	length = size;
}

void _TPackMatrix::add(_TPackMatrix * other, _TPackMatrix * result){
	for (size_t i = 0; i < length; i++) {
		result->values[i] = other->values[i]+values[i];
		result->values[i] &= TALL_MASK;
	}
}

void _TPackMatrix::sub(_TPackMatrix * other, _TPackMatrix * result){
	for (size_t i = 0; i < length; i++) {
		result->values[i] = values[i]-other->values[i];
		result->values[i] &= TALL_MASK;
	}
}
uint8_t _TPackMatrix::get(size_t x, size_t y)
{
	size_t offset = x*column+y;
	int j = offset % 3;
	switch (j) {
	case 0:
		return (uint8_t)(values[offset / 3] & T1_MASK);
	case 1:
		return (uint8_t)((values[offset / 3] & T2_MASK) >> 12);
	case 2:
		return (uint8_t)((values[offset / 3] & T3_MASK) >> 23);
	}
	return 0;
}
#ifdef debug_tmatrix
void _TPackMatrix::debug_out() {
	for (size_t l = 0; l < length; l++) {
		printf("0x%x:\n", values[l]);
		printf("%d,", values[l] & T1_MASK );
		printf("%d,", (values[l] & T2_MASK) >> 12);
		printf("%d\n",(values[l] & T3_MASK) >> 23);
	}
}
