
#include <inttypes.h>
#include <stddef.h>
#include "riscv.h"

void die(int status);
void real_main(void);

volatile unsigned int global_error_nr = 0xFFFA6607;
volatile unsigned int global_magic_number = GLOBAL_MAGIC_NUMBER_INIT;

__attribute__((section(".text.main")))
int
main(void)
{
    real_main();
    die(0);
}

////////////////////////////////////////////////////////////////////////////////
// valloc
////////////////////////////////////////////////////////////////////////////////

#define VALLOC_HEAP_SIZE (1<<20)
#define VALLOC_UNIT_SIZE (1<<6)

char valloc_heap[VALLOC_HEAP_SIZE] __attribute__ ((aligned (VALLOC_UNIT_SIZE)));
size_t valloc_curr = 0;

void*
valloc(size_t req_size)
{
    size_t size = req_size + (VALLOC_UNIT_SIZE - req_size % VALLOC_UNIT_SIZE);
    size_t units = size / VALLOC_UNIT_SIZE;

    void* ptr = &valloc_heap[valloc_curr * VALLOC_UNIT_SIZE];

    valloc_curr += units;

    if (valloc_curr > (VALLOC_HEAP_SIZE >> 6)) {
        die(0x00FA6607);
    }

    return ptr;
}

void
valloc_free(void*)
{}

////////////////////////////////////////////////////////////////////////////////
// die
////////////////////////////////////////////////////////////////////////////////

__attribute__ ((noreturn))
void
die(int status)
{
    while (1) {
        global_error_nr = status;
    }
}

////////////////////////////////////////////////////////////////////////////////
// my_memcpy
////////////////////////////////////////////////////////////////////////////////

void
my_memcpy(void *dest, void *src, size_t n)
{
    int i;
    char *src_char = (char*)src;
    char *dest_char = (char*)dest;
    for (i = 0; i < n; i++)
        dest_char[i] = src_char[i];
}

////////////////////////////////////////////////////////////////////////////////
// my_memmove
////////////////////////////////////////////////////////////////////////////////

void*
my_memmove(void *dest, void *src, size_t n)
{
    uint8_t* from = (uint8_t*) src;
    uint8_t* to = (uint8_t*) dest;

    if (from == to || n == 0)
        return dest;
    if (to > from && to-from < (int)n) {
        /* to overlaps with from */
        /*  <from......>         */
        /*         <to........>  */
        /* copy in reverse, to avoid overwriting from */
        int i;
        for(i=n-1; i>=0; i--)
            to[i] = from[i];
        return dest;
    }
    if (from > to && from-to < (int)n) {
        /* to overlaps with from */
        /*        <from......>   */
        /*  <to........>         */
        /* copy forwards, to avoid overwriting from */
        size_t i;
        for(i=0; i<n; i++)
            to[i] = from[i];
        return dest;
    }
    my_memcpy(dest, src, n);
    return dest;
}

////////////////////////////////////////////////////////////////////////////////
// my_strlen
////////////////////////////////////////////////////////////////////////////////

size_t
my_strlen(const char *str)
{
    const char *s;
    for (s = str; *s; ++s);
    return (s - str);
}