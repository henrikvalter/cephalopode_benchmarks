//-------------------------------------------------------------------
// Copyright 2020 Carl-Johan Seger
// SPDX-License-Identifier: Apache-2.0
//-------------------------------------------------------------------

#include "alloc.h"

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

/************************************************************************/
/*                      Public Functions                                */
/************************************************************************/

pointer
Malloc(unsigned long int size)
{
    pointer ret;
    if( (ret = (pointer) _MALLOC(size)) == (pointer)NULL ) {
        _EXIT(-1);
    }
    return ret;
}

void
Free(pointer p)
{
    _FREE(p);
}
