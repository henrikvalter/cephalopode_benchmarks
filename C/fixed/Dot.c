#include "types.h"
#include "alloc.h"
#include "rec.h"
#include "arb_prec.h"

#ifdef RV
#include "riscv.h"
extern volatile unsigned int global_error_nr;
extern volatile unsigned int global_magic_number;
#endif

typedef struct list_rec	*list_ptr;
typedef struct list_rec	{
	arbi_T	    v;
	list_ptr    next;
} list_rec;

static bool benchmark(list_ptr l1, list_ptr l2, arbi_T answer);

#ifdef RV
void real_main(void)
#else
void main(void)
#endif
{
    rec_mgr	list_mgr;
    list_ptr	tmp, xs, ys;
    arbi_T	answer;

    new_mgr(&list_mgr, sizeof(list_rec));
    Init_arbi();

    xs = NULL;
    ys = NULL;

    #include "Dot.h"

#ifdef RV
    global_magic_number = GLOBAL_MAGIC_NUMBER_BEFORE;
    bool answer_correct = benchmark(xs, ys, answer);
    global_magic_number = GLOBAL_MAGIC_NUMBER_AFTER;
    if (answer_correct) {
        die(0);
    } else {
        die(1);
    }
#else
    if( benchmark(xs, ys, answer) ) {
        exit(0);
    } else {
        exit(1);
    }
#endif
}

static bool
benchmark(list_ptr l1, list_ptr l2, arbi_T answer)
{
    arbi_T  sum;
    sum = Arbi_FromInt(0);
    while( l1 != NULL && l2 != NULL ) {
        sum = Arbi_add(sum, Arbi_mlt(l1->v, l2->v));
        l1 = l1->next;
        l2 = l2->next;
    }
    return Arbi_cmp(sum, answer) == arbi_EQ;
}

