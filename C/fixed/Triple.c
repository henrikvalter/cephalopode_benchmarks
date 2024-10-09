#include "types.h"
#include "alloc.h"
#include "rec.h"
#include "arb_prec.h"

#ifdef RV
#include "riscv.h"
extern volatile unsigned int global_error_nr;
extern volatile unsigned int global_magic_number;
#endif

static arbi_T  zero;
static arbi_T  one;

static bool benchmark(arbi_T n, arbi_T answer);

#ifdef RV
void real_main(void)
#else
void main(void)
#endif
{
    arbi_T	n, answer;

    Init_arbi();
    zero = Arbi_FromInt(0);
    one = Arbi_FromInt(1);

    #include "Triple.h"

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

arbi_T
triple(arbi_T n)
{
    arbi_T  x;
    if (Arbi_cmp(n, zero) == 0) {
        return Arbi_FromInt(1);
    }
    x = triple(Arbi_sub(n, one));
    return Arbi_add(Arbi_add(x, x),x);
}

static bool
benchmark(arbi_T n, arbi_T answer)
{
    arbi_T res;
    res = triple(n);
    return Arbi_cmp(res, answer) == arbi_EQ;
}

