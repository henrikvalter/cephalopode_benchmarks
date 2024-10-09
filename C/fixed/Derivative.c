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

static bool benchmark(list_ptr list, arbi_T answer);

#ifdef RV
void real_main(void)
#else
void main(void)
#endif
{
    rec_mgr	list_mgr;
    list_ptr	xs, tmp;
    arbi_T	answer;

    new_mgr(&list_mgr, sizeof(list_rec));
    Init_arbi();

    xs = NULL;

    #include "Derivative.h"

#ifdef RV
    global_magic_number = GLOBAL_MAGIC_NUMBER_BEFORE;
    bool answer_correct = benchmark(xs, answer);
    global_magic_number = GLOBAL_MAGIC_NUMBER_AFTER;
    if (answer_correct) {
        die(0);
    } else {
        die(1);
    }
#else
    if( benchmark(xs, answer) ) {
        exit(0);
    } else {
        exit(1);
    }
#endif
}


static bool
benchmark(list_ptr list, arbi_T answer)
{
    arbi_T  sum;
    sum = Arbi_FromInt(0);
    while( list != NULL ) {
	if( list->next != NULL ) {
	    sum = Arbi_add(sum, Arbi_sub(list->next->v, list->v));
	}
	list = list->next;
    }
    return Arbi_cmp(sum, answer) == arbi_EQ;
}

