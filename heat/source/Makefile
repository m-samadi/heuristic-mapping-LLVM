OMP = -fopenmp
CFLAGS = -g
LFLAGS = -lm

# -std=c99
TDG = -fopenmp-taskgraph -static-tdg -L${OMP_PATH}

BIN= heat

all: $(BIN)

misc.o: misc.c
	clang -fdebug-default-version=3 -c $(CFLAGS) $< -o $@

heat: heat.c misc.o
	clang -fdebug-default-version=3 -DTDG -DOMP_TASK_DEPENDS $(CFLAGS) $(OMP) $(TDG) -DNB=8 $+ $(LFLAGS) -o heat

heat_static: heat.o tdg.cpp misc.o
	clang -fdebug-default-version=3 $(CFLAGS) $(OMP) $+ $(LFLAGS)  -L${OMP_PATH} -o heat

clean:
	rm -rf heat heat.o heat.pcf heat.prv heat.row heat.ppm misc.o
