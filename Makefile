EXE=transpose_blocking.x
CPPFLAGS=-g -pg -fsanitize=address -fsanitize=leak -fsanitize=undefined

all: $(EXE)

%.x : %.cpp
	g++ $(CPPFLAGS) $< -o $@

test1: $(EXE) 
	./$< 512 32

graph: plot.gp total_report.txt
	gnuplot $<

report: report512.txt
	make clean

report512.txt: $(EXE) gmon.out
	gprof ./$< gmon.out > $@

gmon.out: $(EXE)
	./$< 512 512

clean:
	rm -rf a.out *.x *.x.dSYM *.out *~
