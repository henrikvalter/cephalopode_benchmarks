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
	arbi_T	    x;
	arbi_T	    y;
	arbi_T	    z;
	list_ptr    next;
} list_rec;

static bool benchmark(list_ptr locs, list_ptr my_loc, arbi_T answer);

#ifdef RV
void real_main(void)
#else
void main(void)
#endif
{
    rec_mgr	list_mgr;
    list_ptr	tmp, locs, my_loc;
    arbi_T	answer;

    new_mgr(&list_mgr, sizeof(list_rec));
    Init_arbi();

    #include "MinDistance.h"

#ifdef RV
    global_magic_number = GLOBAL_MAGIC_NUMBER_BEFORE;
    bool answer_correct = benchmark(locs, my_loc, answer);
    global_magic_number = GLOBAL_MAGIC_NUMBER_AFTER;
    if (answer_correct) {
        die(0);
    } else {
        die(1);
    }
#else
    if( benchmark(locs, my_loc, answer) ) {
        exit(0);
    } else {
        exit(-3);
    }
#endif

}


static bool
benchmark(list_ptr locs, list_ptr my_loc, arbi_T answer)
{
    arbi_T  min;
    min = Arbi_FromInt(100);
    while( locs != NULL ) {
	arbi_T diff, sum;
	sum = Arbi_FromInt(0);
	diff = Arbi_sub(locs->x, my_loc->x);
	sum = Arbi_add(sum, Arbi_mlt(diff, diff));
	diff = Arbi_sub(locs->y, my_loc->y);
	sum = Arbi_add(sum, Arbi_mlt(diff, diff));
	diff = Arbi_sub(locs->z, my_loc->z);
	sum = Arbi_add(sum, Arbi_mlt(diff, diff));
	if( Arbi_cmp(sum, min) == arbi_LESS ) { min = sum; }
	locs = locs->next;
    }
    return Arbi_cmp(min, answer) == arbi_EQ;
}

