PROGS = pid_ns.out uts_ns.out ipc_ns.out 

all: $(PROGS)

%.out: %.c
	gcc -O2 -o $*.out $*.c 

clean:
	rm *.out