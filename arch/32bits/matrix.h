
/**
* This module simulates 8bit SIMD on a 32 bit module. The two classes 
* _DPackMatrix and _TPackMatrix pack two or three 8 bit values into
* one 32 bit value. This has its advantages when performing vector ops
* such as addition or multiplication.
*/

#ifndef FAST_MATH_MATRIX_H
#define FAST_MATH_MATRIX_H

#include <stdlib.h>
#include <stdint.h>

class _TPackMatrix {
private:
	size_t column, rows;
	
public:
    uint32_t* values;
	_TPackMatrix(int8_t* val, size_t col, size_t row);
	_TPackMatrix(size_t values, size_t col, size_t row);
	/*
	void matmul(_TPackMatrix* my_mat1, _TPackMatrix* my_mat2, _TPackMatrix* result);
	void dft(); //Performs in-place DFT
	operator+=(_TPackMatrix *t);
	operator-=(_TPackMatrix *t);
	*/
}
#endif