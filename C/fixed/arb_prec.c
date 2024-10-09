#include "arb_prec.h"
#ifdef RV
    #include "riscv.h"
    #define _MALLOC valloc
    #define _FREE valloc_free
    #define _EXIT die
    #define _MEMMOVE my_memmove
    #define _MEMCPY my_memcpy
    #define _STRLEN my_strlen
#else
    #define _MALLOC malloc
    #define _FREE free
    #define _EXIT exit
    #define _MEMMOVE memmove
    #define _MEMCPY memcpy
    #define _STRLEN strlen
#endif

void
Init_arbi()
{
}

arbi_T
Arbi_FromString(char *s, int base)
{
    int	res;
    bool neg = FALSE;
    if( *s == '-' ) {
	s++;
	neg = TRUE;
    }
    res = 0;
    while( *s ) {
	res = (*s - '0')+base*res;
	s++;
    }
    if( neg ) {
	return ((arbi_T) (-1*res));
    } else {
	return ((arbi_T) res);
    }
}

arbi_T
Arbi_FromInt(int i)
{
    return( (arbi_T) i);
}

