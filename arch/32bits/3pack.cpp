#define T1_MASK 0xff000000
#define T2_MASK 0x000ff000
#define T3_MASK 0x000000ff
#define TALL_MASK 0xff0ff0ff

#include "matrix.h"

_TPackMatrix::_TPackMatrix(size_t col, size_t rows){
	rows = row;
	columns = col;
	values = (uint32_t*)malloc(rows*columns*sizeof(int8_t)/3);
}

_TPackMatrix::_TPackMatrix(int8_t* val, size_t col, size_t row){
	rows = row;
	columns = col;
	size_t size = rows*columns;
	size_t orig_size = size;
	if(size%3) {
		size /= 3;
		size += 1;
	} else {
		size /= 3;
	}
	values = (uint32_t*)malloc(size*sizeof(int8_t));
	int8_t* val = values;
	for(size_t i = 0; i < size; i++){
		for(size_t j = 0; j < 3; j++){
			if(i*3+j < orig_size){
				uint32_t castable = (uint32_t)orig_size;
				switch(j){
					case 0:
						val[i] = castable<<24;
					case 1:
						val[i] |= castable<<12;
					case 2:
						val[i] |= castable;
				}
			}
		}
		val++;
	}
}

