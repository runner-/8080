CFLAGS=-g -O2 -Wall
all:test8080.hex t_85.hex ex1.hex 8080test isZ80.hex \
	t_inr.hex t_dcr.hex t_ana.hex t_cmp.hex t_jmp.hex

clean:
	rm *.o *.hex

test: 8080test ex1.hex
	@./8080test ex1.hex

8080test:	8080test.o i8080.o
	$(CC) -o $@ $^

i8080.o:	i8080.h

8080test.o:	i8080.o

.SUFFIXES: .hex .p .asm .c .o

.asm.p:
	asl -qL $<

.p.hex:
	p2hex $<

.c.o:
	$(CC) $(CFLAGS) -c $<
