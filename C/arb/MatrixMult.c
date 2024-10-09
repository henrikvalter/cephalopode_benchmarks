#include "types.h"
#include "alloc.h"
#include "rec.h"
#include "arb_prec.h"

#ifdef RV
#include "riscv.h"
extern volatile unsigned int global_error_nr;
extern volatile unsigned int global_magic_number;
#endif

#include "MatrixMult.h"

;

static bool benchmark(int i);

#ifdef RV
void real_main(void)
#else
void main(void)
#endif
{
    Init_arbi();
    for(int i = 0; i < dim1; i++) {
	for(int j = 0; j < dim2; j++) {
	    M1[i][j] = Arbi_FromString(S_M1[i][j], 10);
	    M2[i][j] = Arbi_FromString(S_M2[i][j], 10);
	    answer[i][j] = Arbi_FromString(S_answer[i][j], 10);
	}
    }

    // Time only this functiopn
#ifdef RV
    global_magic_number = GLOBAL_MAGIC_NUMBER_BEFORE;
    bool answer_correct = benchmark(1);
    global_magic_number = GLOBAL_MAGIC_NUMBER_AFTER;
    if (answer_correct) {
        die(0);
    } else {
        die(1);
    }
#else
    if( benchmark(1) ) {
        exit(0);
    } else {
        exit(-3);
    }
#endif
}


static bool
benchmark(int dummy)
{
    arbi_T zero = Arbi_FromInt(0);
    for(int i = 0; i < dim1; i++) {
	for(int j = 0; j < dim2; j++) {
	    my_result[i][j] = zero;
	    for(int k = 0; k < dim1; k++) {
		my_result[i][j] = Arbi_add(my_result[i][j], Arbi_mlt(M1[i][k], M2[k][j]));
	    }
	}
    }
    // Now compare the result with the expected result
    for(int i = 0; i < dim1; i++) {
	for(int j = 0; j < dim2; j++) {
	    if( Arbi_cmp(my_result[i][j], answer[i][j]) != arbi_EQ ) {
		return FALSE;
	    }
	}
    }
    return TRUE;
}

