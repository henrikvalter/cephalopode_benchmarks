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
	union {
	    arbi_T	    v;
	    list_ptr	    p;
	      }	    u;
	list_ptr    next;
} list_rec;

static rec_mgr	list_mgr;

static bool benchmark(list_ptr M, list_ptr vec, arbi_T answer);

#ifdef RV
void real_main(void)
#else
void main(void)
#endif
{
    list_ptr	tmp, M, matrix, row, col, vec;
    arbi_T	answer;

    new_mgr(&list_mgr, sizeof(list_rec));
    Init_arbi();

#include "NeuralNetwork.h"

    // Time only this functiopn
#ifdef RV
    global_magic_number = GLOBAL_MAGIC_NUMBER_BEFORE;
    bool answer_correct = benchmark(M, vec, answer);
    global_magic_number = GLOBAL_MAGIC_NUMBER_AFTER;
    if (answer_correct) {
        die(0);
    } else {
        die(1);
    }
#else
    if( benchmark(M, vec, answer) ) {
        exit(0);
    } else {
        exit(-3);
    }
#endif
}


static bool
benchmark(list_ptr M, list_ptr vec, arbi_T answer)
{
    list_ptr	tmp;
    arbi_T zero = Arbi_FromInt(0);
    while( M != NULL ) {
	list_ptr m = M->u.p;
	list_ptr vn = NULL;
	list_ptr tail = vn;
	while(m != NULL) {
	    list_ptr r = m->u.p;
	    list_ptr cv = vec;
	    arbi_T  sum = Arbi_FromInt(0);
	    while( r != NULL ) {
		sum = Arbi_add(sum, Arbi_mlt(r->u.v, cv->u.v));
		r = r->next;
		cv = cv->next;
	    }
	    tmp = new_rec(&list_mgr);
	    if( Arbi_cmp(sum, zero) < 0 ) {
		sum = zero;
	    }
	    tmp->u.v = sum;
	    tmp->next = NULL;
	    if( tail == NULL ) {
		vn = tmp;
		tail = vn;
	    } else {
		tail->next = tmp;
		tail = tmp;
	    }
	    m = m->next;
	}
	tmp = vec;
	vec = vn;
	while( tmp != NULL ) {
	    list_ptr old;
	    old = tmp;
	    tmp = tmp->next;
	    free_rec(&list_mgr, old);
	}
	M = M->next;
    }
    return Arbi_cmp(vec->u.v, answer) == arbi_EQ;
}

