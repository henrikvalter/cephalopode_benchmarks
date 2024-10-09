#include "types.h"
#include "alloc.h"
#include "rec.h"
#include "arb_prec.h"

#include <stdint.h>
// typedef unsigned int uint32_t;


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

static bool benchmark(list_ptr list, arbi_T answer);

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

    #include "Sort.h"

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


list_ptr
list_mergesort(list_ptr list)
{
    list_ptr left, right, add, ret;

    uint32_t insize, nmerges, lsize, rsize, i;
    insize = 1;



    while(1){
        left = list;
        list = NULL;
        ret = NULL;
        nmerges = 0;

        while(left){
            nmerges ++;
            right = left; 
            lsize = 0;
            rsize = 0;
            // left and right sublist
            for(i = 0; i < insize; i++){
                lsize++;
                right = right->next;
                if(!right) { 
                    break; 
                }
            }
            rsize = insize;

            while(lsize > 0 || (rsize > 0 && right)) {
                if(lsize == 0) {
                    add = right;
                    right = right -> next;
                    rsize --;
                }
                else if(rsize == 0 || !right) {
                    add = left;
                    left = left -> next;
                    lsize --;
                }
                else if( Arbi_cmp(right->v, left->v) == arbi_LESS ) {
                    add = right;
                    right = right->next;
                    rsize --;
                }
                else{ // right >= left
                    add = left;
                    left = left->next;
                    lsize --;
                }

                if(ret){
                    ret->next = add;
                }
                else{
                    list = add;
                }
                ret = add;
            }
            left = right;
        }
        ret->next = NULL;

        if(nmerges <= 1){
            return list;
        }
        insize *= 2;
    }
}


static bool
benchmark(list_ptr list, arbi_T answer)
{
    arbi_T first, last;

    list = list_mergesort(list);
    first = list->v;
    while( list != NULL ) {
	if( list->next == NULL ) {
	    last = list->v;
	    break;
	}
	list = list->next;
    }
    arbi_T  diff = Arbi_sub(last, first);
    return Arbi_cmp(diff, answer) == arbi_EQ;
}

