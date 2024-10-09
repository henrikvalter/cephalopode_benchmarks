
CC_L=gcc
FL=fl

all: Derivative Conv Dot Factorial MinDistance NeuralNetwork Triple Identity Search Sort MatrixMult MatrixAddConst MatrixMulConst

headers: Derivative.h Sort.h Search.h MatrixMult.h MatrixAddConst.h MatrixMulConst.h Conv.h Dot.h Factorial.h MinDistance.h NeuralNetwork.h Triple.h Identity.h

Derivative: Derivative.h arb_prec.c arb_prec.h Derivative.c
	${CC_L} -o Derivative Derivative.c alloc.c rec.c arb_prec.c

Derivative.h:
	${FL} -noX -f Derivative.fl

Search: Search.h arb_prec.c arb_prec.h Search.c
	${CC_L} -o Search Search.c alloc.c rec.c arb_prec.c

Search.h:
	${FL} -noX -f Search.fl

MatrixMult: MatrixMult.h arb_prec.c arb_prec.h MatrixMult.c
	${CC_L} -o MatrixMult MatrixMult.c alloc.c rec.c arb_prec.c

MatrixMult.h:
	${FL} -noX -f MatrixMult.fl

MatrixAddConst: MatrixAddConst.h arb_prec.c arb_prec.h MatrixAddConst.c
	${CC_L} -o MatrixAddConst MatrixAddConst.c alloc.c rec.c arb_prec.c

MatrixAddConst.h:
	${FL} -noX -f MatrixAddConst.fl

MatrixMulConst: MatrixMulConst.h arb_prec.c arb_prec.h MatrixMulConst.c
	${CC_L} -o MatrixMulConst MatrixMulConst.c alloc.c rec.c arb_prec.c

MatrixMulConst.h:
	${FL} -noX -f MatrixMulConst.fl

Sort: Sort.h arb_prec.c arb_prec.h Sort.c
	${CC_L} -o Sort Sort.c alloc.c rec.c arb_prec.c

Sort.h:
	${FL} -noX -f Sort.fl

Dot: Dot.h arb_prec.c arb_prec.h Dot.c
	${CC_L} -o Dot Dot.c alloc.c rec.c arb_prec.c

Dot.h:
	${FL} -noX -f Dot.fl

Conv: Conv.h arb_prec.c arb_prec.h Conv.c
	${CC_L} -o Conv Conv.c alloc.c rec.c arb_prec.c

Conv.h:
	${FL} -noX -f Conv.fl

Factorial: Factorial.h arb_prec.c arb_prec.h Factorial.c
	${CC_L} -o Factorial Factorial.c alloc.c rec.c arb_prec.c

Factorial.h:
	${FL} -noX -f Factorial.fl

MinDistance: MinDistance.h arb_prec.c arb_prec.h MinDistance.c
	${CC_L} -o MinDistance MinDistance.c alloc.c rec.c arb_prec.c

MinDistance.h:
	${FL} -noX -f MinDistance.fl

NeuralNetwork: NeuralNetwork.h arb_prec.c arb_prec.h NeuralNetwork.c
	${CC_L} -g -o NeuralNetwork NeuralNetwork.c alloc.c rec.c arb_prec.c

NeuralNetwork.h:
	${FL} -noX -f NeuralNetwork.fl

Triple: Triple.h arb_prec.c arb_prec.h Triple.c
	${CC_L} -g -o Triple Triple.c alloc.c rec.c arb_prec.c

Triple.h:
	${FL} -noX -f Triple.fl

Identity:
	${CC_L} -g -o Identity Identity.c alloc.c rec.c arb_prec.c

Identity.h:
	${FL} -noX -f Identity.fl

################################################################################
# RISC-V options
CC=riscv64-unknown-elf-gcc
LD=riscv64-unknown-elf-ld
SREC_CAT=srec_cat
OBJCOPY=riscv64-unknown-elf-objcopy
OPTLEVEL=-O1
CFLAGS=${OPTLEVEL} -ffreestanding -mabi=ilp32 -march=rv32im -ffunction-sections
LDFLAGS=-Tlink.ld -melf32lriscv
################################################################################

%_rv.o: %.c %.h
	${CC} ${CFLAGS} -DRV -c $< -o $@

%_rv.elf: %_rv.o alloc_rv.o arb_prec_rv.o riscv_rv.o rec_rv.o
	${LD} ${LDFLAGS} $< alloc_rv.o arb_prec_rv.o riscv_rv.o rec_rv.o -o $@

%_rv.text.bin: %_rv.elf
	${OBJCOPY} -O binary $< $@ -j .init -j .text --change-addresses -0x400000

%_rv.text.vh: %_rv.text.bin
	${SREC_CAT} $< -binary -byte-swap 4 -O $@ -VMem 32
	sed -i "1i /* $@ */" $@

%_rv.data.bin: %_rv.elf
	${OBJCOPY} -O binary $< $@ -j .data -j .eh_frame -j .fini_array -j .init_array --change-addresses -0x80000000

%_rv.data.vh: %_rv.data.bin
	${SREC_CAT} $< -binary -byte-swap 4 -O $@ -VMem 32
	sed -i "1i /* $@ */" $@

clean:
	-@/bin/rm -f *.o Derivative Conv Dot Factorial MinDistance  NeuralNetwork Triple Identity Search Sort MatrixMult MatrixAddConst MatrixMulConst
	-@/bin/rm -f Derivative.h
	-@/bin/rm -f Search.h
	-@/bin/rm -f MatrixMult.h
	-@/bin/rm -f MatrixAddConst.h
	-@/bin/rm -f MatrixMulConst.h
	-@/bin/rm -f Sort.h
	-@/bin/rm -f Conv.h
	-@/bin/rm -f Dot.h
	-@/bin/rm -f Factorial.h
	-@/bin/rm -f MinDistance.h
	-@/bin/rm -f NeuralNetwork.h
	-@/bin/rm -f Triple.h
	-@/bin/rm -f *_rv.o
	-@/bin/rm -f *_rv.elf
	-@/bin/rm -f *_rv.text.bin
	-@/bin/rm -f *_rv.text.vh
	-@/bin/rm -f *_rv.data.bin
	-@/bin/rm -f *_rv.data.vh
	-@/bin/rm -f testfile.text.vh
	-@/bin/rm -f testfile.data.vh

