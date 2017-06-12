
/**
* This module simulates 8bit SIMD on a 32 bit module. The two classes 
* _DPackMatrix and _TPackMatrix pack two or three 8 bit values into
* one 32 bit value. This has its advantages when performing vector ops
* such as addition or multiplication.
*/

#ifndef FAST_MATH_MATRIX_H
#define FAST_MATH_MATRIX_H

#include <stdint.h>
#include <stdlib.h>

#define debug_tmatrix // comment out in release mode
#ifdef debug_tmatrix
	#include <stdio.h>
#endif
#define T3_MASK 0x7fc00000
#define T2_MASK 0x000ff000
#define T1_MASK 0x000000ff
#define TALL_MASK 0x7fcff0ff

class _TPackMatrix {
private:
	size_t column, rows, length;

public:
	uint32_t* values;
	_TPackMatrix(int8_t *val, size_t col, size_t row);
	_TPackMatrix(size_t col, size_t row);
	void add(_TPackMatrix *other, _TPackMatrix *result);
	void sub(_TPackMatrix *other, _TPackMatrix *result);
	uint8_t get(size_t x, size_t y);
#ifdef debug_tmatrix
	void debug_out();
#endif
};

#endif