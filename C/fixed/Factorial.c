#include "types.h"
#include "alloc.h"
#include "rec.h"
#include "arb_prec.h"

#ifdef RV
#include "riscv.h"
extern volatile unsigned int global_error_nr;
extern volatile unsigned int global_magic_number;
#endif

static bool benchmark(arbi_T n, arbi_T answer);

#ifdef RV
void real_main(void)
#else
void main(void)
#endif
{
    arbi_T	n, answer;

    Init_arbi();

#include "Factorial.h"

#ifdef RV
    global_magic_number = GLOBAL_MAGIC_NUMBER_BEFORE;
    bool answer_correct = benchmark(n, answer);
    global_magic_number = GLOBAL_MAGIC_NUMBER_AFTER;
    if (answer_correct) {
        die(0);
    } else {
        die(1);
    }
#else
    if( benchmark(n, answer) ) {
        exit(0);
    } else {
        exit(1);
    }
#endif
}


static bool
benchmark(arbi_T n, arbi_T answer)
{
    arbi_T  res, one;
    one = Arbi_FromInt(1);
    res = one;
    while( Arbi_cmp(n, one) != 0 ) {
        res = Arbi_mlt(n, res);
        n = Arbi_sub(n, one);
    }
    return Arbi_cmp(res, answer) == arbi_EQ;
}

