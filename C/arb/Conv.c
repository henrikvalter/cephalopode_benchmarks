#include "types.h"
#include "alloc.h"
#include "rec.h"
#include "arb_prec.h"

#ifdef RV
#include "riscv.h"
extern volatile unsigned int global_error_nr;
extern volatile unsigned int global_magic_number;
#endif

#include "Conv.h"

static bool benchmark(int i);

#ifdef RV
void real_main(void)
#else
void main(void)
#endif
{
    Init_arbi();
    for(int i = 0; i < kdim; i++) {
	kernel[i] = Arbi_FromString(S_kernel[i], 10);
    }
    stride = Arbi_FromString(S_stride, 10);
    bias = Arbi_FromString(S_bias, 10);

    for(int i = 0; i < vdim; i++) {
	vec[i] = Arbi_FromString(S_vec[i], 10);
	answer[i] = Arbi_FromString(S_answer[i], 10);
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
    for(int i = 0; i < vdim; i++) {
	arbi_T sum = zero;
	for(int k = 0; k < kdim; k++) {
	    if( (i+k) < vdim ) {
		sum = Arbi_add(sum, Arbi_mlt(kernel[k], vec[i+k]));
	    } else {
		break;
	    }
	}
	sum = Arbi_add(sum, bias);
	my_res[i] = sum;
    }
    // Now compare the result with the expected result
    for(int i = 0; i < vdim; i++) {
	if( Arbi_cmp(my_res[i], answer[i]) != arbi_EQ ) {
	    return FALSE;
	}
    }
    return TRUE;
}
