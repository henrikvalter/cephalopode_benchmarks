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

static rec_mgr	list_mgr;

static bool benchmark(list_ptr list, arbi_T key, arbi_T answer);

#ifdef RV
void real_main(void)
#else
void main(void)
#endif
{
    list_ptr	xs, tmp;
    arbi_T	key;
    arbi_T	answer;

    new_mgr(&list_mgr, sizeof(list_rec));
    Init_arbi();

    xs = NULL;

    #include "Search.h"

#ifdef RV
    global_magic_number = GLOBAL_MAGIC_NUMBER_BEFORE;
    bool answer_correct = benchmark(xs, key, answer);
    global_magic_number = GLOBAL_MAGIC_NUMBER_AFTER;
    if (answer_correct) {
        die(0);
    } else {
        die(1);
    }
#else
    if( benchmark(xs, key, answer) ) {
        exit(0);
    } else {
        exit(1);
    }
#endif
}


static bool
benchmark(list_ptr list, arbi_T key, arbi_T answer)
{
    list_ptr	res = NULL;
    arbi_T  sum;
    while( list != NULL ) {
	if( Arbi_cmp(key, list->v) == arbi_EQ ) {
	    list_ptr tmp = new_rec(&list_mgr);
	    tmp->v = list->v;
	    tmp->next = res;
	    res = tmp;
	}
	list = list->next;
    }
    // Now add up matches
    sum = Arbi_FromInt(0);
    while(res != NULL ) {
	sum = Arbi_add(sum, res->v);
	res = res->next;
    }
    return Arbi_cmp(sum, answer) == arbi_EQ;
}

