
#ifndef _RISCV_H_
#define _RISCV_H_

#include <inttypes.h>
#include <stddef.h>

#define GLOBAL_MAGIC_NUMBER_INIT   0xF1F2F3F4
#define GLOBAL_MAGIC_NUMBER_BEFORE 0x1F2F3F4F
#define GLOBAL_MAGIC_NUMBER_AFTER  0xF4F3F2F1

__attribute__((section(".text.main")))
int
main(void);

////////////////////////////////////////////////////////////////////////////////
// valloc
////////////////////////////////////////////////////////////////////////////////

void*
valloc(size_t req_size);

void
valloc_free(void*);

////////////////////////////////////////////////////////////////////////////////
// die
////////////////////////////////////////////////////////////////////////////////

__attribute__ ((noreturn))
void
die(int status);

////////////////////////////////////////////////////////////////////////////////
// my_memcpy
////////////////////////////////////////////////////////////////////////////////

void
my_memcpy(void *dest, void *src, size_t n);

////////////////////////////////////////////////////////////////////////////////
// my_memmove
////////////////////////////////////////////////////////////////////////////////

void*
my_memmove(void *dest, void *src, size_t n);

////////////////////////////////////////////////////////////////////////////////
// my_strlen
////////////////////////////////////////////////////////////////////////////////

size_t
my_strlen(const char *str);

#endif // _RISCV_H_